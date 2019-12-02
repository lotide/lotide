/* Compute/draw mandelbrot set using MPI/MPE commands
 *
 * Written Winter, 1998, W. David Laverell.
 *
 * Refactored Winter 2002, Joel Adams. 
 *
 * Edited by Aaron Santucci for CS 374
 * 		October 12, 2017
 * Draws a mandelbrot set using a master-worker paradigm
 * 		using MPI prallelization and MPE graphics 			
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
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
               numProcesses = -1,
               doneProcesses = 0,
               nextRow = 0,
               processRow = 0;
    double     spacing  = 0.005,
               x        = 0.0,
               y        = 0.0,
               c_real   = 0.0,
               c_imag   = 0.0,
               x_center = 1.0,
               y_center = 0.0;

    int * recv_row = (int *) malloc(WINDOW_SIZE * sizeof(MPE_Color));
    int * send_row = (int *) malloc(WINDOW_SIZE * sizeof(MPE_Color));
	int * master_rows = (int *) malloc( WINDOW_SIZE * WINDOW_SIZE * sizeof( MPE_Color ) );
	
    MPI_Status status;

    MPE_XGraph graph;
	
	// MPI Time Variables
	double startTime = 0.0, totalTime = 0.0;
    startTime = MPI_Wtime();

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

	// create the graphic
    if (id == 0) {
      MPE_Open_graphics( &graph, MPI_COMM_WORLD,
                         getDisplay(),
                         -1, -1,
                         WINDOW_SIZE, WINDOW_SIZE, 0 );
    }
	//special case for one process
    if (numProcesses == 1) {
		for (iy = 0; iy < WINDOW_SIZE; iy++)
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
				master_rows[iy*WINDOW_SIZE + ix] = MPE_BLUE;	  
			}
			else if (n < 5) {
				master_rows[iy*WINDOW_SIZE + ix] = MPE_CYAN;
			}
			else if (n < 7) {
				master_rows[iy*WINDOW_SIZE + ix] = MPE_GREEN;
			}
			else if (n < 10) {
				master_rows[iy*WINDOW_SIZE + ix] = MPE_YELLOW;
			}
			else if (n < 40) {
				master_rows[iy*WINDOW_SIZE + ix] = MPE_RED;
			}
			else {
				master_rows[iy*WINDOW_SIZE + ix] = MPE_BLACK;
			}
         }
      }
		totalTime = MPI_Wtime() - startTime;
		printf("Finished in time %f secs.\n", totalTime);
		
		for (iy = 0; iy < WINDOW_SIZE; iy++)
		{
			for (ix = 0; ix < WINDOW_SIZE; ix++)	{
				MPE_Draw_point(graph, ix, iy, master_rows[WINDOW_SIZE*iy + ix]);
			}
		}
		
		printf("\nClick in the window to continue...\n");
		MPE_Get_mouse_press( graph, &ix, &iy, &button);
		MPE_Close_graphics( &graph );
	} 
	else 
	{
		// the master process
		if (id == 0) {
			nextRow = numProcesses-2;
			while (doneProcesses < numProcesses-1) 
			{
				MPI_Recv(recv_row, WINDOW_SIZE, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				for (ix = 0; ix < WINDOW_SIZE; ix++) {
					master_rows[(status.MPI_TAG-1)*WINDOW_SIZE + ix] = recv_row[ix];
					//MPE_Draw_point(graph, ix, status.MPI_TAG, recv_row[ix]);
				}

				if (nextRow != -1 && nextRow < WINDOW_SIZE) {
					nextRow += 1;
			  	} else {
					doneProcesses += 1;
					nextRow = -1;
				}
				
			  MPI_Send(&nextRow, 1, MPI_INT, status.MPI_SOURCE, 1, MPI_COMM_WORLD);
			}
			
			totalTime = MPI_Wtime() - startTime;
			printf("Finished in time %f secs.\n", totalTime);
			
			for (iy = 0; iy < WINDOW_SIZE; iy++)
			{
				for (ix = 0; ix < WINDOW_SIZE; ix++)	{
					MPE_Draw_point(graph, ix, iy, master_rows[WINDOW_SIZE*iy + ix]);
				}
			}
			
			printf("\nClick in the window to continue...\n");
        	MPE_Get_mouse_press( graph, &ix, &iy, &button);
			MPE_Close_graphics( &graph );
		} 
		// the worker process
		else 
		{
			processRow = id-1;
			while(processRow != -1) 
			{
				// calculate the row
				for (ix = 0; ix < WINDOW_SIZE; ix++) 
				{
					c_real = (ix - 400) * spacing - x_center;
					c_imag = (processRow - 400) * spacing - y_center;
					x = y = 0.0;
					n = 0;

					while (n < 50 && distance(x, y) < 4.0)
					{
					   compute(x, y, c_real, c_imag, &x, &y);
					   n++;
					}
					if (n < 3) {
						send_row[ix] = MPE_BLUE;	  
					}
					else if (n < 5) {
						send_row[ix] = MPE_CYAN;
					}
					else if (n < 7) {
						send_row[ix] = MPE_GREEN;
					}
					else if (n < 10) {
						send_row[ix] = MPE_YELLOW;
					}
					else if (n < 40) {
						send_row[ix] = MPE_RED;
					}
					else {
						send_row[ix] = MPE_BLACK;
					}
				}
				MPI_Send(send_row, WINDOW_SIZE, MPI_INT, 0, processRow, MPI_COMM_WORLD);
				MPI_Recv(&processRow, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
			}
		}
	}
		
	free(send_row); free(recv_row); free(master_rows);
    MPI_Finalize();
    return 0;
}