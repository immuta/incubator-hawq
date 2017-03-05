#include <iostream>
#include <string>
#include <map>

#include <stdlib.h> // exit
#include <sys/stat.h>
#include <string.h>


#include "hdfs/DirectoryIterator.h"
#include "hdfs/FileSystem.h"
#include "hdfs/FileStatus.h"
#include "hdfs/InputStream.h"
#include "hdfs/XmlConfig.h"

using namespace std;
using namespace Hdfs;
using namespace Hdfs::Internal;


bool file_exists(const char * path) {
    if(path == NULL || strlen(path) == 0) {
        return false;
    } 
    
    struct stat tmp;
    return (stat(path, &tmp) == 0);
}

int main(int argc, char ** argv) {
    if(argc < 2) {
        cerr << argv[0] << " <directory> [kerberos ticket path] [hdfs server]" << endl;
        exit(EXIT_FAILURE);
    }
    
    const char * hdfs_dir = argv[1];
    const char * krb_ticket_path = argc > 2 ? argv[2] : "/tmp/krb5cc_501";
    const char * hdfs_info = argc > 3 ? argv[3] : "hdfs://namenode.immuta.works:8020";
    
    /* Create our filesystem configuration object this can also be an xml file
     * with the sytle of 
     * <configuration>
     *    <property>
     *       <name>property name</name>
     *       <value>property value</value>
     *    </property>
     */
    Config * conf = new Config();
    
    if (file_exists(krb_ticket_path)) {
        // These are needed for kerbros
        conf->set("hadoop.security.authentication", "kerberos");
        conf->set("hadoop.security.kerberos.ticket.cache.path", krb_ticket_path);
    }

    // Create our filesystem object to talk to HDFS
    FileSystem f(*conf);
    f.connect(hdfs_info);

    // Lets list our directory and iterate through the contents
    DirectoryIterator it = f.listDirectory(hdfs_dir);
    cout << endl <<  "Iterating through directory contents for " << hdfs_dir << endl << endl;
    while(it.hasNext()) {
        // Get a filestatus object which contains things like path, length, etc ...
        FileStatus fs = it.getNext();
        string path = fs.getPath(); 
        map<string, string> xattrs = f.listXAttrs(path);

        cout << "File Information for " << path  << endl
             <<  "File Size: " << fs.getLength()  << endl
             <<  "Is Directory? " << fs.isDirectory() << endl
             <<  "Owner: " << fs.getOwner() << endl
             <<  "Group: " << fs.getGroup() << endl;


        cout << "---> XATTRS <---" << endl;
        for(map<string, string>::iterator at = xattrs.begin(); at != xattrs.end(); ++at) {
            cout<< "Name: " << at->first << "Value: " << at->second << endl;
        }

        cout << endl << "End File Information for " << path << endl;
    }
    f.disconnect();
}
