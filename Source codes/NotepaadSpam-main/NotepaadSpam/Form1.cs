using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using NotepaadSpam.Properties;

// hey yall its emmy but i forgor how to code c# now so ill try my best

namespace NotepaadSpam
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        //some code for disabled buttons and exiting

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            button1.Enabled = true;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Hide();
            MessageBox.Show("ARE YOU REALLY SURE YOU WANT TO RUN THIS?", "LAST WARNING", MessageBoxButtons.YesNo, MessageBoxIcon.Warning);
        }

        private void label1_Click(object sender, EventArgs e)
        {
            label1.Text = "Trying to find something?????";
        }
    }
}
