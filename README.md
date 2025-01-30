#  USB File System Explorer (USB Mount Manager)

## Objective of the Project:

The objective of this project is to develop a robust USB Mount Manager capable of managing the mounting and unmounting of USB devices on a system. The project aims to enhance the handling of USB devices by implementing features like automated detection, secure mounting, efficient unmounting, and logging of activities to ensure seamless interaction with external storage devices.

## Completed Task Description:

### 1.Automated USB Detection:

Implemented functionality to detect USB devices as soon as they are plugged into the system. This ensures that the system is aware of new devices immediately, allowing further operations to proceed without delay.

### 2.Secure Mounting:

Developed a mechanism to securely mount the USB devices, ensuring proper access permissions. This prevents unauthorized users from accessing the data and safeguards sensitive information.

### 3.Efficient Unmounting:

Added support for unmounting USB devices safely to prevent data corruption or loss. This feature ensures that all read/write operations are completed before the device is disconnected.

### 4.Malicious File Detection:

Detects potentially malicious files on the USB device and provides options to edit or delete the identified files. The detection is carried out using three methods:

  1.  By File Extension: Identifies potentially harmful files based on their extensions, such as .exe, .bat, or .vbs.

  2.  By File Type: Inspects the file type to ensure it matches the expected type based on its content, flagging discrepancies.

  3.  By Viewing File Content: Scans the file's content for known malicious patterns or	behaviors.

### 5.Command-line Interface:

Designed a simple command-line interface for users to interact with the tool. It provides commands for mounting, unmounting,  and giving interface to perform actions like listing the files,deleting files and directories, editing files, and creating files and directories,  and checking device status, making it easy for users to manage USB devices.
    • Listing Files: Displays all the files and directories within the mounted USB device.
    • Deleting Files and Directories: Provide the functionality to delete specific files or entire directories from the USB device.
    • Editing Files: Allow users to open and edit files directly from the USB device.
    • Creating Files and Directories: Enable users to create new files and directories on the USB device.

### 6.Testing and Validation:

Conducted rigorous testing on different USB devices with various file systems. This ensured that the system is compatible with a wide range of devices and works reliably under different conditions.

### 7.Additional Features:

File System Type Detection: Automatically detects the file system type of the connected USB device. This helps in determining the appropriate actions required for mounting.

Disk Usage Display: Displays the  used space on the USB device and files and their file sizes, providing users with an overview of their storage.

Hotplug Support: Monitors for USB connection and disconnection events in real-time without manual intervention. This enhances the user experience by automating device management.

Custom Mount Points: Allows users to specify custom mount points for USB devices, giving them flexibility in organizing their storage.

Malicious File Detection: Detects potentially malicious files on the USB device and provides options to edit or delete the identified files. The detection is carried out using three methods:
by File Extension ,by File Type, by Viewing File Content.This feature helps in maintaining system security and preventing malware infections.

## Conclusion:

The USB Mount Manager successfully achieved its primary goal of managing USB devices efficiently and securely. The tool ensures seamless interaction with external USB storage devices by automating the detection, mounting, and unmounting processes. With its robust error-handling and logging features, the manager provides a reliable solution for USB management needs.

## Final Outcome:
The project resulted in a fully functional USB Mount Manager tool that:

  1. Automatically detects USB devices upon connection.
  2. Securely mounts and unmounts devices, preventing data corruption.
  3. Offers a user-friendly command-line interface for easy management.
  4. Detects file system types and displays files usage information.
  5. Supports hotplug detection and custom mount points.
  6. Detects malicious files and offers options for editing or deleting them.

This tool is a valuable addition for systems requiring efficient USB device handling and can be further enhanced with features like GUI integration or support for advanced encryption methods in future iterations.

## How to use :
  1.Install lib-magic library <br>
  <pre>sudo apt-get update
sudo apt-get install libmagic-dev
</pre>
  2.Run on command line :<br>
    <pre>  make </pre><br>
  3. Then type on command line :<br>
      <pre>sudo ./usb</pre><br>
        
