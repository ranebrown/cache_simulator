#! /bin/bash

make clean

tpath="../traces/traces_short/"
cpath="../config/"

for trace in tr1 tr2 tr3 tr4 tr5 tr6
do
    for config in default L1-2Way All-2way All-4way L1-8way L1-small L1-small-4way All-small All-FA
    do
        make run trace=$tpath$trace conf=$cpath$config.txt
    done
done

echo complete
