

// #include "dfs.h"
#include "/home/ankush/dfs/include/dfs.h"

#include <fuse3/fuse.h>


//(const char *, struct stat *, struct fuse_file_info *fi)
static int dfs_getattr(const char* path, struct stat* st, struct fuse_file_info* fi) {


    return 0;
}

struct fuse_operations ops = {
    .getattr = dfs_getattr,

};

int main(int argc, char* argv[]) {
    fuse_main(argc, argv, &ops, NULL);
}
