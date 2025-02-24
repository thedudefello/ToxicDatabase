Public Class WindowMaker
    Dim form As New Form()
    Dim label As New Windows.Forms.Label()
    Dim button1 As New Windows.Forms.Button()
    Dim button2 As New Windows.Forms.Button()

    Sub Create(title As String, text As String, x As Integer, y As Integer)
        form.Text = title
        form.StartPosition = FormStartPosition.Manual
        form.Location = New Point(x, y)
        form.Size = New Size(500, 150)
        form.FormBorderStyle = FormBorderStyle.FixedDialog
        form.MaximizeBox = False
        form.MinimizeBox = False
        form.ShowInTaskbar = False

        label.AutoSize = True
        label.Text = text
        label.Location = New Point((form.ClientSize.Width - label.Width) \ 2, 20)
        form.Controls.Add(label)

        button1.Location = New Point((form.ClientSize.Width \ 2) - 55, 80)
        button1.Size = New Size(50, 30)
        button1.Text = "OK"
        form.Controls.Add(button1)

        button2.Location = New Point((form.ClientSize.Width \ 2) + 5, 80)
        button2.Size = New Size(50, 30)
        button2.Text = "Cancel"
        form.Controls.Add(button2)

        form.ShowDialog()
    End Sub
End Class
