function [  ] = costPlot( trace )
% plot cost of simulations
% IN: trace struct containing all configurations

All_2way              =       getValues(trace.All_2way);
All_4way              =       getValues(trace.All_4way);
All_FA                =       getValues(trace.All_FA);
All_small             =       getValues(trace.All_small);
default               =       getValues(trace.default);
L1_2way               =       getValues(trace.L1_2way);
L1_8way               =       getValues(trace.L1_8way);
L1_small_4way         =       getValues(trace.L1_small_4way);
L1_small              =       getValues(trace.L1_small);

% format data to plot
cst = [  All_2way.mainMemCost All_4way.mainMemCost All_FA.mainMemCost  All_small.mainMemCost ...
        default.mainMemCost L1_2way.mainMemCost L1_small_4way.mainMemCost ...
        L1_8way.mainMemCost, L1_small.mainMemCost; ... 
        All_2way.L2Cost All_4way.L2Cost All_FA.L2Cost  All_small.L2Cost   default.L2Cost ...
        L1_2way.L2Cost  L1_small_4way.L2Cost  L1_8way.L2Cost L1_small.L2Cost; ... 
        All_2way.L1Cost All_4way.L1Cost All_FA.L1Cost  All_small.L1Cost   default.L1Cost ...
        L1_2way.L1Cost  L1_small_4way.L1Cost  L1_8way.L1Cost L1_small.L1Cost; ...   
        All_2way.totCost All_4way.totCost All_FA.totCost  All_small.totCost   default.totCost ...
        L1_2way.totCost  L1_small_4way.totCost  L1_8way.totCost L1_small.totCost;]';  

% sort before plotting
[sorCST,ind] = sortrows(cst,4);
       
% sort labels
lbls = {'All-2way', 'All-4way', 'All-FA', 'All-small', 'default-', ...
        'L1-2way', 'L1-small-4way', 'L1-8way', 'L1-small'};
lbls = lbls(ind);

% 3D bar plot
plot(sorCST, '-*');
set(gca,'XTickLabel',lbls);
legend('Main Mem Cost', 'L2 Cost', 'L1 Cost', 'Total Cost');
grid on;
title('Total Simulation Cost');

end