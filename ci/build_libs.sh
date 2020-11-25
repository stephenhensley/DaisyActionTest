#!/bin/bash

START_DIR=$PWD
LIBDAISY_DIR=$PWD/libDaisy
DAISYSP_DIR=$PWD/DaisySP

cd $LIBDAISY_DIR ; make clean ; make | grep "warning\|error" ;
cd $DAISYSP_DIR ; make clean ; make | grep "warning\|error" ;
