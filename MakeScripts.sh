#!/bin/bash 

# Del Files
###########

rm output/ -rf


# Cmake
###########
mkdir Build
cd Build
cmake ..

# Make
###########
make -j8

cd ..
rm compile_commands.json
ln Build/compile_commands.json

tmp=$(grep PROJECT\( CMakeLists.txt)

# Execute
###########

cd output

bash -c "./""$(echo ${tmp:8} | cut -d \) -f1)"

cd ..
