# **Keylogger/KeyStroke-logging**
Keylogger is a type of software, that is used for tracking keystrokes. It doesn't always have to be used for malicious purposes. For instance, the tracking can be used for analyzing and improving search engines based on what people search on a day-to-day basis. Some companies use keyloggers to make sure that employees do their work correctly.

When it comes to malicious keylogger, simply put keylogger malware then we usually talk about sending information to someone else without the user's knowledge. This information is typically used for breaking into some device, system or just spying for other reasons...
## **Description**
> [!WARNING]
> This was not created for malicious purposes. Everything was built just for demonstration and education. I'm not responsible for any caused problems with law.

I created a basic Keylogger in [C#](https://learn.microsoft.com/en-us/dotnet/csharp/) with [WIN API](https://learn.microsoft.com/en-us/windows/win32/apiindex/windows-api-list).

After launch, the keylogger throw fake error message and then it set itself as a startup application. Later on it write kdata.txt where every keystore will be stored.
Then it just do its thing repeatedly until the user Log Out.

Keep in mind that other keyloggers usually send the information to attacker via network. In this case, it just store information in *kdata.txt*. This keylogger is offline which means, nothing bad can happen :)

### **Screenshots**
*Thrown fake error message*

![Screenshot 2024-07-02 094745](https://github.com/MalwareStudio/Keylogger-KeyStroke-logging/assets/49496834/b344f98d-f823-41b0-bef1-ccffa8a1aa1c)

*Keylogger directory and its data*

![Screenshot 2024-07-02 094818](https://github.com/MalwareStudio/Keylogger-KeyStroke-logging/assets/49496834/e8590083-08c0-46d2-9b2c-ec89994522b1)

*Keystroke data*

![Screenshot 2024-07-02 094855](https://github.com/MalwareStudio/Keylogger-KeyStroke-logging/assets/49496834/c52b40e4-1272-419b-baf4-0719b8f21122)

*Copy of keylogger*

![Screenshot 2024-07-02 094925](https://github.com/MalwareStudio/Keylogger-KeyStroke-logging/assets/49496834/2b835908-57b4-48cb-acfd-ba16c230f960)

*Registry value for autostart*

![Screenshot 2024-07-02 095809](https://github.com/MalwareStudio/Keylogger-KeyStroke-logging/assets/49496834/5a9ce485-a358-43e2-8a36-9877b9d92745)

## **Details**

Built in: C# [netframework 4.0](https://www.microsoft.com/en-us/download/details.aspx?id=17851)

External Components: WIN API

Application type: Windows Application

File extention: .exe

UAC required: no

Internal destruction *(e.g manipulation with personal files)*: no

External destruction *(e.g stealing password)*: no, but possible

**Affected directories**
```
C:\Users\jena0\AppData\Roaming\Microsoft - keylogger copy and keystroke data
```
**Affected Registry Keys&Values**
```
HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run - write keylogger copy location in a Default string
```
