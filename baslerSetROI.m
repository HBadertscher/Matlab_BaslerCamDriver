function baslerSetROI( cameraIndex, varargin )
% baslerSetROI.m - Set the region of interest (ROI) of the selected Basler
% camera.
% 
% Calling this function without a specified ROI resets the ROI to the
% maximum possible. The ROI can be specified as vector 'regionOfInterest'
% with format:
%   regionOfInterest = [xOffset, yOffset, width, height] ;
% or as independent values xOffset, yOffset, width, height.
%
% Usage:
%   baslerSetROI(cameraIndex);
%   baslerSetROI(cameraIndex, regionOfInterest);
%   baslerSetROI(cameraIndex, xOffset, yOffset, width, height);
%

% Parse input arguments
if nargin == 1
    regionOfInterest = uint16(zeros(1,4));
    regionOfInterest(3) = baslerGetParameter(cameraIndex,'WidthMax','Int');
    regionOfInterest(4) = baslerGetParameter(cameraIndex,'HeightMax','Int');
elseif nargin == 2
    regionOfInterest = varargin{1};
elseif nargin == 5
    regionOfInterest = cell2mat(varargin);
else
    error('baslerDriver:Error:InputError', ...
          'Wrong number of input arguments. Please try help baslerSetROI for further information');
end

% Convert ROI to integer
regionOfInterest = uint16(regionOfInterest);

% Reset Offset first
baslerSetParameter(cameraIndex,'OffsetX', uint16(0));
baslerSetParameter(cameraIndex,'OffsetY', uint16(0));

% Then set ROI
baslerSetParameter(cameraIndex,'Width', regionOfInterest(3));
baslerSetParameter(cameraIndex,'Height', regionOfInterest(4));
baslerSetParameter(cameraIndex,'OffsetX', regionOfInterest(1));
baslerSetParameter(cameraIndex,'OffsetY', regionOfInterest(2));


end

