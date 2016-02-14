/*
*	Cloud_disk_thread.c
*
*	Disk Benchmarking for AWS-EC2 Cloud.
*	
*	Output : Throughput (MB/s) and Latency (ms)
*
*
*/
#include <stdio.h>      
#include <stdlib.h>
#include <unistd.h>    
#include <sys/types.h> 
#include <pthread.h>    
#include <string.h>     
#include <sys/time.h> 
#include <time.h> 
#include <errno.h>

      
#define FILE_SIZE 100 // File size that will be created in any of blocksize.
#define ONE_B 1		// Block size of 1 byte
#define ONE_KB 1024	// Block size of 1 KByte
#define ONE_MB 1048576	// Block size of 1 Mbyte
#define ONE_US 0.000001 // covert micro-second to second
#define ONE_MS 1000	// convert time from seconds to milli-seconds

typedef struct disk_thdata // struct for thread to store basic information for writing and reading
{   int thread_no;  		// number of threads. 		
    int offset;			// starting offset of file from where read/write will be start
    int iteration;		// endind offset of file from where read/write will be end
    int filesize;		// file of 1B/1KB/1MB
   }d_thdata;

//void calculation(double final_time, int iteration,int file_size);
//void seq_read(int a);
//void seq_write(int b);
//void print_value(double time, double throughput, double speed);
//double getTimer(void (*f)(int),int block_size);


///////////////////////////////////////////////////////////////////////////

////// function for sequential read without threading. //////////////////////
void seq_read(int size)
	{	int size_of_read,i=0;
	        FILE  *f;
	        size_of_read=FILE_SIZE*ONE_MB/size;
		char *c = (char*)calloc(size_of_read,size);
	        f=fopen("disk2.txt","r");
		for(i=0;i<size_of_read;i++){
	        	fread(c,size,sizeof(char),f);     
		}    
	        fclose(f);
	}
///////////////////////////////////////////////////////////////////////////

/////////////////  Function for SEQUENTIAL WRITE without threading..//////
void seq_write(int size)
	{int size_of_write,i=0,ret;
		
	        FILE  *f;
	        size_of_write=FILE_SIZE*ONE_MB/size;
		printf("Inside Write Before Calloc : \t%d \t%d : ",size,size_of_write);
	        char *c=(char*)calloc(size_of_write,size);
		//printf("Inside Write After Calloc");
	        f=fopen("disk2.txt","w");
		for(i=0;i<size_of_write;i++){
	        	fwrite(c,size,sizeof(char),f);         
		}	        
		fclose(f);
	}

/////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

//////////////////////////// Function RANDOM READ without thread .////
void rand_read(int size)
	{       int size_r_read;
        	FILE  *f;
        	int k=0;
		int j=0;      
                size_r_read=FILE_SIZE*ONE_MB/size;
                char *c=(char*)calloc(size_r_read,size);
                f=fopen("disk3.txt","r");
		while(k<size_r_read){ 
			j = rand()%size_r_read;
			fseek(f,j*size,SEEK_SET);	
			fread(c,size,1,f);
			k++;
			
		}
		      
                fclose(f);
}
/////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////

//////////////////////////// Function RANDOM WRITE without thread .////

void rand_write(int size)
       {
		
		int size_r_write,ret;
		
        	FILE  *f;
        	int k=0;
		int j=0;      
                size_r_write=FILE_SIZE*ONE_MB/size;
		
                char *c=(char*)calloc(size_r_write,size);
	        f=fopen("disk3.txt","w+");
		while(k<size_r_write){ 
			
			j = rand()%size_r_write;
			fseek(f,j*size,SEEK_SET);	
			fwrite(c,size,1,f);
			k++;
			
		}
		fclose(f);
		//else{
		//	printf("NOT Deleted");
		//}
}
///////////////////////// All Calculation for Latancy and Speed for all Schenarios //////////////////////


////////////////////////////// Print all calculated parameter Throughput , Latency and Elapsed TIme ////////////////////

void print_value(double elapsed_time, double throughput,double latency){

			//printf("\n/////////////////////////////\n");
			//printf("\n Output of %s\t %s\t %type",block_size,op,type);
			printf("\n \telapsed-time : \t%f",elapsed_time);
			printf("\n \tThroughput : \t%f  MB/s",throughput);
			printf("\n \tLatency : \t%f ms\n\n",latency);
	
}

////////////////////////////  Caluculate Total Elapsed-Time for a function of SEQUENTIAL READ/WRITE or RANDOM READ/WRITE ..////////////////////////

double getTimer(void (*f)(int),int block_size){
		
		struct timeval s_time,e_time;
		gettimeofday(&s_time,NULL);
		double start_time = (double)s_time.tv_sec + (double)s_time.tv_usec * ONE_US;
		(*f)(block_size);
		//c_end = clock();
		gettimeofday(&e_time,NULL);
		double end_time = (double)e_time.tv_sec + (double)e_time.tv_usec * ONE_US;
		//total_time = (double)(c_end-c_start)/CLOCKS_PER_SEC;
		double total_time = end_time - start_time;
		
		return total_time;
}

