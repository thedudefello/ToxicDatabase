Public Class changecaptions

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        My.Settings.caption1 = TextBox1.Text
    End Sub
    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        My.Settings.caption2 = TextBox2.Text
    End Sub
End Class