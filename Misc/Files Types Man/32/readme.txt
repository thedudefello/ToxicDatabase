


FileTypesMan v2.00
Copyright (c) 2008 - 2024 Nir Sofer
Web site: https://www.nirsoft.net



Description
===========

FileTypesMan is an alternative to the 'File Types' tab in the 'Folder
Options' of Windows. It displays the list of all file extensions and
types registered on your computer. For each file type, the following
information is displayed: Type Name, Description, MIME Type, Perceived
Type, Flags, Browser Flags, and more.
FileTypesMan also allows you to easily edit the properties and flags of
each file type, as well as it allows you to add, edit, and remove actions
in a file type.



System Requirements
===================

This utility works on any version of Windows from Windows XP to Windows
11. For using this utility under x64 system, you should download the x64
version.



Crash/hang on Loading Icons...
==============================

If FileTypesMan crashes or hangs on your system while loading icons
('Loading Icons...' message is displayed in the status bar), you should
run FileTypesMan with /DontLoadIcons command:
FileTypesMan.exe /DontLoadIcons 1



Known issue with 'Choose Icon' window on some Windows 10 systems
================================================================

Some people reported that in the latest updates of Windows 10, when
trying to select an icon by clicking the '...' button of the icon field,
the FileTypesMan tool stops responding. I tried to reproduce the problem
on my systems, but in all tests this 'Choose Icon' window worked
completely fine. Moreover, the 'Choose Icon' window is displayed by
calling API of Windows operating system (PickIconDlg) , so this bug is
actually a problem of Windows operating system, it's not a bug inside
FileTypesMan.
If you know the filename and the icon number you want to choose, you can
type it directly inside the field without using the 'Choose Icon' window.

Versions History
================


* Version 2.00:
  o Added new option: Don't Load Icons That May Hang/Crash (Turned on
    by default). When this option is turned on, FileTypesMan doesn't load
    file type icons if their default icon is '%1' (Some of these icons
    cause FileTypesMan to hang or crash when trying to load them).

* Version 1.98:
  o Added option to change the sorting column from the menu (View ->
    Sort By and Actions -> Sort By).
  o Added 'Sort By' buttons to the toolbar.

* Version 1.97:
  o FileTypesMan doesn't allow you anymore to change the 'Default
    Icon' for .exe extension. It's because many people try to modify the
    icon of .exe files and then ask my help in order to revert it back...

* Version 1.96:
  o Fixed the find dialog-box to work properly when you press the Del
    key.

* Version 1.95:
  o Added 'Copy Selected Actions' and 'Paste Actions' options, which
    allows you to copy one or more actions into the clipboard and then
    paste them into another file type / extension.
  o Fixed bug: When a file extension had a 'User Choice' entry that
    cannot be accessed , FileTypesMan displayed and edited the actions of
    the file type, instead of displaying 'Access Denied' error message.

* Version 1.90:
  o Added 'Run As TrustedInstaller' option (Under the Help menu). You
    can use this feature to view and modify file types that their owner
    is TrustedInstaller, like the Windows Media Player menu items of .mp3
    file extension. (If you try to modify TrustedInstaller entries
    without running FileTypesMan as TrustedInstaller, you'll get the
    'Access is denied' error message. )
  o Added 'Registry Key Owner' column for both upper pane and lower
    pane. When the Registry Key Owner on the lower pane is 'NT
    SERVICE\TrustedInstaller' , you have to run FileTypesMan as
    TrustedInstaller in order to modify the file type action. Otherwise,
    you'll get 'Access is denied' error message.

* Version 1.86:
  o You can now use the combination of /SelectedExt command and the
    save command-line options (/scomma, /shtml, and so on...) to export
    from command-line the actions of specified file extension.
  o For example, in order to export to csv file all actions of .txt
    extension:
    FileTypesMan.exe /SelectedExt .txt /scomma "c:\temp\txtext.csv"
  o You can now send the file types information to stdout by
    specifying an empty filename ("") in the save command-line options.
    (For example: FileTypesMan.exe /scomma "" | more)

* Version 1.85:
  o Added 'Icon' column to the lower pane.
  o Added Icon field to the 'Edit Action' window.

* Version 1.83:
  o When you run FileTypesMan, it now automatically selects the last
    selected extension.
  o Added /SelectedExt command-line option for selecting the desired
    extension in the upper pane, for example:
    FileTypesMan.exe /SelectedExt ".txt"

