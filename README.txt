####################################

CLOUD COMPUTING

PROGRAMMING ASSIGNMENT- 1

README.txt 

####################################

Three Benchmark of AWS-EC2 Cloud done in this assignment.

All result and anlysis of the benchmarking experiment is included in Performance_evaluation.pdf.

All Programming files are included in different folder for CPU, DISK and MEMORY.


Benchmark:

1.) CPU
2.) DISK
3.) MEMORY


###############################################

#####################################

CPU - BENCHMARK

###################################


	1.) Go to the Folder Name CPU.

		cd CPU/

	2.) for GFLOPS and GIOPS of CPU for multiple threads (1/2/4)

		bash cpu_flops_iops.sh
	
	3.) If you want to store result in .txt then run following command otherwise not.
		
		 bash cpu_flops_iops.sh | tee cpu_output.txt

	
	4.) For 600 samples of FLOPS into .txt file 

		bash thread_samp.sh

###################################################

#####################################

DISK BENCHMARK

#####################################

	1.) Go to the folder name DISK

		cd DISK/

	2.) For all Result to show on console.

		bash disk_all_functions


#################################################

####################################

MEMORY BENCHMARK

####################################

	1.) Go to Folder name MEMORY

		cd MEMORY/

	2.) For Output you have to run make file 

		To compile the MEMORY BENCHMARK program use

			make
	

		To run the Memory BENCHMARK program use

			make run
	
		To remove the object file(.o file) from the current directory

			make clean
	

		
