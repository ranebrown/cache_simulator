function [  ] = cpiLinePlot( trace )
% plot the cpi, of each trace and configuration 
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
cpi = [ All_2way.cpi; All_4way.cpi; All_FA.cpi; All_small.cpi; ...
        default.cpi; L1_2way.cpi; L1_8way.cpi; L1_small_4way.cpi;...
        L1_small.cpi];
   


%         All_2way.cpi, All_2way.idealMisACPI, All_2way.idealCPI, All_4way.idealMisACPI, All_4way.idealCPI; ...
%         All_FA.cpi, All_FA.idealMisACPI, All_FA.idealCPI; ...
%         All_small.cpi, All_small.idealMisACPI, All_small.idealCPI; ...
%         default.cpi, default.idealMisACPI, default.idealCPI; ...
%         L1_2way.cpi, L1_2way.idealMisACPI, L1_2way.idealCPI; ...
%         L1_8way.cpi, L1_8way.idealMisACPI, L1_8way.idealCPI; ...
%         L1_small_4way.cpi, L1_small_4way.idealMisACPI, L1_small_4way.idealCPI; ...
%         L1_small.cpi, L1_small.idealMisACPI, L1_small.idealCPI;];

% sort before plotting
[cpiSort,ind] = sortrows(cpi);
        
% sort labels to match
lbls = {'All-2way', 'All-4way', 'All-FA', 'All-small', 'default-', ...
        'L1-2way', 'L1-8way', 'L1-small-4way', 'L1-small'};
lbls = lbls(ind);


plot(cpiSort,'-o');
set(gca,'XTickLabel',lbls);
grid on;
title('CPI: All');


% bar plot
% bar(cpiSor, 'grouped');
% set(gca,'XTickLabel',lbls);
% xticklabel_rotate([],45,[],'Fontsize',12);
% grid on;
% title(['CPI: ' trace.name]);
% lg = legend('CPI','Ideal CPI','Ideal mis-aligned CPI');
% set(lg, 'Location', 'northwest'); % legend location






end

