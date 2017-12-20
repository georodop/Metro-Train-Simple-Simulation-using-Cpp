#!/bin/bash
# This script updates the program (if not up to date), compiles and runs it

# This is the default argument given to run the program. Change it here or
# run the program directly from command line giving any integer you want.
arg=10

git pull
retval=$?
if [ $retval -ne 0 ]; then
    echo "Return code was not zero but $retval"
    git clone https://github.com/georodop/Metro-Train-Simple-Simulation-using-Cpp.git
    cd ./Metro-Train-Simple-Simulation-using-Cpp
    g++ metrotrain.cpp -o metrotrain.out -std=c++98;
    ./metrotrain.out $arg
else
    echo "OK"
    g++ metrotrain.cpp -o metrotrain.out -std=c++98;
    ./metrotrain.out $arg
fi
  