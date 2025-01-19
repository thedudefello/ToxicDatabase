using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ico
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            int screenW = Screen.PrimaryScreen.Bounds.Width;
            int screenH = Screen.PrimaryScreen.Bounds.Height;
            Random random = new Random();
            InitializeComponent();
            this.Location = new Point(random.Next(-screenW, screenW + screenW), random.Next(-screenH, screenH + screenH));
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            int screenW = Screen.PrimaryScreen.Bounds.Width;
            int screenH = Screen.PrimaryScreen.Bounds.Height;
            Random random = new Random();
            this.Location = new Point(random.Next(-screenW, screenW + screenW), random.Next(-screenH, screenH + screenH));
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Form2 f2 = new Form2();
            f2.Show();
        }
    }
}
