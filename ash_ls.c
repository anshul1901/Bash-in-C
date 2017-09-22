#include "main.h"
#include "stdio.h"
#include "sys/stat.h"
#include "sys/types.h"
#include "malloc.h"
#include "string.h"
#include "dirent.h"
#include "time.h"
#include "pwd.h"
#include "grp.h"
#define ANSI_COLOR_RED    "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int ash_ls(char **args){
  DIR *dir;
  struct dirent *name;
  struct stat directory;
  struct stat opdir;

  int flag_a = 0, flag_l = 0, dir_count = 0, j = 0;

  for (int i = 1; args[i] != NULL; i++) {
    if (strcmp(args[i], "-a") == 0)
      flag_a = 1;
    else if (strcmp(args[i], "-l") == 0)
      flag_l = 1;
    else if (strcmp(args[i], "-al") == 0 || strcmp(args[i], "-la") == 0){
      flag_a = 1;
      flag_l = 1;
    }
    else if(strcmp(args[i], " ") != 0) dir_count++;
  }
  int dir_flag = 0;
  if (dir_count == 0) {
    dir_count = 1;
    dir_flag = 1;
  }
  // printf("count(%d), a(%d), l(%d)\n", dir_count, flag_a, flag_l);
  char **dir_names = (char **)malloc(dir_count * 8);
  for (int i = 0; i < dir_count; i++) {
    dir_names[i] = (char *)malloc(50);
  }

  for (int i = 1; args[i] != NULL; i++) {
    if (strcmp(args[i], "-al") == 0 || strcmp(args[i], "-la") == 0 ||
    strcmp(args[i], "-a") == 0 || strcmp(args[i], "-l") == 0){
      // printf("fsad\n" );
    }
    else {
      dir_names[j] = args[i];
      j++;
    }
  }

  if (dir_flag) dir_names[0] = ".";
  char date[100];

  // struct group grp;

  for (int i = 0; i < dir_count; i++){
    dir = opendir(dir_names[i]);
    if (dir == NULL) {
      printf("%s: No such file or directory\n", dir_names[i]);
      continue;
    }
    printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET, dir_names[i]);
    // label:
    while((name = readdir(dir)) != NULL){
      // name = readdir(dir);
      // if (name == NULL) break;
      if (stat(name->d_name, &directory) != 0){
        // perror("ash");
        // continue;
        // goto label;
      }
      if (!flag_a && !flag_l) {
        if(name->d_name[0] != '.')
        printf("%s\n", name->d_name);
      }
      else if (!flag_l && flag_a) {
        // stat(name->d_name, &directory);
        printf("%s\n", name->d_name);
      }
      else if (flag_a && flag_l) {
        strftime(date, 100, "%h %d %H:%M", localtime(&(directory.st_ctime)));
        // strftime(date, 100, "%d-%m-%y", localtime(&(directory.st_ctime)));
        printf( (S_ISDIR(directory.st_mode)) ? "d" : "-");
        printf( (directory.st_mode & S_IRUSR) ? "r" : "-");
        printf( (directory.st_mode & S_IWUSR) ? "w" : "-");
        printf( (directory.st_mode & S_IXUSR) ? "x" : "-");
        printf( (directory.st_mode & S_IRGRP) ? "r" : "-");
        printf( (directory.st_mode & S_IWGRP) ? "w" : "-");
        printf( (directory.st_mode & S_IXGRP) ? "x" : "-");
        printf( (directory.st_mode & S_IROTH) ? "r" : "-");
        printf( (directory.st_mode & S_IWOTH) ? "w" : "-");
        printf( (directory.st_mode & S_IXOTH) ? "x" : "-");
        printf(" %d ", (int)directory.st_nlink);
        struct group  *gr = getgrgid(directory.st_gid);
        struct passwd *pw = getpwuid(directory.st_uid);
        printf(" %s", pw->pw_name);
        printf(" %s", gr->gr_name);
        printf(" %s     ", date);
        printf("%d", (int)directory.st_size);
        printf(" \t%s", name->d_name);
        printf("\n");
      }
      else {
        if(name->d_name[0] != '.') {
          strftime(date, 100, "%h %d %H:%M", localtime(&(directory.st_ctime)));
          // strftime(date, 100, "%d-%m-%y", localtime(&(directory.st_ctime)));
          printf( (S_ISDIR(directory.st_mode)) ? "d" : "-");
          printf( (directory.st_mode & S_IRUSR) ? "r" : "-");
          printf( (directory.st_mode & S_IWUSR) ? "w" : "-");
          printf( (directory.st_mode & S_IXUSR) ? "x" : "-");
          printf( (directory.st_mode & S_IRGRP) ? "r" : "-");
          printf( (directory.st_mode & S_IWGRP) ? "w" : "-");
          printf( (directory.st_mode & S_IXGRP) ? "x" : "-");
          printf( (directory.st_mode & S_IROTH) ? "r" : "-");
          printf( (directory.st_mode & S_IWOTH) ? "w" : "-");
          printf( (directory.st_mode & S_IXOTH) ? "x" : "-");
          printf(" %d ", (int)directory.st_nlink);
          struct group  *gr = getgrgid(directory.st_gid);
          struct passwd *pw = getpwuid(directory.st_uid);
          printf(" %s", pw->pw_name);
          printf(" %s", gr->gr_name);
          printf(" %s    ", date);
          printf(" %d", (int)directory.st_size);
          printf(" \t%s", name->d_name);
          printf("\n");
        }
      }
    }
  }
  closedir(dir);

  return 1;
}


//   if (args[1] == NULL){
//     args[1] = ".";
//     dir = opendir(args[1]);
//     while((name = readdir(dir)) != NULL)
//       {
//           stat(name->d_name, &directory);
//           // printf("%d",directory.st_size);
//           if(strcmp(name->d_name, ".") != 0 && strcmp(name->d_name, "..") != 0)
//       }
//     closedir(dir);
//     printf("\n");
//   }
//   else if (args[1][0])
//   else {
//     if (args[1][0] == '-'){
//       dir = opendir(args[1]);
//       while((name = readdir(dir)) != NULL)
//         {
//             stat(name->d_name, &directory);
//             // printf("%d",directory.st_size);
//             if(name->d_name[0] != '.')
//               printf(" %s\n", name->d_name);
//         }
//       closedir(dir);
//       printf("\n");
//     }
//   }
//
//
// }
