// baslerSetParameter.cpp - Set any Basler camera parameter
// see baslerSetParameter.m for help

#include <pylon/PylonIncludes.h>
#include "basler_helper/basler_set_get.h"

#include <matrix.h>
#include <mex.h>

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{       
    // Parse parameters
    if(nrhs < 3)
    {
        mexErrMsgIdAndTxt( "baslerDriver:Error:ArgumentError",
                "Not enough arguments. Use help baslerSetParameter for further information."); 
    }
    else if(nrhs > 4)
    {
        mexErrMsgIdAndTxt( "baslerDriver:Error:ArgumentError",
                "Too many arguments. Use help baslerSetParameter for further information."); 
    }
    
    const int i_cam_number = (int)mxGetScalar(prhs[0]);
    const std::string s_param_name(mxArrayToString(prhs[1]));
    bool b_verbose = 0;
    
    if(nrhs == 4)
    {
        b_verbose = (int)mxGetScalar(prhs[3]) != 0;

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
        
        // Find type of parameter
        if(mxIsNumeric(prhs[2]))                        // Numeric values
        {
            if(mxIsDouble(prhs[2]) ||mxIsSingle(prhs[2]))   // Float types
            {
                const double d_param_value = (const double)mxGetScalar(prhs[2]);
                BaslerHelper::set_parameter(&camera, 
                        s_param_name.c_str(), &d_param_value , b_verbose);
            }
            else                                            // Integers
            {
                const int i_param_value = (const int)mxGetScalar(prhs[2]);
                BaslerHelper::set_parameter(&camera, 
                        s_param_name.c_str(), &i_param_value , b_verbose);
            }
        }
        else if(mxIsLogical(prhs[2]))                   // Boolean
        {
            const bool b_param_value = (const bool)mxGetLogicals(prhs[2]);
            BaslerHelper::set_parameter(&camera, 
                    s_param_name.c_str(), &b_param_value , b_verbose);
        }
        else if(mxIsChar(prhs[2]))                      // Strings
        {
            const char* s_param_value = mxArrayToString(prhs[2]);
            BaslerHelper::set_parameter(&camera, 
                    s_param_name.c_str(), s_param_value , b_verbose);

        }
        else                                            // else: fail!
        {
            mexErrMsgIdAndTxt( "baslerDriver:Error:ArgumentError",
                    "Cannot detect type of parameter value."); 
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

