/* Parallelization:  Sieve of Eratosthenes
 * By Aaron Weeden, Shodor Education Foundation, Inc.
 * January 2012
 *
 * Hybrid code
 *  -- to run, use mpirun -np p ./sieve.serial -n N, where p is the number of
 *     processes and N is the value under which to find primes.
 *  -- see attached module document for discussion of the code and its algorithm
 */
#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    /* Declare variables */
    int N = 16; /* The positive integer under which we are finding primes */
    int sqrtN = 0; /* The square root of N, which is stored in a variable to
                      avoid making excessive calls to sqrt(N) */
    int c = 0; /* Used to check the next number to be circled */
    int m = 0; /* Used to check the next number to be marked */
    int *list1; /* The list of numbers <= sqrtN -- if list1[x] equals 1, then x
                   is marked.  If list1[x] equals 0, then x is unmarked. */
    int *list2; /* The list of numbers > sqrtN -- if list2[x-L] is marked, then
                   x is marked.  If list2[x-L] equals 0, then x is unmarked. */
    char next_option = ' '; /* Used for parsing command line arguments */
    int S = 0; /* A near-as-possible even split of the count of numbers above
                  sqrtN */
    int R = 0; /* The remainder of the near-as-possible even split */
    int L = 0; /* The lowest number in the current process's split */
    int H = 0; /* The highest number in the current process's split */
    int r = 0; /* The rank of the current process */
    int p = 0; /* The total number of processes */

    /* Initialize the MPI Environment */
    MPI_Init(&argc, &argv);

    /* Determine the rank of the current process and the number of processes */
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    /* Parse command line arguments -- enter 'man 3 getopt' on a shell to see
       how this works */
    while((next_option = getopt(argc, argv, "n:")) != -1) {
        switch(next_option) {
        case 'n':
            N = atoi(optarg);
            break;
        case '?':
        default:
            fprintf(stderr, "Usage: %s [-n N]\n", argv[0]);
            exit(-1);
        }
    }

    /* Calculate sqrtN */
    sqrtN = (int)sqrt(N);

    /* Calculate S, R, L, and H */
    S = (N-(sqrtN+1)) / p;
    R = (N-(sqrtN+1)) % p;
    L = sqrtN + r*S + 1;
    H = L+S-1;
    if(r == p-1) {
        H += R;
    }

    /* Allocate memory for lists */
    list1 = (int*)malloc((sqrtN+1) * sizeof(int));
    list2 = (int*)malloc((H-L+1) * sizeof(int));

    /* Exit if malloc failed */
    if(list1 == NULL || list2 == NULL) {
        fprintf(stderr, "Sorry, there was an internal error. Please run again.\n");
        exit(-1);
    }

    /* Run through each number in list1 */
#pragma omp parallel for
    for(c = 2; c <= sqrtN; c++) {

        /* Set each number as unmarked */
        list1[c] = 0;
    }

    /* Run through each number in list2 */
#pragma omp parallel for
    for(c = L; c <= H; c++) {

        /* Set each number as unmarked */
        list2[c-L] = 0;
    }

    /* Run through each number in list1 */
    for(c = 2; c <= sqrtN; c++) {

        /* If the number is unmarked */
        if(list1[c] == 0) {

            /* Run through each number bigger than c in list1 */
#pragma omp parallel for
            for(m = c+1; m <= sqrtN; m++) {

                /* If m is a multiple of c */
                if(m%c == 0) {

                    /* Mark m */
                    list1[m] = 1;
                }
            }

            /* Run through each number bigger than c in list2 */
#pragma omp parallel for
            for(m = L; m <= H; m++)
                {
                    /* If m is a multiple of C */
                    if(m%c == 0)
                        {
                            /* Mark m */
                            list2[m-L] = 1;
                        }
                }
        }
    }

    /* If Rank 0 is the current process */
    if(r == 0) {

        /* Run through each of the numbers in list1 */
        for(c = 2; c <= sqrtN; c++) {

            /* If the number is unmarked */
            if(list1[c] == 0) {

                /* The number is prime, print it */
                printf("%d ", c);
            }
        }

        /* Run through each of the numbers in list2 */
        for(c = L; c <= H; c++) {

            /* If the number is unmarked */
            if(list2[c-L] == 0) {

                /* The number is prime, print it */
                printf("%d ", c);
            }
        }

        /* Run through each of the other processes */
        for(r = 1; r <= p-1; r++) {

            /* Calculate L and H for r */
            L = sqrtN + r*S + 1;
            H = L+S-1;
            if(r == p-1) {
                H += R;
            }

            /* Receive list2 from the process */
            MPI_Recv(list2, H-L+1, MPI_UNSIGNED_LONG, r, 0, MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);

            /* Run through the list2 that was just received */
            for(c = L; c <= H; c++) {

                /* If the number is unmarked */
                if(list2[c-L] == 0) {

                    /* The number is prime, print it */
                    printf("%d ", c);
                }
            }
        }
        printf("\n");

        /* If the process is not Rank 0 */
    } else {

        /* Send list2 to Rank 0 */
        MPI_Send(list2, H-L+1, MPI_UNSIGNED_LONG, 0, 0, MPI_COMM_WORLD);
    }

    /* Deallocate memory for list */
    free(list2);
    free(list1);

    /* Finalize the MPI environment */
    MPI_Finalize();

    return 0;
}
