/* proj02.c
 * CS 374 weekly project about master-worker and message-passing patterns
 * by Aaron Santucci for CS 374 at Calvin College
 */

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>	// malloc()
#include <string.h>	// strlen()

int main(int argc, char** argv) {
	int id = -1, numProcesses = -1; 
	double startTime = 0.0, totalTime = 0.0;
	startTime = MPI_Wtime();
	MPI_Status status;
	const int SIZE = (64+MPI_MAX_PROCESSOR_NAME) * sizeof(char);
	char * sendString = (char*) malloc( SIZE );
    	char * receivedString = (char*) malloc( SIZE );

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

	if ( id == 0 ) {  // process 0 is the master 
		sprintf(sendString, "%d", id);
		MPI_Send(sendString, strlen(sendString) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
		MPI_Recv(receivedString, SIZE, MPI_CHAR, numProcesses-1, 0, 
			MPI_COMM_WORLD, &status);
		totalTime = MPI_Wtime() - startTime;
		printf("%s\ntime: %f secs\n", receivedString, totalTime);
	} else {          // processes with ids > 0 are workers 
		MPI_Recv(receivedString, SIZE, MPI_CHAR, id-1, 0, 
			MPI_COMM_WORLD, &status);
		
		sprintf(sendString, "%s %d", receivedString, id);
		MPI_Send(sendString, strlen(sendString) + 1, MPI_CHAR, (id+1)%numProcesses, 
			0, MPI_COMM_WORLD);
	}
	
	free(sendString); free(receivedString);
	MPI_Finalize();
	return 0;
}
