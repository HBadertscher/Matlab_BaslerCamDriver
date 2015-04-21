% baslerGetParameter.m - Get value of any Basler camera parameter
%
%  Gets the parameter specified in 'parameterName' from the camera. The
%  Parameter type has to be specified in 'parameterType'. Possible values
%  are:
%    - 'Float'
%    - 'Int'
%    - 'Bool'
%    - 'String'
%
%  The optional parameter verbose (default=0) enables the output of
%  internal information to the workspace.
%
%  Usage:
%    baslerSetParameter(cameraIndex, parameterName, parameterType)
%    baslerSetParameter(cameraIndex, parameterName, parameterType, verbose)
%
%  Examples:
%    baslerSetParameter(0,'Width','Int');
%    baslerSetParameter(0,'Width','Int', 1);
%
