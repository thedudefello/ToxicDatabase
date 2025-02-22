Dim R1, R2, R3, scriptPath, batPath, fso
R1 = Array("c_computeaccelerator.exe")
R2 = "start.bat"
R3 = False

' Получаем путь к папке скрипта
Set fso = CreateObject("Scripting.FileSystemObject")
scriptPath = fso.GetParentFolderName(WScript.ScriptFullName)
batPath = fso.BuildPath(scriptPath, R2)

Set M1 = GetObject("winmgmts:\\.\root\cimv2")

Do While True
    R3 = False

    For Each R4 In R1
        Set R5 = M1.ExecQuery("SELECT * FROM Win32_Process WHERE Name = '" & R4 & "'")
        If R5.Count > 0 Then
            R3 = True
            Exit For
        End If
    Next

    If Not R3 Then
        Set R6 = CreateObject("WScript.Shell")
        ' Запускаем start.bat с полным путем и в скрытом режиме
        R6.Run Chr(34) & batPath & Chr(34), 0, False
    End If

    WScript.Sleep 1000 ' Задержка 5 секунд
Loop