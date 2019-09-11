deps=(jarro2783/cxxopts ElitCoder/ncconf ElitCoder/ncnet)

function pull {
    local i=$1
    git clone --depth=1 https://github.com/$i
    repo_name=(${i//// })
    cd ${repo_name[1]}
    if [ ! -f build.sh ]; then
        echo "using cmake as backup"
        mkdir build
        cd build
        cmake -G Ninja ..
        ninja
        sudo ninja install
        cd ..
    else
        ./build.sh
        sudo make install
    fi
    cd ..
}

function check_deps {
    local res=0
    cd dep
    for i in ${deps[@]}; do
        repo_name=(${i//// })
        if [ ! -d ${repo_name[1]} ]; then
            echo "can't find repo dir ${repo_name[1]}, resetting"
            pull $i
            res=1
            continue
        fi
        cd ${repo_name[1]}
        if [ ! -d .git ]; then
            echo "not an git repository ${repo_name[1]}, resetting"
            cd ..
            rm -rf ${repo_name[1]}
            pull $i
            res=1
            continue
        fi
        git fetch
        if [[ $(git rev-parse HEAD) != $(git rev-parse @{u}) ]]; then
            echo "old version for ${repo_name[1]}, resetting"
            cd ..
            rm -rf ${repo_name[1]}
            pull $i
            res=1
            continue
        fi
        cd ..
    done
    return $res
}

if [ ! -d "dep" ]; then
    mkdir dep
fi

# Otherwise, check
check_deps
exit $?