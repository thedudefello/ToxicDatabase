using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Bitmap_Process
{
    public class MainClass
    {
        public static void Main(string[] args)
        {
            var cBitmap = new BitmapClass();
            var thBitmap = new Thread(cBitmap.BitmapMain);

            thBitmap.Start();

            Application.Run();
        }
    }
}
