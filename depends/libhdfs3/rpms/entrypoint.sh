#!/bin/bash

RHEL_VERSION=$(cat /etc/redhat-release | awk {'print $3'} | awk -F'.' '{print $1}')
echo $RHEL_VERSION
if [[ $RHEL_VERSION -eq 6 ]]
then
    source /opt/rh/devtoolset-3/enable
fi
pushd /libhdfs/libhdfs3/rpms
./build.sh run
