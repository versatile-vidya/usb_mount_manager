#include "milli_file_detect.h"


#define MAX_PATH 1024


// List of suspicious file extensions
const char *bad_extensions[] = {".exe", ".bat", ".vbs", ".scr", ".dll",".msi",".bin",".cmd",".com",".scr",".vbs",".ps1",".sh",".js",".wsf",".hta",".ocx",".so",".docm",".xlsm",".pptm",".dotm",".sys",".drv",".cpl",".iso",".jar",".reg",".inf",".msp",".apk",".app",".gadget",".pyc",".deb",".rpm"};
size_t num_bad_extensions = sizeof(bad_extensions) / sizeof(bad_extensions[0]);

// List of known good file extensions
const char *good_extensions[] = {".txt", ".jpg", ".png", ".pdf", ".docx",".doc",".xls",".xlxs",".ppt",".pptx",".odt",".ods",".rtf",".jpeg",".gif",".bmp",".tiff",".tif",".svg",".mp3",".wav",".flac",".aac",".ogg",".mp4",".avi",".mkv",".mov","wmv",".zip",".rar",".7z",".tar",".gz",".html",".css",".js",".json",".xml",".epub",",.csv",".log",".ini"};
size_t num_good_extensions = sizeof(good_extensions) / sizeof(good_extensions[0]);



// Function to get the file extension
const char *get_file_extension(const char *filename)
{

    	const char *dot = strrchr(filename, '.');		 // Find the last occurrence of '.'
	return dot ? dot : "";
}

// Function to check if a file has a bad extension
int is_bad_file(const char *filename) 
{

    	const char *ext = get_file_extension(filename);
	for (size_t i = 0; i < num_bad_extensions; i++)
       	{
        
		if (strcasecmp(ext, bad_extensions[i]) == 0) 
		{
            		return 1; // File has a bad extension
        	}
    	}
    	return 0;
}

// Function to check if a file has a good extension
int is_good_file(const char *filename)
{
    	const char *ext = get_file_extension(filename);
    	for (size_t i = 0; i < num_good_extensions; i++)
       	{
        	if (strcasecmp(ext, good_extensions[i]) == 0)
	       	{
            		return 1; // File has a good extension
        	}
    	}
    	return 0;
}

// Function to check if the file contains suspicious content
int check_for_suspicious_content(const char *file_path)
{
    	FILE *fp = fopen(file_path, "rb");
    	if (!fp)
       	{
        	perror("Failed to open file");
        	return -1;
    	}

    	fseek(fp, -1024, SEEK_END); // Move to the last 1024 bytes of the file
    	char buffer[1024];
    	size_t bytes_read = fread(buffer, 1, sizeof(buffer), fp);
    	fclose(fp);

    	if (bytes_read == 0) 
	{
        	printf("Error reading file content.\n");
        	return 0;
    	}

    	for (size_t i = 0; i < bytes_read - 3; i++) 
	{
        	if ((buffer[i] == 0x90 && buffer[i + 1] == 0x90 && buffer[i + 2] == 0x90) || (buffer[i] == 'e' && buffer[i + 1] == 'v' && buffer[i + 2] == 'a' && buffer[i + 3] == 'l')) 
		{
            		printf("Suspicious content detected in file: %s\n", file_path);
            		return 1; // Suspicious content found
        	}
    	}	
    	return 0; // No suspicious content found
}

// Function to check the file type using libmagic
int check_file_type(const char *file_path) 
{
    	magic_t magic_cookie = magic_open(MAGIC_MIME_TYPE);
    	if (!magic_cookie)
       	{
        	fprintf(stderr, "Failed to initialize libmagic.\n");
        	return -1;
   	}

    	if (magic_load(magic_cookie, NULL) != 0)
       	{
        	fprintf(stderr, "Failed to load magic database: %s\n", magic_error(magic_cookie));
        	magic_close(magic_cookie);
        	return -1;
    	}	

    	const char *file_type = magic_file(magic_cookie, file_path);
    	if (file_type)
       	{
       		 printf("File type of %s: %s\n", file_path, file_type);
    	}
       	else 
	{
        	fprintf(stderr, "Failed to analyze file type: %s\n", magic_error(magic_cookie));
        	magic_close(magic_cookie);
        	return -1;
    	}

    	magic_close(magic_cookie);
    	return 0;
}

// Function to create a directory if it doesn't exist
int create_directory_if_not_exists(const char *dir_path) 
{
    	struct stat st = {0};
    	if (stat(dir_path, &st) == -1)
       	{
        	if (mkdir(dir_path, 0700) != 0)
	       	{
            		perror("Failed to create directory");
            		return -1;
       	 	}
        	printf("Directory created: %s\n", dir_path);
    	}
    	return 0;
}


// Function to copy a file
int copy_file(const char *source_path, const char *destination_path) 
{
    	FILE *src = fopen(source_path, "rb");
    	if (!src) 
	{
        	perror("Failed to open source file");
        	return -1;
    	}

    	FILE *dest = fopen(destination_path, "wb");
    	if (!dest)
       	{
        	perror("Failed to open destination file");
        	fclose(src);
        	return -1;
    	}

    	char buffer[4096];
    	size_t bytes;
    	while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) 
	{
        	fwrite(buffer, 1, bytes, dest);
    	}

    	fclose(src);
    	fclose(dest);
    	return 0;
}

// Function to process all files in a directory (recursively)
void process_directory(const char *dir_path, const char *good_dir, const char *bad_dir) 
{
    	DIR *dir = opendir(dir_path);
    	if (dir == NULL)
       	{
       	 	perror("Failed to open directory");
        	return;
    	}

    	struct dirent *entry;
    	while ((entry = readdir(dir)) != NULL)
       	{
        	if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) 
		{
            		continue; // Skip '.' and '..'
        	}

        	char full_path[MAX_PATH];
        	snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        	struct stat statbuf;
        	if (stat(full_path, &statbuf) == 0)
	       	{
            		if (S_ISDIR(statbuf.st_mode)) 
			{
               			 // Recursively process subdirectory
                		process_directory(full_path, good_dir, bad_dir);
            		}
		       	else if (S_ISREG(statbuf.st_mode)) 
			{
                		printf("\nChecking file: %s\n", full_path);

                		// Step 1: Check extensions
                		char dest_path[MAX_PATH];
                		if (is_bad_file(entry->d_name))
			       	{
                    			printf("File has a bad extension: %s\n", full_path);
                    			snprintf(dest_path, sizeof(dest_path), "%s/%s", bad_dir, entry->d_name);
                    			copy_file(full_path, dest_path);
                    			continue;
                		}
			       	else if (is_good_file(entry->d_name)) 
				{
                    			printf("File has a good extension: %s\n", full_path);
                		}

                		// Step 2: Check file type
                		if (check_file_type(full_path) != 0) 
				{
                    			continue; // Error checking file type
                		}

                		// Step 3: Check for suspicious content
                		if (check_for_suspicious_content(full_path) == 1) 
				{
                   			 printf("Suspicious file detected: %s\n", full_path);
                    			snprintf(dest_path, sizeof(dest_path), "%s/%s", bad_dir, entry->d_name);
                    			copy_file(full_path, dest_path);
                		}
			       	else
			       	{
                    			printf("File is clean: %s\n", full_path);
                    			snprintf(dest_path, sizeof(dest_path), "%s/%s", good_dir, entry->d_name);
                    			copy_file(full_path, dest_path);
                		}
            		}
        	}
    	}

    	closedir(dir);
}











