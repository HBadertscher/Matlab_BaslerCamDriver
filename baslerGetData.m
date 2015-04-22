% baslerGetData.m - Capture any number of frames from a Basler camera
%
%  Captures and returns a number of frames from the selected Basler camera.
%  The default number of frames is 1.
%
%  The optional parameter verbose (default=0) enables the output of
%  internal information to the workspace.
%
%  Usage:
%    baslerGetData(cameraIndex)
%    baslerGetData(cameraIndex, nFrames)
%    baslerGetData(cameraIndex, [], verbose)
%    baslerGetData(cameraIndex, nFrames, verbose)
%
