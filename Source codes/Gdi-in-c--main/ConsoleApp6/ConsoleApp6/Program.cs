using System;
using System.Runtime.InteropServices;

class Program
{
    [DllImport("user32.dll")]
    public static extern IntPtr GetDC(int ptr);

    [DllImport("user32.dll")]
    public static extern int GetSystemMetrics(int nIndex);

    [DllImport("gdi32.dll")]
    public static extern bool BitBlt(IntPtr hdc, int nXDest, int nYDest, int nWidth, int nHeight, IntPtr hdcSrc, int nXSrc, int nYSrc, int dwRop);

    static void Main()
    {
        IntPtr hdc = GetDC(0);

        int y = GetSystemMetrics(0);
        int x = GetSystemMetrics(0);

        int sw = GetSystemMetrics(0);
        int sh = GetSystemMetrics(0);

        while (true)
        {
            BitBlt(hdc, new Random().Next(10) - 20, new Random().Next(20) - 10, y, x, hdc, 0, 0, 0x00CC0020);

            BitBlt(hdc, new Random().Next(10) - 20, new Random().Next(20) - 10, sw, sh, hdc, 0, 0, 0x00CC0020);
        }
    }
}
