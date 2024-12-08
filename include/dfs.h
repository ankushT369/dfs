#ifndef DFS_H
#define DFS_H

#define FUSE_USE_VERSION 31

#include <stdint.h>
#include <stdlib.h>


typedef struct file_mapping {
    uint64_t uid;

    const char* virtual_path;

    size_t virtual_path_len;

    const char* real_path;

    size_t real_path_len;

} f_map;




#endif // DFS_H
