// baslerGetData.cpp - Capture any number of frames from a Basler camera
// see baslerGetData.m for help

#include <pylon/PylonIncludes.h>
#include "basler_helper/basler_set_get.h"
#include "basler_helper/capture_images.h"

#include <matrix.h>
#include <mex.h>

    
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{       
    // Parse parameters
    if(nrhs < 1)
    {
        mexErrMsgIdAndTxt( "baslerDriver:Error:ArgumentError",
                "Not enough arguments. Use help baslerGetParameter for further information."); 
    }
    else if(nrhs > 4)
    {
        mexErrMsgIdAndTxt( "baslerDriver:Error:ArgumentError",
                "Too many arguments. Use help baslerGetParameter for further information."); 
    }
    
    // Get camera number
    const int i_cam_number = (int)mxGetScalar(prhs[0]);
    
    // Get verbose parameter
    bool b_verbose = 0;
    if(nrhs == 4)
    {
        b_verbose = (int)mxGetScalar(prhs[3]) != 0;
    }
    
    // Get number of frames
    int i_num_of_frames = 1;
    if(nrhs >= 2)
    {
        if(mxGetNumberOfElements(prhs[1]) >= 1)
        {
            i_num_of_frames = (int)mxGetScalar(prhs[1]);
        }
    }
    if(b_verbose)
    {
        mexPrintf("Capturing %d frame(s) \n",i_num_of_frames);
    }
    
    // Get output type
    Pylon::EPixelType ept_output_type = Pylon::PixelType_Undefined;
    if(nrhs >= 3)
    {
        if(!(mxGetM(prhs[2]) == 0 && mxGetN(prhs[2]) == 0))
        {
            ept_output_type = Pylon::CPixelTypeMapper().GetPylonPixelTypeByName(mxArrayToString(prhs[2]));
            if(b_verbose)
            {
                mexPrintf("Using output data type \"%s\"\n",mxArrayToString(prhs[2]));
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
        
        // Get width and height 
        const unsigned long long i_width = BaslerHelper::get_int(&camera,"Width",b_verbose);
        const unsigned long long i_height = BaslerHelper::get_int(&camera,"Height",b_verbose);
        unsigned long long i_numel = i_height * i_width;
        
        // Get dimensions of output array
        if(ept_output_type == Pylon::PixelType_Undefined)
        {
            std::string s_pixel_type = BaslerHelper::get_string(&camera,"PixelFormat",b_verbose);
            ept_output_type = Pylon::CPixelTypeMapper().GetPylonPixelTypeByName(s_pixel_type.c_str());
        }
        
        const size_t i_dimensions[] = { i_height, 
                                        i_width,
                                        Pylon::SamplesPerPixel(ept_output_type), 
                                        i_num_of_frames};
                                        
        // Create output array and create pointer
        mxArray* mxa_output;
        if(Pylon::BitDepth(ept_output_type) <= 8)
        {
            mxa_output = mxCreateNumericArray(4, i_dimensions, mxUINT8_CLASS, mxREAL);
            BaslerHelper::capture_images<uint8_t>(&camera, i_num_of_frames, mxa_output, ept_output_type, b_verbose);
        }
        else if(Pylon::BitDepth(ept_output_type) <= 16)
        {
            mxa_output = mxCreateNumericArray(4, i_dimensions, mxUINT16_CLASS, mxREAL);
            BaslerHelper::capture_images<uint16_t>(&camera, i_num_of_frames, mxa_output, ept_output_type, b_verbose);
        }
        else
        {
           mxa_output = mxCreateNumericArray(4, i_dimensions, mxDOUBLE_CLASS, mxREAL);
           BaslerHelper::capture_images<double>(&camera, i_num_of_frames, mxa_output, ept_output_type, b_verbose);
        }

        // Close camera
        camera.Close();
        
        // Remove singleton dimensions
        mexCallMATLAB(1,plhs,1,&mxa_output,"squeeze");
    }
    catch (GenICam::GenericException &e)
    {
        // Error handling.
        mexErrMsgIdAndTxt("baslerDriver:Error:CameraError",e.GetDescription());
    }
    
    return;
}

