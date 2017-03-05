#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
DIST_DIR="${SCRIPT_DIR}/../dist"

g++ -o hdfstest -I ${DIST_DIR}/include -L ${DIST_DIR}/lib -l hdfs3 filesystem.cpp
OS=`uname -s`
if [ $OS == 'Darwin' ]; then
    install_name_tool -change libhdfs3.1.dylib $DIST_DIR/lib/libhdfs3.1.dylib hdfstest
fi
