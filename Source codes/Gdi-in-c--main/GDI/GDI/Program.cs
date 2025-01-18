using System;
using System.Runtime.InteropServices;
using System.Threading;

class ScreenCapture
{
    [DllImport("user32.dll")]
    public static extern IntPtr GetDC(IntPtr hwnd);

    [DllImport("user32.dll")]
    public static extern int ReleaseDC(IntPtr hwnd, IntPtr dc);

    [DllImport("gdi32.dll")]
    public static extern int BitBlt(IntPtr hdc, int x, int y, int width, int height, IntPtr hdcSrc, int xSrc, int ySrc, int dwRop);

    [DllImport("user32.dll")]
    public static extern int GetSystemMetrics(int nIndex);

    public const int SM_CXSCREEN = 0;
    public const int SM_CYSCREEN = 1;
    public const int NOTSRCERASE = 0x001100A6;

    public static void Main()
    {
        while (true)
        {
            IntPtr hdc = GetDC(IntPtr.Zero);
            int x = GetSystemMetrics(SM_CXSCREEN);
            int y = GetSystemMetrics(SM_CYSCREEN);
            int w = GetSystemMetrics(0);
            int h = GetSystemMetrics(1);
            BitBlt(hdc, new Random().Next(666), new Random().Next(666), w, h, hdc, new Random().Next(666), new Random().Next(666), NOTSRCERASE);
            Thread.Sleep(10);
            ReleaseDC(IntPtr.Zero, hdc);
        }
    }
}
