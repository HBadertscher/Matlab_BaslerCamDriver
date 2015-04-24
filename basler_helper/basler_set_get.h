// basler_set_get.h - A collection of helper functions for Basler cameras
// 21.04.2015 / HB

#ifndef __BASLERSETGET_H_INCLUDED__
#define __BASLERSETGET_H_INCLUDED__

#include <string>
#include <pylon/PylonIncludes.h>


namespace BaslerHelper {

    // Set float parameter
    void set_parameter( Pylon::CInstantCamera* p_camera, 
                        const char* s_param_name, 
                        const double* new_value, 
                        const bool b_verbose);
    
    // Set int parameter
    void set_parameter( Pylon::CInstantCamera* p_camera, 
                        const char* s_param_name, 
                        const int* new_value, 
                        const bool b_verbose);
    
    // Set string parameter
    void set_parameter( Pylon::CInstantCamera* p_camera, 
                        const char* s_param_name, 
                        const char* new_value, 
                        const bool b_verbose);

    // Set bool parameter
    void set_parameter( Pylon::CInstantCamera* p_camera, 
                        const char* s_param_name, 
                        const bool* new_value, 
                        const bool b_verbose);

    // Get float parameter
    double get_float(	Pylon::CInstantCamera* p_camera, 
                        const char* s_param_name, 
                        const bool b_verbose);

    // Get int parameter
    int get_int(        Pylon::CInstantCamera* p_camera, 
                        const char* s_param_name, 
                        const bool b_verbose);
    
    // Get bool parameter
    bool get_bool(      Pylon::CInstantCamera* p_camera, 
                        const char* s_param_name, 
                        const bool b_verbose);

    // Get string parameter
    std::string get_string( Pylon::CInstantCamera* p_camera, 
                        const char* s_param_name, 
                        const bool b_verbose);
    
}

#endif 
