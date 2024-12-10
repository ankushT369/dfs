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


/*
void add_file_mapping(char* virtual_path, char* real_path, f_map* fm) {
    real_path = realpath(virtual_path, NULL);
    if (real_path != NULL) {
        printf("Full path: %s\n", real_path);
    }
}
*/


void remove_slash(const char *input, char *output, size_t output_size) {
    if (strlen(input) < 1 || strlen(input) >= output_size) {
        fprintf(stderr, "Output buffer is too small or input is invalid!\n");
        return;
    }

    strncpy(output, input + 1, output_size - 1);
    output[output_size - 1] = '\0';
}


/* hard coded for testing */
f_map fm[] = {
    {"/note.txt", "/home/ankush/exp/note.txt"},
    {"/Linux Kernel Development, 3rd Edition.pdf", "/home/ankush/linux/pdf/Linux Kernel Development, 3rd Edition.pdf"},
};

// f_map* fm = NULL;

static int dfs_getattr(const char* path, struct stat* st, struct fuse_file_info* fi) {
    (void) fi;
    memset(st, 0, sizeof(struct stat));
    struct stat file_stat;

    if (strcmp(path, "/") == 0) {
        st->st_mode = S_IFDIR | 0755; // Directory with read/execute permissions
        st->st_nlink = 2;
        return 0;
    }

    for(size_t i = 0; i < sizeof(fm) / sizeof(fm[0]); i++) {
        if (strcmp(path, fm[i].virtual_path) == 0) {
            if (access(fm[i].real_path, F_OK) == 0) { 
                stat(fm[i].real_path, &file_stat);
                st->st_mode = S_IFREG | 0444;
                st->st_nlink = 1;
                st->st_size = file_stat.st_size;
                return 0;
            }
        }
    }

    return -ENOENT;
}


static int dfs_readdir(const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, 
                       struct fuse_file_info* fi, enum fuse_readdir_flags flags) {
    (void) offset;
    (void) fi;
    (void) flags;

    if (strcmp(path, "/") == 0) {
        filler(buffer, ".", NULL, 0, 0);
        filler(buffer, "..", NULL, 0, 0);


        for(size_t i = 0; i < sizeof(fm) / sizeof(fm[0]); i++) {
            char result[256];
            remove_slash(fm[i].virtual_path, result, sizeof(result));
            filler(buffer, result, NULL, 0, 0);
        }
        return 0;
    }


    return -ENOENT;
}


static int dfs_open(const char *path, struct fuse_file_info *fi) {
    for(size_t i = 0; i < sizeof(fm) / sizeof(fm[0]); i++) {
        if (strcmp(path, fm[i].virtual_path) == 0)
            return 0; 
    }
    return -ENOENT;
}

static int dfs_read(const char* path, char* buffer, size_t size, off_t offset,
                    struct fuse_file_info* fi) {
    FILE* file = NULL;
    for(size_t i = 0; i < sizeof(fm) / sizeof(fm[0]); i++) {
        if(strcmp(path, fm[i].virtual_path) == 0) {
            file = fopen(fm[i].real_path, "r");
        }
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
    const char *optstring = "f:";
    char *filename = NULL;
    fm = malloc(sizeof(f_map));

    while ((opt = getopt(argc, argv, optstring)) != -1) {
        switch (opt) {
            case 'f': // Handle -f option
                filename = optarg;
                break;
            case '?': // Invalid option
                print_usage();
                return 1;
        }
    }

    if (filename) {
        printf("Option -f provided with filename: %s\n", filename);
        char* real_path = NULL;
        add_file_mapping(filename, real_path, fm);
        return 0;
    }
    */
    return fuse_main(argc, argv, &ops, NULL);

    /*
    if (optind < argc) {

    }
    */

    //print_usage();
    return 0;
}
