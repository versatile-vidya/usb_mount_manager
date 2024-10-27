#include "file_explorer.h"
#include<sys/stat.h>
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

void edit_file(const char *file_path)
{
    	char command[300];
    	snprintf(command, sizeof(command), "vim \"%s\"", file_path); 
	// Using vim as the text editor
   	system(command);


}


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

