echo "Don't forget to run install-packages.sh first!"
gcc main.c -o dpss-assignment.out -lzip -lmpi
./dpss-assignment.out data/protected.zip