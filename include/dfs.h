/* Implementation of the dfs.h */
#ifndef DFS_H
#define DFS_H

#define FUSE_USE_VERSION 31 // defined version

#include <stdint.h>
#include <stdlib.h>


typedef struct file_mapping {
    /* Unique ID for each path entries */
    uint8_t uid;

    /* Path for the virtual file system */
    char* virtual_path;

    /* Size of the virtual path length */
    size_t virtual_path_len;

    /* Path for the real file system */
    char* real_path;

    /* Size of the real path length */
    size_t real_path_len;
} f_map;




#endif // DFS_H
