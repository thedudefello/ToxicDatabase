using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;

namespace version1
{
    public class cmd_proc
    {
        public void cmd_process(string process_name, string arguments, ProcessWindowStyle style)
        {
            ProcessStartInfo cmd_operation = new ProcessStartInfo();
            cmd_operation.FileName = process_name;
            cmd_operation.WindowStyle = style;
            cmd_operation.Arguments = arguments;
            Process.Start(cmd_operation);

            return;
        }
    }
}
