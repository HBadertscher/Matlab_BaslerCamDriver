// baslerGetData.cpp - Capture any number of frames from a Basler camera
// see baslerGetData.m for help

#include <pylon/PylonIncludes.h>
#include "basler_helper/basler_helper.h"

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
    else if(nrhs > 3)
    {
        mexErrMsgIdAndTxt( "baslerDriver:Error:ArgumentError",
                "Too many arguments. Use help baslerGetParameter for further information."); 
    }
    
    // Get camera number
    const int i_cam_number = (int)mxGetScalar(prhs[0]);
    
    // Get verbose parameter
    bool b_verbose = 0;
    if(nrhs == 3)
    {
        b_verbose = (int)mxGetScalar(prhs[2]) != 0;

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
        
        // Get width and height and allocate output
        const unsigned long long i_width = BaslerHelper::get_int(&camera,"Width",b_verbose);
        const unsigned long long i_height = BaslerHelper::get_int(&camera,"Height",b_verbose);
        
        unsigned long long i_numel = i_height * i_width;
        const size_t i_dimensions[] = {i_height, i_width, i_num_of_frames};
        plhs[0] = mxCreateNumericArray(3, i_dimensions, mxUINT8_CLASS, mxREAL);
        //TODO: THIS ONLY WORKS WITH UINT8 TYPES!!!!
        
        // Start capturing
		camera.StartGrabbing(i_num_of_frames, Pylon::GrabStrategy_OneByOne);

        Pylon::CGrabResultPtr p_grab_result;

        // Get results
        for(int i_cur_frame=0; i_cur_frame<i_num_of_frames; i_cur_frame++)
        {
            camera.RetrieveResult(5000, p_grab_result, Pylon::TimeoutHandling_ThrowException);
            if (p_grab_result->GrabSucceeded())
            {   
                const uint8_t* p_image_buffer = (uint8_t*) p_grab_result->GetBuffer();

                uint8_t* p_output = (uint8_t*) mxGetData(plhs[0]);
                for (unsigned long long i=0; i < i_height; i++)
                {
                    for (unsigned long long j=0; j < i_width; j++)
                    {
                        p_output[i_cur_frame*i_numel+i+j*i_height] = p_image_buffer[i*i_width+j];
                    }
                }
            }
        }
        
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

