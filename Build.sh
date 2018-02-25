#!/bin/bash

if [ "$1" == "Release" -o "$1" == "Debug" ]; then
	Arguments="-DCMAKE_BUILD_TYPE=$1"
else
	Arguments="-DCMAKE_BUILD_TYPE=Release"
fi

if [ "$2" == "x86" -o "$2" == "x64" ]; then
	Arguments="${Arguments} -DPLATFORM:STRING=\"$2\""
else
	Arguments="${Arguments} -DPLATFORM:STRING=\"x64\""
fi

if [ "$3" == "coverage" ]; then
	Arguments="${Arguments} -DCOVERAGE=ON"
fi

if [ ! -d "Build" ]; then
	mkdir Build
fi

cd Build

cmake ../ -G "Unix Makefiles" ${Arguments}
make
