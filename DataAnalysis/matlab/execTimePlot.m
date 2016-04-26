function [  ] = execTimePlot( trace, op )
% plot the execution time of a trace with each configuration on the same
% plot.
% IN: trace struct containing all configurations
%       op 0 = bar, 1 = line plot

All_2way              =       getValues(trace.All_2way);
All_4way              =       getValues(trace.All_4way);
All_FA                =       getValues(trace.All_FA);
All_small             =       getValues(trace.All_small);
default               =       getValues(trace.default);
L1_2way               =       getValues(trace.L1_2way);
L1_8way               =       getValues(trace.L1_8way);
L1_small_4way         =       getValues(trace.L1_small_4way);
L1_small              =       getValues(trace.L1_small);

% sort execution times before plotting
[exT,ind] = sort([All_2way.execTime, All_4way.execTime, All_FA.execTime, All_small.execTime, ...
            default.execTime, L1_2way.execTime, L1_8way.execTime, L1_small_4way.execTime ...
            L1_small.execTime]);
        
% sort labels for bar graph to match the sorted times
lbls = {'All-2way', 'All-4way', 'All-FA', 'All-small', 'default-', ...
        'L1-2way', 'L1-8way', 'L1-small-4way', 'L1-small'};
lbls = lbls(ind);

if op == 0
    % bar plot
    bar(exT, 0.5);
    set(gca,'XTickLabel',lbls);
    xticklabel_rotate([],45,[],'Fontsize',12);
    grid on;
    title(['Execution Time: ' trace.name]);

else
    plot(exT,'-o');
    set(gca,'XTickLabel',lbls);
    grid on;
    title('Execution Times: All');
end
end