/////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////// Calculate Throughtput (MB/s) and Latency (ms) ./////////////////////////////////////

void calculation(double total_time,int iteration,int size_file){

			//printf("\nFinal-Time:%f\n",total_time); 
			double disk_speed = (double)iteration/(total_time);
			double disk_latency=(double)(total_time*size_file*ONE_MS)/(iteration*ONE_MB);
			//printf("\nspeed:%f Mb/s\t,latency:%.12f ms\n",disk_speed,disk_latency);     
			print_value(total_time,disk_speed,disk_latency);
			
}



 /////////////////////////////////////////

//////////////// Threads Methods ////////////


/////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

//////////////////////////// Function SEQUENTIAL WRITE using thread .////

void seq_write_ths ( void *p )
{   int i;
    int j;
    d_thdata *data;      
    data = (d_thdata *) p;  /* type cast to a pointer to thdata */        
    FILE  *f;
          
	int no_block = (FILE_SIZE*ONE_MB/data->filesize);
        char *c=(char*)calloc(no_block,data->filesize);
        f=fopen("th1KB.txt","w+");
	for(i=0;i<no_block;i++){
	        	fwrite(c,data->filesize,sizeof(char),f);         
		}

       // fwrite(ch,data->siz,data->j,fw);         
        fclose(f);

    pthread_exit(0); /* exit */
}


/////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

//////////////////////////// Function SEQUENTIAL READ without thread .////


void seq_read_ths ( void *p )
{   int i;
    int j;
    d_thdata *data;      
    data = (d_thdata *) p;  /* type cast to a pointer to thdata */        
    FILE  *f;
	int no_block = (FILE_SIZE*ONE_MB/data->filesize);
        char *c=(char*)calloc(no_block,data->filesize);
        f=fopen("th1KB.txt","r");
	for(i=0;i<no_block;i++){
	        	fread(c,data->filesize,sizeof(char),f);         
		}

        //fread(ch,data->siz,data->j,f);         
        fclose(f);

    pthread_exit(0); /* exit */
}



/////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

//////////////////////////// Function RANDOM READ using thread .////


void rand_read_ths ( void *p )
{   int i;
    int rnd_no;
    int cnt;
    d_thdata *data;      
    data = (d_thdata *) p;  /* type cast to a pointer to thdata */        
    FILE  *f;
        int no_block = (FILE_SIZE*ONE_MB/data->filesize);     
        char *c=(char*)calloc(no_block,data->filesize);
        f=fopen("th2KB.txt","r");
        for(cnt=0;cnt<no_block;cnt++)         
	{  
    		rnd_no = rand()%no_block;
    		fseek(f, rnd_no*data->filesize, SEEK_SET );
    		fread(c,data->filesize,1,f);         
	} 
         
        fclose(f);

    pthread_exit(0); /* exit */
}

/////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

//////////////////////////// Function RANDOM WRITE using thread .////


void rand_write_ths ( void *p )
{   int i;
    int rnd_no;
    int cnt;
    d_thdata *data;      
    data = (d_thdata *) p;  /* type cast to a pointer to thdata */        
    FILE  *f;
         int no_block = (FILE_SIZE*ONE_MB/data->filesize);   
        char *c=(char*)calloc(no_block,data->filesize);
        f=fopen("th2KB.txt","w");
        for(cnt=0;cnt<no_block;cnt++)         
	{  
	    rnd_no = rand()%no_block;
	    fseek(f, rnd_no*data->filesize, SEEK_SET );
	    fwrite(c,data->filesize,1,f);         
	} 
         
        fclose(f);

    pthread_exit(0); /* exit */
}



/////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

//////////////////////////// Calculation of parameter using Thread. ////



void Thread_Calculation(int block_size,void (*f)(void *)){

	 struct timeval s_time,e_time;
	pthread_t th_1, th_2;  
	///////////////// set all strucure variable using ALL values  

	d_thdata data1, data2;
	 data1.thread_no = 1;
         data1.offset = 0;
         data1.iteration = (FILE_SIZE/2)/block_size; ///// thread -1 structure variable assignments (Half work)
         data2.thread_no = 2;    
         data2.offset = ((FILE_SIZE/2)/block_size)+1;
         data2.iteration = (FILE_SIZE)/block_size;
         data2.filesize=block_size; ////////////////////////// thread-2 structure variable assignments(another half work)
	
	gettimeofday(&s_time,NULL); // timer start 
	double start_time = (double)s_time.tv_sec + (double)s_time.tv_usec * ONE_US;// Calculate start time in seconds
	pthread_create (&th_1, NULL, (void *) & (*f), (void *) &data1); // create thread -1
        pthread_create (&th_2, NULL, (void *) & (*f), (void *) &data2); // create thread -2
	pthread_join(th_1, NULL); // join thread -1
        pthread_join(th_2, NULL); // join thread -2
	gettimeofday(&e_time,NULL); // end timer
	double end_time = (double)e_time.tv_sec + (double)e_time.tv_usec * ONE_US; //calculate end_time in seconds. 
	double total_time = end_time - start_time; // calculate total elapsed time in seconds.
	
	calculation(total_time,FILE_SIZE,block_size); /// call calculation function for throughput and latency.

}







