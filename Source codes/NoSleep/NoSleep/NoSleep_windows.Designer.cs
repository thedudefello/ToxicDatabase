namespace NoSleep
{
    partial class NoSleep_windows
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(NoSleep_windows));
            this.scary_video = new AxWMPLib.AxWindowsMediaPlayer();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.rules = new System.Windows.Forms.Label();
            this.timer_to_dead = new System.Windows.Forms.Label();
            this.clock_countdown = new System.Windows.Forms.Timer(this.components);
            this.check_values = new System.Windows.Forms.Timer(this.components);
            this.nosleep_image = new System.Windows.Forms.Timer(this.components);
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.glitch_screen = new System.Windows.Forms.Timer(this.components);
            this.dark_screen = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.scary_video)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.SuspendLayout();
            // 
            // scary_video
            // 
            this.scary_video.Dock = System.Windows.Forms.DockStyle.Fill;
            this.scary_video.Enabled = true;
            this.scary_video.Location = new System.Drawing.Point(0, 0);
            this.scary_video.Name = "scary_video";
            this.scary_video.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("scary_video.OcxState")));
            this.scary_video.Size = new System.Drawing.Size(547, 330);
            this.scary_video.TabIndex = 0;
            this.scary_video.TabStop = false;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(0, 276);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(547, 54);
            this.pictureBox1.TabIndex = 1;
            this.pictureBox1.TabStop = false;
            // 
            // rules
            // 
            this.rules.AutoSize = true;
            this.rules.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.rules.Font = new System.Drawing.Font("Arial Black", 21.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.rules.ForeColor = System.Drawing.Color.DarkRed;
            this.rules.Location = new System.Drawing.Point(12, 280);
            this.rules.Name = "rules";
            this.rules.Size = new System.Drawing.Size(128, 43);
            this.rules.TabIndex = 2;
            this.rules.Text = "RULES";
            this.rules.Click += new System.EventHandler(this.rules_Click);
            // 
            // timer_to_dead
            // 
            this.timer_to_dead.AutoSize = true;
            this.timer_to_dead.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.timer_to_dead.Font = new System.Drawing.Font("Arial Black", 21.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.timer_to_dead.ForeColor = System.Drawing.Color.DarkRed;
            this.timer_to_dead.Location = new System.Drawing.Point(429, 280);
            this.timer_to_dead.Name = "timer_to_dead";
            this.timer_to_dead.Size = new System.Drawing.Size(106, 43);
            this.timer_to_dead.TabIndex = 3;
            this.timer_to_dead.Text = "00:00";
            // 
            // clock_countdown
            // 
            this.clock_countdown.Interval = 240000;
            this.clock_countdown.Tick += new System.EventHandler(this.clock_countdown_Tick);
            // 
            // check_values
            // 
            this.check_values.Interval = 1000;
            this.check_values.Tick += new System.EventHandler(this.check_values_Tick);
            // 
            // nosleep_image
            // 
            this.nosleep_image.Interval = 30000;
            this.nosleep_image.Tick += new System.EventHandler(this.nosleep_image_Tick);
            // 
            // pictureBox2
            // 
            this.pictureBox2.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox2.Image")));
            this.pictureBox2.Location = new System.Drawing.Point(12, 12);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(221, 258);
            this.pictureBox2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox2.TabIndex = 4;
            this.pictureBox2.TabStop = false;
            this.pictureBox2.Visible = false;
            // 
            // glitch_screen
            // 
            this.glitch_screen.Interval = 60000;
            this.glitch_screen.Tick += new System.EventHandler(this.glitch_screen_Tick);
            // 
            // dark_screen
            // 
            this.dark_screen.Interval = 60000;
            this.dark_screen.Tick += new System.EventHandler(this.dark_screen_Tick);
            // 
            // NoSleep_windows
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Black;
            this.ClientSize = new System.Drawing.Size(547, 330);
            this.ControlBox = false;
            this.Controls.Add(this.pictureBox2);
            this.Controls.Add(this.timer_to_dead);
            this.Controls.Add(this.rules);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.scary_video);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "NoSleep_windows";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "NoSleep.exe";
            this.TopMost = true;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.NoSleep_windows_FormClosing);
            this.Load += new System.EventHandler(this.NoSleep_windows_Load);
            ((System.ComponentModel.ISupportInitialize)(this.scary_video)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private AxWMPLib.AxWindowsMediaPlayer scary_video;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label rules;
        private System.Windows.Forms.Label timer_to_dead;
        private System.Windows.Forms.Timer clock_countdown;
        private System.Windows.Forms.Timer check_values;
        private System.Windows.Forms.Timer nosleep_image;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.Timer glitch_screen;
        private System.Windows.Forms.Timer dark_screen;
    }
}