echo "..::Package expressions::.."
echo "__ BUILD ____________________"
cd lama
sh build.sh
cd ..
echo "__ CMAKE ____________________"
mkdir -p bin
cd bin
cmake ..
cmake --build .
echo "DONE!"
