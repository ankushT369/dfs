// #include "dfs.h"
// #include "util.h"
#include "/home/ankush/dfs/include/dfs.h"
#include "/home/ankush/dfs/include/util.h"

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

/**
 *  @brief reads the directory
 *
 *  @param path The path is the path of the current 
 *  directory or the file which is getting accessed
 *
 *  @param buffer The buffer holds the information
 *  of the directory entries, we use filler function
 *  given by FUSE to add entries
 *
 *  @param filler The filler is the helper function 
 *  provided by FUSE to read the entries
 *
 *  @param offset Indicates the starting point for 
 *  the directory listing
 *
 *  @param fi Contains information about the file or 
 *  directory being accessed
 *
 *  @param flags Flags that may modify the behavior 
 *  of the directory listing
 *
 */
static int dfs_readdir (const char * path, void * buffer, fuse_fill_dir_t filler, off_t offset, 
        struct fuse_file_info* fi, enum fuse_readdir_flags flags) {

}


struct fuse_operations ops = {
    .getattr = dfs_getattr,
    .readdir = dfs_readdir,
};

int main(int argc, char* argv[]) {
    fuse_main(argc, argv, &ops, NULL);
}
