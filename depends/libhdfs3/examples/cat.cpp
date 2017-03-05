#include <iostream>
#include <string>
#include <sstream>

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
        return EXIT_FAILURE;
    }
    
    const char * hdfs_path = argv[1];
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

    // Lets get our file's information
    FileStatus fs = f.getFileStatus(hdfs_path);
    if( fs.isDirectory() ) {
        cerr << hdfs_path << " is a directory, unable to cat!" << endl;
        return EXIT_FAILURE;
    }

    InputStream inputStream;
    inputStream.open(f, hdfs_path);
    long size = fs.getLength();

    long bytes_read = 0;
    const int BUFFER_SIZE = 1024;
    while(bytes_read < size) {
        /* Read in 1024 bytes (1k) at a time we need to initialize our arrray to
         * 1025 though to add the null terminator or else random characters
         * seem to get added to the end. 
         */
        char buffer[BUFFER_SIZE+1]={}; // Make sure to initailize to null
        bytes_read += inputStream.read(buffer, BUFFER_SIZE);
        cout << buffer;
    }
    cout << endl << "End of file (we added a extra newline)" << endl;
    f.disconnect();
}
