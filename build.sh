mkdir bin
rm -R bin/*.*
g++ -fdiagnostics-color=always -g src/*.cpp -I src/headers -std=c++11 -o bin/Server