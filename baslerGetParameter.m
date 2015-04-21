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
%    baslerGetParameter(cameraIndex, parameterName, parameterType)
%    baslerGetParameter(cameraIndex, parameterName, parameterType, verbose)
%
%  Examples:
%    baslerGetParameter(0,'Width','Int');
%    baslerGetParameter(0,'Width','Int', 1);
%
