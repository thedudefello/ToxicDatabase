using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace locker
{
    public partial class cmd : Form
    {

        private float opacity1 = 0f;
        private float opacity2 = 0f;
        private float opacity5 = 0f;

        public cmd()
        {
            InitializeComponent();
            label1.ForeColor = Color.FromArgb(0, label1.ForeColor.R, label1.ForeColor.G, label1.ForeColor.B);
            label2.ForeColor = Color.FromArgb(0, label2.ForeColor.R, label2.ForeColor.G, label2.ForeColor.B);
            label5.ForeColor = Color.FromArgb(0, label5.ForeColor.R, label5.ForeColor.G, label5.ForeColor.B);

            Timer fadeTimer = new Timer();
            fadeTimer.Interval = 50;
            fadeTimer.Tick += (sender, e) =>
            {
                opacity1 += 0.05f;
                opacity2 += 0.05f;
                opacity5 += 0.05f;

                if (opacity1 >= 1f) opacity1 = 1f;
                if (opacity2 >= 1f) opacity2 = 1f;
                if (opacity5 >= 1f) opacity5 = 1f;

                label1.ForeColor = Color.FromArgb((int)(opacity1 * 255), label1.ForeColor.R, label1.ForeColor.G, label1.ForeColor.B);
                label2.ForeColor = Color.FromArgb((int)(opacity2 * 255), label2.ForeColor.R, label2.ForeColor.G, label2.ForeColor.B);
                label5.ForeColor = Color.FromArgb((int)(opacity5 * 255), label5.ForeColor.R, label5.ForeColor.G, label5.ForeColor.B);

                if (opacity1 == 1f && opacity2 == 1f && opacity5 == 1f)
                {
                    fadeTimer.Stop();
                }
            };

            fadeTimer.Start();
        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void cmd_Load(object sender, EventArgs e)
        {

        }
    }
}
