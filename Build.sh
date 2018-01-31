#!/bin/bash

mkdir Build
cd Build
cmake ../ -G "Unix Makefiles"
make
