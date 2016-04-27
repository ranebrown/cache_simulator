function [  ] = costPlot( trace, op )
% plot cost of simulations
% IN: trace struct containing all configurations
%       op 1 = plot cost, 2 = plot cost v. performance

All_2way              =       getValues(trace.All_2way);
All_4way              =       getValues(trace.All_4way);
All_FA                =       getValues(trace.All_FA);
All_small             =       getValues(trace.All_small);
default               =       getValues(trace.default);
L1_2way               =       getValues(trace.L1_2way);
L1_8way               =       getValues(trace.L1_8way);
L1_small_4way         =       getValues(trace.L1_small_4way);
L1_small              =       getValues(trace.L1_small);

if op == 1
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

    % plot
    plot(sorCST, '-*');
    set(gca,'XTickLabel',lbls);
    legend('Main Mem Cost', 'L2 Cost', 'L1 Cost', 'Total Cost');
    grid on;
    title('Total Simulation Cost');
end

if op == 2
    % performance vs cost
    cost = [ All_2way.totCost All_4way.totCost All_FA.totCost  All_small.totCost   default.totCost ...
            L1_2way.totCost  L1_small_4way.totCost  L1_8way.totCost L1_small.totCost;];
    execT = [ All_2way.execTime, All_4way.execTime, All_FA.execTime, All_small.execTime, default.execTime, ...
            L1_2way.execTime, L1_8way.execTime, L1_small_4way.execTime, L1_small.execTime;];
    cpi   = [ All_2way.cpi, All_4way.cpi, All_FA.cpi, All_small.cpi, default.cpi, ...
            L1_2way.cpi, L1_8way.cpi, L1_small_4way.cpi, L1_small.cpi;];

    % compare cost and cpi
    perf = [cost./100; cpi]';
    
    % scale data between 0 and 1
    scaledP = (perf-min(perf(:))) ./ (max(perf(:)-min(perf(:))));
    
    % sort data
    [sortP,ind] = sortrows(scaledP,2);
    
    % sort labels
    lbls = {'All-2way', 'All-4way', 'All-FA', 'All-small', 'default-', ...
            'L1-2way', 'L1-small-4way', 'L1-8way', 'L1-small'};
    lbls = lbls(ind);
    
    % plot
    bar(sortP)
    set(gca,'XTickLabel',lbls);
    xticklabel_rotate([],45,[],'Fontsize',12);
    grid on;
    title(['Cost vs. Performance: ', trace.name]);
    legend('cost','cpi');
    axis([0 10 0 1.2]);

end