// capture_images.h - A collection of helper functions for Basler cameras
// 24.04.2015 / HB


#ifndef __CAPTUREIMAGES_H_INCLUDED__
#define __CAPTUREIMAGES_H_INCLUDED__

#include <pylon/PylonIncludes.h>
#include <mex.h>

namespace BaslerHelper {

    // Captures the specified number of images from the camera and saves
    // those in the (already existing!) Matlab mxArray.
    template <typename T>
    void capture_images(Pylon::CInstantCamera* camera, const int i_num_of_frames, mxArray* mxa_output, bool b_verbose)
    {
        // Get width and height 
        const unsigned long long i_width = BaslerHelper::get_int(camera,"Width",b_verbose);
        const unsigned long long i_height = BaslerHelper::get_int(camera,"Height",b_verbose);
        const unsigned long long i_numel = i_height * i_width;
        
        // Get Pixel data type
        std::string s_pixel_type = BaslerHelper::get_string(camera,"PixelFormat",b_verbose);
        Pylon::EPixelType ept_pixel_type = Pylon::CPixelTypeMapper().GetPylonPixelTypeByName(s_pixel_type.c_str());
        const unsigned int i_samples_p_pixel = Pylon::SamplesPerPixel(ept_pixel_type);    
        
        // Start capturing
        camera->StartGrabbing(i_num_of_frames, Pylon::GrabStrategy_OneByOne);
        Pylon::CGrabResultPtr p_grab_result;

        // Get results
        for(int i_cur_frame=0; i_cur_frame<i_num_of_frames; i_cur_frame++)
        {
            camera->RetrieveResult(5000, p_grab_result, Pylon::TimeoutHandling_ThrowException);
            if (p_grab_result->GrabSucceeded())
            {   
                T* p_image_buffer = static_cast<T*> (p_grab_result->GetBuffer());
                T* p_output = static_cast<T*> (mxGetData(mxa_output));
                
                // For all bands
                for (unsigned int i_c_band = 0; i_c_band < i_samples_p_pixel; i_c_band ++)
                {
                    // Save pixels to buffer
                    for (unsigned long long i=0; i < i_height; i++)
                    {
                        for (unsigned long long j=0; j < i_width; j++)
                        {
                            p_output[i_cur_frame * (i_numel * i_samples_p_pixel)  // Which frame
                                    + i_c_band * i_numel     // Which color band
                                    +i                      // Which row
                                    +j*i_height]            // Which colum
                            = p_image_buffer[i_c_band+i_samples_p_pixel*(i*i_width+j)];
                        }
                    }
                }
            }
        }

    }
    
    
}

#endif