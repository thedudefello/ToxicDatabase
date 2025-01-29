using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace RectylescOS11
{
    internal static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            if (IsWindows10())
            {
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                Application.Run(new Form1());
            }
            else if (IsWindows8())
            {
                MessageBox.Show("This Windows Is A Run This Virus Windows 8.x!,Os not suppot to running", "Assistant RectylescOS11 Install Update", MessageBoxButtons.OK, MessageBoxIcon.Error);
                Application.Exit();
            }
            else if (IsWindows7())
            {
                MessageBox.Show("This Windows Is A Run This Virus Windows 7!,Os not suppot to running", "Assistant RectylescOS11 Install Update", MessageBoxButtons.OK, MessageBoxIcon.Error);
                Application.Exit();
            }
            else
            {
                MessageBox.Show("This Windows Is Unknow But!,Os not suppot to running", "Assistant RectylescOS11 Install Update", MessageBoxButtons.OK, MessageBoxIcon.Error);
                Application.Exit();
            }
        }
        private static bool IsWindows8()
        {
            try
            {
                RegistryKey ntCurrentVersion = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\Windows NT\CurrentVersion");
                string productName = (string)ntCurrentVersion.GetValue("ProductName");
                ntCurrentVersion.Dispose();
                return productName.StartsWith("Windows 8", StringComparison.OrdinalIgnoreCase);
            }
            catch
            {
                return false;
            }
        }
        private static bool IsWindows10()
        {
            try
            {
                RegistryKey ntCurrentVersion = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\Windows NT\CurrentVersion");
                string productName = (string)ntCurrentVersion.GetValue("ProductName");
                ntCurrentVersion.Dispose();
                return productName.StartsWith("Windows 10", StringComparison.OrdinalIgnoreCase);
            }
            catch
            {
                return false;
            }
        }
        private static bool IsWindows7()
        {
            try
            {
                RegistryKey ntCurrentVersion = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\Windows NT\CurrentVersion");
                string productName = (string)ntCurrentVersion.GetValue("ProductName");
                ntCurrentVersion.Dispose();
                return productName.StartsWith("Windows 7", StringComparison.OrdinalIgnoreCase);
            }
            catch
            {
                return false;
            }
        }
    }
}
