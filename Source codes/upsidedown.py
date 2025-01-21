import ctypes
import numpy as np
from ctypes import windll, byref, Structure, c_long, POINTER
from ctypes.wintypes import RECT
import time

class RECT(Structure):
    _fields_ = [("left", c_long), ("top", c_long), ("right", c_long), ("bottom", c_long)]

user32 = windll.user32
gdi32 = windll.gdi32

hdesktop = user32.GetDesktopWindow()
hdc_screen = user32.GetWindowDC(hdesktop)

rect = RECT()
user32.GetWindowRect(hdesktop, byref(rect))
screen_width = rect.right - rect.left
screen_height = rect.bottom - rect.top

hdc_mem = gdi32.CreateCompatibleDC(hdc_screen)
hbitmap = gdi32.CreateCompatibleBitmap(hdc_screen, screen_width, screen_height)
gdi32.SelectObject(hdc_mem, hbitmap)

class BITMAPINFOHEADER(Structure):
    _fields_ = [
        ("biSize", ctypes.c_uint32),
        ("biWidth", ctypes.c_long),
        ("biHeight", ctypes.c_long),
        ("biPlanes", ctypes.c_uint16),
        ("biBitCount", ctypes.c_uint16),
        ("biCompression", ctypes.c_uint32),
        ("biSizeImage", ctypes.c_uint32),
        ("biXPelsPerMeter", ctypes.c_long),
        ("biYPelsPerMeter", ctypes.c_long),
        ("biClrUsed", ctypes.c_uint32),
        ("biClrImportant", ctypes.c_uint32),
    ]

class BITMAPINFO(Structure):
    _fields_ = [("bmiHeader", BITMAPINFOHEADER)]

def flip_screen_static():
    bmp_info = BITMAPINFO()
    bmp_info.bmiHeader.biSize = ctypes.sizeof(BITMAPINFOHEADER)
    bmp_info.bmiHeader.biWidth = screen_width
    bmp_info.bmiHeader.biHeight = -screen_height
    bmp_info.bmiHeader.biPlanes = 1
    bmp_info.bmiHeader.biBitCount = 32
    bmp_info.bmiHeader.biCompression = 0
    bmp_info.bmiHeader.biSizeImage = 0
    bmp_info.bmiHeader.biXPelsPerMeter = 0
    bmp_info.bmiHeader.biYPelsPerMeter = 0
    bmp_info.bmiHeader.biClrUsed = 0
    bmp_info.bmiHeader.biClrImportant = 0

    screen_buffer = ctypes.create_string_buffer(screen_width * screen_height * 4)

    gdi32.BitBlt(hdc_mem, 0, 0, screen_width, screen_height, hdc_screen, 0, 0, 0x00CC0020)

    gdi32.GetDIBits(hdc_mem, hbitmap, 0, screen_height, screen_buffer, byref(bmp_info), 0)

    screen_array = np.frombuffer(screen_buffer, dtype=np.uint8).reshape((screen_height, screen_width, 4))

    flipped_array = np.flipud(screen_array)

    flipped_bytes = flipped_array.tobytes()

    while True:
        gdi32.SetDIBitsToDevice(
            hdc_screen,
            0,
            0,
            screen_width,
            screen_height,
            0,
            0,
            0,
            screen_height,
            flipped_bytes,
            byref(bmp_info),
            0
        )

try:
    flip_screen_static()
except KeyboardInterrupt:
    gdi32.DeleteObject(hbitmap)
    gdi32.DeleteDC(hdc_mem)
    user32.ReleaseDC(hdesktop, hdc_screen)
    print("Effect stopped.")
