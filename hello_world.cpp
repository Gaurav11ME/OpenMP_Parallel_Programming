// Headers
#include<iostream>
#include<omp.h>

using namespace std;

// function headers
void Hello(void);

int main(int argc, char* argv[])
{
	/* Get number of threads from command line*/
	int thread_count = strtol(argv[1],NULL,10);
	// strtol will convert str to long integer
	
	# pragma omp parallel num_threads(thread_count)
	Hello();
	return 0;
}

void Hello(void)
{       
        // my_rank will store thread number   
	int my_rank = omp_get_thread_num();
	
	// thread_count here will get total number of threads
	int thread_count = omp_get_num_threads();
	cout<<"Hello from thread "<<my_rank<<" of "<<thread_count<<"\n";
}
