// FILE_EXPLORER_H
#ifndef FILE_EXPLORER_H
#define FILE_EXPLORER_H

#include <stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include <sys/stat.h>
#include <unistd.h>

void list_files(const char *path, int depth);
void open_file(const char *file_path);
void edit_file(const char *file_path);
void create_file(const char *path);
int create_directory(const char *dir_path); 
int delete_directory(const char *dir_path);
int delete_file(const char *file_path);
int search_and_delete_file(const char *dir_path, const char *target_file);

#endif 
