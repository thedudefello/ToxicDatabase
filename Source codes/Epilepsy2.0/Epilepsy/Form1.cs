using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;
using System.Media;
using System.IO;

namespace Epilepsy // Feel free to use my payloads!
{
    public partial class gdi : Form
    {
        [DllImport("user32.dll")]
        static extern IntPtr GetDesktopWindow();

        [DllImport("user32.dll")]
        static extern IntPtr GetWindowDC(IntPtr hWnd);

        [DllImport("Shell32.dll", EntryPoint = "ExtractIconExW", CharSet = CharSet.Unicode, ExactSpelling = true,
        CallingConvention = CallingConvention.StdCall)]
        private static extern int ExtractIconEx(string sFile, int iIndex, out IntPtr piLargeVersion,
        out IntPtr piSmallVersion, int amountIcons);

        [DllImport("user32.dll")]
        static extern bool InvalideRect(IntPtr hWnd, IntPtr IpRect, bool bErase);

        [DllImport("gdi32.dll")]
        static extern bool StretchBlt(IntPtr hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest,
        int nHeightDest, IntPtr hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc,
        TernaryRasterOperations dwRop);

        public enum TernaryRasterOperations
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


        public gdi()
        {
            InitializeComponent();
            TransparencyKey = BackColor;
        }

        Icon icon = Extract("shell32.dll", 109, true); // Icons on cursor

