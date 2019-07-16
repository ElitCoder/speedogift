deps=(ElitCoder/ncconf)

function pull {
    for i in ${deps[@]}; do
        git clone https://github.com/$i
        repo_name=(${i//// })
        cd ${repo_name[1]}
        ./build.sh
        sudo make install
        cd ..
    done
}

function check_deps {
    cd dep
    for i in ${deps[@]}; do
        repo_name=(${i//// })
        if [ ! -d ${repo_name[1]} ]; then
            return 1
        fi
        cd ${repo_name[1]}
        git fetch
        if [[ $(git rev-parse HEAD) != $(git rev-parse @{u}) ]]; then
            echo "hej"
            return 1
        fi
    done
    return 0
}

function reset {
    rm -rf dep
    mkdir dep
    cd dep
    pull
}

orig=`pwd`

if [ ! -d "dep" ]; then
    reset
    exit 0
fi

# Otherwise, check
check_deps
if [[ $? != 0 ]]; then
    cd $orig
    reset
    exit 0
fi
