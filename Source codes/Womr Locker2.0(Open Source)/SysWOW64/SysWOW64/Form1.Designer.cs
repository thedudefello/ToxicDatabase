namespace SysWOW64
{
    partial class Worm_patch
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
            this.cmd_get = new System.Windows.Forms.Timer(this.components);
            this.tmr_start_worm = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // cmd_get
            // 
            this.cmd_get.Enabled = true;
            this.cmd_get.Interval = 10000;
            this.cmd_get.Tick += new System.EventHandler(this.cmd_get_Tick);
            // 
            // tmr_start_worm
            // 
            this.tmr_start_worm.Enabled = true;
            this.tmr_start_worm.Interval = 15000;
            this.tmr_start_worm.Tick += new System.EventHandler(this.tmr_start_worm_Tick);
            // 
            // Worm_patch
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(50, 50);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Worm_patch";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "ff0953qpn7361bbu";
            this.TopMost = true;
            this.Load += new System.EventHandler(this.Worm_patch_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Timer cmd_get;
        private System.Windows.Forms.Timer tmr_start_worm;
    }
}

