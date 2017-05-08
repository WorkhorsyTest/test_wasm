

#COPTS=-O3
COPTS=-O0

source ../emsdk/emsdk_env.sh

rm -f *.wasm

em++  *.cpp -Wall -Werror -std=c++14 $COPTS -s WASM=1 -o index.html