////////////////// Main Function of function. v///////////////////////////

void main(){

	
		////////////////////////////////////////////////////////////

		/// 	Calling all Function Without Threads	 ////////////
		
		////////////////////////////////////////////////////////////

		printf("\n\n");
		
		printf("\n Output of \t1B\t Sequencial \t Write\n");
		calculation(getTimer(seq_write,ONE_B),FILE_SIZE,ONE_B);

		printf("\n Output of \t1B\t Sequencial \t Read\n");
		calculation(getTimer(seq_read,ONE_B),FILE_SIZE,ONE_B);

		printf("\n Output of \t1KB\t Sequencial \t Write\n");
		calculation(getTimer(seq_write,ONE_KB),FILE_SIZE,ONE_KB);
	
		printf("\n Output of \t1KB\t Sequencial \t Read\n");
		calculation(getTimer(seq_read,ONE_KB),FILE_SIZE,ONE_KB);
		
		printf("\n Output of \t1MB\t Sequencial \t Write\n");
		calculation(getTimer(seq_write,ONE_MB),FILE_SIZE,ONE_MB);
		
		printf("\n Output of \t1MB\t Sequencial \t Read\n");
		calculation(getTimer(seq_read,ONE_MB),FILE_SIZE,ONE_MB);
		
		//printf("\n Output of \t1B\t Random \t Write\n");
		//calculation(getTimer(rand_write,ONE_B),FILE_SIZE,ONE_B);

		//printf("\n Output of \t1B\t Random \t Read\n");
		//calculation(getTimer(rand_read,ONE_B),FILE_SIZE,ONE_B);

		printf("\n Output of \t1KB\t Random \t Write\n");
		calculation(getTimer(rand_write,ONE_KB),FILE_SIZE,ONE_KB);
	
		printf("\n Output of \t1KB\t Random \t Read\n");
		calculation(getTimer(rand_read,ONE_KB),FILE_SIZE,ONE_KB);
		
		printf("\n Output of \t1MB\t Random \t Write\n");
		calculation(getTimer(rand_write,ONE_MB),FILE_SIZE,ONE_MB);
		
		printf("\n Output of \t1MB\t Random \t Read\n");
		calculation(getTimer(rand_read,ONE_MB),FILE_SIZE,ONE_MB);

		////////////////////////////////////////////////////////

		////// 	All experiments using Threads (2) //////////////				
			
		///////////////////////////////////////////////////////

		
		printf("\n Output of \t1B\t Sequencial \t Write \t 2 threads\n");
		Thread_Calculation(ONE_B,seq_write_ths);

		printf("\n Output of \t1B\t Sequencial \t Read \t 2 threads\n");
		Thread_Calculation(ONE_B,seq_read_ths);

		printf("\n Output of \t1KB\t Sequencial \t Write \t 2 threads\n");
		Thread_Calculation(ONE_KB,seq_write_ths);
	
		printf("\n Output of \t1KB\t Sequencial \t Read \t 2 threads\n");
		Thread_Calculation(ONE_KB,seq_read_ths);

		printf("\n Output of \t1MB\t Sequencial \t Write \t 2 threads\n");
		Thread_Calculation(ONE_MB,seq_write_ths);

		printf("\n Output of \t1MB\t Sequencial \t Read \t 2 threads\n");
		Thread_Calculation(ONE_MB,seq_read_ths);

		//printf("\n Output of \t1B\t Random \t Write \t 2 threads\n");
		//Thread_Calculation(ONE_B,rand_write_ths);
	
		//printf("\n Output of \t1B\t Random \t Read \t 2 threads\n");
		//Thread_Calculation(ONE_B,rand_read_ths);

		printf("\n Output of \t1KB\t Random \t Write \t 2 threads\n");
		Thread_Calculation(ONE_KB,rand_write_ths);
	
		printf("\n Output of \t1KB\t Random \t Read \t 2 threads\n");
		Thread_Calculation(ONE_KB,rand_read_ths);
	
		printf("\n Output of \t1MB\t Random \t Write \t 2 threads\n");
		Thread_Calculation(ONE_MB,rand_write_ths);
	
		printf("\n Output of \t1MB\t Random \t Read \t 2 threads\n");
		Thread_Calculation(ONE_MB,rand_read_ths);
	

	////////////////////////////////////////////

		///// 	END PROGRAM ////////////////

	///////////////////////////////////////////////

}
