#! /bin/bash

make clean
make
zcat < ./tr1.gz | ./sim.exe
zcat < ./tr1.gz | ./sim.exe L1-2way.txt
zcat < ./tr1.gz | ./sim.exe All-2way.txt
zcat < ./tr1.gz | ./sim.exe All-4way.txt
zcat < ./tr1.gz | ./sim.exe L1-8way.txt
zcat < ./tr1.gz | ./sim.exe L1-small.txt
zcat < ./tr1.gz | ./sim.exe L1-small-4way.txt
zcat < ./tr1.gz | ./sim.exe All-small.txt
#./sim.exe All-FA.txt
