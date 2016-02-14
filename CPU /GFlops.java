import java.util.*;;

class CPUThreads extends Thread{ // Thread class for FLOPS and IOPS for Multi-Threading

	int itr;
	int type;
	CPUThreads(int itr,int type ){ // Constructer to initlize no. of iteration and types for IOPS and FLOPS
		this.itr = itr;  // No. of iteration 
		this.type = type;  // type 1 = IOPS and type = 2 FLOPS
		
	}
	
	public void IOPS(int a, int b){ // Functions to calculate IOPS for two integer values
		int loop = 0;
		for(loop=0;loop<itr;loop++){
			a=a*b;
			b=b*a;
			a=a*itr;
			b=b*loop;
					
		}
	}
		
	public void FLOPS(float a,float b){ // Functions to calculate FLOPS  for two float value.
		int loop = 0;
		for(loop=0;loop<itr;loop++){
			a=a*b;
			b=b*a;
			a=a*itr;
			b=b+a;
		}
	}
	
	@Override
	public void run() { // Method perform while thread is calling by start() method.
		// TODO Auto-generated method stub
	
		if(type == 1){ // choose IOPS as type of operation.
			int a=34,b=13;
			IOPS(a,b);
		}
		if(type == 2){ // choose FLOPS as type of operation
			float a=12.5f,b=10.6f;
			FLOPS(a,b);
		}
		
		
	}
	
}


// Main Class to calcilate GFLOPS and GIOPS

public class GFlops {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner s = new Scanner(System.in);
		//System.out.println("Enter No: Thread : ");
		//int no_th =  s.nextInt();
		int no_th = Integer.parseInt(args[0]); 			// Input no. of threads(1/2/4) using command line arguments
	//	System.out.println("Enter No: Iteration : ");
		//int itration = s.nextInt();
		int itration = Integer.parseInt(args[1]);		// Input no. of iteration for GFLOPS and GIOPS
	//	System.out.println("Enter No: operation Type (1 = integer/2 = float): ");
		//int op_type = s.nextInt();
		int op_type = Integer.parseInt(args[2]);  // Input type for selecting IOPS  = 1 and FLOPS = 2
		int itr = itration/no_th; 		 //itr operation for each thread. 
		CPUThreads[] th = new CPUThreads[no_th]; // array of CPUThreads class 
		
		long s_time = System.currentTimeMillis(); // start timer for calculating FLOPS and IOPS.
		//System.out.println("Starting Time : " +s_time);
		
		int cnt =0;
		while(cnt<no_th){
			th[cnt] = new CPUThreads(itr,op_type);   // create an object of CPUThreads class
			th[cnt].start(); 			// start thread.
			cnt++;
		}
		try{
		cnt = 0;
		while(cnt<no_th){
			th[cnt].join();  // join all threads.
			cnt++;
		}
		}catch(Exception e){
			e.printStackTrace();
		}
		
		long e_time = System.currentTimeMillis();  /// stop timer after calculations.
		//System.out.println("End Time : " + e_time);
		//System.out.println("Stop Time : " + (e_time - s_time)); 
		long total_time = e_time - s_time; 			// calculate total time taken by operation by CPU
		float FLOPS = 0,GFLOPS = 0,IOPS=0,GIOPS=0;
		if(op_type == 2){
			FLOPS = (float)((itration*5)/total_time)*1000*16; 	// No. of FLOPS = (total iterations * no. of operation)/total time)*1000(ms) * IPC
		
			GFLOPS = (float)(FLOPS/1E9);			 	// converting FLOPS to GFLOPS
			System.out.println("\nGFLOPS : " +GFLOPS + "\n");
		}
		if(op_type == 1){
			IOPS = (float)((itration*5)/total_time)*1000*16; //Formula for calculating IOPS
		
			GIOPS = (float)(IOPS/1E9); 		// converting IOPS to GIOPS.
			//System.out.println("IOPS : " +IOPS);
			System.out.println("\nGIOPS : " +GIOPS+ "\n");
		}
	}

}
