# Open MPI dpss-assignment
Zip password "cracker" using [libzip](https://libzip.org/), knowing the password size and the message to find.
The archive is sent as an argument to the executable.
The executable will search for a file named "test.txt" inside the archive.
---
# Prerequisites
```shell
sudo chmod +x *.sh
sudo ./install-packages.sh
```
---
# Benchmarks
![legion pic](https://github.com/popescuciprian/dpss-assignment/blob/main/pics/legion.png)
![aws pic](https://github.com/popescuciprian/dpss-assignment/blob/main/pics/aws.png)
---
# Sample commands
### Manually compile the executable
```shell
gcc main.c -o dpss-assignment.out -lzip -lmpi
```
### Start the executable as one process
```shell
./dpss-assignment.out data/protected.zip
```
### Start the executable with MPI on 4 workers
```shell
 mpirun -quiet -np 4 dpss-assignment.out data/protected.zip
````
### Start the executable with MPI on 2 AWS instances
```shell
# Note: you have to set the given AWS hostnames in /etc/hosts
#       Also, the executable and archive must be present on both instances
  mpirun -quiet -np 2 -hostfile data/hosts.txt dpss-assignment.out data/protected.zip
```