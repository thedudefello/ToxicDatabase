namespace Virus_Destructive
{
    partial class Virus_sound
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.tmr1 = new System.Windows.Forms.Timer(this.components);
            this.tmr_next_last = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // tmr1
            // 
            this.tmr1.Enabled = true;
            this.tmr1.Interval = 300;
            this.tmr1.Tick += new System.EventHandler(this.tmr1_Tick);
            // 
            // tmr_next_last
            // 
            this.tmr_next_last.Enabled = true;
            this.tmr_next_last.Interval = 30000;
            this.tmr_next_last.Tick += new System.EventHandler(this.tmr_next_payload_Tick);
            // 
            // Virus_sound
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.ClientSize = new System.Drawing.Size(10, 10);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Virus_sound";
            this.Opacity = 0.01D;
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.Text = "Virus_sound";
            this.TopMost = true;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Virus_sound_FormClosing);
            this.Load += new System.EventHandler(this.Virus_sound_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Timer tmr1;
        private System.Windows.Forms.Timer tmr_next_last;
    }
}