/* mpiArraySum.c uses an array to sum the values in an input file,
 *  using MPI, whose name is specified on the command-line.
 * Joel Adams, Fall 2005
 * for CS 374 (HPC) at Calvin College.
 * edited by Aaron Santucci for  CS 374
 *		November 16, 2017 Project 7
 */

#include <mpi.h>
#include <stdio.h>      /* I/O stuff */
#include <stdlib.h>     /* calloc, etc. */

void readArray(char * fileName, double ** a, int * n);
double sumArray(double * a, int numValues) ;

int main(int argc, char * argv[])
{
	int id = -1, numProcesses = -1;
	int  howMany;
	double localSum;
	double totalSum;
	double * globalArray;
	double * localArray;

	if (argc != 2) {
		fprintf(stderr, "\n*** Usage: arraySum <inputFile>\n\n");
		exit(1);
	}
	
	// MPI time variables
	double 	startTime = 0.0, 
			ioTime = 0.0,
			scatterTime = 0.0,
			sumTime =0.0,
			totalTime = 0.0;
	startTime = MPI_Wtime();

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

	// processes 0 reads in the array
	if (id == 0 )
	{
		readArray(argv[1], &globalArray, &howMany);
		printf("Read in: %d\n", howMany);
		ioTime = MPI_Wtime() - startTime;
	}
	
	MPI_Bcast(&howMany, 1, MPI_INT, 0, MPI_COMM_WORLD);
	// MPI_Barrier(MPI_COMM_WORLD);
	
	localArray = (double*) malloc( howMany * sizeof(double) );
	MPI_Scatter(globalArray, howMany/numProcesses, MPI_DOUBLE, localArray, 
				howMany/numProcesses, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	scatterTime = MPI_Wtime() - startTime - ioTime;

	localSum = sumArray(localArray, howMany);
	MPI_Reduce(&localSum, &totalSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	sumTime = MPI_Wtime() - startTime - (scatterTime + ioTime);
	
	if (id == 0 )
	{
		totalTime = MPI_Wtime() - startTime;
		
		printf("The sum of the values in the input file '%s' is %g\n",
		   argv[1], totalSum);
		printf("The times are:\nTotal: %f\nI/O: %f\nScatter: %f\nSum: %f\n",
			   totalTime, ioTime, scatterTime, sumTime);
	}

	free(localArray);
	MPI_Finalize();

	return 0;
}

/* readArray fills an array with values from a file.
 * Receive: fileName, a char*,
 *          a, the address of a pointer to an array,
 *          n, the address of an int.
 * PRE: fileName contains N, followed by N double values.
 * POST: a points to a dynamically allocated array
 *        containing the N values from fileName
 *        and n == N.
 */

void readArray(char * fileName, double ** a, int * n) {
  int count, howMany;
  double * tempA;
  FILE * fin;

  fin = fopen(fileName, "r");
  if (fin == NULL) {
    fprintf(stderr, "\n*** Unable to open input file '%s'\n\n",
                     fileName);
    exit(1);
  }

  fscanf(fin, "%d", &howMany);
  tempA = calloc(howMany, sizeof(double));
  if (tempA == NULL) {
    fprintf(stderr, "\n*** Unable to allocate %d-length array",
                     howMany);
    exit(1);
  }

  for (count = 0; count < howMany; count++)
   fscanf(fin, "%lf", &tempA[count]);

  fclose(fin);

  *n = howMany;
  *a = tempA;
}

/* sumArray sums the values in an array of doubles.
 * Receive: a, a pointer to the head of an array;
 *          numValues, the number of values in the array.
 * Return: the sum of the values in the array.
 */

double sumArray(double * a, int numValues) {
  int i;
  double result = 0.0;

  for (i = 0; i < numValues; i++) {
    result += *a;
    a++;
  }

  return result;
}

