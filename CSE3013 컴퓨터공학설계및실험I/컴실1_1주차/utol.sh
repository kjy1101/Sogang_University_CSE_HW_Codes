#!/bin/bash

echo "working directory: "
read direc

if [ -z $direc ]; then
	direc=$PWD
fi

if [ ! -d $direc ];
then
	echo "해당 디렉토리가 존재하지 않습니다."
else
	cd $direc

	for i in *
	do
		var=$(echo $i | tr "[A-Z, a-z]" "[a-z, A-Z]")
		mv $i $var
	done
fi
