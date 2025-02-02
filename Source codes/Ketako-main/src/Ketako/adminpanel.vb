Public Class adminpanel

    Private Property A As Integer
    Private Property R As Integer
    Private Property G As Integer
    Private Property B As Integer
    Private Property rand As New Random()

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        Dialog1.Close()
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        changecaptions.Show()
    End Sub

    Private Sub adminpanel_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Timer1.Start()
        If My.Settings.destructivemodeenabled = "Yes" Then
            Button3.Text = "Disable destructive mode (bit bugged)"
        Else
            Button3.Text = "Enable destructive mode (bit bugged)"
        End If
    End Sub

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
        If My.Settings.destructivemodeenabled = "Yes" Then
            My.Settings.destructivemodeenabled = "No"
            Form9.Show()
        Else
            Dialog2.Show()
        End If
    End Sub

    Private Sub Button4_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button4.Click
        If My.Settings.rainbowmode = "Yes" Then
            My.Settings.rainbowmode = "No"
        Else
            My.Settings.rainbowmode = "Yes"
        End If
    End Sub

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        If My.Settings.rainbowmode = "Yes" Then
            Button4.Text = "Disable rainbow mode"
            Button4.ForeColor = Color.Black
        Else
            A = rand.Next(0, 255)
            R = rand.Next(0, 255)
            G = rand.Next(0, 255)
            B = rand.Next(0, 255)
            Button4.ForeColor = Color.FromArgb(A, R, G, B)
            Button4.Text = "RAINBOW MODE"
        End If
    End Sub
End Class