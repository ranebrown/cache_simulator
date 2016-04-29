function [avgIdeal, avgIdealMis] = idealPercentage( trace )
% calculates the percentage difference between ideal and actual execution
% times

All_2way              =       getValues(trace.All_2way);
All_4way              =       getValues(trace.All_4way);
All_FA                =       getValues(trace.All_FA);
All_small             =       getValues(trace.All_small);
default               =       getValues(trace.default);
L1_2way               =       getValues(trace.L1_2way);
L1_8way               =       getValues(trace.L1_8way);
L1_small_4way         =       getValues(trace.L1_small_4way);
L1_small              =       getValues(trace.L1_small);

% ideal 
ideal = [All_2way.execTime / All_2way.idealExecT; All_4way.execTime / All_4way.idealExecT; ...
    All_FA.execTime / All_FA.idealExecT; All_small.execTime / All_small.idealExecT; ...
    default.execTime / default.idealExecT; L1_2way.execTime / L1_2way.idealExecT; ...
    L1_8way.execTime / L1_8way.idealExecT; L1_small_4way.execTime / L1_small_4way.idealExecT; ...
    L1_small.execTime / L1_small.idealExecT;];

% ideal misaligned
idealMis = [ All_2way.execTime / All_2way.idealMisAExecT; All_4way.execTime / All_4way.idealMisAExecT; ...
    All_FA.execTime / All_FA.idealMisAExecT; All_small.execTime / All_small.idealMisAExecT; ...
    default.execTime / default.idealMisAExecT; L1_2way.execTime / L1_2way.idealMisAExecT; ...
    L1_8way.execTime / L1_8way.idealMisAExecT; L1_small_4way.execTime / L1_small_4way.idealMisAExecT; ...
    L1_small.execTime / L1_small.idealMisAExecT;];

% how much faster ideal case is (average of all configs)
avgIdeal = mean(ideal);
avgIdealMis = mean(idealMis);


end

