# Check dependencies
./check_dep.sh
if [ $? -ne 0 ]; then
    # Clean and rebuild
    rm -rf build
fi

# Build (Linux)
mkdir -p build && cd build
cmake -G Ninja ..
ninja
cd ..