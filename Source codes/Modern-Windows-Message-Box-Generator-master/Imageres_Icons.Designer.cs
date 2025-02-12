namespace Windows_Task_Dialog_Generator
{
    partial class Imageres_Icons
    {
        private System.ComponentModel.IContainer components = null;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanelMain;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        protected override void Dispose(bool disposing)
        {
            if ( disposing && (components != null) )
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        private void InitializeComponent()
        {
            flowLayoutPanelMain = new FlowLayoutPanel();
            SuspendLayout();
            // 
            // flowLayoutPanelMain
            // 
            flowLayoutPanelMain.AutoScroll = true;
            flowLayoutPanelMain.Dock = DockStyle.Fill;
            flowLayoutPanelMain.Location = new Point(0, 0);
            flowLayoutPanelMain.Margin = new Padding(2);
            flowLayoutPanelMain.Name = "flowLayoutPanelMain";
            flowLayoutPanelMain.Size = new Size(810, 450);
            flowLayoutPanelMain.TabIndex = 0;
            // 
            // Imageres_Icons
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(810, 450);
            Controls.Add(flowLayoutPanelMain);
            Margin = new Padding(2);
            Name = "Imageres_Icons";
            Text = "Imageres Icons Preview";
            ResumeLayout(false);

        }

        #endregion
    }
}
