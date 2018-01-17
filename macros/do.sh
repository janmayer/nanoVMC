#!/usr/bin/env bash

export LD_LIBRARY_PATH=$(realpath $(pwd)/../build):$LD_LIBRARY_PATH
#export LD_LIBRARY_PATH=/data/jmayer/Development/TCadToGeo/build/:$LD_LIBRARY_PATH

root -l -q createGeoArb8.C
#root -l -q createGeoTet.C

time root -l -q -b 'run_g4.C("geo-arb8.root", "out-arb8.root")'
#time root -l -q -b 'run_g4.C("geo-tet.root", "out-tet.root")'
