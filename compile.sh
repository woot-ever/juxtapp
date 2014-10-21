#!/bin/bash
SRC_PATH="/root/dev/"
SRC_FILE="main.cpp"
LIB_PATH="/root/dev/"
LIB_FILE="juxtapp.so"
KAG_PATH="/root/kag-test/"

cd ${SRC_PATH} && g++ -g ${SRC_FILE} --std=c++11 -static -static-libgcc -ldl -lm -lpthread -Iinclude -Llib -lstdc++ -llua -shared -fPIC -o ${LIB_FILE} && ldd ${LIB_FILE} && cd ${KAG_PATH} && export LD_PRELOAD=${LIB_PATH}${LIB_FILE} && gdb ${KAG_PATH}KAGdedi
