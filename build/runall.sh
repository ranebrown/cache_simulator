#! /bin/bash

make clean

tpath="../traces/traces_5M/"
cpath="../config/"

for trace in sjeng astar bzip2 gobmk libquantum omnetpp
do
    for config in default L1-2Way All-2way All-4way L1-8way L1-small L1-small-4way All-small All-FA
    do
        make run trace=$tpath$trace.gz conf=$cpath$config.txt
    done
done

echo complete
