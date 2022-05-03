// BLAS Level 1 Routine "ISAMAX": C implementation.

// ISAMAX finds the index of the first element having maximum absolute value.
// uses unrolled loops for increment equal to 1.

// On linux, you can compile and run it like so:
// g++ c_isamax.c -o c_isamax 
// ./c_isamax


// ****************************************   ISAMAX   ************************************************
// ISAMAX finds the index of the first element having maximum absolute value.
// Parameters:
// -	N is INTEGER: Number of elements in input vector.
// -	Vector is REAL array:  Array of N real elements.
// -	Incx is INTEGER: Storage spacing between elements of Vector (Default value: 1).

// NOTES: 
// -	For more details about ISAMAX:  http://www.netlib.org/lapack/explore-html/d0/d73/group__aux__blas_ga16c36ed9a25ca6e68931c4a00d2778e5.html
// -	For more details about other BLAS routines: http://www.netlib.org/blas/ 


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//Default parameters' values
#define N 5
#define Incx 1


int main(int argc, char **argv) {
    
    int n = N;
    int incx = Incx;
    
    // Retrieving arguments from command line
    if (argc == 2) 
    	n = atoi(argv[1]);
    	
    else if (argc == 3) {
    	n = atoi(argv[1]);
     	incx = atoi(argv[2]);
    }
    
    else if (argc != 1) {
    	printf("Error: Wrong number of arguments!\n");
    	exit(-1);
    }
	
	
    int isamax;
    
    // Particular case: Vector has less than N = 1 element OR the step Incx = 0.
    if (n < 1 || incx == 0)  
    	isamax = -1;
    	
    else {
    	
    	// *** Construction and printing of a Vector containing N real numbers. ***
    	
    	float vector[n];
    
    	printf("Vector:\n");
    	for (int i = 0; i < n; i++){
    	     vector[i] = 3*i-n;
    	     printf("%.2f\t", vector[i]);
    	}
    	printf("\n");
    	
    	
    	// *** Implementation of ISAMAX ***
    	
    	// Initialize the index and max value to the first element of Vector.
    	int index = 0;
    	float maxVal = vector[0];
	
	// Loop for the rest of Vector while using incx as an increment.
	for (int i = incx; i < n; i+=incx){
	    // Modify the values of index and max value when the condition is fulfilled.
	    if (fabs(vector[i]) > fabs(maxVal) ){
	    	index = i;
	    	maxVal = vector[i];
	   }
	}
  
        // Print the Max Abs Value found within the Vector containing N reals while setting the storage spacing to Incx.  
    	printf("Max abs value = Abs( %.2f ) = %.2f \n", maxVal, fabs(maxVal));
    	
    	isamax = index;
    }
    
    // Print and return ISAMAX: First index of max abs value. 
    printf("Index of max abs value : %d \n", isamax);
    return isamax;
  
}
