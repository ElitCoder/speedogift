deps=(jarro2783/cxxopts ElitCoder/ncconf ElitCoder/ncnet gabime/spdlog)

function pull {
    local i=$1
    git clone --depth=1 https://github.com/$i
    repo_name=(${i//// })
    cd ${repo_name[1]}
    if [ ! -f build.sh ]; then
        echo "using cmake as backup"
        mkdir build
        cd build
        cmake -DCMAKE_BUILD_TYPE=Debug -G Ninja ..
        ninja
        sudo ninja install
    else
        ./build.sh
        sudo make install
    fi
    return $?
}

function parse_dep {
    repo_name=$1
    url=$2
    if [ ! -d ${repo_name[1]} ]; then
        echo "can't find repo dir ${repo_name[1]}, resetting"
        pull $url
        return $?
    fi
    cd ${repo_name[1]}
    if [ ! -d .git ]; then
        echo "not an git repository ${repo_name[1]}, resetting"
        cd ..
        rm -rf ${repo_name[1]}
        pull $url
        return $?
    fi
    git fetch
    if [[ $(git rev-parse HEAD) != $(git rev-parse @{u}) ]]; then
        echo "old version for ${repo_name[1]}, resetting"
        cd ..
        rm -rf ${repo_name[1]}
        pull $url
        return $?
    fi
}

function check_deps {
    local FAIL=0
    cd dep
    for i in ${deps[@]}; do
        local repo_name=(${i//// })
        parse_dep $repo_name $i &
    done
    for job in `jobs -p`; do
        wait $job || let "FAIL+=1"
    done

    if [ "$FAIL" == "0" ]; then
        return 0
    else
        return 1
    fi
}

if [ ! -d "dep" ]; then
    mkdir dep
fi

# Otherwise, check
check_deps
exit $?