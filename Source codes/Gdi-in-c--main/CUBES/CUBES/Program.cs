using System;
using System.Runtime.InteropServices;
using System.Threading;

class Program
{
    [DllImport("user32.dll")]
    public static extern int GetSystemMetrics(int nIndex);

    [DllImport("user32.dll")]
    public static extern IntPtr GetDC(int hWnd);

    [DllImport("gdi32.dll")]
    public static extern IntPtr CreateSolidBrush(uint color);

    [DllImport("gdi32.dll")]
    public static extern IntPtr SelectObject(IntPtr hdc, IntPtr hgdiobj);

    [DllImport("user32.dll")]
    public static extern int ReleaseDC(int hWnd, IntPtr hDC);

    [DllImport("gdi32.dll")]
    public static extern bool DeleteObject(IntPtr hObject);

    [DllImport("gdi32.dll")]
    public static extern void Ellipse(IntPtr hdc, int left, int top, int right, int bottom);

    static void Main()
    {
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        int signX = 1;
        int signY = 1;
        int signX1 = 1;
        int signY1 = 1;
        int incrementor = 10;
        int x = 10;
        int y = 10;

        while (true)
        {
            IntPtr hdc = GetDC(0);
            x += incrementor * signX;
            y += incrementor * signY;
            int top_x = 0 + x;
            int top_y = 0 + y;
            int bottom_x = 100 + x;
            int bottom_y = 100 + y;
            IntPtr brush = CreateSolidBrush((uint)((new Random()).Next(0, 255) << 16 | (new Random()).Next(0, 255) << 8 | (new Random()).Next(0, 255)));
            SelectObject(hdc, brush);
            Ellipse(hdc, top_x, top_y, bottom_x, bottom_y);

            if (y >= GetSystemMetrics(1))
            {
                signY = -1;
            }

            if (x >= GetSystemMetrics(0))
            {
                signX = -1;
            }

            if (y == 0)
            {
                signY = 1;
            }

            if (x == 0)
            {
                signX = 1;
            }

            Thread.Sleep(10);
            DeleteObject(brush);
            ReleaseDC(0, hdc);
        }
    }
}

