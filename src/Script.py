import os
import sys
import subprocess

# Function that compiles and runs halide_isamax.
def launch_halide():

    print("################        ISAMAX in Halide      #################\n") 
    
    # Compiling halide_isamax.cpp (Necessary arguments: <path/to/Halide.h> and <path/to/libHalide.so>)
    os.system("g++ halide_isamax.cpp -g -I {} -L {} -lHalide -lpthread -ldl -o ./halide_isamax".format(sys.argv[1], sys.argv[2]))
  
    # Retrieve ISAMAX arguments from command line and run the program
    if (len(sys.argv) == 4):
        # Specify the argument N
    	halide_subproc = subprocess.run("LD_LIBRARY_PATH={} ./halide_isamax {}".format(sys.argv[2], sys.argv[3]), shell=True)
    	
    elif (len(sys.argv) == 5):
    	# Specify the arguments N and Incx
    	halide_subproc = subprocess.run("LD_LIBRARY_PATH={} ./halide_isamax {} {}".format(sys.argv[2], sys.argv[3], sys.argv[4]), shell=True)
    
    elif (len(sys.argv) < 3 or len(sys.argv) > 4):
    	print("Error: Wrong number of arguments!\n");
   
    else:
        # Default arguments (N = 5, Incx = 1)

    	halide_subproc = subprocess.run("LD_LIBRARY_PATH={} ./halide_isamax".format(sys.argv[2]), shell=True)
    
    return halide_subproc.returncode
    
    
# Function that compiles and runs c_isamax.
def launch_c(): 

    print("################        ISAMAX in C        ####################\n")
    
    # Compiling c_isamax.c
    os.system("gcc c_isamax.c -o ./c_isamax ") 
    
    # Retrieve ISAMAX arguments from command line and run the program
    if (len(sys.argv) == 4):
        # Specify the argument N
    	c_subproc = subprocess.run("./c_isamax {}".format(sys.argv[3]), shell=True)  
    	
    elif (len(sys.argv) == 5):
        # Specify the arguments N and Incx
    	c_subproc = subprocess.run("./c_isamax {} {}".format(sys.argv[3], sys.argv[4]), shell=True)  
    
    elif (len(sys.argv) < 3 or len(sys.argv) > 4):
    	print("Error: Wrong number of arguments!\n");
   
    else:
        # Default arguments (N = 5, Incx = 1)
    	c_subproc = subprocess.run("./c_isamax", shell=True)
    
    return c_subproc.returncode
 
    	
# Function that compares the returned values of both executions.
def compare(): 

    # Run halide_isamax and c_isamax
    halide_isamax = launch_halide()
    print("\n\n")
    c_isamax = launch_c()
    

    # Compare the results
    if (c_isamax == halide_isamax): print("\n\nSuccess: Results from C and Halide match!\n")
    else: print("\n\nError: Results from C and Halide didn't match!\n")


# Start the execution.
compare()



    

