% baslerGetData.m - Capture any number of frames from a Basler camera
%
%  Captures and returns a number of frames from the selected Basler camera.
%  The default number of frames is 1. The outputType specifies the
%  desired output type, which the captured frames are converted to. When
%  omiting the parameter, the type from PixelFormat is used. Possible
%  values are: 
%    - BGRA8packed
%    - BGR8packed
%    - RGB8packed 
%    - RGB16packed
%    - RGB8planar 
%    - RGB16planar
%    - Mono8
%    - Mono16
%  
%  The optional parameter verbose (default=0) enables the output of
%  internal information to the workspace.
%
%  Usage:
%    baslerGetData(cameraIndex)
%    baslerGetData(cameraIndex, nFrames)
%    baslerGetData(cameraIndex, [], outputType)
%    baslerGetData(cameraIndex, [], [], verbose)
%    baslerGetData(cameraIndex, nFrames, outputType, verbose)
%
