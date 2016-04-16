/*
 * Author: 王志伟-2014302580136
 * Description: 《UNIX程序设计》第二次作业
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>

#define SAFE_FREE(p) if(p){ free(p); p = NULL; }

typedef enum FindMode_{
    FindMode_None = 0,
    FindMode_Name = 1 << 0,
    FindMode_Content = 1 << 1
}FindMode;

static char* find_name_str = NULL;
static char* find_content_str = NULL;
static char* find_path = NULL;
static FindMode find_mode = 0;

void rfind_help(){
    fprintf(stderr, 
            "rfind -mode pattern [-mode pattern] path\n"
            "   -name                       Find in the files'name\n"
            "   -content                    Find in the files'content\n"
            "\nDESCRIPTION\n"
            "The rfind utility finds the targeted files according to the name-mode or content-mode recursively.\n"
            "The starting point is a specified directory. If the meta-character * is used, all the matched files must be located.\n"
            "\nEXAMPLES\n"
            "The following examples show common usage:\n"
            "rfind -name test.txt .\n"
            "rfind -content stdio.h /\n"
            "rfind -name \"*.txt\" /dev\n"
            "rfind -content \"put*()\" /home/chenzuolin\n"
            "rfind -content \"Hello World\" /home/chenzuolin\n"
            "rfind -content \"get*()\" -name \"*.c\" /home/chenzuolin\n"
            "\nEXIT STATUS\n"
            "rfind exits 0 on success, and >0 if an error occurred.\n"
            "\nNOTE\n"
            "Some terminal will try to translate the wildcard before it pass to the application, so it's recommended to quote the pattern.\n"
            "\nSEE ALSO\n"
            "opendir(3), readdir(2), read(2), strcmp(3)\n");
}

void parse_opt(int argc, char **argv){
    int argpos = 1;
    int last_find_mode = FindMode_None;
    for(; argpos < argc; ++argpos){
        /*printf("argv[%d]: %s\n", argpos, argv[argpos]);*/
        //for the arguments show the find FindMode
        if(argv[argpos][0] == '-'){
            if(strcmp(argv[argpos], "-name") == 0){
                find_mode |= FindMode_Name;
                last_find_mode = FindMode_Name;
            }
            else if(strcmp(argv[argpos], "-content") == 0){
                find_mode |= FindMode_Content;
                last_find_mode = FindMode_Content;
            }
        }
        else{
            switch(last_find_mode){
                case FindMode_Name:
                    find_name_str = (char *)malloc(strlen(argv[argpos]) * sizeof(char));
                    strcpy(find_name_str, argv[argpos]);
                    last_find_mode = FindMode_None;
                    break;

                case FindMode_Content:
                    find_content_str = (char *)malloc(strlen(argv[argpos]) * sizeof(char) + 2);
                    strcat(find_content_str, "*");
                    strcat(find_content_str, argv[argpos]);
                    strcat(find_content_str, "*");
                    last_find_mode = FindMode_None;
                    break;

                default:
                    if(FindMode_None == find_mode){
                        rfind_help();
                        return;
                    }
                    find_path = (char *)malloc(strlen(argv[argpos]) * sizeof(char));
                    strcpy(find_path, argv[argpos]);
                    return;
            }
        }
    }
}

int string_match(char *pattern, char *target){
    assert(NULL != pattern && NULL != target);
    /*fprintf(stderr, "pattern:%s  target:%s \n", pattern, target);*/
    const int pattern_len = strlen(pattern);
    const int target_len = strlen(target);
    int pattern_pos = 0;
    int target_pos = 0;
    int last_wildcard_pos = -1;
    for(; pattern_pos < pattern_len && target_pos < target_len; ++pattern_pos, ++target_pos){
        /*fprintf(stderr, "patter: %c  target:%c \n", pattern[pattern_pos], target[target_pos]);*/
        if('*' == pattern[pattern_pos]){
            last_wildcard_pos = pattern_pos;
            //get the next sensable charactor of '*'
            char next;
            do{
                if(pattern_len == pattern_pos + 1){
                    return 0;
                }
                ++pattern_pos;
                next = pattern[pattern_pos];
            }while('*' == next);

            //match '*' and the charactor next to '*'
            while(next != target[target_pos]){
                if(target_len == target_pos + 1){
                    return 1;
                }
                ++target_pos;
            }
        }
        else if('?' == pattern[pattern_pos]){
            continue;
        }
        else{
            if(pattern[pattern_pos] == target[target_pos]){
                continue;
            }
            else{
                if(-1 != last_wildcard_pos){
                    pattern_pos = last_wildcard_pos - 1;
                    continue;
                }
                else{
                    return 1;
                }
            }
        }
    }
    /*fprintf(stderr, "pattern:\npos: %d len:%d\ntarget:\npos: %d len:%d\n", pattern_pos, pattern_len, target_pos, target_len);*/
    if(pattern_pos == pattern_len && target_pos != target_len){
        return 1;
    }
    if(target_pos == target_len && pattern_pos != pattern_len){
        //check whether all the left charactors is '*'
        while('*' == pattern[pattern_pos]){
            ++pattern_pos;
        }
        if(pattern_len == pattern_pos){
            return 0;
        }
        else{
            return 1;
        }
    }
    return 0;
}

