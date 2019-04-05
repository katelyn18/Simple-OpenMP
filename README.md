# Simple-OpenMP
Create an openMP program that <br />
1. initializes an array to zero for 8 threads <br />
2. adds i to the array[i] <br />
3. calculate the number of even values by using a cyclic distribution <br />
To run in the terminal: <br />
gcc -fopenmp [filename] <br />
export OMP_NUM_THREADS=8 <br />
./a.out
