/* ompArraySum.c uses an array to sum the values in an input file,
 *  using OpenMP, whose name is specified on the command-line.
 * Joel Adams, Fall 2005
 * for CS 374 (HPC) at Calvin College.
 * edited by Aaron Santucci for CS 374
 *		November 17, 2017 Project 7
 */

#include <stdio.h>      /* I/O stuff 	*/
#include <stdlib.h>     /* calloc, etc. */
#include <omp.h>     	/* OpenMP		*/

void readArray(char * fileName, double ** a, int * n);
double sumArray(double * a, int numValues) ;

int main(int argc, char * argv[])
{
	int  howMany;
	double sum;
	double * a;
	
	double 	startTime = 0.0, 
			ioTime = 0.0,
			sumTime =0.0,
			totalTime = 0.0;

	if (argc != 2) {
		fprintf(stderr, "\n*** Usage: arraySum <inputFile>\n\n");
		exit(1);
	}
	
	startTime = omp_get_wtime();

	readArray(argv[1], &a, &howMany);
	ioTime = omp_get_wtime() - startTime;
	
	sum = sumArray(a, howMany);
	printf("Read in: %d\n", howMany);
	sumTime = omp_get_wtime() - startTime - ioTime;
	
	totalTime = omp_get_wtime() - startTime;
	
	printf("The sum of the values in the input file '%s' is %g\n",
		   argv[1], sum);
	printf("The times are:\nTotal: %f\nI/O: %f\nSum: %f\n",
			   totalTime, ioTime, sumTime);

	free(a);

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

	#pragma omp parallel for
	for (i = 0; i < numValues; i++) {
		result += *a;
		a++;
	}

	return result;
}

