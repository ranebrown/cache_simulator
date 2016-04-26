% John-Austen Francisco
% 11 October 2014
%
% preconditions: MATLAB
% postconditions: graph stacked 3D bars
%	returns NaN, it is of no significance but to indicate that this code has no usable return value
%
% parameter specifications:
%	dataLayers: matrix: [MxNxP]
%	- each MxN matrix is one of the P layers of stacked bars
%	colorSpec: array: [1xP]
%	- array of characters from the MATLAB color codes:
%	i.e.: b, g, r, c, m, y, k, w
%	(these could potentially be RGB arrays, but that option is not currently supported)
%
% invocation & examples:
%
% A test invocation:
%	Graph a set of 3 random 10x5 matricies as stacked bars, with each layer/segment colored
%	red, then blue, then magenta:
%	bar3collected( rand(10, 5, 3), ['r', 'b', 'm'] )
%
% Note: you will need to rotate the graph to see it since it will be drawn looking down from the z axis
%


function result = bar3collected( dataLayers, colorSpec )
result = NaN;

%initialize plot area
cla
clf
hold on

%compute layer dimensions
layerDims = [size( dataLayers, 1), size( dataLayers, 2 )];
numLayers = size( dataLayers, 3);

%get the first layer of the stacked bars graphed - all others will be built on top
prevLayer = reshape( dataLayers(:, :, 1), layerDims(1,1), layerDims(1,2) );
baseHandlePrevious = bar3( prevLayer , 0.5 );
set(baseHandlePrevious,'FaceColor',colorSpec(1,1));

%for the rest of the layers...
for currentLayerInd = 2:1:numLayers
%graph the next layer - it will overlap the previous layer right now
currentLayer = reshape( dataLayers(:, :, currentLayerInd), layerDims(1,1), layerDims(1,2) );
baseHandleCurrent = bar3( currentLayer, 0.5 );
set(baseHandleCurrent, 'FaceColor', colorSpec(1,currentLayerInd));	

%for each column...
for currentColumn = 1:1:layerDims(1,2)
%fetch the Z-axis data for all bars in a column from the data we just graphed
modSegment = get( baseHandleCurrent(currentColumn), 'Zdata');

%for each element (row) of the column-wise Z-axis data
for currentRow = 1:1:layerDims(1,1)
%each bar's data is recorded as a block of 6 rows in the Z-axis data matrix
% .. grab all the Z-axis data for the current bar
indexSet = [(currentRow-1)*6:1:(currentRow*6)-1]+1;
% increase all the Z-axis data values for the current bar by the Z-values for the previous bar
% .. this should take the current bar and 'manually' slide it up above the previously-graphed group of bars
modSegment(indexSet, :) = modSegment(indexSet, :) + prevLayer(currentRow, currentColumn);
end

%implement the changes we computed above and write out the new Z-axis data values to the current
% .. column of bars
set( baseHandleCurrent(currentColumn), 'Zdata', modSegment);

end

%done shifting the Z-axis for the current graph
% .. the next graph will be stacked on top of the current, so swap the baseHandles
% .. the next graph will be stacked on top of the current, so add the currentLayer's z-values to
% .. .. the previous layer's values so that the next layer is stacked on top of BOTH the current
% .. .. and the previous (not doing this will stack the next on top of the previous, overlapping the current)
baseHandlePrevious = baseHandleCurrent;
prevLayer = currentLayer+prevLayer;


end

%equal axes aren't required, but are certainly recommended
%axis equal

hold off

end