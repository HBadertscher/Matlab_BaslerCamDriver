// baslerSetParameter.cpp - Set any Basler camera parameter
// see baslerSetParameter.m for help

#include <pylon/PylonIncludes.h>
#include "basler_helper/basler_set_get.h"

#include <matrix.h>
#include <mex.h>

#include <boost/assign/list_of.hpp> 

// Enum of possible parameter types
enum class ParamType {
    Float,
    Int,
    Bool,
    String
};
    
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{       
    // Parse parameters
    if(nrhs < 3)
    {
        mexErrMsgIdAndTxt( "baslerDriver:Error:ArgumentError",
                "Not enough arguments. Use help baslerGetParameter for further information."); 
    }
    else if(nrhs > 4)
    {
        mexErrMsgIdAndTxt( "baslerDriver:Error:ArgumentError",
                "Too many arguments. Use help baslerGetParameter for further information."); 
    }
    
    const int i_cam_number = (int)mxGetScalar(prhs[0]);
    const std::string s_param_name(mxArrayToString(prhs[1]));
    const std::string s_param_type(mxArrayToString(prhs[2]));
    
    // Map string to parameter type
    std::map<std::string,ParamType> paramMap = boost::assign::map_list_of
            ("Float",ParamType::Float)
            ("Int",ParamType::Int)
            ("Bool",ParamType::Bool)
            ("String",ParamType::String);
         
    // Get verbose parameter
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
        switch(paramMap[s_param_type])
        {
            case ParamType::Float:
            {
                double d_param_value = BaslerHelper::get_float(
                        &camera,s_param_name.c_str(),b_verbose);
                plhs[0] = mxCreateDoubleScalar(d_param_value);
                break;
        }
            case ParamType::Int:
            {
                int i_param_value = BaslerHelper::get_int(
                        &camera,s_param_name.c_str(),b_verbose);
                plhs[0] = mxCreateNumericMatrix(1,1,mxINT64_CLASS,mxREAL);
                int64_t* p_output = (int64_t*) mxGetData(plhs[0]);
                p_output[0] = i_param_value;
                break;
            }
            case ParamType::Bool:
            {
                bool b_param_value = BaslerHelper::get_bool(
                        &camera,s_param_name.c_str(),b_verbose);
                plhs[0] = mxCreateLogicalScalar(b_param_value);
                break;
            }
            case ParamType::String:
            {
                std::string s_param_value = BaslerHelper::get_string(
                        &camera,s_param_name.c_str(),b_verbose);
                plhs[0] = mxCreateString(s_param_value.c_str());
                break;
            }
            default:
            {
                mexErrMsgIdAndTxt( "baslerDriver:Error:ArgumentError",
                           "Cannot detect type of parameter value."); 
                break;
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

