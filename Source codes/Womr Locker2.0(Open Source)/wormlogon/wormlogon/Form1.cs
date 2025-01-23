using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace wormlogon
{
    public partial class logon : Form
    {
        public logon()
        {
            InitializeComponent();
        }

        private void logon_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true; //anti kill
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            timer1.Stop();
            pictureBox1.Visible = false; //Make Black
            timer2.Start();
        }

        private void logon_Load(object sender, EventArgs e)
        {
            timer1.Start();
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            timer2.Stop();
            pictureBox1.Visible = true; //Make Red
            timer1.Start();
        }
    }
}
