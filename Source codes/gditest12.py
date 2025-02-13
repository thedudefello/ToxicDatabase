import ctypes
import time
import colorsys
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

# Animation parameters
hue = 0.0
offset_x = 0
offset_y = 0
speed_x = 4  # Increased speed for faster movement
speed_y = 3

# Main loop for XOR fractal animation
try:
    while True:
        # Convert hue to RGB
        rgb = colorsys.hsv_to_rgb(hue, 1, 1)
        r_base, g_base, b_base = [int(255 * val) for val in rgb]

        # Draw XOR fractal pattern with movement offset
        for x in range(screen_width):
            for y in range(screen_height):
                color_value = (x + offset_x) ^ (y + offset_y)  # Apply offset for movement
                r = (color_value * r_base) % 256
                g = (color_value * g_base) % 256
                b = (color_value * b_base) % 256
                color = (b << 16) | (g << 8) | r
                gdi32.SetPixel(hdc_mem, x, y, color)  # Set pixel color

        # Blit the off-screen buffer to the screen
        gdi32.BitBlt(hdc_screen, 0, 0, screen_width, screen_height, hdc_mem, 0, 0, 0x00CC0020)  # SRCCOPY

        # Update hue and offsets for color cycling and movement
        hue += 0.003  # Fine-tune hue increment for smooth color cycling
        if hue > 1:
            hue = 0
        offset_x += speed_x
        offset_y += speed_y

        # Ensure offsets wrap around for continuous motion
        offset_x %= screen_width
        offset_y %= screen_height

        # 1 ms delay between frames for smooth animation
        time.sleep(0.001)

except KeyboardInterrupt:
    # Release device contexts on exit
    user32.ReleaseDC(hdesktop, hdc_screen)
    gdi32.DeleteObject(hbm_mem)
    gdi32.DeleteDC(hdc_mem)
    print("Animation stopped.")
