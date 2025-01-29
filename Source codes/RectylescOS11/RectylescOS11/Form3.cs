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
    public partial class Form3 : Form
    {
        int h, m, s;

        private void Form3_Load(object sender, EventArgs e)
        {

        }

        public Form3()
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
        private void timer1_Tick(object sender, EventArgs e)
        {
            Invoke(new Action(() =>
            {
                s += 1;
                if (s == 100)
                {
                    timer1.Stop();
                    this.Hide();
                    new Form4().ShowDialog();
                    this.Close();
                }
                label2.Text = string.Format("{0}", s.ToString().PadLeft(2, '0')) + "%";
            }));
        }
    }
}
