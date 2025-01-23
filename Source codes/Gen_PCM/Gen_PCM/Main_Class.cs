using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Gen_PCM
{
    public class Main_Class
    {
        public static void Main(string[] args)
        {
            var c_pcm = new PCM_Audio();
            c_pcm.pcm();

            Application.Run();
        }
    }
}
