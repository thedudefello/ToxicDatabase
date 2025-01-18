using System;
using System.Runtime.InteropServices;
using System.Threading;

class Program
{
    [DllImport("user32.dll")]
    public static extern IntPtr GetDC(IntPtr hwnd);

    [DllImport("user32.dll")]
    public static extern int GetSystemMetrics(int nIndex);

    [DllImport("gdi32.dll")]
    public static extern IntPtr CreateSolidBrush(uint color);

    [DllImport("gdi32.dll")]
    public static extern IntPtr SelectObject(IntPtr hdc, IntPtr hgdiobj);

    [DllImport("gdi32.dll")]
    public static extern bool DeleteObject(IntPtr hObject);

    [DllImport("gdi32.dll")]
    public static extern bool PatBlt(IntPtr hdc, int nXLeft, int nYLeft, int nWidth, int nHeight, uint dwRop);

    [DllImport("user32.dll")]
    public static extern int ReleaseDC(IntPtr hwnd, IntPtr hdc);

    [DllImport("kernel32.dll")]
    public static extern void Sleep(int dwMilliseconds);

    const int SM_CXSCREEN = 0;
    const int SM_CYSCREEN = 1;
    const uint PATINVERT = 0x005A0049;

    static void Main()
    {
        IntPtr desk = GetDC(IntPtr.Zero);
        int x = GetSystemMetrics(SM_CXSCREEN);
        int y = GetSystemMetrics(SM_CYSCREEN);

        Random rand = new Random();

        for (int i = 0; i < 100; i++)
        {
            IntPtr brush = CreateSolidBrush((uint)((rand.Next(256) << 16) + (rand.Next(256) << 8) + rand.Next(256)));
            SelectObject(desk, brush);
            PatBlt(desk, rand.Next(x), rand.Next(y), rand.Next(x), rand.Next(y), PATINVERT);
            DeleteObject(brush);
            Sleep(100);
        }

        ReleaseDC(IntPtr.Zero, desk);
    }
}
