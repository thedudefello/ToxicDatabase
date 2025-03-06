


Network Password Recovery v1.57
Copyright (c) 2005 - 2024 Nir Sofer
Web Site: https://www.nirsoft.net



Description
===========

When you connect to a network share on your LAN or to your .NET Passport
account, Windows allows you to save your password in order to use it in
each time that you connect the remote server. This utility recovers all
network passwords stored on your system for the current logged-on user.
It can also recover the passwords stored in Credentials file of external
drive, as long as you know the last log-on password.



Which passwords this utility can recover ?
==========================================


* Login passwords of remote computers on your LAN.
* Passwords of mail accounts on exchange server (stored by Microsoft
  Outlook)
* Password of MSN Messenger / Windows Messenger accounts
* Internet Explorer 7.x and 8.x: passwords of password-protected Web
  sites ("Basic Authentication" or "Digest Access Authentication")
  The item name of IE7 passwords always begin with "Microsoft_WinInet"
  prefix.
* The passwords stored by Remote Desktop 6.



System Requirements
===================

This utility works properly on Windows XP, Windows 2003, Windows Vista,
Windows 2008, Windows 7, Windows 8, Windows 10, and Windows 11 - only
when you logged on as user with Administrator privileges. You can also
use this utility for recovering network passwords under Windows 98/ME.
Windows 2000 is not supported, because this version of operating system
doesn't save the network passwords.



Versions History
================


* Version 1.57:
  o Fixed a problem with decrypting passwords from external drive on
    Windows 11 22H2.

* Version 1.56:
  o Fixed the external drive feature to work properly if you sign in
    with Microsoft account.
  o Be aware that in order to decrypt Windows passwords created while
    you signed in with Microsoft account, you have to provide the random
    DPAPI password generated for your Microsoft account instead of the
    actual login password. You can find this DPAPI password with the
    MadPassExt tool.

* Version 1.55:
  o Added new option 'Load the passwords of the all logged-in users'.
    This new option allows you to recover the passwords of
    non-administrator users without typing their password, as long as the
    user is already logged into your system. Added 'Filename' column,
    which displays the credentials file where the password is stored.

* Version 1.50:
  o Added support for decrypting passwords from external drive /
    another user profile for all versions of Windows from Windows XP and
    up to Windows 10 ! (In 'Advanced Options' window - F9 )
  o Added advanced external drive settings which allows you to choose
    the desired Windows Protect folder and the Windows Credential folder
    (In 'Advanced Options' window - F9).

* Version 1.40:
  o Added 'Export Raw Passwords Data' option, which allows you to
    export all raw data from Windows credential files. You can view the
    exported file with any Hex viewer/editor, and you may find in this
    file some information that is not displayed in the main window of
    Network Password Recovery tool.

* Version 1.34:
  o Removed the command-line options that export the passwords to a
    file from the official version. A version of this tool with full
    command-line support will be posted on separated Web page.

* Version 1.33:
  o To avoid from deletion by mistake, the delete menu item is now
    separated from the others. Also, the default answer for the delete
    question is No.

* Version 1.32:
  o Added 'Mark Odd/Even Rows' option, under the View menu. When it's
    turned on, the odd and even rows are displayed in different color, to
    make it easier to read a single line.

* Version 1.31:
  o Added 'Copy Password' option (Ctrl+P).

* Version 1.30:
  o Added 'Password Strength' column, which calculates the strength
    of the password and displays it as Very Weak, Weak, Medium, Strong,
    or Very Strong.
  o Added 'Add Header Line To CSV/Tab-Delimited File' option. When
    this option is turned on, the column names are added as the first
    line when you export to csv or tab-delimited file.

* Version 1.24:
  o Fixed bug: pressing the delete key in the find window deleted an
    item in the main window.

* Version 1.23:
  o Fixed a problem with Application Compatibility Engine on Windows
    7/Vista: In some rare circumstances, this utility was shimmed by
    Application Compatibility Engine, which means that apphelp.dll and
    AcLayers.DLL were loaded into the process and replaced the Windows
    API pointers in the exports table. This API replacement caused this
    utility to crash lsass.exe and restart the operating system after a
    minute.
    This problem occured when running this utility from NirLauncher
    package, because the executable of NirLauncher contains the word
    'launch', and from unknown reason, Microsoft automatically shim every
    executable that contains the word 'launch'.

* Version 1.22:
  o Fixed bug: In some systems, Network Password Recovery crashed on
    start with Exception C0000005.

* Version 1.21:
  o Added /sort command-line option.

* Version 1.20:
  o Added support for reading and decrypting the passwords stored in
    external Credentials file.

* Version 1.15:
  o Added support for saving as comma-delimited file.
  o Fixed bug: The main window lost the focus when the user switched
    to another application and then returned back.

* Version 1.12:
  o The configuration is now saved to a file instead of the Registry.

* Version 1.11:
  o Under Vista, this utility now runs as admin automatically. You
    don't have to explicitly choose the "Run As Administrator" option.

* Version 1.10:
  o Added support for Windows Vista (both 32-bit and x64 versions)

