# dpss-assignment

Zip password "cracker" using [libzip](https://libzip.org/), knowing the password size and the message to find.

```shell
sudo chmod +x install-packages.sh # will install required build tools
sudo chmod +x install.sh          # will install libzip
sudo chmod +x compile-n-run.sh    # will compile-n-run main.c

sudo ./install-packages.sh
sudo ./install.sh

./compile-n-run.sh
```

> You have to specify the zip file as an argument!