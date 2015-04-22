function cameraCell = baslerCameraInfo(cameraIndex, visibility)
% baslerCameraInfo.m - Get all info on the selected Basler camera
%
%  Returns a cell containing all relevant information on the selected
%  Basler camera. The visibility parameter specifies which camera
%  information is displayed.
%  Possible values are:
%    - 0: Beginner
%    - 1: Expert
%    - 2: Guru
%
%  Usage:
%  cameraCell = baslerCameraInfo(cameraIndex, visibility);
%

cameraCell = baslerGetRawCameraParams(cameraIndex);

% Remove empty values
emptyRows = cellfun( @isempty, cameraCell(:,2) );
cameraCell = cameraCell(~emptyRows,:);

% Remove N parameters
nParamRows = cellfun(                                       ...
        @(x) ~isempty( regexp(x,'N\d{1,4}','once')) ,         ...
        cameraCell(:,1));
cameraCell = cameraCell(~nParamRows,:);

% Remove parameters with '_ConvertTo' or '_convertFrom'
nParamConv = cellfun(                                       ...
        @(x) ~isempty( strfind(x,'_ConvertTo')) ,           ...
        cameraCell(:,1))                                    ...
    |                                                       ...
    cellfun(                                                ...
        @(x) ~isempty( strfind(x,'_ConvertFrom')) ,           ...
        cameraCell(:,1))                                    ...
    ;
cameraCell = cameraCell(~nParamConv,:);

% Only correct visibility
nVisRows = cellfun( @(x)x>visibility, cameraCell(:,3) );
cameraCell = cameraCell(~nVisRows,:);

% Remove visibility
cameraCell = cameraCell(:,1:2);

end