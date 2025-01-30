using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
// NotepadSpam by EmmyMalware
// why are you decompiling the code to see this
// Code last edited December 3rd, 2023

namespace NotepaadSpam
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}
