Public Class Form4

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        If TextBox1.Text = "jKmKU8n23F" Then
            Form1.ProgressBar1.Value = 0
            Form1.Button4.Enabled = False
            Form1.Label5.Show()
            Me.Hide()
        End If
    End Sub
End Class