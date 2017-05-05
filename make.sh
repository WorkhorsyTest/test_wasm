

COPTS=-O3
#COPTS=-Os

source ../emsdk/emsdk_env.sh

rm -f *.wasm

em++  main.cpp -std=c++14 $COPTS -s WASM=1 -s SIDE_MODULE=1 -o main.wasm
