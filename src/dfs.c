#include "dfs.h"
#include "util.h"

#include <fuse3/fuse.h>
#include <getopt.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

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

/* hard coded for testing */
f_map fm[] = {
    {"/note.txt", "/home/ankush/exp/note.txt"},
};

//f_map* fm = NULL;

static int dfs_getattr(const char* path, struct stat* st, struct fuse_file_info* fi) {
    (void) fi;
    memset(st, 0, sizeof(struct stat));
    struct stat file_stat;

    if (strcmp(path, "/") == 0) {
        st->st_mode = S_IFDIR | 0755; // Directory with read/execute permissions
        st->st_nlink = 2;
        return 0;
    }

    if (strcmp(path, fm[0].virtual_path) == 0) {
        if (access(fm[0].real_path, F_OK) == 0) { // Check if real file exists
            stat(fm[0].real_path, &file_stat);
            st->st_mode = S_IFREG | 0444; // Regular file, read-only
            st->st_nlink = 1;
            st->st_size = file_stat.st_size; // Simulate file size (optional: use stat on the real file)
            return 0;
        }
    }

    return -ENOENT;
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

static int dfs_readdir(const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, 
                       struct fuse_file_info* fi, enum fuse_readdir_flags flags) {
    (void) offset;
    (void) fi;
    (void) flags;

    if (strcmp(path, "/") == 0) {
        filler(buffer, ".", NULL, 0, 0);
        filler(buffer, "..", NULL, 0, 0);
        filler(buffer, "note.txt", NULL, 0, 0);
        return 0;
    }


    return -ENOENT;
}

/**
 *  @brief Opens the file
 *
 *  @param Path is the opened file path
 *
 *  @param fi Contains information about the file or 
 *  directory being accessed
 *
 */

static int dfs_open(const char *path, struct fuse_file_info *fi) {
    if (strcmp(path, fm[0].virtual_path) == 0)
        return 0; 
    return -ENOENT;
}

/**
 *  @brief reads the opened file
 *
 *  @param path The path is the path of the current 
 *  file which is getting accessed
 *
 *  @param buffer The buffer holds the information
 *  of the file entries
 *
 *  @param size is the size to read
 *
 *  @param offset Indicates the starting point for 
 *  the file
 *
 *  @param fi Contains information about the file or 
 *  directory being accessed
 *
 */

static int dfs_read(const char* path, char* buffer, size_t size, off_t offset,
                    struct fuse_file_info* fi) {
    FILE* file = NULL;
    if(strcmp(path, fm[0].virtual_path) == 0) {
        file = fopen(fm[0].real_path, "r");
    }

    if(!file)
        return -ENOENT;

    fseek(file, offset, SEEK_SET);
    size_t bytes = fread(buffer, 1, size, file);
    fclose(file);

    return bytes;
}


struct fuse_operations ops = {
    .getattr = dfs_getattr,
    .readdir = dfs_readdir,
    .open = dfs_open,
    .read =  dfs_read,
};

int main(int argc, char* argv[]) {
    /*
    int opt;
    fm = malloc(sizeof(f_map));
    while ((opt = getopt(argc, argv, "s:")) != -1) {
        switch (opt) {
            case 's':
                add_file_mapping("/file.txt", "/dir1/file.txt", fm);
                break;
            default:
                fprintf(stderr, "Usage: %s [-s virtual_file] ...\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    */
    fuse_main(argc, argv, &ops, NULL);
}
