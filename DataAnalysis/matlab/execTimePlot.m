function [  ] = execTimePlot( trace, op )
% plot the execution time of a trace with each configuration on the same
% plot.
% IN: trace struct containing all configurations
%       op 0 = bar, 1 = line plot, 2 = bar of ideal exec times

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
end

if op == 1
    plot(exT,'-o');
    set(gca,'XTickLabel',lbls);
    grid on;
    title('Execution Times: All');
end

if op == 2
    % sort execution times before plotting
    [exT,ind] = sortrows([All_2way.idealExecT, All_4way.idealExecT, All_FA.idealExecT, ...
            All_small.idealExecT, default.idealExecT, L1_2way.idealExecT, ...
            L1_8way.idealExecT, L1_small_4way.idealExecT, L1_small.idealExecT; ...
            All_2way.idealMisAExecT, All_4way.idealMisAExecT, All_FA.idealMisAExecT, ...
            All_small.idealMisAExecT, default.idealMisAExecT, L1_2way.idealMisAExecT, ...
            L1_8way.idealMisAExecT, L1_small_4way.idealMisAExecT, L1_small.idealMisAExecT; ...
            All_2way.execTime, All_4way.execTime, All_FA.execTime, All_small.execTime, ...
            default.execTime, L1_2way.execTime, L1_8way.execTime, L1_small_4way.execTime ...
            L1_small.execTime;]');
    % sort labels for bar graph to match the sorted times
    lbls = {'All-2way', 'All-4way', 'All-FA', 'All-small', 'default-', ...
        'L1-2way', 'L1-8way', 'L1-small-4way', 'L1-small'};
    lbls = lbls(ind);
    bar3(exT);
    set(gca,'YTickLabel',lbls);
    legend('Ideal Execution Time', 'Ideal mis-aligned Execution Time', 'Actual Execution Time');
    grid on;
    title(['Ideal Execution Time Comparision: ' trace.name]);
end

end

