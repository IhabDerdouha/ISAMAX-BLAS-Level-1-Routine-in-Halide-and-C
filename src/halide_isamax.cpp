// BLAS Level 1 Routine "ISAMAX": Halide implementation

// ISAMAX finds the index of the first element having maximum absolute value.
// uses unrolled loops for increment equal to 1.

// On linux, you can compile and run it like so:
// g++ halide_isamax.cpp -g -I <path/to/Halide.h> -L <path/to/libHalide.so> -lHalide -lpthread -ldl -o halide_isamax -std=c++17
// LD_LIBRARY_PATH = <path/to/libHalide.so> ./halide_isamax


// ****************************************   ISAMAX   ************************************************
// ISAMAX finds the index of the first element having maximum absolute value.
// Parameters:
// -	N is INTEGER: Number of elements in input vector.
// -	Vector is REAL array:  Array of N real elements.
// -	Incx is INTEGER: Storage spacing between elements of Vector (Default value: 1).

// NOTES: 
// -	For more details about ISAMAX:  http://www.netlib.org/lapack/explore-html/d0/d73/group__aux__blas_ga16c36ed9a25ca6e68931c4a00d2778e5.html
// -	For more details about other BLAS routines: http://www.netlib.org/blas/
// -	Halide contains a predefined function argmax(...) that could be used to implement ISAMAX, however this is an implementation from scratch.
// 	For more details about argmax: https://halide-lang.org/docs/namespace_halide.html#a6d380afde4e7d1dd1cdf9fca5b40a95c


#include "Halide.h"
#include <stdio.h>
#include <random>
#include <cmath>

using namespace Halide;
using namespace std;

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
    	cout<<"Error: Wrong number of arguments!\n";
    	exit(-1);
    }
	
	
    int isamax;
    
    // Particular case: Vector has less than N = 1 element OR the step Incx = 0.
    if (n < 1 || incx == 0)  
    	isamax = -1;
    	
    else {
    	
    	// *** Construction of a Vector containing N real numbers. ***
    	
    	// Define Func vectorFill: Used to construct a vector of N elements. This Func take x as Var.
    	Func vectorFill;
    	Var x;
    	
    	// Elements of Vector are define as follows...
    	vectorFill(x) = cast<float>(3*x-n);
    	Buffer<float> vector = vectorFill.realize({n});
    
    	// Print the Vector.
    	cout << "Vector:\n";
    	for (int i = 0; i < n; i++){
    	     cout << vector(i) << "\t";
    	}
    	cout << "\n";
    
    
    	// *** Implementation of ISAMAX ***
    	
    	// Define Func arg_max: This Func contains a Tuple(Index of max abs value, max abs value). 
    	// arg_max is initialized to the first element of Vector.
    	Func arg_max;
    	arg_max() = {0, vector(0)};
  	
  	// Initialize the Reduction Domain to [1, (n-1)/incx].
    	RDom r(1, (n-1)/incx);
    	
    	// Set the old values of index and max, and define the value of nextIndex that is affected by the step Incx.
    	Expr old_index = arg_max()[0];
    	Expr old_max = arg_max()[1];
    	Expr nextIndex = r*incx;
    	
    	// Modify the values of index and max if the condition is fulfilled. Then, set arg_max to the new Tuple.
    	Expr new_index = select(abs(old_max) < abs(vector(nextIndex)), nextIndex, old_index);
    	Expr new_max = select(abs(old_max) < abs(vector(nextIndex)), vector(nextIndex), old_max);
    	arg_max() = {new_index, new_max};
	
	// Realize the Func arg_max and extract the index and max abs value from the output.
    	Realization output = arg_max.realize();
    	Buffer<int> index = output[0];
    	Buffer<float> maxVal = output[1];
              
        // Print the Max Abs Value found within the Vector containing N reals while setting the storage spacing to Incx.  
    	cout << "Max abs value = Abs(" << maxVal(0) << ") = "<< abs(maxVal(0)) << "\n";
    	
    	isamax = index(0);
    }
    
    // Print and return ISAMAX: First index of max abs value. 
    cout << "Index of max abs value : " << isamax << "\n";
    return isamax;
    
}
