#!/bin/bash

# Submoudle
#########################
function Submoudle(){
submoudle=""
	for i in glfw glad glm assimp stb
	do
		if [ ! -n "$(ls ./Source/dependence/$i/)" ]
		then
			echo "[INFO] Dependence \"$i\" not exists, will clone this submoudle. "
			submoudle=$submoudle" $i"
		else
			echo "[INFO] Found $i"
		fi
	done
	Mirrors_Sele
	Submoudle_clone
}

# Git mirrors select 
########################
function Mirrors_Sele(){
	echo 
	echo
	echo -e "\t ..::     Mirrors select     ::.."
	echo -e "\t1. Origin:  github.com/"
	echo -e "\t2. CN:      github.com.cnpmjs.org/"
	#echo -e "\t3. CN       gitclone.com/github.com/"
	echo -e "\t ..::     ==============     ::.."
	read -p " Select:  " -n 1 MirrorsChoice
	echo ""
	echo ""
	
	
	if [ $MirrorsChoice == '1' ]
	then
		gitCloneUrl="https://github.com/"
	else if [ $MirrorsChoice == '2' ] 
	then
		gitCloneUrl="https://github.com.cnpmjs.org/"
#	else if [ $MirrorsChoice == '3' ]
#	then
#		gitCloneUrl="https://gitclone.com/github.com/"
	else
		echo "[INFO] Error Choice, "
		Mirrors_Sele
	fi
	fi
#	fi
	echo "[INFO] You choice $gitCloneUrl"
} 

function Submoudle_clone(){
	for i in $submoudle
	do
		case $i in 
			"glfw" ) 
				Repos=$Repos" glfw/glfw"
				;;
			"glad" )
				Repos=$Repos" Dav1dde/glad"
				;;
			"glm" )
				Repos=$Repos" g-truc/glm"
				;;
			"assimp" )
				Repos=$Repos" assimp/assimp"
				;;
			"stb" )
				Repos=$Repos" nothings/stb"
				;;
		esac
	done

	cd ./Source/dependence/
	rm $submoudle -rf
	for i in $Repos
	do
		if [ $i == "Dav1dde/glad" ]
		then
			git clone $gitCloneUrl$i -b c 
		else
			git clone $gitCloneUrl$i 
		fi
	done
	cd ../../
}


function Project_init(){
	# Project Name
	########################
	read -p "Project Name : " ProjectName
	while [ -z $ProjectName ]
	do
	  read -p "Please Input a ProjectName : " ProjectName
	done
	
	
	# Project C++ std
	########################
	read -p "What's version of C++ do you want to use (defualt: c++11) : " CVersion
	if [ -z $CVersion ]
	then 
	  CVersion="c++11"
	fi
	CBeforeVersion=$(cat CMakeLists.txt|grep '\-std' |cut -d = -f 2 |cut -d \" -f 1) 
	CVersion="$CVersion)"
	
	
	# Project Info
	########################
	echo
	echo ##############################
	echo ProjectName:$ProjectName
	echo CVersion:$CVersion
	echo Wall:$Wall
	echo CBeforeVersion:$CBeforeVersion
	echo ##############################
	echo
	
	Submoudle
	
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
	
	echo [INFO] Removing initfile.
#	rm init.sh

	mkdir Build -v
	
	echo "[INFO] Init Complate!"
}



Project_init
