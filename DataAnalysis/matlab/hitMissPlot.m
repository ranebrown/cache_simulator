function [  ] = hitMissPlot( trace )
% plot hits and misses as 3D plot
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
hm = [  All_2way.L1iVChit, All_2way.L1imiss, All_2way.L1ihits; ...
        All_4way.L1iVChit, All_4way.L1imiss, All_4way.L1ihits; ...
        All_FA.L1iVChit, All_FA.L1imiss, All_FA.L1ihits; ...
        All_small.L1iVChit, All_small.L1imiss, All_small.L1ihits; ...
        default.L1iVChit, default.L1imiss, default.L1ihits; ...
        L1_2way.L1iVChit, L1_2way.L1imiss, L1_2way.L1ihits; ...
        L1_8way.L1iVChit, L1_8way.L1imiss, L1_8way.L1ihits; ...
        L1_small_4way.L1iVChit, L1_small_4way.L1imiss, L1_small_4way.L1ihits; ...
        L1_small.L1iVChit, L1_small.L1imiss, L1_small.L1ihits;];  

% log scale for data
hm = log10(hm);

% sort before plotting
% [sorhm,ind] = sortrows(hm);
       
% sort labels
lbls = {'All-2way', 'All-4way', 'All-FA', 'All-small', 'default-', ...
         'L1-2way', 'L1-8way', 'L1-small-4way', 'L1-small'};
% lbls = lbls(ind);

% 3D bar plot
bar3(hm);
set(gca,'YTickLabel',lbls);
set(gca,'XTickLabel',{'L1i VC hit', 'L1i miss', 'L1i hit'});
zlabel('log_{10} scale');
grid on;
title(['L1i hit/miss count: ' trace.name]);

end