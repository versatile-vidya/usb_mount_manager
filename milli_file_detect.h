//MILLICIOUS_FILE_DETECTION_H
//
#ifndef MILLI_FILE_DETECT_H
#define MILLI_FILE_DETECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <magic.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

// Function declarations

const char *get_file_extension(const char *filename);		// to get the file extension
int is_bad_file(const char *filename);				// to check if file has  a bad extension
int is_good_file(const char *filename);				// to check if file has a good extension
int check_file_type(const char *file_path);			// to check file type using libmagic
int check_for_suspicious_content(const char *file_path);	// check  for suspicious file contents 
int create_directory_if_not_exists(const char *dir_path);	// creating a directory if it doesn't exist
int copy_file(const char *source_path, const char *destination_path);	// copying a file from its source to destination (good_file/ | bad_files)
void process_directory(const char *dir_path, const char *good_dir, const char *bad_dir);	//process all files in a directory (recursively)

/*
int check_for_suspicious_content(const char *file_path);
int check_file_type(const char *file_path);
int create_directory_if_not_exists(const char *dir_path);
int move_file(const char *path, const char *dest_path);
void process_directory(const char *dir_path, const char *good_dir,const char *bad_dir);
const char *get_file_extension(const char *filename);
int is_bad_file(const char *filename);
int is_good_file(const char *filename);
int classify_file_by_mime(const char *file_path);
int copy_file(const char *source, const char *destination);
void process_files(const char *usb_path, const char *good_dir, const char *bad_dir);
*/
#endif 
