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
    public partial class virus_last_again : Form
    {
        public virus_last_again()
        {
            InitializeComponent();
        }

        private void virus_last_again_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
        }

        private void virus_last_again_Load(object sender, EventArgs e)
        {
            var NewForm = new Virus_last();
            NewForm.ShowDialog();
        }
    }
}