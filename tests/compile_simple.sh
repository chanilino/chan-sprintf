#!/bin/bash -x

CURRENT_DIR=$(readlink -f $(dirname "${0}"))

gcc -Wall -g -o3 -I"${CURRENT_DIR}/../include" simple_test.c -lm -o simple_test 
