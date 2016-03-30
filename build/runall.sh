#! /bin/bash

make clean
make 
./sim.exe 
./sim.exe L1-2way.txt
./sim.exe All-2way.txt
./sim.exe All-4way.txt
./sim.exe L1-8way.txt
./sim.exe L1-small.txt
./sim.exe L1-small-4way.txt
./sim.exe All-small.txt
#./sim.exe All-FA.txt
