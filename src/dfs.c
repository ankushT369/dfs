

// #include "dfs.h"
#include "/home/ankush/dfs/include/dfs.h"

#include <fuse3/fuse.h>
#include <getopt.h>
#include <errno.h>
#include <string.h>



/**
 *  @brief get the attributes of the directory or file
 *
 *  @param path The path is the path of the current 
 *  directory or the file which is getting accessed
 *
 *  @param st The st is the pointer to the struct stat which
 *  the information of the current directory or file
 *
 *  @param fi The fi is the pointer to the fuse_file_info 
 *  currenty unused
 *
 */
static int dfs_getattr(const char* path, struct stat* st, struct fuse_file_info* fi) {

    return 0;
}


struct fuse_operations ops = {
    .getattr = dfs_getattr,

};

int main(int argc, char* argv[]) {
    fuse_main(argc, argv, &ops, NULL);
}
