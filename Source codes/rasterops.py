import ctypes
import time
import random
from ctypes import windll, byref
from ctypes.wintypes import RECT

# Load necessary GDI libraries
gdi32 = windll.gdi32
user32 = windll.user32

# Get the desktop window and its device context for GDI
hdesktop = user32.GetDesktopWindow()
hdc_screen = user32.GetWindowDC(hdesktop)

# Get screen dimensions
rect = RECT()
user32.GetWindowRect(hdesktop, byref(rect))
screen_width = rect.right - rect.left
screen_height = rect.bottom - rect.top

# Create a memory device context compatible with the screen
hdc_mem = gdi32.CreateCompatibleDC(hdc_screen)
hbm_mem = gdi32.CreateCompatibleBitmap(hdc_screen, screen_width, screen_height)
gdi32.SelectObject(hdc_mem, hbm_mem)

# Main loop for chaotic screen-warping effect
try:
    while True:
        # Randomly select an area of the screen to copy and distort
        src_x = random.randint(0, screen_width - 1)
        src_y = random.randint(0, screen_height - 1)
        width = random.randint(50, 300)  # Random width for warp section
        height = random.randint(50, 300)  # Random height for warp section

        # Random destination coordinates to copy the warped section
        dest_x = random.randint(0, screen_width - 1)
        dest_y = random.randint(0, screen_height - 1)

        # Randomly choose a raster operation for chaotic effects
        raster_ops = [0x00CC0020, 0x00EE0086, 0x00660046, 0x00990066]  # SRCCOPY, SRCINVERT, SRCAND, SRCERASE
        raster_op = random.choice(raster_ops)

        # Copy a section of the screen with random offset and blend it
        gdi32.BitBlt(hdc_screen, dest_x, dest_y, width, height, hdc_screen, src_x, src_y, raster_op)

        # Frame delay of 1 ms for high-speed chaos
        time.sleep(0.001)

except KeyboardInterrupt:
    # Release device contexts on exit
    user32.ReleaseDC(hdesktop, hdc_screen)
    gdi32.DeleteObject(hbm_mem)
    gdi32.DeleteDC(hdc_mem)
    print("Screen warping stopped.")
