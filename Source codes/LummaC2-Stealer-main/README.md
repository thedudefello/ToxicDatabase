# LummaC2 Stealer

        
![image](https://github.com/user-attachments/assets/eda793a2-e3d0-46ca-ac80-205fcb613759)


## 1. Introduction

LummaC2 is a commodity stealer malware that gained notoriety in underground cybercrime forums. It's primarily advertised as a "premium" infostealer, targeting browsers, cryptocurrency wallets, and authentication data. Despite the marketing hype, a deep dive into the provided code snippets reveals a series of significant weaknesses, hardcoded configurations, and questionable coding practices – all red flags pointing to a rushed, low-quality malware product. The "advanced" label is highly misleading; this is a project likely built by skiddies with a shaky grasp of secure coding principles.

## 2. Origins and Developer Background (Based on Advertised Claims)

While we can't definitively confirm the developers' identities based on the code, the advertised origins point to typical locations for this kind of malware:

*   **Distribution:** Sold on underground forums (XSS, Exploit.in, RAMP) and promoted via Telegram hacking groups and darknet marketplaces.

    ![image](https://github.com/user-attachments/assets/54a158f1-501b-4c17-984c-5a43a4122947)
    
    ![image](https://github.com/user-attachments/assets/b5dc58df-4519-449a-b133-885ed5eea3db)
    
    ![image](https://github.com/user-attachments/assets/fed5aaf5-508d-404f-9154-d155d7cf30a9)
    
    ![image](https://github.com/user-attachments/assets/5f9f3160-a5da-4889-90ba-722038f87fa5)


*   **Targeting:** Primarily aimed at less-skilled attackers looking for quick financial gains through a "Malware-as-a-Service" (MaaS) model, providing easy deployment for various types of targets.
*   **Subscription Model:** The use of subscriptions indicates an attempt to provide continuous updates and a revenue stream, though the quality of the product remains a serious question.

## 3. Technical Analysis of LummaC2 - The Real Story

The provided C code snippets expose the inner workings, or lack thereof, of this supposedly "premium" stealer. Let's strip away the marketing and focus on the reality:

![image](https://github.com/user-attachments/assets/ac257609-1686-480f-ace0-a1db9058154e)




### 3.1. Code Structure and Anti-Analysis Techniques (Reality Check)

The code snippet *attempts* some anti-analysis techniques, but they're laughably inadequate:

*   **API Hashing:**  The use of `ResolveTheHash` to resolve Windows API functions is a standard, albeit easily defeated, tactic.  It's a basic hurdle, easily surpassed by anyone using tools like Binja
*   **String Obfuscation:**  The repeated use of the `"edx765"` marker for string encoding is a textbook example of weak obfuscation. This is a major giveaway. It's trivial to write a script to automatically remove this marker and expose the actual strings.
*   **Memory Management "Tricks":** The custom memory allocation functions, `allocateMemory`, `requestMemoryAllocation`, are likely designed to make the code more opaque. They add unnecessary layers of complexity and likely contribute to poor performance.
*   **Dynamic API Resolution:** Attempts to obfuscate API calls, but the method used is simplistic.
*   **Hardcoded Paths & Extensions:** This is where the stealer really falls apart. Instead of dynamically identifying targets, LummaC2 relies on hardcoded file paths for browsers, crypto wallets, and authentication data. This predictability is a huge weakness.

### 3.2. Targeted Data and Associated File Paths

We have identified the targets and file locations. The inclusion of the wallets and 2FA extension is a key factor of the stealer.

**Browser Data:**

*   **Chrome/Chromium/Edge/Brave/Opera:**
    *   Data Location (Hardcoded):
        *   Chrome, Chromium, Edge:
            *   `%LOCALAPPDATA%\Google\Chrome\User Data`
            *   `%LOCALAPPDATA%\Chromium\User Data`
            *   `%LOCALAPPDATA%\Microsoft\Edge\User Data`
        *   Brave:
            *   `%LOCALAPPDATA%\BraveSoftware\Brave-Browser\User Data`
        *   Opera:
            *   `%APPDATA%\Opera Software\Opera Stable`
            *   `%APPDATA%\Opera Software\Opera GX Stable`
            *   `%APPDATA%\Opera Software\Opera Neon\User Data`
    *   Specific File Targets: The stealer focuses on common files within the "User Data" directories of the Chromium-based browsers. The most likely targets include:
        *   `Login Data` (passwords)
        *   `Cookies` (session cookies)
        *   `History` (browsing history)
        *   `Local Storage` (data stored by websites)
        *   `Network\Cookies`
*   **Firefox:**
    *   Data Location (Hardcoded): `%APPDATA%\Mozilla\Firefox\Profiles\`
    *   Specific File Targets:
        *   `key4.db` - Encryption key (crucial for decrypting the `logins.json` data)
        *   `logins.json` - Saved usernames and passwords
        *   `cookies.sqlite` - Stored session cookies
        *   `places.sqlite` - Browsing history and bookmarks
        *   `formhistory.sqlite` - Autofill data
        *   `cert9.db` - Security certificates

**Crypto Wallets and Extensions (Hardcoded):**

*   **MetaMask**: (Extension ID: `ejbalbakoplchlghecdaalmeeeajnimhm` and `nkbihfbeogaeaoehlefedknkodbefgpgknn`)
*   **TronLink**: (`ibnejdfjmmkpcnlpebklmnkoeoihofec`)
*   **Ronin Wallet**: (`fnjhmkhhmkbedjkkabndcnnogagogbneec`)
*   **Binance Chain Wallet**: (`fhbohimaelbohpjbbldcngcnapnedx765dodjp`)
*   **Coinbase Wallet**: (`hnfanknocfeedofbddgcijnmedhnfnkdnaad`)
*   **Yoroi**: (`ffnbelfdoeiohenkjibnmadjiehjhajb`)
*   **Nifty Wallet**: (`jbdaocneiiinmjbjlgalhcelgbejmnid`)
*   **Math Wallet**: (`afbcbjpbpfadlkmhmclhkeeodmamcflc`)
*   **Guarda Wallet**: (`hpglfhgfnhbgpjdenjgmdgoeiappafln`)
*   **EQUAL Wallet**: (`blnieiiffboillknjnepogjhkgnoapac`)
*   **Jaxx Liberty**: (`cjelfplplebdjjenllpjcblmjkfcffne`)
*   **BitApp Wallet**: (`fihkakfobkmkjojpchpfgcmhfjnmnfpi`)
*   **iWlt Wallet**: (`kncchdigobghenbbaddojjnnaogfppfj`)
*   **Wombat Wallet**: (`amkmjjmmflddogmhpjloimipbofnfjih`)
*   **MEW CX**: (`nlbmnnijcnlegkjjpcfjclmcfggfefdm`)
*   **Guild Wallet**: (`nanjmdknhkinifnkgdcggcfnhdaammmj`)
*   **Saturn Wallet**: (`nkddgncdjgjfcddamfgcmfnlhccnimig`)
*   **NeoLine Wallet**: (`cphhlgmgameodnhkjdmkpanlelnlohao`)
*   **Clover Wallet**: (`nhnkbkgjikgcigadomkphalanndcapjk`)
*   **Liquality Wallet**: (`kpfopkelmapcoipemfendmdcghnegimn`)
*   **Terra Station**: (`aiifbnbfobpmeekipheeijimdpnlpgpp`)
*   **Keplr Wallet**: (`dmkamcknogkgcdfhhbddcghachkejeap`)
*   **Sollet**: (`fhmfendgdocmcbmfikdcogofphimnkno`)
*   **Auro Wallet**: (`cnmamaachppnkjgnildpdmkaakejnhae`)
*   **Polymesh Wallet**: (`jojhfeoedkpkglbfimdfabpdfjaoolaf`)
*   **ICONex Wallet**: (`flpiciilemghbmfalicajoolhkkenfel`)
*   **Nabox Wallet**: (`nknhiehlklippafakaeklbeglecifhad`)
*   **KHC Wallet**: (`hcflpincpppdclinealmandijcmnkbgn`)
*   **Temple Wallet**: (`ookjlbkiijinhpmnjffcofjonbfbgaoc`)
*   **TezBox Wallet**: (`mnfifefkajgofkcjkemidiaecocnkjeh`)
*   **DAppPlay Wallet**: (`lodccjjbdhfakaekdiahmedfbieldgik`)
*   **BitClip Wallet**: (`ijmpgkjfkbfhoebgogflfebnmejmfbml`)
*   **Steem Keychain**: (`lkcjlnjfpbikmcmbachjpdbijejflpcm`)
*   **Nash Extension**: (`onofpnbbkehpmmoabgpcpmigafmmnjhl`)
*   **Hycon Lite Client**: (`bcopgchhojmggmffilplmbdicgaihlkp`)
*   **ZilPay**: (`klnaejjgbibmhlephnhpmaofohgkpgkd`)
*   **Coin98 Wallet**: (`aeachknmefphepccionboohckonoeemg`)
*   **Authenticator**: (`bhghoamapcdpbohphigoooaddinpkbai`)
*   **Cyano Wallet**: (`dkdedlpgdmmkkfjabffeganieamfklkm`)
*   **Byone Wallet**: (`nlgbhdfgdhgbiamfdfmbikcdghidoadd`)
*   **OneKey Wallet**: (`infeboajgfhgbjpjbeppbkgnabfdkdaf`)
*   **Leaf Wallet**: (`cihmoadaighcejopammfbmddcmdekcje`)
*   **Authy**: (`gaedmjdfmmahhbjefcbgaolhhanlaolb`)
    *   **EOS Authenticator**: `oeljdldpnmdbchonielidgobddffflal`
    *   **Google Authenticator**: `ilgcnhelpchnceeipipijaljkblbcobl`
    *   **Trezor Password Manager**: `imloifkgjagghnncjkhggdhalmcnfklk`
    *   and also grabs the History, Login Data, Web Data and Network/Cookies Data

    *   **Electrum**:
        *   Path: `%APPDATA%\Electrum`
        *   Files (Likely): `wallets/*` and associated configuration/backup files.
    *   **Binance Chain Wallet**:
        *   Path: `%APPDATA%\Binance`
        *   Files (Likely): `*.json` files, potentially including seed phrases or private keys.
    *   **Ethereum Wallets**:
        *   Path: `%APPDATA%\Ethereum`
        *   Files (Likely): `keystore` directory, storing encrypted key files.

### 3.3. Data Exfiltration Mechanism

The malware is surprisingly straightforward in its communication:

*   **C2 Communication:** Uses `wininet.dll` to establish an HTTP connection, which means it would use standard HTTP GET/POST methods.
*   **Data Transmission:** The stolen data is packed into an HTTP POST request with the `multipart/form-data` content type. This suggests that the data is likely being sent as either a compressed archive or as a file.
*   **IP Address:** The code shows a hardcoded IP address: `195.123.226.91`.  The code does not have the hardcoded C2 domain, and we will have to find out how they are using it.

### 3.4. Breakdown of Key Functions (Focus on Weaknesses)

*   **`allocateMemory`**:
    *   **Analysis Notes:** Unnecessary and likely used to avoid detection. Poor error handling makes it unreliable.

*   **`processPath`**:
    *   **Analysis Notes:** Recursive directory traversal.  This is a very basic method.  If it's not handled well, it is easy to perform path traversal, also the recursive calls can cause a DOS or stack overflow issues.

*   **`ExtractUserData`**:
    *   **Analysis Notes:** Targets browsers (Chrome, Chromium-based, and Edge). Decryption techniques, are likely to be weak. The function hardcodes the file paths to the browser profile folders (e.g., `Login Data`, `Cookies`), making it easy to identify the targets.

*   **`ExtractFirefoxProfileData`**:
    *   **Analysis Notes:** Same as `ExtractUserData`, but for Firefox. Focus on decryption, access to `key4.db`, `logins.json`, `cookies.sqlite` is a must.

*   **`ProcessAndSendData`**:
    *   **Analysis Notes:** Constructs an HTTP POST request.  The reliance on `wininet.dll` is a weakness, as it can be readily detected by network monitoring.

*   **`TrasStrings` and `GetFilePath`**:
    *   **Analysis Notes:** "edx765" obfuscation is trivial to bypass.
  
## 4. Indicators of Compromise (IOCs)
*   **Files & Registry Keys:**
    *   `%APPDATA%\Lumma*` - Files created by LummaC2.
    *   `%LOCALAPPDATA%\Temp*` - Temporary files, also possible.
     ![image](https://github.com/user-attachments/assets/56f9f623-c5e6-4d31-9dc6-55f7a4ed7313)

      
*   **C2 Communications:**
    *   **IP Address:** `195.123.226.91` (probably hosted on a $5 VPS, just kidding lmfao)
    *   HTTP POST requests with `multipart/form-data` content type.
*   **Process Behavior:**
    *   Unusual HTTP POST requests using `wininet.dll`.
    *   Suspicious file access patterns to browser credential files.
    *   Creation of files matching wallet/browser file patterns (e.g., `key4.db`, `logins.json`).


## 6. Conclusion

LummaC2 is a relatively unsophisticated stealer, a low-effort creation targeting common vulnerabilities and assets. Its reliance on hardcoded configurations, weak anti-analysis techniques, and an easily detectable exfiltration mechanism severely limits its threat level. It is more a nuisance for the victims than a serious threat to well-secured systems. However, continued monitoring of the stealer is necessary, as with all malware, to track possible updates, new targets, or changes to its attack methodology.

well well well, so let me say To any so-called "malware devs" reading this: You're embarrassing yourselves. We, as reverse engineers, enjoy a real challenge—but This is just skid tier garbage. If this is the best you can do, even 2010-era antivirus could wipe you off the map without breaking a sweat.
