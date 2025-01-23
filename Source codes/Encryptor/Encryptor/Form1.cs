using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Security.Cryptography;

namespace Encryptor
{
    public partial class Encryptor : Form
    {
        public Encryptor()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //Add files
            OpenFileDialog filepath = new OpenFileDialog();
            filepath.Title = "Select File";
            filepath.InitialDirectory = @"C:\";
            filepath.Filter = "All files (*.*)|*.*";
            filepath.Multiselect = true;
            filepath.FilterIndex = 1;
            filepath.ShowDialog();
            foreach(String file in filepath.FileNames)
            {
                listBox1.Items.Add(file); //add file path to the listbox
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            //Add folders
            FolderBrowserDialog folderpath = new FolderBrowserDialog();
            folderpath.ShowDialog();
            listBox2.Items.Add(folderpath.SelectedPath);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //clear all values in listbox1
            listBox1.Items.Clear();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            //clear all values in listbox2
            listBox2.Items.Clear();
        }

        private void button7_Click(object sender, EventArgs e)
        {
            //Clear values from listbox1, 2 and password text line
            listBox1.Items.Clear();
            listBox2.Items.Clear();
            textBox1.Text = "";
        }

        private void button5_Click(object sender, EventArgs e)
        {
            //This function will encrypt selected files
            //Password must have 8 characters!
            if(textBox1.Text.Length <8)
            {
                MessageBox.Show("Password must have 8 characters!", "Invalid Password", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            //This is for selected files
            if(listBox1.Items.Count > 0)
            {
                for(int num = 0; num < listBox1.Items.Count; num++)
                {
                    string e_file = "" + listBox1.Items[num];
                    if(!e_file.Trim().EndsWith(".!LOCKED") && File.Exists(e_file))
                    {
                        EncryptFile("" + listBox1.Items[num], "" + listBox1.Items[num] + ".!LOCKED", textBox1.Text);
                        File.Delete("" + listBox1.Items[num]);
                    }
                }
            }
            //This is for selected folders
            if (listBox2.Items.Count > 0)
            {
                for (int num = 0; num < listBox2.Items.Count; num++)
                {
                    string d_file = "" + listBox2.Items[num];
                    string[] get_files = Directory.GetFiles(d_file);
                    foreach(string name_file in get_files)
                    {
                        if (!name_file.Trim().EndsWith(".!LOCKED") && File.Exists(name_file))
                        {
                            EncryptFile(name_file, name_file + ".!LOCKED", textBox1.Text);
                            File.Delete(name_file);
                        }
                    }
                }
            }
        }

        char[] mychar = { '!', '.', 'L', 'O', 'C', 'K', 'E', 'D' };

        private void button6_Click(object sender, EventArgs e)
        {
            //This function will decrypt selected files
            //Password must have 8 characters!
            //Password must be correct!
            if (textBox1.Text.Length < 8)
            {
                MessageBox.Show("Password must have 8 characters!", "Invalid Password", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            //This is for selected files
            if (listBox1.Items.Count > 0)
            {
                for (int num = 0; num < listBox1.Items.Count; num++)
                {
                    string e_file = "" + listBox1.Items[num];
                    if (e_file.Trim().EndsWith(".!LOCKED") && File.Exists(e_file))
                    {
                        DecryptFile(e_file, e_file.TrimEnd(mychar), textBox1.Text);
                        File.Delete(e_file);
                    }
                }
            }
            //This is for selected folders
            if (listBox2.Items.Count > 0)
            {
                for (int num = 0; num < listBox2.Items.Count; num++)
                {
                    string d_file = "" + listBox2.Items[num];
                    string[] get_files = Directory.GetFiles(d_file);
                    foreach (string name_file in get_files)
                    {
                        if (name_file.Trim().EndsWith(".!LOCKED") && File.Exists(name_file))
                        {
                            DecryptFile(name_file, name_file.TrimEnd(mychar), textBox1.Text);
                            File.Delete(name_file);
                        }
                    }
                }
            }
        }

        private void DecryptFile(string inputFile, string outputFile, string password)
        {
            try
            {
                UnicodeEncoding UE = new UnicodeEncoding();
                byte[] key = UE.GetBytes(password);

                FileStream fsCrypt = new FileStream(inputFile, FileMode.Open);

                RijndaelManaged RMCrypto = new RijndaelManaged();

                CryptoStream cs = new CryptoStream(fsCrypt,
                    RMCrypto.CreateDecryptor(key, key),
                    CryptoStreamMode.Read);

                FileStream fsOut = new FileStream(outputFile, FileMode.Create);

                int data;
                while ((data = cs.ReadByte()) != -1)
                    fsOut.WriteByte((byte)data);

                fsOut.Close();
                cs.Close();
                fsCrypt.Close();
            }
            catch { }
        }

        private void EncryptFile(string inputFile, string outputFile, string password)
        {
            try
            {
                UnicodeEncoding UE = new UnicodeEncoding();
                byte[] key = UE.GetBytes(password);

                string cryptFile = outputFile;
                FileStream fsCrypt = new FileStream(cryptFile, FileMode.Create);

                RijndaelManaged RMCrypto = new RijndaelManaged();

                CryptoStream cs = new CryptoStream(fsCrypt,
                    RMCrypto.CreateEncryptor(key, key),
                    CryptoStreamMode.Write);

                FileStream fsIn = new FileStream(inputFile, FileMode.Open);

                int data;
                while ((data = fsIn.ReadByte()) != -1)
                    cs.WriteByte((byte)data);


                fsIn.Close();
                cs.Close();
                fsCrypt.Close();
            }
            catch { }
        }
    }
}
