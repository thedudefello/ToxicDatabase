using System;
using System.Runtime.InteropServices;
using System.Threading;

class MouseMover
{
    [DllImport("user32.dll")]
    static extern bool GetCursorPos(out POINT lpPoint);
    [DllImport("user32.dll")]
    static extern bool SetCursorPos(int X, int Y);
    [DllImport("user32.dll")]
    static extern bool BlockInput(bool blockIt);
    [DllImport("user32.dll")]
    static extern int ShowCursor(bool bShow);
    [StructLayout(LayoutKind.Sequential)]
    public struct POINT
    {
        public int x;
        public int y;
    }
    public static void Mover()
    {
        Random rand = new Random();
        POINT cursor;
        ShowCursor(false);

        while (true)
        {
            GetCursorPos(out cursor);
            int X = cursor.x + rand.Next(-1, 2);
            int Y = cursor.y + rand.Next(-1, 2);
            BlockInput(true);
            SetCursorPos(X, Y);
            Thread.Sleep(10);
            BlockInput(false);
        }
    }
}
