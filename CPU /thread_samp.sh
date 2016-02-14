#!/bin/bash


javac GFlops.java

	
	
	for (( i = 0; i < 600; i++ ))
	do
		echo "Samples are taken for IOPS :" $i " = "
		java GFlops 4 100000000 1 >> Sample"_"600"_IOPS".txt
		sleep 0.6
		
	done

	for (( i = 0; i < 600; i++ ))
	do
		echo "Samples are taken for FLOPS:" $i " = "
		java GFlops 4 100000000 2 >> Sample"_"600"_FLOPS".txt
		sleep 0.492
		
	done
