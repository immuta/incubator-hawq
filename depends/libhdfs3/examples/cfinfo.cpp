#include "hdfs/hdfs.h"
#include <iostream>

using namespace std;

int main(int arc, char ** argv) {
    struct hdfsBuilder * bld = hdfsNewBuilder();
    hdfsBuilderSetNameNode(bld, "hdfs://namenode.immuta.works:8020");
    hdfsBuilderSetKerbTicketCachePath(bld, "/tmp/krb5cc_501");
    hdfsBuilderConfSetStr(bld, "hadoop.security.authentication", "kerberos");
    hdfsFS fs = hdfsBuilderConnect(bld);
    int num;
    hdfsXAttr * xattrs = hdfsListXAttrs(fs, "/user/centos/redhat-release", &num);
    cout << xattrs[0].name << "," << xattrs[0].value << endl;
    hdfsDisconnect(fs);
    return (0);
}
