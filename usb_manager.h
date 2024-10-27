//USB_MANAGER_H
//
#ifndef USB_MANAGER_H
#define USB_MANAGER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/mount.h>
#include<sys/stat.h>
#include<errno.h>


void mount_usb(const char *device, const char *mount_point);
void unmount_usb(const char *mount_point);

#endif 
