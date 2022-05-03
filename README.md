# ISAMAX-BLAS-Level-1-Routine-in-Halide-and-C
This is an implementation of a BLAS (Level 1) routine called "ISAMAX" which finds the index of the first element having maximum absolute value, in both Halide and C.

## 1. Description
This repository mainly contains:
  - ./src: This folder includes the implementation of the routine ISAMAX in Halide and C and the Script that compiles and runs the programs.
  - ./buildLogs: This folder contains log files resulting from building Halide from source.

## 2. Requirements
- Build Halide from source or install the binaries. For more details: https://github.com/halide/Halide/blob/master/README.md.
- Install the following packages: g++, gcc, pyhton3, python-to-python3 using ```sudo apt install <name-of-package>```\.
- Clone this repository and use the command ```cd``` to access the folder ```./src```\.

## 3. How it works?
### 3.1. Option 1: Using Script.py
- While in ```./src```\, run the following command ```python Script.py <path/to/Halide.h> <path/to/libHalide.so> [N] [N Incx]```\.
- The paths to Halide files is obligatory, however the arguments [N] and [N Incx] are optional (Check the implementaion for more details about these parameters).
- There are 3 possible scenarios while running the script:
  - #### No parameters: In this case, the execution will use the default values of N and Incx. Here is an example of the running command if Halide was built from source: ```python Script.py ../Halide-14.0.0/build/include/ ../Halide-14.0.0/build/src/```\.
  - #### [N] parameter only: In this case, the execution will use the entered value of N and the default one of Incx. Here is an example of the running command if Halide was built from source (N is set to 6): ```python Script.py ../Halide-14.0.0/build/include/ ../Halide-14.0.0/build/src/ 6```\.
  - #### [N Incx]: In this case, the execution will use the entered values of N and Incx. Here is an example of the running command if Halide was built from source (N is set to 6 and Incx to 2): ```python Script.py ../Halide-14.0.0/build/include/ ../Halide-14.0.0/build/src/ 6 2```\.
  ##### Note: Any other scenario leads to an error.

### 3.2. Option 2: Compile and run Halide and C codes 
Instead of using Script.py, it is possible to run the programs seperatly. For more details, check the header section within each code and follow the stated instructions. Note that these programs follow the same logic in parsing arguments N and Incx as explained in Option 1.



