#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <assert.h>

//处理出错信息
#define ECHO_ERROR_AND_EXIT(msg) perror(msg);exit(1);

//存放出错信息
char error[256];

/*
 *获取子路径文件名
 *子路径名由inout_file_name参数返回
 */
void get_child_path(char *inout_file_name, char *child_name){
  assert(inout_file_name != NULL && child_name != NULL);
  strcat(inout_file_name, "/");
  strcat(inout_file_name, child_name);
}

/*
 *判断文件是否为目录
 *返回值0 不是目录
 *返回值1 是目录
 */
int is_dir(char *file_name){
  int result = 0;
  
  struct stat file_stat;
  if(-1 == stat(file_name, &file_stat)){
    sprintf(error, "复制失败：%s\n", strerror(errno));
    ECHO_ERROR_AND_EXIT(error);
  }
  if((S_IFDIR & file_stat.st_mode) == S_IFDIR){
    result = 1;
  }
  
  return result;
}

/*
 *根据源文件属性创建新文件
 *若成功，返回新文件的句柄
 */
int create_file_by_stat(char *source_file, char *target_file){
  struct stat source_stat;
  if(-1 == stat(source_file, &source_stat)){
    sprintf(error, "获取文件%s状态失败：%s\n", source_file, strerror(errno));
    ECHO_ERROR_AND_EXIT(error);
  }
  int target_id = open(target_file, O_CREAT|O_RDWR|O_TRUNC, source_stat.st_mode);
  if(-1 == target_id){
    sprintf(error, "创建目标文件%s失败：%s\n", target_file, strerror(errno));
    ECHO_ERROR_AND_EXIT(error);
  }
  return target_id;
}

//根据源目录属性创建新目录
void create_dir_by_stat(char *source_dir, char *target_dir){
  struct stat source_stat;
  if(-1 == stat(source_dir, &source_stat)){
    sprintf(error, "获取文件%s状态失败：%s\n", source_dir, strerror(errno));
    ECHO_ERROR_AND_EXIT(error);
  }
  mkdir(target_dir, source_stat.st_mode);
  return;
}

//复制文件
void copyfile(char *source_file, char *target_file){
  int source_id = 0;
  int target_id = 0;
  source_id = open(source_file, O_RDONLY);
  if(-1 == source_id){
    sprintf(error, "打开文件%s失败：%s\n", source_file, strerror(errno));
    ECHO_ERROR_AND_EXIT(error);
  }
  size_t filesize = lseek(source_id, 0, SEEK_END);
  target_id = create_file_by_stat(source_file, target_file);
  ftruncate(target_id, filesize);

  char *source_map = NULL;
  char *target_map = NULL;
  
  source_map = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, source_id, 0);
  if(MAP_FAILED == source_map){
    sprintf(error, "创建%s文件映射失败：%s\n", source_file, strerror(errno));
    ECHO_ERROR_AND_EXIT(error);
  }
  target_map = mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, target_id, 0);
  if(MAP_FAILED == target_map){
    sprintf(error, "创建%s文件映射失败：%s\n", target_file, strerror(errno));
    ECHO_ERROR_AND_EXIT(error);
  }
  memcpy(target_map, source_map, filesize);
  munmap(source_map, filesize);
  munmap(target_map, filesize);
  
  /*char content[MAXCOUNT_READ_ONETIME];
  int last_copy_len = MAXCOUNT_READ_ONETIME;
  while(MAXCOUNT_READ_ONETIME == last_copy_len){
    last_copy_len = read(source_id, content, MAXCOUNT_READ_ONETIME);
    write(target_id, content, last_copy_len);
    }*/
  
  close(source_id);
  close(target_id);
  return;
}

//递归复制目录
void copydir(char *source_dir, char *target_dir){
  create_dir_by_stat(source_dir, target_dir);
  
  DIR *dir = opendir(source_dir);
  struct dirent *source_dirent = readdir(dir);
  for(; source_dirent != NULL; source_dirent = readdir(dir)){
    if(strcmp(source_dirent->d_name, ".") == 0
       || strcmp(source_dirent->d_name, "..") == 0){
      continue;
    }
    if(DT_DIR == source_dirent->d_type){
      char child_source_dir[256];
      char child_target_dir[256];
      strcpy(child_source_dir, source_dir);
      strcpy(child_target_dir, target_dir);
      get_child_path(child_source_dir, source_dirent->d_name);
      get_child_path(child_target_dir, source_dirent->d_name);
      copydir(child_source_dir, child_target_dir);
    }
    else{
      char child_source_file[256];
      char child_target_file[256];
      strcpy(child_source_file, source_dir);
      strcpy(child_target_file, target_dir);
      get_child_path(child_source_file, source_dirent->d_name);
      get_child_path(child_target_file, source_dirent->d_name);
      copyfile(child_source_file, child_target_file);
    }
  }
  closedir(dir);
  return;
}

//复制
void copy(char *source, char *target){
  if(0 != access(source, F_OK)){
    sprintf(error, "复制失败，无法访问文件%s：%s\n", source, strerror(errno));
    ECHO_ERROR_AND_EXIT(error);
  }
  if(0 == access(target, F_OK)){
    if(is_dir(target)){
      get_child_path(target, source);
    }
    else{
      sprintf(error, "复制失败，目标文件%s已存在\n", target);
      ECHO_ERROR_AND_EXIT(error);
    }
  }
  if(is_dir(source)){
    copydir(source, target);
  }
  else{
    copyfile(source, target);
  }
  return;
}

void show_help_info(){
  printf("用法：tcp [source] [target]\n示例：tcp file cp_file\n将对目录自动进行递归");
}

int main(int argc, char **argv){
  switch(argc){
  case 1:
  case 2:
    show_help_info();
    break;

  default:
    copy(argv[1], argv[2]);
  }
  return 0;
}


