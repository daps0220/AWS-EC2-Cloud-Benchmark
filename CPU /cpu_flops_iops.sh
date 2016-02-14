#!/bin/bash

#bash file to run GFlops.java and get all results.

#run it like bash cpu_flops_iops.sh | tee flops_iops.txt

javac GFlops.java

	echo "---------------------------------------------------------------------"
	echo
	echo "		GFLOPS and GIOPS for 1-thread"
	java GFlops 1 100000000 2 # GFLOPS for 100000000 iterations
	java GFlops 1 100000000 1 # GIOPS for 100000000 iterations
	echo "---------------------------------------------------------------------"
	echo "		GFLOPS and GIOPS for 2-thread"
	echo
	java GFlops 2 100000000 2 # GFLOPS for 100000000 iterations
	java GFlops 2 100000000 1 # GIOPS for 100000000 iterations
	echo "----------------------------------------------------------------------"
	echo "		GFLOPS and GIOPS for 4-thread"
	echo
	java GFlops 4 100000000 2 # GFLOPS for 100000000 iterations
	java GFlops 4 100000000 1 # GIOPS for 100000000 iterations
	echo "----------------------------------------------------------------------"

