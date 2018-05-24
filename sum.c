//
//  sum.c
//
//
//  Created by Calvin Ku on 14/05/2018.
//

# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>

typedef int bool;
enum { false, true };

int main (int argc, char *argv[]) {

    /*
     Initialize MPI.
     */
    MPI_Init (&argc, &argv);

    /*
     Get the number of processes.
     */
    int numprocs;
    MPI_Comm_size (MPI_COMM_WORLD, &numprocs);

    /*
     Determine the rank of this process.
     */
    int my_id;
    MPI_Comm_rank (MPI_COMM_WORLD, &my_id);

    /*
     set up randome seed.
     */
    time_t t;
    srand((unsigned) time(&t)+my_id);
    int* array = malloc (sizeof (int *) * numprocs); //initialize local array
    
    int value = rand() % 10;
    array[my_id] = value;
    MPI_Barrier(MPI_COMM_WORLD);
    
    for(int i = 0; i < numprocs; i++) {
        MPI_Bcast(&array[i], 1, MPI_INT ,i ,MPI_COMM_WORLD);
    }
    
    if(my_id == 1) {
        printf("Array values (randomly generated):");
        for (int i = 0; i < numprocs; i++) {
            printf(" %d", array[i]);
        }
        printf("\n");
    }
    
    for(int j = 1; j <= log2(numprocs); j++) {
        int temp;
        bool flag = false;
        if((my_id + 1) % (int)pow(2, j) == 0){
            temp = array[my_id - (int)pow(2, j - 1)] + array[my_id];
            flag = true;
        }
        if(flag)
            array[my_id] = temp;
        MPI_Barrier(MPI_COMM_WORLD);
        for(int i = 0; i < numprocs; i++)
            MPI_Bcast(&array[i], 1, MPI_INT ,i ,MPI_COMM_WORLD);
    }
    
    if(my_id == 1) {
        printf("Sum is %d\n", array[numprocs-1]);
    }
    
    MPI_Finalize ();
    free(array);
    return 0;
}
