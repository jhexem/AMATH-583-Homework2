This homework is arranged into one function .cpp file titled "HW2Funcs.cpp", one
header file containing all of the function specifications from "HW2Funcs.cpp" called
"refBLAS.hpp", and five individual main files for problems 1 through 5 titled 
"Problem1Main.cpp", "Problem2Main.cpp", "Problem3Main.cpp", "Problem4Main.cpp", and 
"Problem5Main.cpp". 

The performance plots for this assignment are contained in .pdf files called 
"Problem1Plot.pdf", "Problem2Plot.pdf", "Problem3Plot.pdf", "Problem4Plot.pdf", 
"Problem5Plot1.pdf", "Problem5Plot2.pdf", and "Problem5Plot3.pdf". The first two 
extra credit problems are in "ExtraCreditProblems1and2.txt" and the third extra credit
problem is in "ExtraCreditProblem3.pdf". The shared library file is called 
"librefBLAS.so".

Each of the main files for problems 1 through 5 will output the resulting times in
MFLOPS into a .csv file called "results.csv". Then this data can be read and plotted
using the python script called "PlotResults.py". 

To compile and run each main file for each problem, we must run the following code:

g++ -c -std=c++14 HW2Funcs.cpp
g++ -c -std=c++14 Problem1Main.cpp
g++ HW2Funcs.o Problem1Main.o -o Problem1Main
./Problem1Main

To compile and run each main file for each problem using the shared library, we must
run the following code:

g++ -std=c++14 -o Problem1Main -I. Problem1Main.cpp -L. -lrefBLAS