#include "usb_manager.h"
#include "file_explorer.h"

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
    		printf("7. Exit\n");
		printf("Enter your choice :");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1: 
				printf("Enter USB device (e.g. /dev/sdb1):\t");
				scanf("%s",device);
				printf("\nEnter mount point (e.g. /media/vidi/):\t");
				scanf("%s",mount_point);
				mount_usb(device,mount_point);
				break;
			case 2:
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

			case 7:
				exit(0);
			default:
				printf("Invalid choice !!! Please try again !! \n");
		}
	}
	return 0;
}


