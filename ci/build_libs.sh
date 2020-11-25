#!/bin/bash

START_DIR=$PWD
LIBDAISY_DIR=./libDaisy
DAISYSP_DIR=./DaisySP

cd $LIBDAISY_DIR ; make clean ; make
cd $PWD
cd $DAISYSP_DIR ; make clean ; make
cd $PWD
