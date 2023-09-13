// Headers
#include<iostream>
#include<cmath>
#include<omp.h>

using namespace std;

// function headers
double f(double x);
double Trap(double a, double b, int n);

int main(int argc, char* argv[])
{	
	
	double a,b;
	int n;
	int thread_count;
	double full_integrand;
	thread_count = strtol(argv[1], NULL,10);
	cout<<"Enter a, b, and n in that order"<<"\n";
	cin>>a;
	cout<<"a = "<<a<<"\n";
	cin>>b;
	cout<<"b = "<<a<<"\n";
        cin>>n;
	cout<<"n = "<<a<<"\n";
	
	# pragma omp parallel num_threads(thread_count)
	{
		double my_integrand;
		my_integrand = Trap(a,b,n);
		/* at pragma omp critical, each thread waits for the other threads to
		complete the operation. The summing happens sequentially.
		*/
		# pragma omp critical
		full_integrand = full_integrand + my_integrand;
	}
	cout<<"The value of the integrand is "<<full_integrand<<"\n";
	
	return 0;
	
	
	
	
	
}

double Trap(double a, double b, int n)
{
	double h;
	double local_a, local_b;
	int i, local_n;
	double x, local_integ;
	
	// Calculating step size
	h = (b-a)/n;
	
	// my_rank will store the thread number
	int my_rank = omp_get_thread_num();
	
	// thread_count will store total number of threads
	int thread_count = omp_get_num_threads();
	
	// local number of trapezoids
	local_n = n/thread_count;
	
	// local left extent
	local_a = a + my_rank*local_n*h;
	
	// local right extent
	local_b = local_a + local_n*h;
	
        // initializing local sum
        local_integ = 0.5*(f(local_a)+f(local_b));
        
        /* Loop to update local_integ
           Loop will run from i=1 to i=local_n-1, increasing by 1 in each iteration
           local_integ will get updated by summing the second term in rhs to its 
           previous iteration value
        */
        for(i=1; i<=local_n-1; i++)
        {
        	x = local_a + i*h;
        	local_integ = local_integ + f(x);
        }
        // updating local_integ value by multiplying its current value (on rhs) to step-size
        local_integ = h*local_integ;
        
        # pragma omp critical
        cout<<"for thread "<<my_rank<<" the local integrand is "<<local_integ<<" \n";
        return local_integ;
        
        
}/* Trap */

double f(double x)
{
	return x-x*x;
}


