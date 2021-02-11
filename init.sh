#!/bin/bash

hppkeep='y'

read -p "Project Name : " ProjectName
while [ -z $ProjectName ]
do
  read -p "Please Input a ProjectName : " ProjectName
done


read -p "What's version of C++ do you want to use (defualt: c++11) : " CVersion
if [ -z $CVersion ]
then 
  CVersion="c++11"
fi
CBeforeVersion=$(cat CMakeLists.txt|grep '\-std' |cut -d = -f 2 |cut -d \" -f 1) 
CVersion="$CVersion)"

read -p "Did you want to keep My hpp files? (y/n) " hppkeep

echo
echo ##############################
echo ProjectName:$ProjectName
echo CVersion:$CVersion
echo Wall:$Wall
echo CBeforeVersion:$CBeforeVersion
echo ##############################
echo


sed -i s/OpenGL_Template/$ProjectName/g CMakeLists.txt
sed -i s/$CBeforeVersion/$CVersion/g CMakeLists.txt

if [[ $Wall == 'n' || $Wall == 'N' ]]
then
  sed -i "s/-Wall //g" CMakeLists.txt
  sed -i "s/-Wextra //g" CMakeLists.txt
  sed -i "s/-Wpedantic //g" CMakeLists.txt
  sed -i "s/\/W4//g" CMakeLists.txt
fi


echo [INFO] Removing git files
rm $(find ./ -name "*git*") -rf
rm README.md -r

echo [INFO] Removing NULL file
rm $(find ./ -name "Del_This_File") -rf

if [[ $hppkeep == 'n' || $hppkeep == 'N' ]]
then
  echo [INFO] Removing My hpp files
  rm ./Source/include/* -rf
fi

echo [INFO] Removing initfile.
rm init.sh

echo "[INFO] Init Complate!"
