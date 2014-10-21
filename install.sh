#!/bin/bash
SRC_PATH="/root/dev/"
SRC_FILE="main.cpp"
LIB_PATH="/root/dev/"
LIB_FILE="juxtapp.so"
KAG_PATH="/root/kag-test/"

cd ${SRC_PATH} && g++ ${SRC_FILE} --std=c++11 -static -static-libgcc -ldl -lm -lpthread -Iinclude -Llib -lstdc++ -llua -shared -fPIC -o ${LIB_FILE} && cp ${SRC_PATH}${LIB_FILE} /srv/ftp/${LIB_FILE} && cp ${SRC_PATH}juxtapp_config.cfg /srv/ftp/ && cp ${SRC_PATH}version.txt /srv/ftp/version.txt && cp ${SRC_PATH}version-text.txt /srv/ftp/version-text.txt
