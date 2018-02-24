#!/bin/bash

if [ ! -d "Build" ]; then
	mkdir Build
fi

cd Build

if [ "$1" == "COVERAGE" ]; then
cmake ../ -G "Unix Makefiles" -DCOVERAGE=ON
else
cmake ../ -G "Unix Makefiles"
fi
make
