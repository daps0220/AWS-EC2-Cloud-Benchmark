/*
*
*	Program is for analyzing the Memory Benchmarking 
*	Throughput(MB/s) and Latency(ms)
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h> 

/// Structure for maintaining  all data for read/write into memory
struct m_th_data 
{
    char *block_size;//block  block size
	char *temp; // store read result.
    int s_offset;   // s_offseting offset
    int e_offset;	//  ending offset
    int access_type;	/// access type is random(2) /sequential (1)
};


//////////////////////////////////////////
////////////////////////////////

/// Function for read/Write of SEQUENTIAL and RANDOM Access of Memory.

/////////////////////////////////////////////////////////////////////////


void thread_all ( void * p)
{
    struct m_th_data *data = (struct m_th_data *) p;  
    long rnd_no = 0; // random number for random access and for sequrntial it's starting point
   
	while(data->s_offset< data->e_offset)
    {
        rnd_no = (long)data->s_offset; 
        if(data->access_type == 2) {  ///// if access type is random then generate random number
            rnd_no = rand()%(data->e_offset); /// random number is generating
        }
	if(rnd_no>sizeof(data->block_size))
		rnd_no=rnd_no%sizeof(data->block_size); ///// generated no is beyond the block size 	
	memset((data->block_size + rnd_no),'a',1);
        (data->s_offset)++;
    }
    while(data->s_offset < data->e_offset)  ///// read data from data structre and put into one char array.
    {
        rnd_no = (long)data->s_offset;
        if(data->access_type == 2) {
		rnd_no = rand()%(data->e_offset);
        }
        
	data->temp = strchr((data->block_size + rnd_no), '1');
        
	(data->s_offset)++;
    }
    
    pthread_exit(0); // exit 
}

int main(void){

	struct timeval start_time, end_time;
    	//struct timezone zone;
	pthread_t th_1, th_2;
	int no_thread, d_size, accesstype, b_size;
	double roundTime,s_time,e_time;
	long itr = 1000000; /// total no. of iterations calculated. 


	/// input all parameter
	printf("Enter number of Threads:");
	scanf("%d",&no_thread);
	printf("Enter data size (1: 1B, 2: 1KB, 3: 1MB): ");
	scanf("%d",&d_size);
	printf("Enter access type (1: Sequential, 2: Random): ");
	scanf("%d",&accesstype);	
	

	//make block according to input
	switch(d_size){
		case 1: b_size = 1;
			break;
		case 2: b_size = 1024;
			break;
		case 3: b_size =1048576;	
	}


	/// for single thread
	if (no_thread == 1){
		struct m_th_data data;
		data.access_type=accesstype;
		
		data.block_size = (char *) malloc(b_size);
		data.s_offset = 0;
        	data.e_offset = itr;
		
		gettimeofday(&start_time,NULL);
		s_time = (double)start_time.tv_sec+(double)start_time.tv_usec*0.000001;

        	pthread_create (&th_1, NULL, (void *) &thread_all, (void *) &data);
        	
		gettimeofday(&end_time,NULL);
		
		e_time = (double)end_time.tv_sec+(double)end_time.tv_usec*0.000001;		

		roundTime=e_time-s_time;  
		      	

		free(data.block_size);
        		
	}
	//// for 2 thread.
	else{
		struct m_th_data data1, data2;
		
		data1.access_type=accesstype;
		data1.block_size = (char *) malloc(b_size);
		data1.s_offset = 0;
    		data1.e_offset = itr/2;
		
		data2.access_type=accesstype;
		data2.block_size = (char *) malloc(b_size);
		data2.s_offset = itr/2;
		data2.e_offset = itr;

		gettimeofday(&start_time,NULL);   

    		pthread_create (&th_1, NULL, (void *) &thread_all, (void *) &data1);
    		pthread_create (&th_2, NULL, (void *) &thread_all, (void *) &data2);
    
    		pthread_join(th_1, NULL);
    		pthread_join(th_2, NULL);
    
		gettimeofday(&end_time,NULL);    
		roundTime=end_time.tv_usec-start_time.tv_usec;    

    		free(data1.block_size);
    		free(data2.block_size);
	}
	

	///// calculate all parameters..

	
	printf("\nstart_time: %lf seconds\n",s_time);
	printf("\nend_time: %lf seconds\n",e_time);
	printf("\nTotalTime: %lf seconds\n",roundTime);
  	
	//float rt_milli = (float)roundTime/1000;
  	//float rt_sec = (float)rt_milli/1000;
  	printf("Latency: sec: %.12f \n",(roundTime*b_size*1000)/itr);
//  	float throughput = (float)(1/rt_sec);
	double throughput = (double)(itr/(1000*roundTime*b_size)/1000);	
  	printf("Throughput: %f MB/sec\n\n",throughput);
	   
	return 0;
} 
