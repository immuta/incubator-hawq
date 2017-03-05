#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
DIST_DIR="${SCRIPT_DIR}/../dist"
OS=`uname -s`
PLATFORM_BUILD_ARGS=""

if [ $OS == 'Linux' ]; then
    PLATFORM_BUILD_ARGS="-std=c++0x "
fi    

for file in `ls *.cpp`
do
    action="${file%.*}"
    bin=hdfs${action}
    g++ -o ${bin} ${PLATFORM_BUILD_ARGS} -I ${DIST_DIR}/include -L ${DIST_DIR}/lib -l hdfs3 $file
    if [ $OS == 'Darwin' ]; then
        install_name_tool -change libhdfs3.1.dylib $DIST_DIR/lib/libhdfs3.1.dylib hdfs${action}
    fi

    if [ $OS == 'Linux' ]; then
        mv $bin ${bin}.binary
        cat > $bin <<EOF
            #!/bin/bash
            LD_LIBRARY_PATH=${DIST_DIR}/lib ${SCRIPT_DIR}/${bin}.binary \$@
EOF
        chmod +x $bin
    fi
done
