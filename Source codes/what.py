import ctypes
import time

user32 = ctypes.windll.user32
gdi32 = ctypes.windll.gdi32

hDesktopWindow = user32.GetDesktopWindow()

while True:
    hDesktopDC = user32.GetWindowDC(hDesktopWindow)
    
    # Get screen width and height
    screen_width = user32.GetSystemMetrics(0)
    screen_height = user32.GetSystemMetrics(1)

    for i in range(1900):
        gdi32.StretchBlt(
            hDesktopDC, i, i, screen_width - i, screen_height - i, 
            hDesktopDC, i, i, screen_width, screen_height, 0x00CC0020  # SRCCOPY
        )
    user32.ReleaseDC(hDesktopWindow, hDesktopDC)
    
    
    time.sleep(1)