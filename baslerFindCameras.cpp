// baslerFindCameras.cpp - Find all connected Basler cameras
// see baslerFindCameras.m for help

#include <pylon/PylonIncludes.h>

#include <matrix.h>
#include <mex.h>

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{       
    
    // Initiatlize Pylon
    Pylon::PylonAutoInitTerm auto_init_term;

    try
    {
        // Get the transport layer factory.
        Pylon::CTlFactory& tlFactory = Pylon::CTlFactory::GetInstance();
        
        // Get all attached devices
        Pylon::DeviceInfoList_t devices;
        tlFactory.EnumerateDevices(devices);

        
        // Create an array of instant cameras for the found devices
        Pylon::CInstantCameraArray cameras(devices.size());

        // Init output
        plhs[0] = mxCreateCellMatrix(cameras.GetSize(),2);
        
        // Find all names
        for(size_t i = 0; i < cameras.GetSize(); ++i)
        {
            cameras[i].Attach(tlFactory.CreateDevice(devices[i]));
            mxSetCell(plhs[0],i+cameras.GetSize(),mxCreateString(cameras[i].GetDeviceInfo().GetModelName()));
            mxSetCell(plhs[0],i,mxCreateDoubleScalar(i));
        }
        
    }
    catch (GenICam::GenericException &e)
    {
        // Error handling.
        mexErrMsgIdAndTxt("baslerDriver:Error:CameraError",e.GetDescription());
    }
    
    return;
}

