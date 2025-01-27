#include "usb_manager.h"
#include "file_explorer.h"
#include "milli_file_detect.h"

int main()
{
	char device[256];
	char mount_point[256];
	int choice;

	while(1)
	{
		printf("\nUSB Mount Manager and File System Explorer\n");
   		printf("1. Mount USB\n");
    		printf("2. Unmount USB\n");
    		printf("3. List Files\n");
    		printf("4. Open File\n");
    		printf("5. Edit File\n");
    		printf("6. Create  File\n");
    		printf("7. Create Directory\n");
    		printf("8. Delete  File\n");
    		printf("9. Delete  Directory \n");
    		printf("10. Exit\n");
		printf("Enter your choice :");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:	/* mounting and scannig  all files and directories 
				 * and  separating all good files  and bad files 
				 * Based on :
				 * 	1. extension
				 * 	2. file type
				 * 	3. file content 
				 * deleteing  good files directory and
				 * deleting millicious  files  
				 * */
				printf("Enter USB device (e.g. /dev/sdb1):\t");
				scanf("%s",device);
				printf("\nEnter mount point (e.g. /media/vidi/):\t");
				scanf("%s",mount_point);
				mount_usb(device,mount_point);
				// scanning process  and making good and bad directories 
				
				// Process the mounted directory for suspicious files
   				printf("Scanning for malicious files in mounted directory...\n");
    				char good_dir[512], bad_dir[512];
    				snprintf(good_dir, sizeof(good_dir), "%s/good_files", mount_point);
    				snprintf(bad_dir, sizeof(bad_dir), "%s/bad_files", mount_point);

    				create_directory_if_not_exists(good_dir);
    				create_directory_if_not_exists(bad_dir);

    				process_directory(mount_point, good_dir, bad_dir);
				//process_files(mount_point, good_dir, bad_dir);
				printf("file classification completed\n");

				delete_directory(good_dir);
				int ch;
				do
				{
					printf("\nOptions to handle millicious files\n");
					printf("1.List Files\n");
					printf("2.Delete File \n");
				//	printf("3.Delete Directory\n");
					printf("3.Exit\n");
				       	printf("Enter the choice :\t");
			       		scanf("%d",&ch);       
					switch(ch)
					{
						case 1: 
							//char  dr_path[256];
							printf("\nEnter path (e.g /media/vidi/bad_files):\t");
							scanf("%s",mount_point); //dr_path);
							printf("Printing all files in bad_files directory.\n ");
							list_files(mount_point,0);//dr_path,0);
							break;
						case 2: char file_name[256];
							printf("Delete file from bad_files directory.\n");
							printf("\nEnter path (e.g /media/vidi/):\t");
							scanf("%s",mount_point);
							printf("Enter the file name:\t");
						        scanf("%s",file_name);
						//	delete_file(mount_point);
							search_and_delete_file(mount_point, file_name);
	
							break;
						/*case 3:
							printf("Delete the directory .\n");
							printf("\nEnter mount_point (path) (e.g /media/vidi/bad_files):\t");
							scanf("%s",mount_point); 
							delete_directory(mount_point);
							break;*/
						case 3:
							printf("exiting loop\n");
							break;							
						default:
							printf("Invalid choice !!! Please try again !! \n");

					}
				}while(ch != 3);

				break;
			case 2:	// umount 
				// first deleting bad files directory if not deleted
				printf("Enter path of bad_files directory:\t");
			        scanf("%s",mount_point);

				printf("Attempting to delete directory: %s\n", mount_point);

   				if (delete_directory(mount_point) == 0)
			       	{
       					 printf("directory deleted successfully.\n");
    				}
		       		else 
				{
        				printf("Failed to delete the directory.\n");
    				} 
				printf("\nEnter mount point (e.g /media/vidi/):\t");
				scanf("%s",mount_point);
				unmount_usb(mount_point);
				break;
			case 3 : // ls command
				printf("\nEnter mount point  (e.g /media/vidi/device_name):\t");
				scanf("%s",mount_point);
				list_files(mount_point,0);
				break;
			case 4: // cat command
				printf("Enter the file path  to open:\t ");
				char file_path[256];
				scanf("%s",file_path);
				open_file(file_path);
				break;
			case 5: // vim command  i.e. edit file
				printf("Enter the file path  to open:\t ");
				char edit_file_path[256];
				scanf("%s",edit_file_path);
				edit_file(edit_file_path);
				break;
			case 6: // creating file 
				printf("Enter the mount point :\t");
				scanf("%s",mount_point);
				create_file(mount_point);
				break;
			case 7: // mkdir command (i.e. creating directory) 
				printf ("Enter the directory name :\t");
				char dir_name[256];
				scanf("%s",dir_name);
				char new_dir[512];
    				snprintf(new_dir, sizeof(new_dir), "%s/%s", mount_point,dir_name);

    				create_directory(new_dir);
				break;

			case 8: // rm command (i.e deleting  file)
				printf("Enter the file path  to delete :\t");
			        char fp[256];  		// fp -> file path 
				scanf("%s",fp);
				printf("Attempting to delete file: %s\n", file_path);

    				if (delete_file(fp) == 0) 
				{
        				printf("File deleted successfully.\n");
    				}
			       	else
			       	{
       					 printf("Failed to delete the file.\n");
    				}
			        //delete_file(fp);
				break;
			case 9: // rm -R command (i.e. deleting directory )
				printf("Enter the directory path  to delete :\t");
			        char dirpath[256];  		 
				scanf("%s",dirpath);
			       // delete_file(dirpath);
				printf("Attempting to delete directory: %s\n", dirpath);

   				if (delete_directory(dirpath) == 0)
			       	{
       					 printf("directory deleted successfully.\n");
    				}
		       		else 
				{
        				printf("Failed to delete the directory.\n");
    				}
				break;


			case 10:
				exit(0);
			default:
				printf("Invalid choice !!! Please try again !! \n");
		}
	}
	return 0;
}


