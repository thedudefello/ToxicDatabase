using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace RectylescOS11
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (keyData == (Keys.Alt | Keys.F4))
            {
                return true;
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }
        private void button1_Click(object sender, EventArgs e)
        {
            if(textBox1.Text == "")
            {
                label2.Visible = true;
                timer1.Start();
            } 
            else if(textBox1.Text == "W269N-WFGWX-YVC9B-4J6C9-T83GX")
            {
                this.Hide();
                new Form3().ShowDialog();
                this.Close();
            }   
            else
            {
                label2.Visible = true;
                timer1.Start();
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            timer1.Stop();
            label2.Visible = false;
        }

        private void Form2_Load(object sender, EventArgs e)
        {

        }
    }
}
