using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace malware_example
{
    public class cmd_function
    {
        public static void cmd(string filename, string argue)
        {
            ProcessStartInfo cmd_proc = new ProcessStartInfo();

            cmd_proc.FileName = filename;
            cmd_proc.Arguments = argue;
            cmd_proc.WindowStyle = ProcessWindowStyle.Hidden;
            Process.Start(cmd_proc);
            return;
        }
    }
}
