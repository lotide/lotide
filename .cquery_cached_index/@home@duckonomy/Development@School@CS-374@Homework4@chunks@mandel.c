/* Compute/draw mandelbrot set using MPI/MPE commands
 *
 * Written Winter, 1998, W. David Laverell.
 *
 * Refactored Winter 2002, Joel Adams. 
 *
 * Edited by Aaron Santucci for CS 374
 * 		October 12, 2017
 * Draws a mandelbrot set using a parallel chunk loop paradigm
 * 		using MPI prallelization and MPE graphics 			
 */

#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>	// malloc()
#include <mpi.h>
#include <mpe.h>
#include "display.h"


/* compute the Mandelbrot-set function for a given
 *  point in the complex plane.
 *
 * Receive: doubles x and y,
 *          complex c.
 * Modify: doubles ans_x and ans_y.
 * POST: ans_x and ans_y contain the results of the mandelbrot-set
 *        function for x, y, and c.
 */
void compute(double x, double y, double c_real, double c_imag,
              double *ans_x, double *ans_y)
{
        *ans_x = x*x - y*y + c_real;
        *ans_y = 2*x*y + c_imag;
}

/* compute the 'distance' between x and y.
 *
 * Receive: doubles x and y.
 * Return: x^2 + y^2.
 */
double distance(double x, double y)
{
        return x*x + y*y;
}


int main(int argc, char* argv[])
{
    const int  WINDOW_SIZE = 1024;

    int        n        = 0,
               ix       = 0,
               iy       = 0,
               button   = 0,
               id       = 0,
				numProcesses = -1;
    double     spacing  = 0.005,
               x        = 0.0,
               y        = 0.0,
               c_real   = 0.0,
               c_imag   = 0.0,
               x_center = 1.0,
               y_center = 0.0;

    MPE_XGraph graph;
	
	double startTime = 0.0, totalTime = 0.0;
    startTime = MPI_Wtime();
	
    MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);
	
	int * chunkPoints = (int *) malloc( ((WINDOW_SIZE * WINDOW_SIZE * sizeof( MPE_Color)) / numProcesses ) );
	int * chunkFinal = (int *) malloc( WINDOW_SIZE * WINDOW_SIZE * sizeof( MPE_Color ) );

	
	int chunkSize = WINDOW_SIZE / numProcesses;
	int i = 0;
	
    for (iy = id*chunkSize; iy < (id+1)*chunkSize; iy++)
    {
       for (ix = 0; ix < WINDOW_SIZE; ix++)
       {
          c_real = (ix - 400) * spacing - x_center;
          c_imag = (iy - 400) * spacing - y_center;
          x = y = 0.0;
          n = 0;

          while (n < 50 && distance(x, y) < 4.0)
          {
             compute(x, y, c_real, c_imag, &x, &y);
             n++;
          }

          if (n < 3) {
             chunkPoints[(i) * WINDOW_SIZE + ix] = MPE_BLUE;	  
          }
		   else if (n < 5) {
			  chunkPoints[(i) * WINDOW_SIZE + ix] = MPE_CYAN;
		  }
		   else if (n < 7) {
			  chunkPoints[(i) * WINDOW_SIZE + ix] = MPE_GREEN;
		  }
		   else if (n < 10) {
			  chunkPoints[(i) * WINDOW_SIZE + ix] = MPE_YELLOW;
		  }
		   else if (n < 40) {
			  chunkPoints[(i) * WINDOW_SIZE + ix] = MPE_RED;
		  }
		  else {
             chunkPoints[(i) * WINDOW_SIZE + ix] = MPE_BLACK;
          }
       }
		i++;
    }
	
	MPI_Gather(chunkPoints, (WINDOW_SIZE * WINDOW_SIZE) / numProcesses, MPI_INT, chunkFinal, (WINDOW_SIZE * WINDOW_SIZE) / numProcesses, MPI_INT, 0, MPI_COMM_WORLD);
	
    // Process 0 draws the mandelbrot set and prints the time
    if (id == 0) 
	{
		MPE_Open_graphics( &graph, MPI_COMM_WORLD, 
                         getDisplay(),
                         -1, -1,
                         WINDOW_SIZE, WINDOW_SIZE, 0 );
		
		totalTime = MPI_Wtime() - startTime;
		printf("Finished in time %f secs.\n", totalTime);
		
		for (iy = 0; iy < WINDOW_SIZE; iy++)
		{
			for (ix = 0; ix < WINDOW_SIZE; ix++)	{
				MPE_Draw_point(graph, ix, iy, chunkFinal[WINDOW_SIZE*iy + ix]);
			}
		}
		
		printf("\nClick in the window to continue...\n");
        MPE_Get_mouse_press( graph, &ix, &iy, &button );
		MPE_Close_graphics( &graph );
    }

	free(chunkPoints); free(chunkFinal);
    MPI_Finalize();
    return 0;
}

