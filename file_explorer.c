#include "file_explorer.h"
#include<sys/stat.h>

//  ls
void list_files(const char *path,int depth)
{
	//int depth =0;
	struct dirent *de;
	DIR *dr = opendir(path);

	if(dr == NULL)
	{
		perror("opendir");
		return;
	}
		// Indentation for readability
    	for (int i = 0; i < depth; i++)
       	{
        	printf("    "); // Indentation for nested levels
    	}
	printf("Directory:  %s\n",path);
	while((de =readdir(dr)) != NULL)
	{
		if(de->d_name[0] =='.')
		{
			continue;
		}
		char full_path[512];
		snprintf(full_path, sizeof(full_path), "%s/%s", path, de->d_name);

		if (de->d_type == DT_DIR) 
		{
            		list_files(full_path, depth + 1); // Recursively list files in the directory
       		 
		}
	       	else if (de->d_type == DT_REG)
	       	{ // Regular file
            		struct stat file_stat;
           		if (stat(full_path, &file_stat) == 0) 
			{
                		for (int i = 0; i < depth + 1; i++) 
				{
                    			printf("     "); // Indentation for file names
                		}
                		printf("\nFile: %s	 {Size: %ld bytes}\n", de->d_name, file_stat.st_size);
            		} 
			else
		       	{
				perror("stat");
            		}
		}
		/*if(strcmp(de->d_name,".")!=0 && strcmp(de->d_name,"..") !=0)
		{
			printf(" - %s\n", de->d_name);
        
		}*/
	}
	closedir(dr);

}

// cat
void open_file(const char *file_path)
{
	FILE *fp = fopen(file_path,"r");
	if(fp)
	{
		char ch;
		while((ch = fgetc(fp))!= EOF)
		{
			putchar(ch);
		}
		fclose(fp);
	}
	else
	{
		perror("fopen");
	}
}

// editor command i.e. vim 
void edit_file(const char *file_path)
{
    	char command[300];
    	snprintf(command, sizeof(command), "vim \"%s\"", file_path); 
	// Using vim as the text editor
   	system(command);


}

// vim  to create file 
void create_file(const char *path)
{
	char f_name[256];
	char full_path[512];
	char content[1024];	// buffer for holding file contents 
	
	printf("Enter the name of the file to create (e.g. filename.txt):\t");
	scanf("%s",f_name);
	snprintf(full_path,sizeof(full_path),"%s/%s",path,f_name);
	printf("Enter Content for the file (end with a blank line ):\n");

	//read multiple lines of input until a blank line is entered
	int i =0;
	while(i < sizeof(content) -1)
	{
		//// Read a line of input
		fgets(content + i , sizeof(content) - i, stdin);
		//// Stop if a blank line is entered
		if (strcmp(content + i,"\n") == 0)
		{
			break;
		
		}
		//Moving index to the end of content
		i += strlen(content + i);

	}

	FILE *fp = fopen(full_path,"w");
	if(fp)
	{
		fputs(content,fp);
		fclose(fp);
		printf("File '%s' is created successfully.\n",full_path );
	}
	else
	{
		perror("error creating file");
	}
}

// Function to create a directory if it doesn't exist
int create_directory(const char *dir_path) 
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

// Function to delete a directory and its contents
int delete_directory(const char *dir_path) 
{
    	DIR *dir = opendir(dir_path);
    	if (!dir)
       	{
        	perror("Failed to open directory");
        	return -1;
    	}

    	struct dirent *entry;
    	char full_path[1024];

    	while ((entry = readdir(dir)) != NULL) 
	{
        	// Skip '.' and '..' directories
        	if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) 
		{
            		continue;
        	}

        	// Construct the full path for the entry
        	snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        	struct stat statbuf;
        	if (stat(full_path, &statbuf) == 0) 
		{
            		if (S_ISDIR(statbuf.st_mode)) 
			{
                		// Recursively delete subdirectory
                		if (delete_directory(full_path) != 0) 
				{
                    			closedir(dir);
                    			return -1;
                		}
           		}
		       	else if (S_ISREG(statbuf.st_mode) || S_ISLNK(statbuf.st_mode)) 
			{
                		// Delete file or symbolic link
                		if (unlink(full_path) != 0) 
				{
                    			perror("Failed to delete file");
                   			closedir(dir);
                    			return -1;
               			}
                		printf("Deleted file: %s\n", full_path);
            		}
        	}
    	}

    	closedir(dir);

    	// Remove the now-empty directory
    	if (rmdir(dir_path) != 0) 
	{
        	perror("Failed to remove directory");
        	return -1;
    	}

    	printf("Deleted directory: %s\n", dir_path);
    	return 0;
}

int delete_file(const char *file_path) 
{
    	struct stat statbuf;

    	// Check if the file exists and is a regular file
    	if (stat(file_path, &statbuf) != 0) 
	{
        	perror("File does not exist or cannot be accessed");
        	return -1;
    	}

    	if (!S_ISREG(statbuf.st_mode))
       	{
        	fprintf(stderr, "Specified path is not a regular file: %s\n", file_path);
        	return -1;
    	}

    	// Delete the file
    	if (unlink(file_path) == 0) 
	{
        	printf("Successfully deleted file: %s\n", file_path);
        	return 0;
    	}
	else
       	{
       		perror("Failed to delete file");
        	return -1;
    	}
}


// Function to search for a file in a directory and delete it if found
int search_and_delete_file(const char *dir_path, const char *target_file) {
    DIR *dir = opendir(dir_path);
    if (!dir) {
        perror("Failed to open directory");
        return -1;
    }

    struct dirent *entry;
    char full_path[1024];
    int found = 0; // Flag to indicate if the file was found

    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct the full path for the entry
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        struct stat statbuf;
        if (stat(full_path, &statbuf) == 0) {
            if (S_ISDIR(statbuf.st_mode)) {
                // Recursively search in subdirectory
                if (search_and_delete_file(full_path, target_file) == 1) {
                    found = 1; // Mark as found if the file is located in a subdirectory
                }
            } else if (S_ISREG(statbuf.st_mode)) {
                // Check if the current file matches the target file
                if (strcmp(entry->d_name, target_file) == 0) {
                    printf("File found: %s\n", full_path);
                    // Delete the file
                    if (unlink(full_path) == 0) {
                        printf("File deleted: %s\n", full_path);
                        found = 1; // File found and deleted
                    } else {
                        perror("Failed to delete file");
                    }
                }
            }
        } else {
            perror("Failed to get file status");
        }
    }

    closedir(dir);
    return found;
}
