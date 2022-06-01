git clone https://github.com/nih-at/libzip.git
mkdir -p libzip/build
cd libzip/build || exit
cmake ..
make
make test
make install
cd ../../