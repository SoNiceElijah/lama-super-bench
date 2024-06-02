cd build
sh build.sh
cd ..
mkdir -p bin
cd bin
cmake ..
cmake --build .
