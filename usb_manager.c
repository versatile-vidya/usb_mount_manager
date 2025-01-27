#include"usb_manager.h"
void mount_usb(const char *device , const char *mount_point)
{
	/*mkdir(mount_point,0755)
	 * => This creates a new directory with the path specified by mount_point 
	 and the permissions set to 0755 (rwx for owner, rx for group and others).
	 * errno is a global variable set by system calls when an error occurs.
	 * EEXIST is a specific error code that means the directory already exists.
	 * The condition checks that the error is something other than the directory 
	 	 already existing. If errno == EEXIST, it’s not considered a fatal error, 
	  	since the directory already being there is often fine 		
	  	(e.g., when reusing a mount point).
	 * */
	if(mkdir(mount_point,0755) == -1 && errno != EEXIST)
	{
		perror("mkdir");
		return;
	}
	
	/*
	 * mount(device, mount_point, "vfat", 0, NULL):
	 * device: This is the file path to the device you want to mount,(e.g. /dev/sdb1).
	 * mount_point: This is the directory where the file system should be attached, (like /mnt/usb).
	 * "vfat": This is the type of file system on the device. In this case, vfat is used, which refers to FAT32 (common on USB flash drives).
	 *  0: This is a set of flags that control how the file system is mounted. A value of 0 means default options (read and write access, etc.).
	 *  NULL: This is used for file system-specific options. In most cases, it can be set to NULL.
    */
	if(mount(device,mount_point,"vfat",0,NULL) == -1 )
	{
		perror("mount");
	}
	else
	{
		printf("mounted %s to %s \n",device, mount_point);
	}
}


void unmount_usb(const char *mount_point)
{
	/*
	 * umount(mount_point):
	 * umount(): This system call unmounts a previously mounted file system from the directory specified by mount_point.
	 * After the unmount operation, the directory will no longer give access to the file system on the mounted device (like a USB drive).
	 *  mount_point: This is the directory where the device was mounted (e.g., /mnt/usb).
    */
	if(umount(mount_point) == -1)
	{
		perror("unmount");
	}
	else
	{
		printf("Unmounted %s \n",mount_point);
	}
}


