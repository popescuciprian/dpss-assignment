 gcc main.c -o dpss-assignment.out -lzip -lmpi
 mpirun -quiet -np 2 -hostfile data/hosts.txt dpss-assignment.out data/protected.zip