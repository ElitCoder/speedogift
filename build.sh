# Check dependencies
./check_dep.sh

# Build
cores=`grep --count ^processor /proc/cpuinfo`
make -j $cores