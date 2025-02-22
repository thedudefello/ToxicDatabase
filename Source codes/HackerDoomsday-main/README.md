**HackerDoomsday is a trojan written in python and capable of many features, but let's start in order:**

![image](https://github.com/user-attachments/assets/f70b3456-6d21-46d1-ad92-de26f7794313)
*First page of the application*

# What happens after the launch?

After launching, a siren starts to sound and a fake message appears stating that the computer urgently needs an antivirus update(**The language can be changed only on the first page, using the buttons in the upper left corner, Russian and English are available.)**, after the fake configuration, the internet traffic is supposedly hacked by hackers and after rebooting a video is played where the hacker explains the basic rules (what to do to keep your computer safe). After one more reboot the system will boot with explorer.exe (before it was removed in the registry), application icons, wallpaper, and the main color of windows will be changed, access to some system applications will be disabled through the registry (cmd, regedit, etc.) and scary music will play. Also on the desktop will appear about 200 files, txt along with empty exe. In txt files will be written literally all the same things that were in the video. But the most important thing is GDI effects that will appear when opening applications. The more applications the user opens, the stronger the GDI effects will be, which will greatly hinder the removal of the virus. 

![Windows 10-2025-02-22-21-03-25](https://github.com/user-attachments/assets/59f01a29-6b12-4ba5-9fc7-d63d25fa6fb8)

# Other possibilities of the virus
- Pressing ctrl+alt+del or ctrl+alt+insert causes a BSOD
- If the user launches any application that is unwanted by the virus, a short video is played where the hacker makes threats, and after the video, a BSOD occurs
- Video, the “settings” window of the antivirus is on top of other windows
- When closing a virus process, a BSOD occurs, but not because the process is critical, but because VBS monitors the presence of the process, and if the process is not found, a bat is launched, which causes a BSOD. But if you first close VBS, and then only the virus process, everything will go well (I want to make the process truly critical in future versions, but I don’t know how to do this in Python and I’m not even sure if this is possible, but if someone knows how to do this, you can write in the issue or by contact information).
- The virus autostarts via Shell in the registry (it also starts in safe mode)
- The virus file is copied to Windows\INF under a different name and under the attributes hidden and system
- BSOD will be thrown when opening Windows or Windows\INF folders in Explorer
  
*If you have any wishes or ideas, you can write an issue or contact information* 
