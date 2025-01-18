using System;
using System.Runtime.InteropServices;
using System.Threading;

class Program
{
    [DllImport("user32.dll")]
    public static extern IntPtr GetDC(IntPtr hwnd);

    [DllImport("user32.dll")]
    public static extern IntPtr GetDesktopWindow();

    [DllImport("user32.dll")]
    public static extern int ReleaseDC(IntPtr hwnd, IntPtr hDC);

    [DllImport("user32.dll")]
    public static extern int GetSystemMetrics(int nIndex);

    [DllImport("gdi32.dll")]
    public static extern IntPtr CreateSolidBrush(int color);

    [DllImport("gdi32.dll")]
    public static extern IntPtr SelectObject(IntPtr hdc, IntPtr hObject);

    [DllImport("gdi32.dll")]
    public static extern bool PatBlt(IntPtr hdc, int nXLeft, int nYLeft, int nWidth, int nHeight, uint dwRop);

    [DllImport("gdi32.dll")]
    public static extern bool LineTo(IntPtr hdc, int nXEnd, int nYEnd);

    [DllImport("gdi32.dll")]
    public static extern bool RoundRect(IntPtr hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nWidth, int nHeight);

    [DllImport("gdi32.dll")]
    public static extern bool StretchBlt(IntPtr hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, IntPtr hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, uint dwRop);

    [DllImport("gdi32.dll")]
    public static extern bool BitBlt(IntPtr hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, IntPtr hdcSrc, int nXSrc, int nYSrc, uint dwRop);

    [DllImport("kernel32.dll")]
    public static extern bool Beep(int dwFreq, int dwDuration);

    public const int SM_CXSCREEN = 0;
    public const int SM_CYSCREEN = 1;
    public const uint PATINVERT = 0x005A0049;
    public const uint SRCCOPY = 0x00CC0020;
    public const uint SRCPAINT = 0x00EE0086;
    public const uint SRCINVERT = 0x00660046;

    static void Main()
    {
        IntPtr desk = GetDC(IntPtr.Zero);
        int xs = GetSystemMetrics(SM_CXSCREEN), ys = GetSystemMetrics(SM_CYSCREEN);
        Random rand = new Random();

        while (true)
        {
            Thread.Sleep(1);

            if (rand.Next(3) == 3)
            {
                IntPtr brush = CreateSolidBrush((rand.Next(955) << 16) | (rand.Next(955) << 8) | rand.Next(955));
                SelectObject(desk, brush);
                PatBlt(desk, 0, 0, xs, ys, PATINVERT);
                Thread.Sleep(rand.Next(1000));
            }
            else if (rand.Next(3) == 1)
            {
                IntPtr brush = CreateSolidBrush((rand.Next(25) << 16) | (rand.Next(95) << 8) | rand.Next(95));
                SelectObject(desk, brush);
                PatBlt(desk, 0, 0, xs, ys, PATINVERT);
                Thread.Sleep(rand.Next(1000));
            }

            if (rand.Next(25) == 9)
            {
                IntPtr brush = CreateSolidBrush((rand.Next(955) << 16) | (rand.Next(955) << 8) | rand.Next(955));
                SelectObject(desk, brush);
                Thread.Sleep(10);
            }
            else if (rand.Next(25) == 5)
            {
                IntPtr brush = CreateSolidBrush((rand.Next(905) << 16) | (rand.Next(905) << 8) | rand.Next(905));
                SelectObject(desk, brush);
            }

            if (rand.Next(2) == 1)
            {
                LineTo(desk, rand.Next(xs), rand.Next(ys));
                RoundRect(desk, rand.Next(xs), rand.Next(ys), rand.Next(xs), rand.Next(ys), rand.Next(xs), rand.Next(ys));
                Thread.Sleep(10);
            }

            if (rand.Next(2) == 1)
            {
                LineTo(desk, rand.Next(xs), rand.Next(ys));
                RoundRect(desk, rand.Next(xs), rand.Next(ys), rand.Next(xs), rand.Next(ys), rand.Next(xs), rand.Next(ys));
                Thread.Sleep(10);
            }
            else if (rand.Next(2) == 0)
            {
                IntPtr hdc = GetDC(IntPtr.Zero);
                int x = GetSystemMetrics(SM_CXSCREEN);
                int y = GetSystemMetrics(SM_CYSCREEN);
                int r1 = rand.Next(x);
                int r2 = rand.Next(y);
                IntPtr hbrush = CreateSolidBrush((rand.Next(955) << 16) | (rand.Next(955) << 8) | rand.Next(955));
                StretchBlt(hdc, 0, 0, x, r1, hdc, r1, r2, 1, 1, PATINVERT);
            }

            if (rand.Next(7) == 5)
            {
                StretchBlt(desk, rand.Next(xs), rand.Next(ys), xs, ys, desk, 0, 0, xs, ys, SRCCOPY);
                StretchBlt(desk, 10, 10, xs - 80, ys - 80, desk, 0, 0, xs, ys, SRCPAINT);
                StretchBlt(desk, -10, -10, xs + 20, ys + 20, desk, 0, 0, xs, ys, SRCPAINT);
                StretchBlt(desk, 0, 0, xs, ys, desk, rand.Next(xs), rand.Next(ys), xs, ys, SRCINVERT);
                IntPtr hbrush = CreateSolidBrush((rand.Next(255) << 16) | (rand.Next(255) << 8) | rand.Next(255));
                SelectObject(desk, hbrush);
                PatBlt(desk, 0, 0, xs, ys, PATINVERT);
            }

            for (int i = 4; i >= 0; i--)
            {
                IntPtr hbrush = CreateSolidBrush((rand.Next(955) << 16) | (rand.Next(955) << 8) | rand.Next(955));
                SelectObject(desk, hbrush);
                BitBlt(desk, rand.Next(10), rand.Next(10), xs, ys, desk, rand.Next(10), rand.Next(10), 0x98123c);
            }

            // Play audio
            Beep(500 + rand.Next(2000), 200);
        }
    }
}
