<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form remplace la méthode Dispose pour nettoyer la liste des composants.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Requise par le Concepteur Windows Form
    Private components As System.ComponentModel.IContainer

    'REMARQUE : la procédure suivante est requise par le Concepteur Windows Form
    'Elle peut être modifiée à l'aide du Concepteur Windows Form.  
    'Ne la modifiez pas à l'aide de l'éditeur de code.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form1))
        Me.PictureBox1 = New System.Windows.Forms.PictureBox()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.Button2 = New System.Windows.Forms.Button()
        Me.Button3 = New System.Windows.Forms.Button()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.ProgressBar1 = New System.Windows.Forms.ProgressBar()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.Button4 = New System.Windows.Forms.Button()
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.Label5 = New System.Windows.Forms.Label()
        Me.ProgressBar2 = New System.Windows.Forms.ProgressBar()
        Me.Button5 = New System.Windows.Forms.Button()
        Me.Label6 = New System.Windows.Forms.Label()
        Me.ProgressBar3 = New System.Windows.Forms.ProgressBar()
        Me.Label7 = New System.Windows.Forms.Label()
        Me.Timer2 = New System.Windows.Forms.Timer(Me.components)
        Me.Timer3 = New System.Windows.Forms.Timer(Me.components)
        Me.Timer4 = New System.Windows.Forms.Timer(Me.components)
        Me.Button6 = New System.Windows.Forms.Button()
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'PictureBox1
        '
        Me.PictureBox1.Image = CType(resources.GetObject("PictureBox1.Image"), System.Drawing.Image)
        Me.PictureBox1.Location = New System.Drawing.Point(-3, 0)
        Me.PictureBox1.Name = "PictureBox1"
        Me.PictureBox1.Size = New System.Drawing.Size(308, 326)
        Me.PictureBox1.TabIndex = 0
        Me.PictureBox1.TabStop = False
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Font = New System.Drawing.Font("Trebuchet MS", 18.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Location = New System.Drawing.Point(392, 19)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(84, 29)
        Me.Label1.TabIndex = 1
        Me.Label1.Text = "Label1"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Font = New System.Drawing.Font("Trebuchet MS", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label2.Location = New System.Drawing.Point(420, 59)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(56, 22)
        Me.Label2.TabIndex = 2
        Me.Label2.Text = "Label2"
        '
        'Button1
        '
        Me.Button1.Font = New System.Drawing.Font("Microsoft Sans Serif", 26.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Button1.Location = New System.Drawing.Point(-3, 333)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(308, 68)
        Me.Button1.TabIndex = 3
        Me.Button1.Text = "A random button"
        Me.Button1.UseVisualStyleBackColor = True
        '
        'Button2
        '
        Me.Button2.Font = New System.Drawing.Font("Trebuchet MS", 14.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Button2.Location = New System.Drawing.Point(324, 119)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(510, 33)
        Me.Button2.TabIndex = 4
        Me.Button2.Text = "Trash my computer now."
        Me.Button2.UseVisualStyleBackColor = True
        '
        'Button3
        '
        Me.Button3.Font = New System.Drawing.Font("Trebuchet MS", 14.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Button3.Location = New System.Drawing.Point(324, 197)
        Me.Button3.Name = "Button3"
        Me.Button3.Size = New System.Drawing.Size(510, 33)
        Me.Button3.TabIndex = 5
        Me.Button3.Text = "Please, stop !"
        Me.Button3.UseVisualStyleBackColor = True
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Font = New System.Drawing.Font("Microsoft Sans Serif", 15.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label3.Location = New System.Drawing.Point(553, 245)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(66, 25)
        Me.Label3.TabIndex = 6
        Me.Label3.Text = "No :D"
        '
        'ProgressBar1
        '
        Me.ProgressBar1.Location = New System.Drawing.Point(324, 284)
        Me.ProgressBar1.Maximum = 2000
        Me.ProgressBar1.Name = "ProgressBar1"
        Me.ProgressBar1.Size = New System.Drawing.Size(510, 42)
        Me.ProgressBar1.TabIndex = 7
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(321, 257)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(39, 13)
        Me.Label4.TabIndex = 8
        Me.Label4.Text = "Timer :"
        '
        'Button4
        '
        Me.Button4.Font = New System.Drawing.Font("Microsoft Sans Serif", 15.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Button4.Location = New System.Drawing.Point(324, 356)
        Me.Button4.Name = "Button4"
        Me.Button4.Size = New System.Drawing.Size(224, 33)
        Me.Button4.TabIndex = 9
        Me.Button4.Text = "Reset the TIMER !"
        Me.Button4.UseVisualStyleBackColor = True
        '
        'Timer1
        '
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(361, 392)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(147, 13)
        Me.Label5.TabIndex = 10
        Me.Label5.Text = "You can't reset the timer now."
        '
        'ProgressBar2
        '
        Me.ProgressBar2.Location = New System.Drawing.Point(650, 19)
        Me.ProgressBar2.Maximum = 5
        Me.ProgressBar2.Name = "ProgressBar2"
        Me.ProgressBar2.Size = New System.Drawing.Size(100, 23)
        Me.ProgressBar2.TabIndex = 11
        '
        'Button5
        '
        Me.Button5.Font = New System.Drawing.Font("Microsoft Sans Serif", 15.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Button5.Location = New System.Drawing.Point(594, 356)
        Me.Button5.Name = "Button5"
        Me.Button5.Size = New System.Drawing.Size(224, 33)
        Me.Button5.TabIndex = 12
        Me.Button5.Text = "Exit"
        Me.Button5.UseVisualStyleBackColor = True
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.Font = New System.Drawing.Font("Microsoft Sans Serif", 15.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label6.Location = New System.Drawing.Point(674, 392)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(66, 25)
        Me.Label6.TabIndex = 13
        Me.Label6.Text = "No :D"
        '
        'ProgressBar3
        '
        Me.ProgressBar3.Location = New System.Drawing.Point(650, 59)
        Me.ProgressBar3.Maximum = 5
        Me.ProgressBar3.Name = "ProgressBar3"
        Me.ProgressBar3.Size = New System.Drawing.Size(100, 23)
        Me.ProgressBar3.TabIndex = 14
        '
        'Label7
        '
        Me.Label7.AutoSize = True
        Me.Label7.Location = New System.Drawing.Point(503, 333)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(136, 13)
        Me.Label7.TabIndex = 15
        Me.Label7.Text = "Ketako v1.2, coded by Rix."
        '
        'Timer2
        '
        '
        'Timer3
        '
        '
        'Timer4
        '
        '
        'Button6
        '
        Me.Button6.Font = New System.Drawing.Font("Microsoft Sans Serif", 15.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Button6.Location = New System.Drawing.Point(460, 158)
        Me.Button6.Name = "Button6"
        Me.Button6.Size = New System.Drawing.Size(224, 33)
        Me.Button6.TabIndex = 16
        Me.Button6.Text = "Changelog"
        Me.Button6.UseVisualStyleBackColor = True
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(846, 413)
        Me.Controls.Add(Me.Button6)
        Me.Controls.Add(Me.Label7)
        Me.Controls.Add(Me.ProgressBar3)
        Me.Controls.Add(Me.Label6)
        Me.Controls.Add(Me.Button5)
        Me.Controls.Add(Me.ProgressBar2)
        Me.Controls.Add(Me.Label5)
        Me.Controls.Add(Me.Button4)
        Me.Controls.Add(Me.Label4)
        Me.Controls.Add(Me.ProgressBar1)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.Button3)
        Me.Controls.Add(Me.Button2)
        Me.Controls.Add(Me.Button1)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.PictureBox1)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None
        Me.MaximizeBox = False
        Me.Name = "Form1"
        Me.Text = "Ketako"
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents PictureBox1 As System.Windows.Forms.PictureBox
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents Button2 As System.Windows.Forms.Button
    Friend WithEvents Button3 As System.Windows.Forms.Button
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents ProgressBar1 As System.Windows.Forms.ProgressBar
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents Button4 As System.Windows.Forms.Button
    Friend WithEvents Timer1 As System.Windows.Forms.Timer
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents ProgressBar2 As System.Windows.Forms.ProgressBar
    Friend WithEvents Button5 As System.Windows.Forms.Button
    Friend WithEvents Label6 As System.Windows.Forms.Label
    Friend WithEvents ProgressBar3 As System.Windows.Forms.ProgressBar
    Friend WithEvents Label7 As System.Windows.Forms.Label
    Friend WithEvents Timer2 As System.Windows.Forms.Timer
    Friend WithEvents Timer3 As System.Windows.Forms.Timer
    Friend WithEvents Timer4 As System.Windows.Forms.Timer
    Friend WithEvents Button6 As System.Windows.Forms.Button

End Class
