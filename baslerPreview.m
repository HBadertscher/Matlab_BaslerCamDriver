function baslerPreview( cameraIndex  )
% baslerPreview.m - Live preview of video data from the selected Basler
% camera
%
%  Creates a new Video preview window that displays live video data from 
%  the selected Basler camera
%
%  Usage:
%  baslerPreview(cameraIndex)
%

% Create a new figure
fig = figure;
set(fig,'NumberTitle','off')
set(fig,'Name','Basler Preview Window');
set(fig,'Visible','on');

% Get preview data until window is closed
while ishandle(fig)
    
    % Get video and preview
    imagesc(baslerGetData(cameraIndex,1,'RGB8packed'));
    axis off;
    pause(0.1);
    
end


end


