#!/bin/bash

this_dir=`cd "\`dirname \"$0\"\`";pwd`
top_dir=${this_dir}/../
PREFIX=${2:-""}

die() {
    echo "$@" 1>&2 ; popd 2>/dev/null; exit 1
}

build_google_test() {
    pushd ${top_dir}/../thirdparty/googletest
    rm -rf build && mkdir -p build && cd build || die "cannot create build directory" 
    cmake ../
    make 
    make install
    popd
}

install_depends() {
    for package in boost protobuf ossp-uuid libxml2 krb5 gsasl cmake
    do
        brew install $package
    done
}

build_with_boost() {
    pushd ${top_dir}
    rm -rf build && mkdir -p build && cd build || die "cannot create build directory"
    ../bootstrap --enable-boost || die "bootstrap failed"
    make -j2 unittest || die "failed to run unit tests"
    popd
}

build_with_debug() {
    pushd ${top_dir}
    rm -rf build && mkdir -p build && cd build || die "cannot create build directory"
    ../bootstrap --enable-debug || die "bootstrap failed"
    make -j2 unittest || die "failed to run unit tests"
    popd
}

install_package() {
    pushd ${top_dir}
    rm -rf build && mkdir -p build && cd build || die "cannot create build directory"
    bootstrap="../bootstrap"
    echo $PREFIX
    if [ ! -z "$PREFIX" ]; then
        echo "In here!"
        bootstrap="${bootstrap} --prefix=${PREFIX} "
    fi
    $bootstrap --enable-boost || die "bootstrap failed"
    make
    make install
    popd
}

run() {
    install_depends   || die "Failed to install dependencies"
    build_google_test || die "Unable to build google test"
    build_with_boost  || die "Build failed with boost"
    build_with_debug  || die "Build failed with debug mode"
}

"$@"
