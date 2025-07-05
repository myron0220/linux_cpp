#!/bin/bash

# used on VM guest side for quiack start test
cd /media/sf_VMshared/linux_cpp
g++ 2-hello_world.cpp -o a.exe && ./a.exe
