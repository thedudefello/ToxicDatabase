using System;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Threading;
using System.Windows.Forms;

namespace rensenWare
{
	public partial class frmManualDecrypter : Form
	{
		private byte[] Key;
		private byte[] IV;

		public frmManualDecrypter()
		{
			this.InitializeComponent();
		}

		private void ButtonKey_Click(object sender, EventArgs e)
		{
			OpenFileDialog openFileDialog = new OpenFileDialog
			{
				Title  = "Open Key File",
				Filter = "Key/IV Binary File (*.bin)|*.bin"
			};

			if (openFileDialog.ShowDialog() == DialogResult.OK)
			{
				this.KeyPath.Text = openFileDialog.FileName;
				this.Key = File.ReadAllBytes(openFileDialog.FileName);
				if (this.Key.Length != 32)
				{
					MessageBox.Show("Invalid Key File!");
				}
			}
			else
			{
				this.Key = null;
			}
			this.StartDecrypt.Enabled = (this.Key == null || this.IV == null);
		}

		private void StartDecrypt_Click(object sender, EventArgs e)
		{
			OpenFileDialog openFileDialog = new OpenFileDialog
			{
				Title  = "Open Multiple Encrypted Files",
				Filter = "All (*.*)|*.*",
				Multiselect = true
			};

			if (openFileDialog.ShowDialog() == DialogResult.OK)
			{
				string[] files = openFileDialog.FileNames;
				this.ProgressDecrypt.Value = 0;
				this.ProgressDecrypt.Maximum = files.Length;
				new Thread(delegate()
				{
					foreach (string fileName in files)
					{
						try
						{
							this.DecryptStatus.Invoke(new MethodInvoker(delegate()
							{
								this.DecryptStatus.Text = Path.GetFileName(fileName);
							}));

							Program.Crypt(fileName, true); // Decrypt the file
							
							this.ProgressDecrypt.Invoke(new MethodInvoker(delegate()
							{
								ProgressBar progressDecrypt = this.ProgressDecrypt;
								int value = progressDecrypt.Value;
								progressDecrypt.Value = value + 1;
							}));

							this.DecryptedList.Invoke(new MethodInvoker(delegate()
							{
								this.DecryptedList.Items.Add(fileName);
								this.DecryptedList.SelectedIndex = this.DecryptedList.Items.Count - 1;
							}));
						}
						catch
						{
							this.DecryptedList.Invoke(new MethodInvoker(delegate()
							{
								this.DecryptedList.Items.Add("FAIL : " + fileName);
								this.DecryptedList.SelectedIndex = this.DecryptedList.Items.Count - 1;
							}));
						}
					}
				}).Start();
			}
		}

		private void ButtonIV_Click(object sender, EventArgs e)
		{
			OpenFileDialog openFileDialog = new OpenFileDialog
			{
				Title  = "Open IV File",
				Filter = "Key/IV Binary File (*.bin)|*.bin"
			};

			if (openFileDialog.ShowDialog() == DialogResult.OK)
			{
				this.IVPath.Text = openFileDialog.FileName;
				this.Key = File.ReadAllBytes(openFileDialog.FileName);
				if (this.Key.Length != 16)
				{
					MessageBox.Show("Invalid IV File!");
				}
			}
			else
			{
				this.IV = null;
			}
			this.StartDecrypt.Enabled = (this.Key == null || this.IV == null);
		}
	}
}
