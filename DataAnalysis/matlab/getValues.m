function [ res ] = getValues( trace )
% takes a specific memory configuration i.e. astar.default and returns a
% struct containing specific values from the simulation for that
% configuration

res.L1size              =       trace(1);
res.L1ways              =       trace(2);
res.L1block             =       trace(3);
res.L2size              =       trace(4);
res.L2ways              =       trace(5);
res.L2block             =       trace(6);
res.execTime            =       trace(7);
res.totalRefs           =       trace(8);
res.numInstRefs         =       trace(9);
res.numDataRefs         =       trace(10);
res.numCycReads         =       trace(11);
res.numCycWrites        =       trace(12);
res.numCycInst          =       trace(13);
res.cpi                 =       trace(14);
res.idealExecT          =       trace(15);
res.idealCPI            =       trace(16);
res.idealMisAExecT      =       trace(17);
res.idealMisACPI        =       trace(18);
res.L1ihits             =       trace(19);
res.L1dhits             =       trace(20);
res.L2hits              =       trace(21);
res.L1imiss             =       trace(22);
res.L1dmiss             =       trace(23);
res.L2miss              =       trace(24);
res.L1iTotReqs          =       trace(25);
res.L1dTotReqs          =       trace(26);
res.L2TotReqs           =       trace(27);
res.L1iKicks            =       trace(28);
res.L1dKicks            =       trace(29);
res.L2Kicks             =       trace(30);
res.L1iDrtyKcks         =       trace(31);
res.L1dDrtyKcks         =       trace(32);
res.L2DrtyKcks          =       trace(33);
res.L1iVChit            =       trace(34);
res.L1dVChit            =       trace(35);
res.L2VChit             =       trace(36);
res.L1Cost              =       trace(37);
res.L2Cost              =       trace(38);
res.mainMemCost         =       trace(39);
res.totCost             =       trace(40);

end

