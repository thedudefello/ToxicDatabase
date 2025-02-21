> [!WARNING]
> This project was built for Windows 8.1.
> 
> I am not sure if you can run this script properly on newer operating systems.
> 
> This warning message will be removed/changed when I be sure.

# Immortal.bat (My First Batch Project)
Batch script which was created for educational and entertaiment purposes only. The script provides interesting tricks with modern Windows (particularly Windows 8.1 and newer), but is also capable of damaging files, registry data etc.

![](https://github.com/MalwareStudio/Immortal/blob/main/images/Menu_1.1.1.png)

Check out the video about Immortal.bat 👉 [Full Demonstration](https://www.youtube.com/watch?v=p6LZ-45KQ60)

## Watch out!
There is an Operating System Detection so do not be surprised why the script is not working on Windows 7 or older.

![](https://github.com/MalwareStudio/Immortal/blob/main/images/OsDetection.png)

## This was a challenge!

Yes, it really was. One day I asked my self "Wouldn't be a crazy idea to create interesting and destructive batch script with user interface?".
And just with that, I started learning the batch script.

## What's the purpose?

A lot of people in our community view batch script as a "scripting language for skidders". This might be true due to the fact how easy is to code in the batch script. However, I am not a script kiddie anymore and I want to prove you that even with the batch script you can do pretty amazing stuff in the Windows.

So what's the purpose of this? Just to show you what batch script can be capable of!

## My opinion on Batch Script

Well, I have to say that learning this script did not take long becuase batch is very low level scripting language. However, I ran into a lot of problems with syntax, spacing issues and escaping. So, it was not clean process as I thought it will be.

For instance: When I was trying to escape keyword "do" inside if statement it did not let me do that. No metter how hard you try to escape "do" keyword inside if statement or for loop, you will always fail.

Would I recommend batch script to you? Yes, but be prepared for a lot of errors and stay calm (not like me :D) because there is always reason why the problem occured.

## How this script works?

When you launch Immortal.bat, the first thing that you are going to experience is UAC promt. That is because this script need a administrator privileges to change and remove important files. Without these rights, the script would not do much. Then the script will show you the main menu with all stages (in other words levels) which you can try. 

Meanwhile, the script already dropped some of its files in `C:\Immortal` directory and it created bunch of registry files in `HKEY_LOCAL_MACHINE\SOFTWARE\Immortal`. These files are very important for the script functionality. Also, it chnage the registry value "Shell" in order to start up along with explorer.exe.

## Levels

### Casual 😇
The harmless level.

It hide files, randomly launch applications, open random websites and lastly it restart the system via shutdown command.

The console window is visible.

![](https://github.com/MalwareStudio/Immortal/blob/main/images/casual_1.1.2.png)

### Normal 😊
It is a still harmless level, but some of its features can cause problems to users who does not understand basic stuff in registry and basically anyone who lacks basic knowledge in Windows.

First it disable Task Manager then Registry Editor, it will also disable UAC protection. Lastly it remove the wallpaper and write a message to the user.

The console window is visible.

![](https://github.com/MalwareStudio/Immortal/blob/main/images/normal_1.1.3.png)

> [!WARNING]
> The `msg` command is not part of the Windows Home Edition.
>
> So if you are running Immortal on Windows 10/11 Home it will not show up, on the other hand, both Pro Editions have this command.

### Annoying 😐
This level can do mess in the system. However, it does not do any kind of damage so it is still classified as a harmless level.

After execution it change a lot of file icons, rename username, create welcome message, swap the mouse inputs and it disable the Task Manager, Registry Editor and UAC protection. Pressing any key will lead to reboot.

![](https://github.com/MalwareStudio/Immortal/blob/main/images/annoying_1.1.2.png)

**1st Payload**

After reboot, the Annoying Level will activate first payload.
In this payload, the script will try to create a gibberish files on all drives and its subdirectories.

> [!NOTE]
> If you want to launch any of these payloads then you need to restart the computer.
> 
> After every restart you will come across to another payload.

**2nd Payload** (not shown in the video)

When this payload is launched, random gibberish message boxes will be displayed. Styles and buttons of the message boxes can appear randomly.

**3rd Payload**

This payload is about downloading files from hardcoded download links. When the file is downloaded, it will try to open it.
All the files will be stored inside `C:\Download` directory.

**4th Payload**

It will launch two scripts `spam.bat` and `letmeransomeaps.bat`. This payload will slowdown the system because it will attempt to launch all files from system32 directory. `spam.bat` only display command `dir C:\ /s` with different variations of colors.

When you try to reboot the system again, you will return to the main menu.

The console window is visible, but it will change after reboot.

### Harsh 🙁
This level can actually damage some data.

After execution the script will take ownership of some non critical system files such as Device Manager, Task Manager and so on... Then it will delete these files.

Keyboard is going to be also changed. Some keys can even open applications.

This level have also date timed payloads such as 02/11 | 11.2 - Shell Overwritter, 04/01 | 1.4 - Delete Classes. The default payload without date timed changes is File Overwritter. Date timed payloads and default can happen in the last payload aka 4th one.

The console window is visible, but it will change after reboot.

![](https://github.com/MalwareStudio/Immortal/blob/main/images/harsh_1.1.5.png)

**1st Payload**

When the message box apper with the text `"Lets get some friends"` it will immediatelly start to creating 1000 accounts with random gibberish names and passwords. Luckely your account will not be affected.

> [!WARNING]
> Sometimes accounts can appear right after the payload starts, but it is not always like that.
> 
> If you cannot see any changes then you need to restart the computer.

**2nd Payload**

Another payload will create new drives. That can explain the message `"Its time to expand"`.

But before that, the script will convert the primary disk into dynamic disk. By doing this, it can create as many drives as it wants.

**3rd Payload**

This payload just disconnects the internet connection. Nothing else to say about this one ...

**4th Payload - (default) File Overwritter**

It will search for all conected drives and then it will overwrite all files within these drives and their subdirectories with message `"OVERWRITTEN BY IMMORTAL.BAT"`.

You might even lose files in the share folder so be careful!

**4th Payload - 02/11 | 11.2 - Shell Overwritter**

This payload will just replace `explorer.exe` to `epilepsy.bat` so after reboot instead of seeing your desktop with all icons, you are going to see batch script which changes its colors randomly and says `"HACKED BY IMMORTAL.BAT"` multiple times.

**4th Payload - 04/01 | 1.4 - Delete Classes**

It will try to delete all classes from registry which are exactly located in `HKEY_LOCAL_MACHINE\SOFTWARE\Classes` or `HKEY_CLASSES_ROOT`. By deleting these classes you will not be able to open any application.

After reboot you are going to see a black screen with some error messages.

### Cruel 😡
This level causes a serious problems on Windows.

When you execute this level, you are paused by its menu. Before you press any key you can decide which type of payload you want to execute.

03/30 | 30.3 - System32 Corruption
12/25 | 25.12 - Image File Execution Option
01/01 | 1.1 - File Injection
There is also a default payload - Font Corruption

![](https://github.com/MalwareStudio/Immortal/blob/main/images/cruel_1.1.9.png)

> [!WARNING]
> Because these payloads will cause a serious damage to your devide, you might not be able to return to the script UI.

The console window is visible, but it will change after reboot.

**(default) Font Corruption**

This payload will try to delete all fonts from the registry. Fonts will not be deleted directly, only their registry data.

After reboot you are going to experience gibberish text across the screen and Windows will eventually crash.

**03/30 | 30.3 - System32 Corruption**

When you launch this payload it will try to take ownership of all files in the system32 folder and then it will try to erase them all.

After reboot you will not be able to boot into your system again.

**12/25 | 25.12 - Image File Execution Option**

This payload is fully based on registry. It will create a new key called `dwm.exe` inside `HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options`. After that it will create a new string value called `debugger` with string `notepad.exe`. 

After reboot it will try to open `dwm.exe` from `notepad.exe` which will cause some problems with Windows UI.

> [!NOTE]
> Desktop Window Manager or DWM.exe is the system manager that generates every element visible on a PC/laptop. In addition, it is responsible for stimulating all visual effects in Windows menus, transparent components, wallpapers, themes, thumbnails and
> system animations.

**01/01 | 1.1 - File Injection**

Another based registry payload. This one will hook all files in `HKEY_LOCAL_MACHINE\SOFTWARE\Classes` by modifying default string value located in `command` key.
Instead of running for example notepad.exe you will get batch script with random colors and it will say `"INJECTED BY IMMORTAL.BAT"`.

### Deadly 😈
This level does not require any date time changes. When you press any key it will try to take ownership of all files in all drives and delete them.

It will also try to delete all registry data.

Lastly it will delete `C:\Recovery` directory. Because recovery directory contains necessary files to launch the `Automatic repair`, Windows will not be able to even try to repair the system.

![](https://github.com/MalwareStudio/Immortal/blob/main/images/deadly_recovery_1.1.14.png)

## Fun facts
It took me 1 month to finish this project.

The code is hardcoded because I was working on some payloads separately outside of the script. If you are wondering why, it is because when the code grew more and more it got much more confusing.
