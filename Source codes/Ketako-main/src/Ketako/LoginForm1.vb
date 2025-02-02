Public Class LoginForm1

    Private Sub OK_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OK.Click
        If UsernameTextBox.Text = "Ketako" And PasswordTextBox.Text = "ketakoisthebest123" Then
            SplashScreen1.Show()
            Me.Close()
        Else
            Label2.Show()
        End If
    End Sub

    Private Sub Cancel_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Cancel.Click
        Me.Close()
    End Sub

    Private Sub LoginForm1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Label2.Hide()
    End Sub
End Class
