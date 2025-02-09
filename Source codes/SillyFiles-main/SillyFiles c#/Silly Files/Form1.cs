using System;
using System.Drawing;
using System.IO;
using System.Security.Cryptography;
using System.Text;
using System.Windows.Forms;
//using Silly.Github.S-illy;
namespace Silly_Files
{
    public partial class Form1 : Form
    {
        private string selectedFilePath = string.Empty;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            label5.Text = "Nothing selected...";
            label11.Text = "Nothing selected...";
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("https://github.com/S-illy/SillyFiles"); //My github!!!! :3
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            textBox1.UseSystemPasswordChar = !textBox1.UseSystemPasswordChar;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.Filter = "Todos los archivos (*.*)|*.*";
                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    selectedFilePath = openFileDialog.FileName;
                    string fileName = Path.GetFileName(selectedFilePath);
                    label5.Text = fileName;
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //handling
            if (string.IsNullOrWhiteSpace(textBox1.Text))
            {
                label6.Text = "Please select a password";
                label6.ForeColor = Color.Red;
                return;
            }

            if (string.IsNullOrEmpty(selectedFilePath))
            {
                label6.Text = "Please select a file";
                label6.ForeColor = Color.Red;
                return;
            }

            try
            {
                string password = textBox1.Text;
                EncryptFile(selectedFilePath, password);
                File.Delete(selectedFilePath);
                string encryptedFilePath = Path.ChangeExtension(selectedFilePath, ".silly");
                File.Move(selectedFilePath + ".silly", encryptedFilePath);
                label6.Text = "File encrypted successfully";
                label6.ForeColor = Color.Green;
                MessageBox.Show("File encrypted successfully", "SillyFiles");
                ResetForm();
            }
            catch (UnauthorizedAccessException)
            {
                label6.Text = "You need administrator privileges to encrypt this";
                label6.ForeColor = Color.Red;
                ResetForm();
            }
            catch (Exception ex)
            {
                label6.Text = "An error occurred";
                label6.ForeColor = Color.Red;
                MessageBox.Show(ex.Message, "Error");
                ResetForm();
            }
        }

        private void EncryptFile(string filePath, string password)
        {
            using (Aes aes = Aes.Create())
            {
                byte[] key = new byte[32];
                byte[] iv = new byte[16];
                using (var hash = new SHA256Managed())
                {
                    key = hash.ComputeHash(Encoding.UTF8.GetBytes(password));
                }

                aes.Key = key;
                aes.IV = iv;

                // save the original extension on the first bytes 
                string extension = Path.GetExtension(filePath);
                byte[] extensionBytes = Encoding.UTF8.GetBytes(extension);
                byte extensionLength = (byte)extensionBytes.Length;

                using (FileStream fsInput = new FileStream(filePath, FileMode.Open, FileAccess.Read))
                using (FileStream fsEncrypted = new FileStream(filePath + ".silly", FileMode.Create, FileAccess.Write))
                using (CryptoStream cs = new CryptoStream(fsEncrypted, aes.CreateEncryptor(), CryptoStreamMode.Write))
                {
                    fsEncrypted.WriteByte(extensionLength); // Ex. lenght 
                    fsEncrypted.Write(extensionBytes, 0, extensionBytes.Length); // Write the extension :3
                    fsInput.CopyTo(cs); // Write the encrypted file
                }
            }
        }

        private void ResetForm()
        {
            textBox1.Clear();
            textBox2.Clear();
            selectedFilePath = string.Empty;
            label5.Text = "Nothing selected...";
            label6.Text = string.Empty;
            label9.Text = string.Empty;
            label11.Text = "Nothing selected...";
        }

        private void button3_Click(object sender, EventArgs e)
        {
            // handling
            if (string.IsNullOrWhiteSpace(textBox2.Text))
            {
                label9.Text = "Please enter a password";
                label9.ForeColor = Color.Red;
                return;
            }

            if (string.IsNullOrEmpty(selectedFilePath))
            {
                label9.Text = "Please select a file";
                label9.ForeColor = Color.Red;
                return;
            }
            try
            {
                string password = textBox2.Text;
                DecryptFile(selectedFilePath, password);
                label9.Text = "File decrypted successfully";
                label9.ForeColor = Color.Green;
                MessageBox.Show("File decrypted successfully", "SillyFiles");
                ResetForm();
            }
            catch (CryptographicException)
            {
                label9.Text = "Invalid file or Invalid pass";
                label9.ForeColor = Color.Red;
                return;
            }
            catch (UnauthorizedAccessException)
            {
                label9.Text = "You need administrator privileges to decrypt this";
                label9.ForeColor = Color.Red;
                ResetForm();
            }
            catch (Exception ex)
            {
                label9.Text = "An error occurred";
                label9.ForeColor = Color.Red;
                MessageBox.Show(ex.Message, "Error");
                ResetForm();
            }
        }

        private void DecryptFile(string filePath, string password)
        {
            using (Aes aes = Aes.Create())
            {
                byte[] key = new byte[32];
                byte[] iv = new byte[16];
                using (var hash = new SHA256Managed())
                {
                    key = hash.ComputeHash(Encoding.UTF8.GetBytes(password));
                }

                aes.Key = key;
                aes.IV = iv;

                string decryptedFilePath = null;
                try
                {
                    using (FileStream fsInput = new FileStream(filePath, FileMode.Open, FileAccess.Read))
                    using (CryptoStream cs = new CryptoStream(fsInput, aes.CreateDecryptor(), CryptoStreamMode.Read))
                    {
                        // Read extension shit
                        int extensionLength = fsInput.ReadByte();
                        byte[] extensionBytes = new byte[extensionLength];
                        fsInput.Read(extensionBytes, 0, extensionLength);
                        string extension = Encoding.UTF8.GetString(extensionBytes);
                        decryptedFilePath = Path.ChangeExtension(filePath, extension);

                        // Build the decrypted file
                        using (FileStream fsDecrypted = new FileStream(decryptedFilePath, FileMode.Create, FileAccess.Write))
                        {
                            cs.CopyTo(fsDecrypted);
                        }
                    }
                    File.Delete(filePath);
                }
                catch (CryptographicException)
                {
                    if (!string.IsNullOrEmpty(decryptedFilePath) && File.Exists(decryptedFilePath))
                    {
                        File.Delete(decryptedFilePath);
                    }
                    throw; // Re-throw for handling
                }
            }
        }



        private void button4_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.Filter = "Todos los archivos (*.*)|*.*";
                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    selectedFilePath = openFileDialog.FileName;
                    string fileName = Path.GetFileName(selectedFilePath);
                    label11.Text = fileName;
                }
            }
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            textBox2.UseSystemPasswordChar = !textBox2.UseSystemPasswordChar;
        }
    }
}
