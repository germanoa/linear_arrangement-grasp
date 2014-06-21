#!/bin/bash

NOW=`date "+%d%m%y%H%M%S"`
BIN=bin/la-grasp4

make clean
make



for f in `ls -1 in/`; do
	for i in `echo 1 10 50 100 200`; do
		for x in `seq 1 10`; do
			echo "$BIN $i $f < in/$f >> out/logfile-$NOW.txt"
			$BIN $i $f < in/$f >> out/logfile-$NOW.txt
		done
	done
done
