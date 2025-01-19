using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using WinApiGdi32;

namespace Bitmap_Process
{
    public class BitmapClass : WinGdi32
    {
        private BITMAPINFO BitmapInfo(int right, int bottom, int bitmapSize, ushort bitCount)
        {
            BITMAPINFO binfo = new BITMAPINFO();

            binfo.bmiHeader.biSize = (uint)Marshal.SizeOf(typeof(BITMAPINFOHEADER));
            binfo.bmiHeader.biWidth = right;
            binfo.bmiHeader.biHeight = bottom;
            binfo.bmiHeader.biPlanes = 1;
            binfo.bmiHeader.biBitCount = bitCount;
            binfo.bmiHeader.biCompression = 0;

            binfo.bmiHeader.biSizeImage = (uint)bitmapSize;

            return binfo;
        }
        private byte[] ProcessLogic(byte[] buffer, bool process)
        {
            if (!process)
                return buffer;

            for(int num = 0; num < buffer.Length; num += 3)
            {
                byte r = buffer[num + 2];
                byte g = buffer[num + 1];
                byte b = buffer[num];

                buffer[num + 2] = (byte)(r + (num / 10));
                buffer[num + 1] = (byte)(g);
                buffer[num] = (byte)(b + (num / 2));
            }

            return buffer;
        }
        public void BitmapMain()
        {
            while (true)
            {
                int left = Screen.PrimaryScreen.Bounds.Left;
                int top = Screen.PrimaryScreen.Bounds.Top;
                int right = Screen.PrimaryScreen.Bounds.Right;
                int bottom = Screen.PrimaryScreen.Bounds.Bottom;

                int bitmapSize = right * bottom * 3;
                IntPtr hdcScr = GetDC(IntPtr.Zero);
                Bitmap_Process(hdcScr, left, top, right, bottom, Rop.SRCCOPY, Rop.SRCCOPY, bitmapSize, 24, true);

                Thread.Sleep(100);
            }
        }
        public void Bitmap_Process(IntPtr hdcScr, int left, int top, int right, int bottom, 
            Rop input, Rop output, int bitmapSize, ushort bitCount, bool process)
        {
            IntPtr memDc = CreateCompatibleDC(hdcScr);
            IntPtr hBitmap = CreateCompatibleBitmap(hdcScr, right, bottom);
            IntPtr hOldBitmap = SelectObject(memDc, hBitmap);

            BitBlt(memDc, left, top, right, bottom, hdcScr, 0, 0, input);

            BITMAPINFO binfo = BitmapInfo(right, bottom, bitmapSize, bitCount);

            byte[] curbufferdata = new byte[bitmapSize];

            GetDIBits(memDc, hBitmap, 0, (uint)bottom, curbufferdata, ref binfo, 0);

            byte[] newbufferdata = ProcessLogic(curbufferdata, process);

            SetDIBits(memDc, hBitmap, 0, (uint)bottom, newbufferdata, ref binfo, 0);

            BitBlt(hdcScr, left, top, right, bottom, memDc, 0, 0, output);

            SelectObject(memDc, hOldBitmap);
            DeleteDC(memDc);
            DeleteObject(hBitmap);
            ReleaseDC(IntPtr.Zero, hdcScr);
        }
    }
}
