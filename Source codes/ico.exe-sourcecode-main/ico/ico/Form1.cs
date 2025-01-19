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
    public partial class Form1 : Form
    {
		private static Random random = new Random();
        private static int screenW = Screen.PrimaryScreen.Bounds.Width;
        private static int screenH = Screen.PrimaryScreen.Bounds.Height;
        private static int redrawCounter;
        private static int codcod;
        private static int ballWidth = 401;
        private static int ballHeight = 174;
        private static int ballPosX = random.Next(screenW-ballWidth);
        private static int ballPosY = random.Next(screenH-ballHeight);
        private static int moveStepX = 4;
        private static int moveStepY = 4;
        public Form1()
        {
            InitializeComponent();
			ballPosX = random.Next(screenW - ballWidth);
			ballPosY = random.Next(screenH - ballHeight);
		}

        private void timer1_Tick(object sender, EventArgs e)
        {
            this.Location = new Point(ballPosX, ballPosY);
            ballPosX += moveStepX;
            if (
                ballPosX < 0 ||
                ballPosX + ballWidth > screenW
                )
            {
                moveStepX = -moveStepX;
            }

            ballPosY += moveStepY;
            if (
                ballPosY < 0 ||
                ballPosY + ballHeight > screenH
                )
            {
                moveStepY = -moveStepY;
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
		#region rgb to hsl
		public struct RGB
		{
			private byte _r;
			private byte _g;
			private byte _b;

			public RGB(byte r, byte g, byte b)
			{
				this._r = r;
				this._g = g;
				this._b = b;
			}

			public byte R
			{
				get { return this._r; }
				set { this._r = value; }
			}

			public byte G
			{
				get { return this._g; }
				set { this._g = value; }
			}

			public byte B
			{
				get { return this._b; }
				set { this._b = value; }
			}

			public bool Equals(RGB rgb)
			{
				return (this.R == rgb.R) && (this.G == rgb.G) && (this.B == rgb.B);
			}
		}

		public struct HSL
		{
			private int _h;
			private float _s;
			private float _l;

			public HSL(int h, float s, float l)
			{
				this._h = h;
				this._s = s;
				this._l = l;
			}

			public int H
			{
				get { return this._h; }
				set { this._h = value; }
			}

			public float S
			{
				get { return this._s; }
				set { this._s = value; }
			}

			public float L
			{
				get { return this._l; }
				set { this._l = value; }
			}

			public bool Equals(HSL hsl)
			{
				return (this.H == hsl.H) && (this.S == hsl.S) && (this.L == hsl.L);
			}
		}

		public static RGB HSLToRGB(HSL hsl)
		{
			byte r = 0;
			byte g = 0;
			byte b = 0;

			if (hsl.S == 0)
			{
				r = g = b = (byte)(hsl.L * 255);
			}
			else
			{
				float v1, v2;
				float hue = (float)hsl.H / 360;

				v2 = (hsl.L < 0.5) ? (hsl.L * (1 + hsl.S)) : ((hsl.L + hsl.S) - (hsl.L * hsl.S));
				v1 = 2 * hsl.L - v2;

				r = (byte)(255 * HueToRGB(v1, v2, hue + (1.0f / 3)));
				g = (byte)(255 * HueToRGB(v1, v2, hue));
				b = (byte)(255 * HueToRGB(v1, v2, hue - (1.0f / 3)));
			}

			return new RGB(r, g, b);
		}

		private static float HueToRGB(float v1, float v2, float vH)
		{
			if (vH < 0)
				vH += 1;

			if (vH > 1)
				vH -= 1;

			if ((6 * vH) < 1)
				return (v1 + (v2 - v1) * 6 * vH);

			if ((2 * vH) < 1)
				return v2;

			if ((3 * vH) < 2)
				return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);

			return v1;
		}
		#endregion
		private void timer2_Tick(object sender, EventArgs e)
        {
			redrawCounter += 1;
			int cc = redrawCounter;
			codcod += 2;
			int cod = codcod;
			HSL data = new HSL(cc, 1f, 0.5f);
			RGB value = HSLToRGB(data);
			HSL data1 = new HSL(cod, 1f, 0.5f);
			RGB value1 = HSLToRGB(data1);
			Random r = new Random();
			this.BackColor = Color.FromArgb(value.R, value.G, value.B);
			label1.ForeColor = Color.FromArgb(value1.R, value1.G, value1.B);
			ballPosX += moveStepX;
			if (
				ballPosX < 0 ||
				ballPosX + ballWidth > screenW
				)
			{
				moveStepX = -moveStepX;
			}

			ballPosY += moveStepY;
			if (
				ballPosY < 0 ||
				ballPosY + ballHeight > screenH
				)
			{
				moveStepY = -moveStepY;
			}
			if (redrawCounter >= 360) { redrawCounter = 0; }
			if (codcod >= 360) { codcod = 0; }
		}

        private void timer3_Tick(object sender, EventArgs e)
        {
			this.Close();
        }
    }
}