        private void gdis_Load(object sender, EventArgs e)
        {
            timer1.Start();
            timer2.Stop();
            timer3.Stop();
            timer4.Stop();
            timer5.Stop();
            timer6.Stop();
            timer7.Stop();
            timer8.Stop();
            timer9.Stop();
            timer10.Stop();
            timer11.Stop();
            timer12.Stop();
            timer13.Stop();
            timer14.Stop();
            timer15.Start();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            timer1.Stop(); // Screen wobble payload
            IntPtr hwnd = GetDesktopWindow();
            IntPtr hdc = GetWindowDC(hwnd);
            int x = Screen.PrimaryScreen.Bounds.Width;
            int y = Screen.PrimaryScreen.Bounds.Height;
            StretchBlt(hdc, 20, 5, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCCOPY);
            StretchBlt(hdc, 20, 10, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCCOPY);
            StretchBlt(hdc, 20, 10, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCCOPY);
            StretchBlt(hdc, 20, 5, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCCOPY);
            StretchBlt(hdc, 20, 0, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCCOPY);
            StretchBlt(hdc, -40, -5, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCCOPY);
            StretchBlt(hdc, -40, -10, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCCOPY);
            StretchBlt(hdc, -40, -10, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCCOPY);
            StretchBlt(hdc, -40, -5, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCCOPY);
            StretchBlt(hdc, -40, 0, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCCOPY);
            StretchBlt(hdc, 20, 5, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCCOPY);
            StretchBlt(hdc, 20, 10, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCCOPY);
            StretchBlt(hdc, 20, 10, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCCOPY);
            StretchBlt(hdc, 20, 5, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCCOPY);
            StretchBlt(hdc, 20, -30, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCCOPY);
            timer1.Start();
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            timer2.Stop(); // Inverted colors payload
            IntPtr hwnd = GetDesktopWindow();
            IntPtr hdc = GetWindowDC(hwnd);
            int x = Screen.PrimaryScreen.Bounds.Width;
            int y = Screen.PrimaryScreen.Bounds.Height;
            StretchBlt(hdc, 0, 0, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            timer2.Start();
        }

        private void timer3_Tick(object sender, EventArgs e)
        {
            timer3.Stop(); // Icons on cursor payload
            this.Cursor = new Cursor(Cursor.Current.Handle);
            int posX = Cursor.Position.X;
            int posY = Cursor.Position.Y;

            IntPtr desktop = GetWindowDC(IntPtr.Zero);
            using (Graphics g = Graphics.FromHdc(desktop))
            {
                g.DrawIcon(icon, posX, posY);
            }
            timer3.Start();
        }

        private void timer4_Tick(object sender, EventArgs e)
        {
            timer4.Stop(); // Inverted color lines
            IntPtr hwnd = GetDesktopWindow();
            IntPtr hdc = GetWindowDC(hwnd);
            int x = Screen.PrimaryScreen.Bounds.Width;
            int y = Screen.PrimaryScreen.Bounds.Height;
            StretchBlt(hdc, 10, -10, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, 10, 10, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, -10, 10, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, -10, -10, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            timer4.Start();
        }

        private void timer5_Tick(object sender, EventArgs e)
        {
            timer5.Stop(); // Screen compression payload
            IntPtr hwnd = GetDesktopWindow();
            IntPtr hdc = GetWindowDC(hwnd);
            int x = Screen.PrimaryScreen.Bounds.Width;
            int y = Screen.PrimaryScreen.Bounds.Height;
            StretchBlt(hdc, 250, 0, x - 500, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, -250, 0, x + 500, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            timer5.Start();
        }

        private void timer6_Tick(object sender, EventArgs e)
        {
            timer6.Stop(); // Tunnel exit payload
            IntPtr hwnd = GetDesktopWindow();
            IntPtr hdc = GetWindowDC(hwnd);
            int x = Screen.PrimaryScreen.Bounds.Width;
            int y = Screen.PrimaryScreen.Bounds.Height;
            StretchBlt(hdc, -2, -2, x + 4, y + 4, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            timer6.Start();
        }

        private void timer7_Tick(object sender, EventArgs e)
        {
            timer7.Stop(); // In & out tunnel (Massive color distortion) payload
            IntPtr hwnd = GetDesktopWindow();
            IntPtr hdc = GetWindowDC(hwnd);
            int x = Screen.PrimaryScreen.Bounds.Width;
            int y = Screen.PrimaryScreen.Bounds.Height;
            StretchBlt(hdc, 250, 250, x - 500, y - 500, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, -250, -250, x + 500, y + 500, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            timer7.Start();
        }

        private void timer8_Tick(object sender, EventArgs e)
        {
            timer8.Stop(); // Bouncy screen payload
            IntPtr hwnd = GetDesktopWindow();
            IntPtr hdc = GetWindowDC(hwnd);
            int x = Screen.PrimaryScreen.Bounds.Width;
            int y = Screen.PrimaryScreen.Bounds.Height;
            StretchBlt(hdc, 25, -25, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, 25, -20, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, 25, -15, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, 25, -10, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, 25, -5, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, 25, 0, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, 25, 5, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, 25, 10, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, 25, 15, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, 25, 20, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, 25, 25, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, -25, -25, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, -25, -20, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, -25, -15, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, -25, -10, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, -25, -5, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, -25, 0, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, -25, 5, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, -25, 10, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, -25, 15, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, -25, 20, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            StretchBlt(hdc, -25, 25, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            timer8.Start();
        }

        private void timer9_Tick(object sender, EventArgs e)
        {
            timer9.Stop(); // Top-left Tunnel payload
            IntPtr hwnd = GetDesktopWindow();
            IntPtr hdc = GetWindowDC(hwnd);
            int x = Screen.PrimaryScreen.Bounds.Width;
            int y = Screen.PrimaryScreen.Bounds.Height;
            StretchBlt(hdc, 25, 25, x, y, hdc, 50, 50, x, y, TernaryRasterOperations.SRCINVERT);
            timer9.Start();
        }

        private void timer10_Tick(object sender, EventArgs e)
        {
            timer10.Stop(); // Screen crushing payload
            IntPtr hwnd = GetDesktopWindow();
            IntPtr hdc = GetWindowDC(hwnd);
            int x = Screen.PrimaryScreen.Bounds.Width;
            int y = Screen.PrimaryScreen.Bounds.Height;
            StretchBlt(hdc, 25, 0, x - 50, y, hdc, 0, 0, x, y, TernaryRasterOperations.NOTSRCCOPY);
            timer10.Start();
        }

        private void timer11_Tick(object sender, EventArgs e)
        {
            timer11.Stop(); // Middle to Top-Left to Bottom-right to Middle to Top-Right to Bottom-left and so on Payload
            IntPtr hwnd = GetDesktopWindow();
            IntPtr hdc = GetWindowDC(hwnd);
            int x = Screen.PrimaryScreen.Bounds.Width;
            int y = Screen.PrimaryScreen.Bounds.Height;
            StretchBlt(hdc, -100, -100, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, -100, -100, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, 100, 100, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, 100, 100, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, 100, 100, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, 100, 100, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, -100, -100, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, -100, -100, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, 100, -100, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, 100, -100, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, -100, 100, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, -100, 100, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, -100, 100, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, -100, 100, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, 100, -100, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, 100, -100, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            timer11.Start();
        }

        private void timer12_Tick(object sender, EventArgs e)
        {
            timer12.Stop(); // Up & Down payload
            IntPtr hwnd = GetDesktopWindow();
            IntPtr hdc = GetWindowDC(hwnd);
            int x = Screen.PrimaryScreen.Bounds.Width;
            int y = Screen.PrimaryScreen.Bounds.Height;
            StretchBlt(hdc, 0, 20, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, 0, 20, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, 0, 20, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, 0, 20, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, 0, 20, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, 0, -40, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, 0, -40, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, 0, -40, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, 0, -40, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, 0, -40, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, 0, 20, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, 0, 20, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, 0, 20, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, 0, 20, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            StretchBlt(hdc, 0, 20, x, y, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            timer12.Start();
        }

        private void timer13_Tick(object sender, EventArgs e)
        {
            timer13.Stop(); // Super-Tunnel payload (Second-to-last payload)
            IntPtr hwnd = GetDesktopWindow();
            IntPtr hdc = GetWindowDC(hwnd);
            int x = Screen.PrimaryScreen.Bounds.Width;
            int y = Screen.PrimaryScreen.Bounds.Height;
            StretchBlt(hdc, 5, 5, x - 10, y - 10, hdc, 0, 0, x, y, TernaryRasterOperations.SRCINVERT);
            timer13.Start();
        }

        private void timer14_Tick(object sender, EventArgs e)
        {
            timer14.Stop(); // Every payload combined (Last payload)
            if (timer14.Interval <= 2)
            {
                timer1.Start();
                timer4.Start();
                timer5.Start();
                timer6.Start();
                timer7.Start();
                timer8.Start();
                timer9.Start();
                timer10.Start();
                timer11.Start();
                timer12.Start();
                timer14.Interval += 2147483646;
            }
            else if(timer14.Interval >= 3)
            {
                timer14.Interval -= 1;
            }
        }

        private void timer15_Tick(object sender, EventArgs e)
        {
            timer15.Stop(); // Timer until Payload 2
            if (timer15.Interval >= 4999)
            {
                timer15.Interval -= 1;
            }
            else if(timer15.Interval <= 4999)
            {
                timer2.Start();
                timer16.Start();
                timer15.Interval += 2147468648;
            }
            timer15.Start();
        }

        private void timer16_Tick(object sender, EventArgs e)
        {
            timer16.Stop(); // Timer until Payload 3
            if (timer16.Interval >= 4999)
            {
                timer16.Interval -= 1;
            }
            else if (timer16.Interval <= 4999)
            {
                timer3.Start(); // Starts payload 3
                timer17.Start();
                timer16.Interval += 2147468648;
            }
            timer16.Start();
        }

        private void timer17_Tick(object sender, EventArgs e)
        {
            timer17.Stop(); // Timer until Payload 4
            if (timer17.Interval >= 4999)
            {
                timer17.Interval -= 1;
            }
            else if (timer17.Interval <= 4999)
            {
                timer4.Start(); // Starts payload 4
                timer1.Stop(); // Stops the screen wobble payload
                timer18.Start();
                timer17.Interval += 2147468648;
            }
            timer17.Start();
        }

        private void timer18_Tick(object sender, EventArgs e)
        {
            timer18.Stop(); // Timer until Payload 5
            if (timer18.Interval >= 4999)
            {
                timer18.Interval -= 1;
            }
            else if (timer18.Interval <= 4999)
            {
                timer5.Start(); // Starts payload 5
                timer4.Stop(); // Stops the inverted color lines payload
                timer19.Start();
                timer18.Interval += 2147468648;
            }
            timer18.Start();
        }

        private void timer19_Tick(object sender, EventArgs e)
        {
            timer19.Stop(); // Timer until Payload 6
            if (timer19.Interval >= 4999)
            {
                timer19.Interval -= 1;
            }
            else if (timer19.Interval <= 4999)
            {
                timer6.Start(); // Starts payload 6
                timer5.Stop(); // Stops the screen compression payload
                timer20.Start();
                timer19.Interval += 2147468648;
            }
            timer19.Start();
        }

        private void timer20_Tick(object sender, EventArgs e)
        {
            timer20.Stop(); // Timer until Payload 7
            if (timer20.Interval >= 4999)
            {
                timer20.Interval -= 1;
            }
            else if (timer20.Interval <= 4999)
            {
                timer7.Start(); // Starts payload 7
                timer6.Stop(); // Stops the tunnel exit payload
                timer21.Start();
                timer20.Interval += 2147468648;
            }
            timer20.Start();
        }

        private void timer21_Tick(object sender, EventArgs e)
        {
            timer21.Stop(); // Timer until Payload 8
            if (timer21.Interval >= 4999)
            {
                timer21.Interval -= 1;
            }
            else if (timer21.Interval <= 4999)
            {
                timer8.Start(); // Starts payload 8
                timer7.Stop(); // Stops the in & out tunnel (massive color distortion) payload
                timer22.Start();
                timer21.Interval += 2147468648;
            }
            timer21.Start();
        }

        private void timer22_Tick(object sender, EventArgs e)
        {
            timer22.Stop(); // Timer until Payload 9
            if (timer22.Interval >= 4999)
            {
                timer22.Interval -= 1;
            }
            else if (timer22.Interval <= 4999)
            {
                timer9.Start(); // Starts payload 9
                timer8.Stop(); // Stops the screen bounce payload
                timer23.Start();
                timer22.Interval += 2147468648;
            }
            timer22.Start();
        }

        private void timer23_Tick(object sender, EventArgs e)
        {
            timer23.Stop(); // Timer until Payload 10
            if (timer23.Interval >= 4999)
            {
                timer23.Interval -= 1;
            }
            else if (timer23.Interval <= 4999)
            {
                timer10.Start(); // Starts payload 10
                timer9.Stop(); // Stops the top-left tunnel payload
                timer24.Start();
                timer23.Interval += 2147468648;
            }
            timer23.Start();
        }

        private void timer24_Tick(object sender, EventArgs e)
        {
            timer24.Stop(); // Timer until Payload 11
            if (timer24.Interval >= 4999)
            {
                timer24.Interval -= 1;
            }
            else if (timer24.Interval <= 4999)
            {
                timer11.Start(); // Starts payload 11
                timer10.Stop(); // Stops the screen crushing payload
                timer25.Start();
                timer24.Interval += 2147468648;
            }
            timer24.Start();
        }

        private void timer25_Tick(object sender, EventArgs e)
        {
            timer25.Stop(); // Timer until Payload 12
            if (timer25.Interval >= 4999)
            {
                timer25.Interval -= 1;
            }
            else if (timer25.Interval <= 4999)
            {
                timer12.Start(); // Starts payload 12
                timer11.Stop(); // Stops the Middle to Top-Left to Bottom-right to Middle to Top-Right to Botton-left and so on Payload
                timer26.Start();
                timer25.Interval += 2147468648;
            }
            timer25.Start();
        }

        private void timer26_Tick(object sender, EventArgs e)
        {
            timer26.Stop(); // Timer until Payload 13
            if (timer26.Interval >= 4999)
            {
                timer26.Interval -= 1;
            }
            else if (timer26.Interval <= 4999)
            {
                timer13.Start(); // Starts payload 13
                timer12.Stop(); // Stops the Up & Down Payload
                timer27.Start();
                timer26.Interval += 2147468648;
            }
            timer26.Start();
        }

        private void timer27_Tick(object sender, EventArgs e)
        {
            timer27.Stop(); // Timer until Payload 14
            if (timer27.Interval >= 4999)
            {
                timer27.Interval -= 1;
            }
            else if (timer27.Interval <= 4999)
            {
                timer14.Start(); // Starts payload 14
                timer27.Interval += 2147468648;
            }
            timer27.Start();
        }
    }
}
