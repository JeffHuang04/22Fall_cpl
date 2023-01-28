#include "ramfs.h"
/* modify this file freely */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define max_fd 4096
#define max_fileanddir 65536
#define length_name 32
#define length_road 1024
typedef struct node {
    enum {
        FILE_NODE = 1,
        DIR_NODE  = 2
    }type;
    struct node *child;
    struct node *sibling;
    void *contnet;
//    int number_child;
    int size;
    char *shortname;
}node;
node *root;
typedef struct filedesc{
    bool use;
    int offset;
    int flags;
    int writable;
    int readable;
    node *file;
}filedesc;
filedesc filed[max_fd];
int pathname_simple(char **str, char *temp_string, const char *pathname) {
    int lengthofroad = strlen(pathname);
    if(*pathname == '/' && lengthofroad <= length_road){
        int index = 0;
        char *temp = malloc(length_name + 3);
        temp = strtok(temp_string, "/");
        while (temp != NULL){
            if(strlen(temp) > length_name) {
                free(temp);
                str = NULL;
                return 0;
            }
            str[index] = temp;
            temp = strtok(NULL,"/");
            index ++;
        }
        if(pathname[lengthofroad - 1] == '/' && (strtok(str[index - 1],".text") !=NULL)) {
            free(temp);
            str = NULL;
            return 0;
        }
        free(temp);
        return index;
    } else {
        str = NULL;
        return 0;
    }
}
int ropen(const char *pathname, int flags) {
    char *temp_string = malloc(length_road + 1);
    strcpy(temp_string, pathname);
    char **str = malloc(length_road + 1);
    int index = pathname_simple(str, temp_string, pathname);
    if(str == NULL) {
        return -1;
    }
    // todo

    free(temp_string);
    free(str);
}


int rclose(int fd) {
  // TODO();
}

ssize_t rwrite(int fd, const void *buf, size_t count) {
  // TODO();
}

ssize_t rread(int fd, void *buf, size_t count) {
  // TODO();
}

off_t rseek(int fd, off_t offset, int whence) {
  // TODO();
}

int rmkdir(const char *pathname) {
    char *temp_string = malloc(length_road + 1);
    strcpy(temp_string, pathname);
    char **str = malloc(length_road + 1);
    int index = pathname_simple(str, temp_string, pathname);
    if(str == NULL) {
        return -1;
    }
    node *instruction = malloc(sizeof (struct node) + 5);
    instruction = root->child;
//    instruction->sibling = NULL;
//    instruction->child = NULL;
//    int number_low = instruction->number_child;
    for (int i = 0; i <= index - 1 ; i ++) {
        if (i == index - 1) {
            for (; ; ) {
                if(instruction->sibling == NULL && instruction->shortname != NULL)
                if (strcmp(str[i], instruction->shortname) == 0) {
                    return -1;
                }
                if (instruction->sibling == NULL) {
                    break;
                }
                instruction = instruction->sibling;
            }//检查没有重名的
            if(instruction->shortname != NULL) {
                instruction->sibling = malloc(sizeof(struct node));
                instruction->sibling->sibling = NULL;
                instruction->sibling->shortname = malloc(strlen(str[i]));
                strcpy(instruction->sibling->shortname, str[i]);
                if ((strtok(str[index - 1], ".text") != NULL)) {
                    instruction->sibling->type = DIR_NODE;
                } else {
                    instruction->sibling->type = FILE_NODE;
                }
                return 0;
            }else{
                instruction->sibling = NULL;
                instruction->shortname = malloc(strlen(str[i]));
                strcpy(instruction->shortname, str[i]);
                if ((strtok(str[index - 1], ".text") != NULL)) {
                    instruction->type = DIR_NODE;
                } else {
                    instruction->type = FILE_NODE;
                }
                return 0;
            }
        }
        for (; ; ) {
            if(strcmp(str[i],instruction->shortname) == 0){
                if(instruction->type == DIR_NODE) {
//                    number_low = instruction->number_child;
                    instruction = instruction->child;
                    continue;
                }else{
                    return -1;
                }
            }
            if(instruction->sibling == NULL) {
                return -1;
            }
            instruction = instruction->sibling;
        }
    }
    free(instruction);
    free(temp_string);
    free(str);
}
int rrmdir(const char *pathname) {

    char *temp_string = malloc(length_road + 1);
    strcpy(temp_string, pathname);
    char **str = malloc(length_road + 1);
    int index = pathname_simple(str, temp_string, pathname);
    if(str == NULL) {
        return -1;
    }
    // todo

    free(temp_string);
    free(str);
}

int runlink(const char *pathname) {
    char *temp_string = malloc(length_road + 1);
    strcpy(temp_string, pathname);
    char **str = malloc(length_road + 1);
    int index = pathname_simple(str, temp_string, pathname);
    if(str == NULL) {
        return -1;
    }
    // todo

    free(temp_string);
    free(str);
}

void init_ramfs() {
    root = malloc(sizeof (struct node));
    root->type = DIR_NODE;
    root->shortname = "/";
//    root->number_sibling = 0;
    root->sibling = malloc(sizeof (struct node));
    root->child = malloc(sizeof (struct node));
}
