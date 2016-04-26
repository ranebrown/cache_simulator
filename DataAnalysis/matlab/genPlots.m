% clean up workspace
clear all; close all; clc;

% control which plots are shown
execT_bar = 0;
execT_line = 0;
cpi_bar = 0;
hm_plot = 1;

% read in data
[ astar, bzip2, gobmk, libquantum, omnetpp, sjeng ] = readData;

% bar plots of execution times
if execT_bar == 1
    figure, execTimePlot( astar, 0 );
    figure, execTimePlot( bzip2, 0 );
    figure, execTimePlot( gobmk, 0 );
    figure, execTimePlot( libquantum, 0 );
    figure, execTimePlot( omnetpp, 0 );
    figure, execTimePlot( sjeng, 0 );
end

% all execution times same plot
% TODO the x-labels could possibly be off last function call writes labels
if execT_line == 1
    figure, execTimePlot( astar, 1 );
    hold on
    execTimePlot( bzip2, 1 );
    execTimePlot( gobmk, 1 );
    execTimePlot( libquantum, 1 );
    execTimePlot( omnetpp, 1 );
    execTimePlot( sjeng, 1 );
    lg = legend('astar', 'bzip2', 'gobmk', 'libquantum', 'omnetpp', 'sjeng');
    set(lg, 'Location', 'northwest'); % legend location
    hold off
end

% cpi bar plots
if cpi_bar == 1
    figure, cpiPlot( astar );
    figure, cpiPlot( bzip2 );
    figure, cpiPlot( gobmk );
    figure, cpiPlot( libquantum );
    figure, cpiPlot( omnetpp );
    figure, cpiPlot( sjeng );
end

if hm_plot == 1
    figure, hitMissPlot( astar );
    figure, hitMissPlot( bzip2 );
    figure, hitMissPlot( gobmk );
    figure, hitMissPlot( libquantum );
    figure, hitMissPlot( omnetpp );
    figure, hitMissPlot( sjeng );
end