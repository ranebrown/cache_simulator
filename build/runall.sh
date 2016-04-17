#! /bin/bash

make clean
make
rm ../sim_results/testresults.txt

# echo "tr1"  > ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr1.gz >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr1.gz conf=../config/L1-2way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr1.gz conf=../config/All-2way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr1.gz conf=../config/All-4way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr1.gz conf=../config/L1-8way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr1.gz conf=../config/L1-small.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr1.gz conf=../config/L1-small-4way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr1.gz conf=../config/All-small.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr1.gz conf=../config/All-FA.txt >> ../sim_results/testresults.txt
#
# echo "tr2"  >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr2.gz >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr2.gz conf=../config/L1-2way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr2.gz conf=../config/All-2way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr2.gz conf=../config/All-4way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr2.gz conf=../config/L1-8way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr2.gz conf=../config/L1-small.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr2.gz conf=../config/L1-small-4way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr2.gz conf=../config/All-small.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr2.gz conf=../config/All-FA.txt >> ../sim_results/testresults.txt
#
# echo "tr3"  >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr3.gz >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr3.gz conf=../config/L1-2way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr3.gz conf=../config/All-2way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr3.gz conf=../config/All-4way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr3.gz conf=../config/L1-8way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr3.gz conf=../config/L1-small.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr3.gz conf=../config/L1-small-4way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr3.gz conf=../config/All-small.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr3.gz conf=../config/All-FA.txt >> ../sim_results/testresults.txt
#
# echo "tr4"  >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr4.gz >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr4.gz conf=../config/L1-2way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr4.gz conf=../config/All-2way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr4.gz conf=../config/All-4way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr4.gz conf=../config/L1-8way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr4.gz conf=../config/L1-small.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr4.gz conf=../config/L1-small-4way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr4.gz conf=../config/All-small.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr4.gz conf=../config/All-FA.txt >> ../sim_results/testresults.txt
#
# echo "tr5"  >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr5.gz >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr5.gz conf=../config/L1-2way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr5.gz conf=../config/All-2way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr5.gz conf=../config/All-4way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr5.gz conf=../config/L1-8way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr5.gz conf=../config/L1-small.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr5.gz conf=../config/L1-small-4way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr5.gz conf=../config/All-small.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr5.gz conf=../config/All-FA.txt >> ../sim_results/testresults.txt

# echo "tr6"  >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr6.gz >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr6.gz conf=../config/L1-2way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr6.gz conf=../config/All-2way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr6.gz conf=../config/All-4way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr6.gz conf=../config/L1-8way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr6.gz conf=../config/L1-small.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr6.gz conf=../config/L1-small-4way.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr6.gz conf=../config/All-small.txt >> ../sim_results/testresults.txt
# make run trace=../traces/traces_short/tr6.gz conf=../config/All-FA.txt >> ../sim_results/testresults.txt

echo "sjeng 5M"  >> ../sim_results/testresults.txt
make run trace=../traces/traces_5M/sjeng.gz      >> ../sim_results/testresults.txt
make run trace=../traces/traces_5M/sjeng.gz conf=../config/L1-2way.txt >> ../sim_results/testresults.txt
make run trace=../traces/traces_5M/sjeng.gz conf=../config/All-2way.txt >> ../sim_results/testresults.txt
make run trace=../traces/traces_5M/sjeng.gz conf=../config/All-4way.txt >> ../sim_results/testresults.txt
make run trace=../traces/traces_5M/sjeng.gz conf=../config/L1-8way.txt >> ../sim_results/testresults.txt
make run trace=../traces/traces_5M/sjeng.gz conf=../config/L1-small.txt >> ../sim_results/testresults.txt
make run trace=../traces/traces_5M/sjeng.gz conf=../config/L1-small-4way.txt >> ../sim_results/testresults.txt
make run trace=../traces/traces_5M/sjeng.gz conf=../config/All-small.txt >> ../sim_results/testresults.txt
make run trace=../traces/traces_5M/sjeng.gz conf=../config/All-FA.txt >> ../sim_results/testresults.txt

echo $'\a\a\a\a\a'
echo "Done running test scripts"
