% baslerSetParameter.m - Set any Basler camera parameter
%
%  Sets the parameter specified in 'parameterName' to the value
%  'parameterValue'.  Important: the 'parameterValue' has to have the same
%  data type as the underlying camera property. For float types, double or
%  single can be used. For integer types, any integer type can be used.
%  The optional parameter verbose (default=0) enables the output of
%  internal information to the workspace.
%
%  Usage:
%    baslerSetParameter(cameraIndex, parameterName, parameterValue)
%    baslerSetParameter(cameraIndex, parameterName, parameterValue, verbose)
%
%  Examples:
%    baslerSetParameter(0,'Width',uint16(1024));
%    baslerSetParameter(0,'ExposureTime',double(10000));
%    baslerSetParameter(0,'AcquisitionFrameRateEnable',logical(1));
%    baslerSetParameter(0,'PixelFormat','Mono8');
%    baslerSetParameter(..., 1);