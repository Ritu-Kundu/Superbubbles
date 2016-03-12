#! /bin/sh

mkdir -p temp
tar -xvf sdsl-lite.tar.gz --directory temp/
cd temp
cd sdsl-lite
./install.sh "$(pwd)"/install
cd ../../
mv temp/sdsl-lite/install/include/* include/
mv temp/sdsl-lite/install/lib/* lib/
rm -fR ./temp/