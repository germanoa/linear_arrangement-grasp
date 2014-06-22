#!/bin/bash

NOW=`date "+%d%m%y%H%M%S"`
BIN=bin/la-grasp5
MY_RANDOM=1

make clean
make



for x in `seq 1 10`; do
	#for i in `echo 1 10 100 1000`; do
	for i in `echo 10000 100000`; do
		for f in `ls -1 in/`; do
			echo "$BIN $i $MY_RANDOM $f < in/$f >> out/logfile-$NOW.txt"
			$BIN $i $MY_RANDOM $f < in/$f >> out/logfile-$NOW.txt
		done
	done
done

mkdir out/results/$NOW
for i in `ls -1 in/`; do
	cat out/logfile-$NOW.txt |grep $i > out/results/$NOW/$i.txt
done
