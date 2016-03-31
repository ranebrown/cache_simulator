#! /bin/bash

make clean
make
zcat < ../trace_short/tr1.gz | ./sim.exe
zcat < ../trace_short/tr1.gz | ./sim.exe ../config/L1-2way.txt
zcat < ../trace_short/tr1.gz | ./sim.exe ../config/All-2way.txt
zcat < ../trace_short/tr1.gz | ./sim.exe ../config/All-4way.txt
zcat < ../trace_short/tr1.gz | ./sim.exe ../config/L1-8way.txt
zcat < ../trace_short/tr1.gz | ./sim.exe ../config/L1-small.txt
zcat < ../trace_short/tr1.gz | ./sim.exe ../config/L1-small-4way.txt
zcat < ../trace_short/tr1.gz | ./sim.exe ../config/All-small.txt
#./sim.exe All-FA.txt
