namespace rensenWare
{
	public partial class frmManualDecrypter : global::System.Windows.Forms.Form
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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.KeyPath = new System.Windows.Forms.Label();
            this.IVPath = new System.Windows.Forms.Label();
            this.ButtonKey = new System.Windows.Forms.Button();
            this.ButtonIV = new System.Windows.Forms.Button();
            this.StartDecrypt = new System.Windows.Forms.Button();
            this.DecryptStatus = new System.Windows.Forms.Label();
            this.ProgressDecrypt = new System.Windows.Forms.ProgressBar();
            this.DecryptedList = new System.Windows.Forms.ListBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Consolas", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(13, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(84, 15);
            this.label1.TabIndex = 0;
            this.label1.Text = "Key File : ";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Consolas", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.White;
            this.label2.Location = new System.Drawing.Point(13, 45);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(84, 15);
            this.label2.TabIndex = 0;
            this.label2.Text = "IV File  : ";
            // 
            // KeyPath
            // 
            this.KeyPath.Font = new System.Drawing.Font("Consolas", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.KeyPath.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.KeyPath.Location = new System.Drawing.Point(95, 17);
            this.KeyPath.Name = "KeyPath";
            this.KeyPath.Size = new System.Drawing.Size(193, 14);
            this.KeyPath.TabIndex = 1;
            // 
            // IVPath
            // 
            this.IVPath.Font = new System.Drawing.Font("Consolas", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.IVPath.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.IVPath.Location = new System.Drawing.Point(95, 48);
            this.IVPath.Name = "IVPath";
            this.IVPath.Size = new System.Drawing.Size(193, 14);
            this.IVPath.TabIndex = 1;
            // 
            // ButtonKey
            // 
            this.ButtonKey.Font = new System.Drawing.Font("Consolas", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ButtonKey.Location = new System.Drawing.Point(294, 13);
            this.ButtonKey.Name = "ButtonKey";
            this.ButtonKey.Size = new System.Drawing.Size(75, 27);
            this.ButtonKey.TabIndex = 2;
            this.ButtonKey.Text = "Browse...";
            this.ButtonKey.UseVisualStyleBackColor = true;
            this.ButtonKey.Click += new System.EventHandler(this.ButtonKey_Click);
            // 
            // ButtonIV
            // 
            this.ButtonIV.Font = new System.Drawing.Font("Consolas", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ButtonIV.Location = new System.Drawing.Point(294, 43);
            this.ButtonIV.Name = "ButtonIV";
            this.ButtonIV.Size = new System.Drawing.Size(75, 27);
            this.ButtonIV.TabIndex = 2;
            this.ButtonIV.Text = "Browse...";
            this.ButtonIV.UseVisualStyleBackColor = true;
            this.ButtonIV.Click += new System.EventHandler(this.ButtonIV_Click);
            // 
            // StartDecrypt
            // 
            this.StartDecrypt.Font = new System.Drawing.Font("Consolas", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.StartDecrypt.Location = new System.Drawing.Point(16, 82);
            this.StartDecrypt.Name = "StartDecrypt";
            this.StartDecrypt.Size = new System.Drawing.Size(353, 36);
            this.StartDecrypt.TabIndex = 3;
            this.StartDecrypt.Text = "Select File / Decrypt";
            this.StartDecrypt.UseVisualStyleBackColor = true;
            this.StartDecrypt.Click += new System.EventHandler(this.StartDecrypt_Click);
            // 
            // DecryptStatus
            // 
            this.DecryptStatus.Font = new System.Drawing.Font("Consolas", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.DecryptStatus.ForeColor = System.Drawing.Color.White;
            this.DecryptStatus.Location = new System.Drawing.Point(13, 129);
            this.DecryptStatus.Name = "DecryptStatus";
            this.DecryptStatus.Size = new System.Drawing.Size(356, 23);
            this.DecryptStatus.TabIndex = 0;
            this.DecryptStatus.Text = "Ready";
            // 
            // ProgressDecrypt
            // 
            this.ProgressDecrypt.Location = new System.Drawing.Point(16, 162);
            this.ProgressDecrypt.Name = "ProgressDecrypt";
            this.ProgressDecrypt.Size = new System.Drawing.Size(348, 27);
            this.ProgressDecrypt.TabIndex = 4;
            // 
            // DecryptedList
            // 
            this.DecryptedList.Font = new System.Drawing.Font("Consolas", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.DecryptedList.FormattingEnabled = true;
            this.DecryptedList.ItemHeight = 14;
            this.DecryptedList.Location = new System.Drawing.Point(16, 197);
            this.DecryptedList.Name = "DecryptedList";
            this.DecryptedList.Size = new System.Drawing.Size(348, 102);
            this.DecryptedList.TabIndex = 5;
            // 
            // frmManualDecrypter
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 14F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Red;
            this.ClientSize = new System.Drawing.Size(376, 308);
            this.Controls.Add(this.DecryptedList);
            this.Controls.Add(this.ProgressDecrypt);
            this.Controls.Add(this.StartDecrypt);
            this.Controls.Add(this.ButtonIV);
            this.Controls.Add(this.ButtonKey);
            this.Controls.Add(this.IVPath);
            this.Controls.Add(this.KeyPath);
            this.Controls.Add(this.DecryptStatus);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Font = new System.Drawing.Font("Consolas", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "frmManualDecrypter";
            this.ShowIcon = false;
            this.Text = "ManualDecrypt";
            this.ResumeLayout(false);
            this.PerformLayout();

		}

		private global::System.ComponentModel.IContainer components = null;

		private global::System.Windows.Forms.Label label1;

		private global::System.Windows.Forms.Label label2;

		private global::System.Windows.Forms.Label KeyPath;

		private global::System.Windows.Forms.Label IVPath;

		private global::System.Windows.Forms.Button ButtonKey;

		private global::System.Windows.Forms.Button ButtonIV;

		private global::System.Windows.Forms.Button StartDecrypt;

		private global::System.Windows.Forms.Label DecryptStatus;

		private global::System.Windows.Forms.ProgressBar ProgressDecrypt;

		private global::System.Windows.Forms.ListBox DecryptedList;
	}
}
