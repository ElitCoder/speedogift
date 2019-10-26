# Check dependencies
./check_dep.sh
if [ $? -ne 0 ]; then
    # Clean and rebuild
    rm -rf build
fi

# Build (Linux)
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug -G Ninja ..
ninja
cd ..