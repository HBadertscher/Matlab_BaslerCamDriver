% baslerSaveData.m - Capture and save a number of frames from Basler a camera
%
%  Captures and saves a number of frames from the selected Basler camera.
%  The save path has to be specified in savePath. Currently the only output
%  format is a number of .tiff files.
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
%    baslerSaveData(cameraIndex, savePath)
%    baslerSaveData(cameraIndex, savePath, nFrames)
%    baslerSaveData(cameraIndex, savePath, [], outputType)
%    baslerSaveData(cameraIndex, savePath, [], [], verbose)
%    baslerSaveData(cameraIndex, savePath, nFrames, outputType, verbose)
%
