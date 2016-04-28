function [  ] = extraSjeng( sjeng )
% plot cost of simulations
% IN: the sjeng struct

% get the results for each configuration
sbw8  = getValues(sjeng.default);
sbw16 = getValues(sjeng.bw16);
sbw32 = getValues(sjeng.bw32);
sbw64 = getValues(sjeng.bw64);


% performance vs cost
cost  = [ sbw8.totCost, sbw16.totCost, sbw32.totCost, sbw64.totCost ];
cpi   = [ sbw8.cpi, sbw16.cpi, sbw32.cpi, sbw64.cpi ];

% scale cost down
perf = [cost./100; cpi]';

% scale data between 0 and 1
scaledP = (perf-min(perf(:))) ./ (max(perf(:)-min(perf(:))));

% sort data
[sortP,ind] = sortrows(scaledP,2);

% sort labels
lbls = {'BW = 8', 'BW = 16', 'BW = 32', 'BW = 64'};
lbls = lbls(ind);

% plot
bar(sortP)
set(gca,'XTickLabel',lbls);
xticklabel_rotate([],45,[],'Fontsize',12);
grid on;
title('Cost vs. Performance: Bandwidth Increase');
legend('cost','cpi');
axis([0 5 0 1.2]);