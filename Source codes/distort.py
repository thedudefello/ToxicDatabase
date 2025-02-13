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

# Calculate half dimensions for cloning effect
half_width = screen_width // 2
half_height = screen_height // 2

# Create a memory device context compatible with the screen
hdc_mem = gdi32.CreateCompatibleDC(hdc_screen)
hbm_mem = gdi32.CreateCompatibleBitmap(hdc_screen, screen_width, screen_height)
gdi32.SelectObject(hdc_mem, hbm_mem)

# Explosion parameters
clone_size = 50  # Initial size of cloned regions
growth_rate = 1.2  # Multiplier to grow each cloned region per frame

# Main loop for chaotic cloning and explosion effect
try:
    while True:
        # Copy and clone top-right corner across the screen
        for i in range(0, screen_width, int(clone_size)):
            for j in range(0, screen_height, int(clone_size)):
                # Randomly choose a source corner for variety
                src_x = random.choice([0, half_width])
                src_y = random.choice([0, half_height])

                # Copy the selected corner with random flipping
                gdi32.StretchBlt(
                    hdc_screen,
                    i,
                    j,
                    int(clone_size),
                    int(clone_size),
                    hdc_screen,
                    src_x,
                    src_y,
                    half_width,
                    half_height,
                    0x00CC0020
                )

        # Expand the clone size for explosive effect
        clone_size *= growth_rate
        if clone_size > screen_width:
            clone_size = 50  # Reset size to start explosion again

        # Frame delay for high-speed effect
        time.sleep(0.01)

except KeyboardInterrupt:
    # Release device contexts on exit
    user32.ReleaseDC(hdesktop, hdc_screen)
    gdi32.DeleteObject(hbm_mem)
    gdi32.DeleteDC(hdc_mem)
    print("Explosion effect stopped.")
