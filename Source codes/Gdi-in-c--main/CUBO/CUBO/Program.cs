using System;
using System.Runtime.InteropServices;

class Program
{
    [DllImport("user32.dll")]
    public static extern int GetSystemMetrics(int nIndex);

    [DllImport("user32.dll")]
    public static extern IntPtr GetDC(int hWnd);

    [DllImport("user32.dll")]
    public static extern int ReleaseDC(int hWnd, IntPtr hDC);

    [DllImport("gdi32.dll")]
    public static extern int SetPixel(IntPtr hdc, int x, int y, int color);

    static void Main()
    {
        int y = GetSystemMetrics(1); // SM_CYSCREEN
        int x = GetSystemMetrics(0); // SM_CXSCREEN
        int yfull = GetSystemMetrics(17); // SM_CYFULLSCREEN
        int xfull = GetSystemMetrics(16); // SM_CXFULLSCREEN
        int rainbow = x - new Random().Next() % x - (x / 150 - 112) % 149;
        int inc = (int)Math.Round(x / 100.0);
        Math.Round(y / 1.0);
        Math.Round(yfull / 100.0);
        Math.Round(xfull / 10.0);

        while (true)
        {
            IntPtr hdc = GetDC(0);
            for (int yp = 0; yp < y; ++yp)
            {
                for (int xp = 0; xp < x; ++xp)
                {
                    int xa = inc * xp;
                    SetPixel(hdc, xp, yp, (int)RGB(xa, xa, xa));
                    SetPixel(hdc, yp, rainbow, (int)RGB(yfull, xa, xfull));
                    SetPixel(hdc, rainbow, rainbow, (int)RGB(rainbow, rainbow, rainbow));
                    SetPixel(hdc, rainbow, yp, (int)RGB(xfull, yfull, xfull));
                }
            }
            ReleaseDC(0, hdc);
        }
    }

    static uint RGB(int r, int g, int b)
    {
        return (uint)((r << 16) | (g << 8) | b);
    }
}
