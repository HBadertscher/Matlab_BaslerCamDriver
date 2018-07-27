# Matlab_BaslerCamDriver
A universal MATLAB driver for Basler cameras

Copyright (c) 2015 Hannes Badertscher, ICOM Institute for Communication Systems
at HSR University of Applied Sciences of Eastern Switzerland - [icom.hsr.ch](http://www.icom.hsr.ch)

Until now, interfacing cameras in MATLAB was a cumbersome task. 
MATLAB offers no support for USB3 Vision cameras, and the GigE driver is rather buggy.
This driver package provides an open-source C++ interface between MATLAB and Basler's Pylon interface.

This driver was developed at the ICOM Institute for Communication Systems 
at HSR University of Applied Sciences of Eastern Switzerland, Rapperswil. 

## Disclaimer

Unfortunately, this project is not being actively developed and maintained anymore.
Due to that, it is still required to use Pylon 4 and not the most recent Pylon 5.
If you are interested in updating this driver to Pylon 5 please feel free to contact me.
Further, the camera support in MATLAB has improved significantly since this project was first published - 
I suggest giving the MATLAB Image Acquisition Toolbox a try first.

## Build

The MATLAB Basler Camera Driver is built by calling the provided `make.m` file.

### Requirements:
* [Boost C++ Libraries](http://www.boost.org/) (+ `BOOST_ROOT` set to the Boost root directory)
* [Basler Pylon 4](http://www.baslerweb.com/de/produkte/software) 
* And of course: a Basler Camera. 
This driver should support any Basler camera, but has only been tested on:
  - acA1600-20gc - GigE Vision camera
  - acA2000-165um - USB3.0 Vision camera
  - raL8192-12gm - GigE Vision line scan camera

## Functions
* `baslerFindCameras` returns a cell array containing the camera index and the camera name.
* `baslerCameraInfo` returns a struct containing all parameters of the selected camera.
* `baslerSetParameter` sets a camera parameter.
* `baslerGetParameter` returns the selected camera parameter.
* `baslerSetROI` sets the region of interest (ROI).
* `baslerPreview` displays a preview image.
* `baslerGetData` captures and returns the selected number of frames.
* `baslerSaveData` captures and saves the selected number of frames to disk.

## License

The MIT License (MIT)

Copyright (c) 2015 Hannes Badertscher and ICOM Institute for Communication Systems
at HSR University of Applied Sciences of Eastern Switzerland - [icom.hsr.ch](http://www.icom.hsr.ch)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
