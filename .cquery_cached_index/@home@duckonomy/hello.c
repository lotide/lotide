#include <stdio.h>

int main(void) {
    long int low_value;
    long int high_value;
    int num_processes = 4;
    int n = 100;
    int i;

    for (i = 0; i < num_processes; ++i) {
        low_value = 2 + (long int)(i) * (long int)(n - 1) / (long int)num_processes;
        high_value = 2 + (long int)(i + 1) * (long int)(n - 1) / (long int)num_processes;
        printf( "The results are %ld, %ld\n" , low_value, high_value);
    }


    return 0;
}
