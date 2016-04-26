function [ astar, bzip2, gobmk, libquantum, omnetpp, sjeng ] = readData(  )
% reads in simulation results from a csv file

% read simulation data from csv file
M = csvread('../csv/allData_noName.csv');

% separate data into individual components

% astar
astar.name                  =       'astar';
astar.All_2way              =       M(1,:);
astar.All_4way              =       M(2,:);
astar.All_FA                =       M(3,:);
astar.All_small             =       M(4,:);
astar.default               =       M(5,:);
astar.L1_2way               =       M(6,:);
astar.L1_8way               =       M(7,:);
astar.L1_small_4way         =       M(8,:);
astar.L1_small              =       M(9,:);

% bzip2
bzip2.name                  =       'bzip2';
bzip2.All_2way              =       M(10,:);
bzip2.All_4way              =       M(11,:);
bzip2.All_FA                =       M(12,:);
bzip2.All_small             =       M(13,:);
bzip2.default               =       M(14,:);
bzip2.L1_2way               =       M(15,:);
bzip2.L1_8way               =       M(16,:);
bzip2.L1_small_4way         =       M(17,:);
bzip2.L1_small              =       M(18,:);

% gobmk
gobmk.name                  =       'gobmk';
gobmk.All_2way              =       M(19,:);
gobmk.All_4way              =       M(20,:);
gobmk.All_FA                =       M(21,:);
gobmk.All_small             =       M(22,:);
gobmk.default               =       M(23,:);
gobmk.L1_2way               =       M(24,:);
gobmk.L1_8way               =       M(25,:);
gobmk.L1_small_4way         =       M(26,:);
gobmk.L1_small              =       M(27,:);

% libquantum
libquantum.name             =       'libquantum';
libquantum.All_2way         =       M(28,:);
libquantum.All_4way         =       M(29,:);
libquantum.All_FA           =       M(30,:);
libquantum.All_small        =       M(31,:);
libquantum.default          =       M(32,:);
libquantum.L1_2way          =       M(33,:);
libquantum.L1_8way          =       M(34,:);
libquantum.L1_small_4way    =       M(35,:);
libquantum.L1_small         =       M(36,:);

% omnetpp
omnetpp.name                =       'omnetpp';
omnetpp.All_2way            =       M(37,:);
omnetpp.All_4way            =       M(38,:);
omnetpp.All_FA              =       M(39,:);
omnetpp.All_small           =       M(40,:);
omnetpp.default             =       M(41,:);
omnetpp.L1_2way             =       M(42,:);
omnetpp.L1_8way             =       M(43,:);
omnetpp.L1_small_4way       =       M(44,:);
omnetpp.L1_small            =       M(45,:);

% sjeng
sjeng.name                  =       'sjeng';
sjeng.All_2way              =       M(46,:);
sjeng.All_4way              =       M(47,:);
sjeng.All_FA                =       M(48,:);
sjeng.All_small             =       M(49,:);
sjeng.default               =       M(50,:);
sjeng.L1_2way               =       M(51,:);
sjeng.L1_8way               =       M(52,:);
sjeng.L1_small_4way         =       M(53,:);
sjeng.L1_small              =       M(54,:);

% sjeng extra
sjeng.bw16                  =       M(55,:);
sjeng.bw32                  =       M(56,:);
sjeng.bw64                  =       M(57,:);