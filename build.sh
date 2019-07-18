# Check dependencies
./check_dep.sh
if [ $? -ne 0 ]; then
    # Clean and rebuild
    make clean
fi

# Build
cores=`grep --count ^processor /proc/cpuinfo`
make -j $cores