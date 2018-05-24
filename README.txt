Build sum.c
mpicc sum.c -o sum

Running sum.c, where 4 can be any number in the integral power of 2.
mpirun -np 4 ./sum

Build partialSum.c
mpicc partialSum.c -o partialSum

Running partialSum.c, where 4 can be any number in the integral power of 2.
mpirun -np 4 ./partialSum