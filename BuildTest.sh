#!/bin/bash
rm output -rf

cd Build
cmake ..

make -j 8
cd ..

rm compile_commands.json
ln Build/compile_commands.json

tmp=$(grep -i PROJECT\( CMakeLists.txt)

cd output 

bash "./""$(echo ${tmp:8} | cut -d \) -f1)"

cd ..