* Version 1.03:
  o Added support for IE7 passwords. (For Web sites with HTTP
    Authentication)

* Version 1.02:
  o Delete passwords option (Windows XP only).

* Version 1.01:
  o Added support for Windows XP styles.
  o Added support for Autologon password stored by Microsoft Tweak UI
    tool

* Version 1.00: First release.



Where the network passwords are stored ?
========================================

Older versions of Windows (Windows 95,98 and ME) stored the network
passwords in pwl files located under the main Windows folder.
Starting from Windows XP, the network passwords are encrypted inside the
Credentials file, located under Documents and Settings\<User
Name>\Application Data\Microsoft\Credentials\<User SID>. Some passwords
may also be stored in the Credentials file under Documents and
Settings\<User Name>\Local Settings\Application
Data\Microsoft\Credentials\<User SID>.
In addition to the passwords of network shares, Windows XP also stores
the passwords of .NET Passport (MSN Messenger) in the same Credentials
files



Credentials file in external drive
==================================

Starting from version 1.20, you can also read the Credentials from an
external profile in your current operating system or from another
external drive (For example: from a dead system that cannot boot
anymore). In order to use this feature, you must know the last logged-on
password used for this profile, because the Credentials file is encrypted
with the SHA hash of the log-on password, and without that hash, the
Credentials file cannot be decrypted.
You can use this feature from the UI, by selecting the 'Advanced Options'
in the File menu, or from command-line, by using /external parameter. The
user profile path should be something like "C:\Documents and
Settings\admin" in Windows XP/2003 or "C:\users\myuser" in Windows
10/8/7/Vista/2008.

Notice: If the passwords were encrypted under Microsoft account sign-in,
you have to extract the encryption password with the MadPassExt tool and
then paste this password into the Windows Login Password field.



License
=======

This utility is released as freeware. You are allowed to freely
distribute this utility via floppy disk, CD-ROM, Internet, or in any
other way, as long as you don't charge anything for this and you don't
sell it or distribute it as a part of commercial product. If you
distribute this utility, you must include all files in the distribution
package, without any modification !



Disclaimer
==========

The software is provided "AS IS" without any warranty, either expressed
or implied, including, but not limited to, the implied warranties of
merchantability and fitness for a particular purpose. The author will not
be liable for any special, incidental, consequential or indirect damages
due to loss of data or any other reason.



Using Network Password Recovery
===============================

This utility doesn't require any installation process or additional DLLs.
In order to start using it, just extract the zip file to any folder you
like, and run the executable file - netpass.exe .
When you run this utility, the main window displays all network passwords
found on your system. You can select one or more items, and then copy
them to the clipboard, or save them to text/HTML/XML file.



Command-Line Options
====================



/stext <Filename>
Save the list of network passwords into a regular text file.

/stab <Filename>
Save the list of network passwords into a tab-delimited text file.

/scomma <Filename>
Save the list of network passwords into a comma-delimited text file.

/stabular <Filename>
Save the list of network passwords into a tabular text file.

/shtml <Filename>
Save the list of network passwords into HTML file.

/sverhtml <Filename>
Save the list of network passwords into vertical HTML file.

/sxml <Filename>
Save the list of network passwords into XML file.

/sort <column>
This command-line option can be used with other save options for sorting
by the desired column. If you don't specify this option, the list is
sorted according to the last sort that you made from the user interface.
The <column> parameter can specify the column index (0 for the first
column, 1 for the second column, and so on) or the name of the column,
like "Item Name" and "Type". You can specify the '~' prefix character
(e.g: "~Password") if you want to sort in descending order. You can put
multiple /sort in the command-line if you want to sort by multiple
columns.

Examples:
netpass.exe /shtml "f:\temp\pass.html" /sort 2 /sort ~1
netpass.exe /shtml "f:\temp\pass.html" /sort "Type" /sort "Item Name"

/nosort
When you specify this command-line option, the list will be saved without
any sorting.

/NoLoadSettings
Run without loading your last settings. (window position, columns size,
etc. )

/DeleteRegKey
Delete the Registry key that this utility use to save your last settings.

/external <User Profile Path> <Last Log-On Password>
Load the Credentials file from external drive/profile. For example:
netpass.exe /external "F:\Documents and Settings\administrator"
"MyPassword"



Translating this utility to other languages
===========================================

In order to translate this utility to other language, follow the
instructions below:
1. Run Network Password Recovery with /savelangfile parameter:
   netpass.exe /savelangfile
   A file named netpass_lng.ini will be created in the folder of Network
   Password Recovery utility.
2. Open the created language file in Notepad or in any other text
   editor.
3. Translate all string entries to the desired language. Optionally,
   you can also add your name and/or a link to your Web site.
   (TranslatorName and TranslatorURL values) If you add this information,
   it'll be used in the 'About' window.
4. After you finish the translation, Run Network Password Recovery,
   and all translated strings will be loaded from the language file.
   If you want to run this utility without the translation, simply rename
   the language file, or move it to another folder.



Feedback
========

If you have any problem, suggestion, comment, or you found a bug in my
utility, you can send a message to nirsofer@yahoo.com
