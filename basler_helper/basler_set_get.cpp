// basler_set_get.cpp - A collection of helper functions for Basler cameras
// 21.04.2015 / HB


#include "basler_set_get.h"
#include <mex.h>
#include <pylon/PylonIncludes.h>


namespace BaslerHelper {
    //---------------------------------------------------------------------
    // Set float parameter
    void set_parameter( Pylon::CInstantCamera* p_camera, const char* s_param_name, const double* new_value, const bool b_verbose)    {
        GenApi::CPointer<GenApi::IFloat> p_parameter = p_camera->GetNodeMap().GetNode(s_param_name);
        if (IsWritable(p_parameter))
        {
        p_parameter->SetValue(*new_value);
        }
        else
        {
            throw( RUNTIME_EXCEPTION("Parameter not writable. Maybe wrong datatype?"));
        }
        if(b_verbose)
        {
            printf("Set Parameter \"%s\" to %f\n",s_param_name, *new_value);
        }
    }
    
    //---------------------------------------------------------------------
    // Set int parameter
    void set_parameter(Pylon::CInstantCamera* p_camera, const char* s_param_name, const int* new_value, const bool b_verbose)
    {
        GenApi::CPointer<GenApi::IInteger> p_parameter = p_camera->GetNodeMap().GetNode(s_param_name);
        if (IsWritable(p_parameter))
        {
            p_parameter->SetValue(*new_value);
        }
        else
        {
            throw( RUNTIME_EXCEPTION("Parameter not writable. Maybe wrong datatype?"));
        }
        if(b_verbose)
        {
            printf("Set Parameter \"%s\" to %d\n",s_param_name, *new_value);
        }
    }
    
    //---------------------------------------------------------------------
    // Set string parameter
    void set_parameter(Pylon::CInstantCamera* p_camera, const char* s_param_name, const char* new_value, const bool b_verbose)
    {
        GenApi::CPointer<GenApi::IEnumeration> p_parameter = p_camera->GetNodeMap().GetNode(s_param_name);
        if (IsWritable(p_parameter))
        {
            p_parameter->FromString(new_value);
        }
        else
        {
            throw( RUNTIME_EXCEPTION("Parameter not writable. Maybe wrong datatype?"));
        }
        if(b_verbose)
        {
            printf("Set Parameter \"%s\" to %s\n",s_param_name, new_value);
        }
    }
    
    //---------------------------------------------------------------------
    // Set bool parameter
    void set_parameter(Pylon::CInstantCamera* p_camera, const char* s_param_name, const bool* new_value, const bool b_verbose)
    {
        GenApi::CPointer<GenApi::IBoolean> p_parameter = p_camera->GetNodeMap().GetNode(s_param_name);
        if (IsWritable(p_parameter))
        {
            p_parameter->SetValue(*new_value);
        }
        else
        {
            throw( RUNTIME_EXCEPTION("Parameter not writable. Maybe wrong datatype?"));
        }
        if(b_verbose)
        {
            printf("Set Parameter \"%s\" to %d\n",s_param_name, *new_value);
        }
    }
    
    //---------------------------------------------------------------------
    // Get float parameter
    double get_float( Pylon::CInstantCamera* p_camera, const char* s_param_name, const bool b_verbose)
    {
        GenApi::CPointer<GenApi::IFloat> p_parameter = p_camera->GetNodeMap().GetNode(s_param_name);
        
        if(b_verbose)
        {
            std::string s_result = p_parameter->ToString();
            printf("Read Parameter \"%s\": %s\n",s_param_name, s_result);
        }
        
        return p_parameter->GetValue();
    }
    
    //---------------------------------------------------------------------
    // Get int parameter
    int get_int( Pylon::CInstantCamera* p_camera, const char* s_param_name, const bool b_verbose)
    {
        GenApi::CPointer<GenApi::IInteger> p_parameter = p_camera->GetNodeMap().GetNode(s_param_name);
        
        if(b_verbose)
        {
            std::string s_result = p_parameter->ToString();
            printf("Read Parameter \"%s\": %s\n",s_param_name, s_result);
        }
        
        return p_parameter->GetValue();
    } 

    //---------------------------------------------------------------------
    // Get string parameter
    std::string get_string( Pylon::CInstantCamera* p_camera, const char* s_param_name, const bool b_verbose)
    {
        GenApi::CPointer<GenApi::IEnumeration> p_parameter = p_camera->GetNodeMap().GetNode(s_param_name);
        
        if(b_verbose)
        {
            std::string s_result = p_parameter->ToString();
            printf("Read Parameter \"%s\": %s\n",s_param_name, s_result);
        }
        
        return p_parameter->ToString();
    }
    
    //---------------------------------------------------------------------
    // Get bool parameter
    bool get_bool( Pylon::CInstantCamera* p_camera, const char* s_param_name, const bool b_verbose)
    {
        GenApi::CPointer<GenApi::IBoolean> p_parameter = p_camera->GetNodeMap().GetNode(s_param_name);
        
        if(b_verbose)
        {
            std::string s_result = p_parameter->ToString();
            printf("Read Parameter \"%s\": %s\n",s_param_name, s_result);
        }
        
        return p_parameter->GetValue();
    } 
    
    

}