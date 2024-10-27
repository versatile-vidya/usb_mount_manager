// FILE_EXPLORER_H
#ifndef FILE_EXPLORER_H
#define FILE_EXPLORER_H

#include <stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>

void list_files(const char *path, int depth);
void open_file(const char *file_path);
void edit_file(const char *file_path);
void create_file(const char *path);


#endif 
