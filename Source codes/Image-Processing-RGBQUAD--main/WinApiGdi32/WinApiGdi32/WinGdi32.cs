using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace WinApiGdi32
{
    public class WinGdi32
    {
        [DllImport("user32.dll")]
        public static extern IntPtr GetDC(IntPtr hdcScr);
        [DllImport("gdi32.dll")]
        public static extern bool DeleteDC(IntPtr hdc);
        [DllImport("user32.dll")]
        public static extern int ReleaseDC(IntPtr hwnd, IntPtr hdc);
        [DllImport("gdi32.dll")]
        public static extern IntPtr SelectObject(IntPtr hdc, IntPtr handleObj);
        [DllImport("gdi32.dll")]
        public static extern bool DeleteObject(IntPtr handleObj);
        [DllImport("gdi32.dll")]
        public static extern bool BitBlt(IntPtr hdcDes, int left, int top, int right, int bottom,
            IntPtr hdcSrc, int leftSrc, int topSrc, Rop rop);
        [DllImport("gdi32.dll")]
        public static extern IntPtr CreateCompatibleDC(IntPtr hdc);
        [DllImport("gdi32.dll")]
        public static extern IntPtr CreateCompatibleBitmap(IntPtr hdc, int cx, int cy);
        [DllImport("gdi32.dll")]
        public static extern int GetDIBits(IntPtr hdc, IntPtr hBitmap, uint start, uint cLines, byte[] buffer,
            ref BITMAPINFO lpbmi, uint usage);
        [DllImport("gdi32.dll")]
        public static extern int SetDIBits(IntPtr hdc, IntPtr hBitmap, uint start, uint cLines, byte[] buffer,
            ref BITMAPINFO lpbmi, uint usage);

        [StructLayout(LayoutKind.Sequential)]
        public struct BITMAPINFO
        {
            public BITMAPINFOHEADER bmiHeader;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
            public RGBQUAD[] bmiColors;
        }
        [StructLayout(LayoutKind.Sequential)]
        public struct RGBQUAD
        {
            public byte rgbBlue;
            public byte rgbGreen;
            public byte rgbRed;
            public byte rgbReserved;
        }
        [StructLayout(LayoutKind.Sequential)]
        public struct BITMAPINFOHEADER
        {
            public uint biSize;
            public int biWidth;
            public int biHeight;
            public ushort biPlanes;
            public ushort biBitCount;
            public uint biCompression;
            public uint biSizeImage;
            public int biXPelsPerMeter;
            public int biYPelsPerMeter;
            public uint biClrUsed;
            public uint biClrImportant;
        }
        public enum Rop
        {
            BLACKNESS = 0x0,
            NOTSRCERASE = 0x001100A6,
            NOTSRCCOPY = 0x00330008,
            SRCERASE = 0x00440328,
            DSTINVERT = 0x00550009,
            PATINVERT = 0x005A0049,
            SRCINVERT = 00660046,
            SRCAND = 0x008800C6,
            MERGEPAINT = 0x00BB0226,
            MERGECOPY = 0x00C000CA,
            SRCCOPY = 0x00CC0020,
            SRCPAINT = 0x00EE0086,
            PATCOPY = 0x00F00021,
            PATPAINT = 0x00FB0A09,
            WHITENESS = 0x00FF0062
        }
    }
}