void find_file_by_name(char *dir_name){
    DIR *dir = opendir(dir_name);
    if(NULL == dir){
        fprintf(stderr, "Can't open dir %s: %s", dir_name, strerror(errno));
        return;
    }
    /*fprintf(stderr, "%s\n", dir_name);*/
    struct dirent *dir_content = NULL;
    while(NULL != (dir_content = readdir(dir))){
        if(0 == strcmp(dir_content->d_name, "..") || 0 == strcmp(dir_content->d_name, ".")){
            continue;
        }
        if(DT_DIR == dir_content->d_type){
            char *sub_dir_str = (char *)malloc(strlen(dir_name) + strlen(dir_content->d_name) + 1);
            strcpy(sub_dir_str, dir_name);
            strcat(sub_dir_str, "/");
            strcat(sub_dir_str, dir_content->d_name);
            find_file_by_name(sub_dir_str);
            SAFE_FREE(sub_dir_str);
        }
        else if(0 == string_match(find_name_str, dir_content->d_name)){
            printf("%s/%s\n", dir_name, dir_content->d_name);
        }
    }
}

int content_match(char *pattern, char *file_name){
    int fd = open(file_name, O_RDONLY);
    if(-1 == fd){
        fprintf(stderr, "Can't read file %s: %s\n", file_name, strerror(errno));
        /*exit(1);*/
        return 1;
    }
    int file_size = lseek(fd, 0, SEEK_END);
    char *file_contents = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if(MAP_FAILED == file_contents){
        fprintf(stderr, "Can't read file %s: %s\n", file_name, strerror(errno));
        return 1;
    }
    int result = string_match(pattern, file_contents);
    munmap(file_contents, file_size); 
    return result;
}

void find_file_by_content(char *dir_name){
    DIR *dir = opendir(dir_name);
    if(NULL == dir){
        fprintf(stderr, "Can't open dir %s: %s", dir_name, strerror(errno));
        exit(1);
    }

    struct dirent *dir_content = NULL;
    while(NULL != (dir_content = readdir(dir))){
        if(0 == strcmp(dir_content->d_name, "..") || 0 == strcmp(dir_content->d_name, ".")){
            continue;
        }
        if(DT_DIR == dir_content->d_type){
            char *sub_dir_str = (char *)malloc(strlen(dir_name) + strlen(dir_content->d_name) + 1);
            strcpy(sub_dir_str, dir_name);
            strcat(sub_dir_str, "/");
            strcat(sub_dir_str, dir_content->d_name);
            find_file_by_content(sub_dir_str);
            SAFE_FREE(sub_dir_str);
        }
        else{
            char *original_dir = getcwd(NULL, 0);
            chdir(dir_name);
            if(0 == content_match(find_content_str, dir_content->d_name)){
                printf("%s/%s\n", dir_name, dir_content->d_name);
            }
            chdir(original_dir);
            SAFE_FREE(original_dir);
        }
    }
}

void clear(){
    SAFE_FREE(find_name_str);
    SAFE_FREE(find_content_str);
    SAFE_FREE(find_path);
}

int main(int argc, char **argv){
    switch(argc){
        case 1:
            rfind_help();
            return 0;
        case 2:
            rfind_help();
            return 0;
        default:
            break;
    }
    parse_opt(argc, argv);
    if(find_mode & FindMode_Name){
        find_file_by_name(find_path);
    }
    if(find_mode & FindMode_Content){
        find_file_by_content(find_path);
    }
    printf("\n");
    /*if(NULL != find_name_str){*/
    /*printf("find_name_str: %s\n", find_name_str);*/
    /*}*/
    /*if(NULL != find_content_str){*/
    /*printf("find_content_str: %s\n", find_content_str);*/
    /*}*/
    /*if(NULL != find_path){*/
    /*printf("find_path: %s\n", find_path);*/
    /*}*/
    clear();
    return 0;
}
