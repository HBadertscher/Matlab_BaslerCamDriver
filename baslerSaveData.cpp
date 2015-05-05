// baslerSaveData.cpp - Capture and save a number of frames from a Basler camera
// see baslerSaveData.m for help

#include <pylon/PylonIncludes.h>
#include "basler_helper/basler_set_get.h"
#include "basler_helper/capture_images.h"

#include <boost/filesystem.hpp>
#include <boost/format.hpp>

#include <matrix.h>
#include <mex.h>

    
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{       
    const std::string s_filename = "frame_%04d.tif";
    
    // Parse parameters
    if(nrhs < 1)
    {
        mexErrMsgIdAndTxt( "baslerDriver:Error:ArgumentError",
                "Not enough arguments. Use help baslerGetParameter for further information."); 
    }
    else if(nrhs > 5)
    {
        mexErrMsgIdAndTxt( "baslerDriver:Error:ArgumentError",
                "Too many arguments. Use help baslerGetParameter for further information."); 
    }
    
    // Get camera number
    const int i_cam_number = (int)mxGetScalar(prhs[0]);
    
    // Get verbose parameter
    bool b_verbose = 0;
    if(nrhs == 5)
    {
        b_verbose = (int)mxGetScalar(prhs[3]) != 0;
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

    
    // Initiatlize Pylon
    Pylon::PylonAutoInitTerm auto_init_term;
    
    try
    {
        // Get the transport layer factory.
        Pylon::CTlFactory& tlFactory = Pylon::CTlFactory::GetInstance();
        
        // Get all attached devices
        Pylon::DeviceInfoList_t devices;
        int i_num_of_cameras = tlFactory.EnumerateDevices(devices);
        if ( i_num_of_cameras == 0 )
        {
            throw RUNTIME_EXCEPTION( "No camera found.");
        }
        
        // Check if camera exists
        if (i_cam_number > i_num_of_cameras-1 )
        {
            throw RUNTIME_EXCEPTION("No camera with this index exists.");
        }
        
        // Create camera object
        Pylon::CInstantCamera camera(tlFactory.CreateDevice(devices[i_cam_number]));
        
        // Open Camera
        camera.Open();
        if(b_verbose)
        {
            mexPrintf("Using camera \"%s\"\n", camera.GetDeviceInfo().GetModelName().c_str());
        }
           
        // Find pixel type if needed
        if(ept_output_type == Pylon::PixelType_Undefined)
        {
            std::string s_pixel_type = BaslerHelper::get_string(&camera,"PixelFormat",b_verbose);
            ept_output_type = Pylon::CPixelTypeMapper().GetPylonPixelTypeByName(s_pixel_type.c_str());
        }
        
        // Capture and save images                                
        BaslerHelper::save_images(&camera, bfp_save_path, i_num_of_frames, ept_output_type, b_verbose);
       
        // Close camera
        camera.Close();
        
    }
    catch (GenICam::GenericException &e)
    {
        // Error handling.
        mexErrMsgIdAndTxt("baslerDriver:Error:CameraError",e.GetDescription());
    }
    
    return;
}

