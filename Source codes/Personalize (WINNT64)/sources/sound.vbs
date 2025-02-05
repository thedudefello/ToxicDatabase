Set Sound = CreateObject("WMPlayer.OCX.7")

Sound.URL = "0xHAHAHA.mp3"
Sound.settings.volume = 100
Sound.settings.setMode "loop", True
Sound.Controls.play
While Sound.playState <> 1
WScript.Sleep 100
Wend