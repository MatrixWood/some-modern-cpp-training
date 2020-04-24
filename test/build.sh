#!/bin/bash

g++ test.cpp -o test -L/usr/include/ #-std=c++11 -stdlib=libc++
./test
