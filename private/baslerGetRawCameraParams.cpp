// baslerGetRawCameraParams.cpp - INTERNAL FUNCTION!!!
// Returns the complete list of camera parameters, including their 
// visibility

#include <pylon/PylonIncludes.h>

#include <matrix.h>
#include <mex.h>

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{       
    // Parse parameters
    if(nrhs < 1)
    {
        mexErrMsgIdAndTxt( "baslerDriver:Error:ArgumentError",
                "Not enough arguments. Use help baslerCameraInfo for further information."); 
    }
    else if(nrhs > 1)
    {
        mexErrMsgIdAndTxt( "baslerDriver:Error:ArgumentError",
                "Too many arguments. Use help baslerCameraInfo for further information."); 
    }
    const int i_cam_number = (int)mxGetScalar(prhs[0]);    
    
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
        
        // Find nodes
        GenApi::NodeList_t nl_nodes;
        camera.GetNodeMap().GetNodes(nl_nodes);
        
        // Init output
        plhs[0] = mxCreateCellMatrix(nl_nodes.size(),3);
        
        int i=0;
        for(GenApi::NodeList_t::iterator it=nl_nodes.begin(); it != nl_nodes.end(); ++it)
        {
            int i_cur_vis = (int)(*it)->GetVisibility();

            // Set Node name
            mxSetCell(plhs[0],i,mxCreateString((*it)->GetName()));

            // Try to find correct Node type
            try 
            {
                GenApi::CPointer<GenApi::IBoolean> p_cur_node = camera.GetNodeMap().GetNode((*it)->GetName());
                mxSetCell(plhs[0],i+nl_nodes.size(),mxCreateString(p_cur_node->ToString()));
            }
            catch(GenICam::GenericException &e)
            {
                try 
                {
                    GenApi::CPointer<GenApi::IInteger> p_cur_node = camera.GetNodeMap().GetNode((*it)->GetName());
                    mxSetCell(plhs[0],i+nl_nodes.size(),mxCreateString(p_cur_node->ToString()));
                }
                catch(GenICam::GenericException &e)
                {
                    try 
                    {
                        GenApi::CPointer<GenApi::IFloat> p_cur_node = camera.GetNodeMap().GetNode((*it)->GetName());
                        mxSetCell(plhs[0],i+nl_nodes.size(),mxCreateString(p_cur_node->ToString()));
                    }
                    catch(GenICam::GenericException &e)
                    {

                        try 
                        {
                            GenApi::CPointer<GenApi::IEnumeration> p_cur_node = camera.GetNodeMap().GetNode((*it)->GetName());
                            mxSetCell(plhs[0],i+nl_nodes.size(),mxCreateString(p_cur_node->ToString()));
                        }
                        catch(GenICam::GenericException &e)
                        {

                        }
                    }
                }
            }

            // Visibility
            mxSetCell(plhs[0],i+2*nl_nodes.size(),mxCreateDoubleScalar(i_cur_vis));
            
            // Counter variable
            i++;
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

