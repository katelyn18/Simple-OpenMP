/*
Katelyn Jaing
Hector Medina
CPSC 479-01
Homework 4: 
	Problem 1: initialize an array of size 32 to 0
	Problem 2: add i to array[ i ]
	Problem 3: add all even numbers together

gcc -fopenmp <filename>
export OMP_NUM_THREADS=8
./a.out
*/

#include <stdio.h>
#include <omp.h>

int main()   { 
	int array[ 32 ]; 
	int thread_id, local_sum, sum = 0;

	//******************PROBLEM 1******************//
	printf( "******************PROBLEM 1******************\n" );
	#pragma omp parallel shared( thread_id, array )
	{
		thread_id = omp_get_thread_num();

		//use 4 because 8 threads each working 4 times = 32 numbers
		#pragma omp for schedule( static, 4 )
		for( int i = 0; i < 32; i++ ){
			array[ i ] = 0;
			printf( "thread_id: %d, array[ %d ] = %d\n", thread_id, i, array[ i ] );
		}
		
	}

	printf( "******************PROBLEM 2******************\n" );
	//******************PROBLEM 2******************//
	//add i to array[ i ]
	#pragma omp for
	for( int i = 0; i < 32; i++ ){
		array[ i ] += i;
		printf( "array[%d] = %d\n", i, array[ i ] );
	}

	printf( "******************PROBLEM 3******************\n" );
	//******************PROBLEM 3******************//
	#pragma omp parallel private( local_sum ) shared( array )
	{
		thread_id = omp_get_thread_num();
		local_sum = 0;	//each thread will have own local_sum
		
		//use 1 because 8 threads looking one at a time in a cycle
		//thread1 = 1 time, thread2 = 1 time, ..., thread8 = 1 time, thread1 = 1 time again, etc.
		#pragma omp for schedule( static, 1 )
		for( int i = 0; i < 32; i++ ){
			if( array[ i ] % 2 == 0 ){
				local_sum += array[ i ];
				printf( "thread_id %d, array[ %d ] %d\n", thread_id, i, local_sum );
			}
		}

		#pragma omp critical
		{
			sum += local_sum;
		}
	}
	printf( "Sum of all even: %d\n", sum );

	
	return 0;
}







