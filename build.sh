mkdir bin
g++ -fdiagnostics-color=always -g src/address.cpp src/server.cpp src/socket.cpp -I src/headers -std=c++11 -o bin/server.out