* Version 1.82:
  o Added 'Icon Handler CLSID' column. When a file type has an icon
    handler, the icon handler set the actual icon that will be displayed
    for the file, instead of the 'Default Icon' value.

* Version 1.81:
  o Added Drive and Directory\Background types.
  o Fixed bug: FileTypesMan displayed incorrect Registry keys for
    Directory.

* Version 1.80:
  o Added 'Detach File Type' button to the 'Replace File Type For
    Selected Extension' option, which allows you to detach a file type
    from the selected file extension and leave the file extension as a
    standalone extension without a file type. If you detach a file type
    from a file extension, changing the icon and menu items won't affect
    other file extensions (Be aware that you may also need to clear the
    'User Choice' field, if it's not empty)
  o Added '...' button to the 'User Choice' field, which opens a
    window that allows you to easily choose the desired file type.
  o Fixed FileTypesMan to use the correct file type Registry key,
    when there is a CurVer subkey that redirects to other file type key.
    In previous versions, FileTypesMan failed to change the icon and menu
    items of .pdf and other extensions due to this bug.
  o FileTypesMan now stores the selected font in the .cfg file.
  o FileTypesMan now displays an error message if it fails to modify
    action or file type.

* Version 1.72:
  o Fixed a crash problem occurred while loading the icon of
    .appref-ms extension, on some systems.
  o Added 'NoIconsExt' line to the .cfg file, which contains a
    comma-delimited list of file extensions that FileTypesMan won't load
    their icons, in order to avoid a crash.

* Version 1.71:
  o FileTypesMan now displays the extension name in the status bar
    while loading the icons of all file extensions.

* Version 1.70:
  o When editing a file type that shares multiple file extensions,
    FileTypesMan will display a list of file extensions that might be
    affected by editing the file type.

* Version 1.68:
  o FileTypesMan now doesn't allow you to replace the file type of
    .exe extension, because this action may cause a severe problem in
    Windows Explorer.

* Version 1.67:
  o Fixed bug: FileTypesMan failed to display the menu items of
    Directory under Windows 7.

* Version 1.66:
  o Added /scomma command-line option, which was missing in previous
    versions.

* Version 1.65:
  o Fixed the flickering occurred while scrolling the file types list.
  o Added new command-line options: /DontLoadIcons ,
    /MarkDisabledActions , /AutoDesktopRefresh , /ShowURLProtocols ,
    /ExtractResourceCaption , /ShowApplicationsTypes

* Version 1.62:
  o Added 'Auto Size Columns+Headers' option.
  o Fixed issue: Dialog-boxes opened in the wrong monitor, on
    multi-monitors system.

* Version 1.61:
  o Added 'Mark Odd/Even Rows' option, under the View menu. When it's
    turned on, the odd and even rows are displayed in different color, to
    make it easier to read a single line.

* Version 1.60:
  o Added 'Add Header Line To CSV/Tab-Delimited File' option. When
    this option is turned on, the column names are added as the first
    line when you export to csv or tab-delimited file.

* Version 1.58:
  o Fixed issue: Removed the wrong encoding from the xml string,
    which caused problems to some xml viewers.

* Version 1.57:
  o Added 'Hide Dot In Extension' option. When this option is turned
    on, the preceding dot is not displayed in the extension column.

* Version 1.56:
  o Fixed icons problem on Windows7/x64.

* Version 1.55:
  o Fixed issue: When UserChoice is selected, FileTypesMan now
    displays the right file type properties loaded from the UserChoice
    application key.
  o Fixed issue: When UserChoice is selected, the 'Open File Type In
    RegEdit' option now opens the right UserChoice application key.

* Version 1.53:
  o When UserChoice is selected for specific extension in Windows
    7/Vista, FileTypesMan now display the actions of the UserChoice
    instead of the actions of the file type/extension.

* Version 1.52:
  o Added command-line options to save the types/extensions list into
    html/text/xml/csv file.

* Version 1.51:
  o Added 'Choose Icon' dialog-box like in the file types manager of
    Windows, to allow you to easily choose the desired file type icon.
    (Works only on Windows XP or greater)

* Version 1.50:
  o Added the option to select one or more file extensions, and then
    send the information to extension.nirsoft.net Web site. This Web site
    collects a general statistics information about file extensions and
    allows you to find out which programs can open the desired file
    extension.
  o Added 'View Extension In extension.nirsoft.net' option, so you
    can view the extensions information submitted by other users of
    FileTypesMan utility.
  o Added version information columns for the extension, according to
    the dll/exe of the file-type icon.

* Version 1.45:
  o Added version information columns in the actions table - Product
    Name, Product Version, Product Description, and Company Name.

* Version 1.42:
  o Added 'Extended' property to action dialog-box. When this
    property is turned on, the menu item will be displayed only if you
    press the Shift key.

* Version 1.41:
  o Added 'Jump To User Choice Entry' option - for file types with
    'User Choice' in Windows Vista/7.

* Version 1.40:
  o Added application entries. (Stored in
    HKEY_CLASSES_ROOT\Applications)
  o Added support for 'UserChoice' entries in Windows Vista/7 (Stored
    in
    HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Explorer\Fi
    leExts\[.extension]\UserChoice). User Choice option is used when you
    right click on a file, and choose the default program (Open With ->
    Choose Default Program). UserChoice overwrites the default action
    when you double-click the file.
  o Added 'File Type Group' column - Standard, Perceived Type, URL
    Protocol, or Application.

* Version 1.30:
  o Added support for actions under
    HKEY_CLASSES_ROOT\SystemFileAssociations key.
  o Added 'SystemFileAssociations' column for actions.
  o Added 'Registry Key' column for actions.
  o Added 'Extract Resource Captions' option - For actions that their
    captions are stored inside a resource (For example:
    '@%SystemRoot%\system32\stobject.dll,-417') this option automatically
    loads the real caption from the resource file and displays it in the
    caption column.

* Version 1.21:
  o Fixed bug: Adding new extension didn't work if the user didn't
    specify the extension name with a dot prefix.
  o Added more accelerator keys.

* Version 1.20:
  o Added support for creating and deleting file extensions.
  o A few bugs fixed.

* Version 1.11:
  o Added more accelerator keys.

* Version 1.10:
  o Added support for perceived types (video, audio, image, text, and
    system)
  o Added 'Open Action In RegEdit' option.
  o Added 'Open File Type In RegEdit' option.

* Version 1.08 - The dialog-boxes are now resizable.
* Version 1.07 - Added new option: Select Another Font.
* Version 1.06 - Fixed bug: The main window lost the focus when the
  user switched to another application and then returned back to
  FileTypesMan.
* Version 1.05 - Added support for URL protocols. (Options->Show URL
  Protocols)
* Version 1.04 - Added support for saving to comma-delimited file.
* Version 1.03 - Added 'Always Show Extension' column.
* Version 1.02 - Fixed bug: FileTypesMan failed to add the first action
  in a file type.
* Version 1.01 - Fixed critical bug under Windows 98 - Icons
  disappeared in the 'start' menu.
* Version 1.00 - First release.



Start Using FileTypesMan
========================

FileTypesMan doesn't require any installation process or additional DLL
files. In order to start using it, simply copy the executable file
(FileTypesMan.exe) to any folder you like, and run it.
After running it, you should wait a few seconds until the file types list
is loaded. If the loading process is too slow, it's recommended to turn
off the icons loading (Options->Don't Load Icons in menu), so in the next
time that you run FileTypesMan, the loading process will be faster.
The main window of FileTypesMan contains 2 panes. The upper pane displays
the list of all extensions/file types registered on your computer. When
you select a single file type in the upper pane, the lower pane displays
the list of all actions of the selected type.



'Replace File Type For Selected Extension' option (F4)
======================================================

Sometimes, when you install a new software, it automatically replaces the
file types associated with various file extensions. This means that when
you double-click the file, the new installed application is opened,
instead of the old one. The icon of the extension is usually also
replaced to the icon of the new application.
The 'Replace File Type' feature allows you to set the file extension back
to the original file type. In order to do that, select the desired file
extension in the main window of FileTypesMan, and press F4. You'll get a
long list of available file types on your computer. Find and select the
previous file type that handled the extension, and choose 'Ok'.



Desktop Refresh
===============

Each time that you make a change in the properties of a file type,
FileTypesMan automatically initiate a general desktop refresh, so your
changes will take affect immediately, even for opened Explorer windows.
However, on slow computers, this desktop refresh might consume a fair
amount of CPU resources, and even hang the entire operating system for a
few seconds. If you want to avoid this desktop refresh on every change
that you make, simply disable the automatic refresh, by unchecking the
option under the following menu: Options->Automatic Desktop Refresh.
You can always initiate a desktop refresh when you need it, simply by
selecting 'File->Refresh Desktop Now' from the main menu.



Sending extension information to extension.nirsoft.net
======================================================

extension.nirsoft.net is a Web site that allows you to find out which
programs can open a specific file extension.
If you want, you can add the extension information stored in your
computer into extension.nirsoft.net Web site, by using the 'Send Report
to extension.nirsoft.net' option under the Help menu.(Ctrl+F9).
For more infromation about how to submit your extension information, read
here



Command-Line Options
====================



/SelectedExt <Extension>
Select the specified file extension in the upper pane, for example:
FileTypesMan.exe /SelectedExt ".txt"

You can also use /SelectedExt command to export the actions of specified
file extension, for example:
FileTypesMan.exe /SelectedExt .txt /scomma "c:\temp\txtext.csv"

/DontLoadIcons <0 | 1>
Specifies whether to load the icons from the file type dll. 0 = No, 1 =
Yes.
If FileTypesMan crashes while loading the file types list, running
FileTypesMan with '/DontLoadIcons 1' command may solve the problem.

/MarkDisabledActions <0 | 1>
Specifies whether to mark disabled items. 0 = No, 1 = Yes.


/AutoDesktopRefresh <0 | 1>
Specifies whether to automatically refresh the desktop on every change. 0
= No, 1 = Yes.


/ShowURLProtocols <0 | 1>
Specifies whether to show URL protocols. 0 = No, 1 = Yes.


/ExtractResourceCaption <0 | 1>
Specifies whether to extract resource captions. 0 = No, 1 = Yes.


/ShowApplicationsTypes <0 | 1>
Specifies whether to show application types. 0 = No, 1 = Yes.


/stext <Filename>
Save the list of types/extensions into a regular text file.

/stab <Filename>
Save the list of types/extensions into a tab-delimited text file.

/scomma <Filename>
Save the list of types/extensions into a comma-delimited text file (csv).

/stabular <Filename>
Save the list of types/extensions into a tabular text file.

/shtml <Filename>
Save the list of types/extensions into HTML file (Horizontal).

/sverhtml <Filename>
Save the list of types/extensions into HTML file (Vertical).

/sxml <Filename>
Save the list of types/extensions into XML file.

/sort <column>
This command-line option can be used with other save options for sorting
by the desired column. If you don't specify this option, the list is
sorted according to the last sort that you made from the user interface.
The <column> parameter can specify the column index (0 for the first
column, 1 for the second column, and so on) or the name of the column,
like "Type Name" and "Extension". You can specify the '~' prefix
character (e.g: "~Extension") if you want to sort in descending order.
You can put multiple /sort in the command-line if you want to sort by
multiple columns.

Examples:
FileTypesMan.exe /shtml "f:\temp\types.html" /sort 2 /sort ~3
FileTypesMan.exe /shtml "f:\temp\types.html" /sort "Extension"

/nosort
When you specify this command-line option, the list will be saved without
any sorting.




Translating FileTypesMan to other languages
===========================================

In order to translate FileTypesMan to other language, follow the
instructions below:
1. Run FileTypesMan with /savelangfile parameter:
   FileTypesMan.exe /savelangfile
   A file named FileTypesMan_lng.ini will be created in the folder of
   FileTypesMan utility.
2. Open the created language file in Notepad or in any other text
   editor.
3. Translate all string entries to the desired language. Optionally,
   you can also add your name and/or a link to your Web site.
   (TranslatorName and TranslatorURL values) If you add this information,
   it'll be used in the 'About' window.
4. After you finish the translation, Run FileTypesMan, and all
   translated strings will be loaded from the language file.
   If you want to run FileTypesMan without the translation, simply rename
   the language file, or move it to another folder.



License
=======

This utility is released as freeware. You are allowed to freely
distribute this utility via floppy disk, CD-ROM, Internet, or in any
other way, as long as you don't charge anything for this. If you
distribute this utility, you must include all files in the distribution
package, without any modification !



Disclaimer
==========

The software is provided "AS IS" without any warranty, either expressed
or implied, including, but not limited to, the implied warranties of
merchantability and fitness for a particular purpose. The author will not
be liable for any special, incidental, consequential or indirect damages
due to loss of data or any other reason.



Feedback
========

If you have any problem, suggestion, comment, or you found a bug in my
utility, you can send a message to nirsofer@yahoo.com
