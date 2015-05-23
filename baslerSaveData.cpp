// baslerSaveData.cpp - Capture and save a number of frames from a Basler camera
// see baslerSaveData.m for help

#include <pylon/PylonIncludes.h>
#include "basler_helper/basler_set_get.h"
#include "basler_helper/capture_images.h"

#include <boost/filesystem.hpp>
#include <boost/format.hpp>

#include <matrix.h>
#include <mex.h>
#include <thread>
    
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{       
    const std::string s_filename = "frame_%04d.tif";
    
    // Parse parameters
    if(nrhs < 1)
    {
        mexErrMsgIdAndTxt( "baslerDriver:Error:ArgumentError",
                "Not enough arguments. Use help baslerGetParameter for further information."); 
    }
    else if(nrhs > 6)
    {
        mexErrMsgIdAndTxt( "baslerDriver:Error:ArgumentError",
                "Too many arguments. Use help baslerGetParameter for further information."); 
    }
    
    // Get camera number
    const int i_cam_number = (int)mxGetScalar(prhs[0]);
    
    // Get verbose parameter
    bool b_verbose = 0;
    if(nrhs == 6)
    {
        b_verbose = (int)mxGetScalar(prhs[5]) != 0;
    }
    
    // Get save path
    std::string s_save_path = mxArrayToString(prhs[1]);
    boost::filesystem::path bfp_save_path;
    if(b_verbose)
    {
        mexPrintf("Saving to \"%s\"\n",mxArrayToString(prhs[1]));
    }
    try
    {
        bfp_save_path = s_save_path;
        boost::filesystem::create_directory(bfp_save_path);
        bfp_save_path /= s_filename;
    }
    catch(boost::filesystem::filesystem_error &e)
    {
        mexErrMsgIdAndTxt("baslerDriver:Error:FileError", e.what() );
    }
    
    // Get number of frames
    int i_num_of_frames = 1;
    if(nrhs >= 3)
    {
        if(mxGetNumberOfElements(prhs[2]) >= 1)
        {
            i_num_of_frames = (int)mxGetScalar(prhs[2]);
        }
    }
    if(b_verbose)
    {
        mexPrintf("Capturing %d frame(s) \n",i_num_of_frames);
    }
    
    // Get output type
    Pylon::EPixelType ept_output_type = Pylon::PixelType_Undefined;
    if(nrhs >= 4)
    {
        if(!(mxGetM(prhs[3]) == 0 && mxGetN(prhs[3]) == 0))
        {
            ept_output_type = Pylon::CPixelTypeMapper().GetPylonPixelTypeByName(mxArrayToString(prhs[3]));
            if(b_verbose)
            {
                mexPrintf("Using output data type \"%s\"\n",mxArrayToString(prhs[3]));
            }
        }
    }
    
    // Get detach option
    bool b_detach = 0;
    if(nrhs >= 5)
    {
        b_detach = (int)mxGetScalar(prhs[4]) != 0;
    }
    
    try
    {
        // Capture and save images in separate thread
        std::thread processThread(  &BaslerHelper::save_images,
                                    i_cam_number,
                                    bfp_save_path,
                                    i_num_of_frames,
                                    ept_output_type,
                                    b_verbose
                                );
        
        // Detach thread if required - otherwise wait for it
        if(b_detach)
        {
            if(b_verbose)
                mexPrintf("Detaching camera thread\n");
            processThread.detach();
        }
        else
        {
            if(b_verbose)
                mexPrintf("Waiting for camera thread\n");
            processThread.join();
        }
        
    }
    catch (GenICam::GenericException &e)
    {
        // Error handling.
        mexErrMsgIdAndTxt("baslerDriver:Error:CameraError",e.GetDescription());
    }
    
    return;
}

