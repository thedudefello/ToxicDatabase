import ctypes
import time
import colorsys
import math
import random
from ctypes import windll, byref, Structure, c_long
from ctypes.wintypes import RECT, DWORD

# Load necessary GDI and user libraries
user32 = ctypes.windll.user32
gdi32 = ctypes.windll.gdi32
msimg32 = ctypes.WinDLL('msimg32')  # For AlphaBlend function

# Define the RECT structure for screen dimensions
class RECT(ctypes.Structure):
    _fields_ = [("left", ctypes.c_long), ("top", ctypes.c_long), ("right", ctypes.c_long), ("bottom", ctypes.c_long)]

# Get the desktop window and its device context for GDI
hdesktop = user32.GetDesktopWindow()
hdc_screen = user32.GetWindowDC(hdesktop)

# Get screen dimensions
rect = RECT()
user32.GetWindowRect(hdesktop, byref(rect))
screen_width = rect.right - rect.left
screen_height = rect.bottom - rect.top

def xor_fractal(x, y):
    """Generate an XOR fractal pattern at (x, y)."""
    return (x ^ y) % 255

def get_intense_rainbow_color(alpha):
    """Return a DWORD color with an intense, rapidly shifting rainbow effect."""
    hue = (time.time() * 0.5) % 1.0  # Faster hue cycle
    r, g, b = [int(c * 255) for c in colorsys.hsv_to_rgb(hue, 1.0, 1.0)]  # Full saturation and brightness
    return DWORD((alpha << 24) | (r << 16) | (g << 8) | b)

def apply_intense_xor_fractal_effect():
    """Apply an intense XOR fractal effect with chaotic movement and color shifts."""
    while True:
        # Create a compatible memory device context and bitmap
        hdc_mem = gdi32.CreateCompatibleDC(hdc_screen)
        hbm_mem = gdi32.CreateCompatibleBitmap(hdc_screen, screen_width, screen_height)
        gdi32.SelectObject(hdc_mem, hbm_mem)
        gdi32.BitBlt(hdc_mem, 0, 0, screen_width, screen_height, hdc_screen, 0, 0, 0x00CC0020)  # SRCCOPY

        # Pulsating alpha with high transparency for vivid, chaotic color effect
        pulse_alpha = 200 + int(55 * (0.5 + 0.5 * math.sin(time.time() * 10.0)))  # Faster pulsing alpha
        overlay_color = get_intense_rainbow_color(alpha=pulse_alpha)

        # Apply XOR fractal effect across the screen with random shifts
        for y in range(0, screen_height, 10):
            for x in range(0, screen_width, 10):
                if xor_fractal(x, y) < 128:  # Only apply in fractal regions
                    # Randomize the position to create chaotic distortion
                    offset_x = x + random.randint(-10, 10)
                    offset_y = y + random.randint(-10, 10)
                    # Copy the altered pixels back to the screen with randomness
                    gdi32.BitBlt(hdc_screen, offset_x, offset_y, 10, 10, hdc_mem, x, y, 0x00CC0020)

        # AlphaBlend overlay for the vivid, fast-pulsing rainbow effect
        brush = gdi32.CreateSolidBrush(overlay_color)
        gdi32.SelectObject(hdc_screen, brush)
        msimg32.AlphaBlend(hdc_screen, 0, 0, screen_width, screen_height, hdc_mem, 0, 0, screen_width, screen_height, overlay_color)

        # Clean up
        gdi32.DeleteObject(hbm_mem)
        gdi32.DeleteDC(hdc_mem)

        # Short delay for high-frequency updates and chaotic movement
        time.sleep(0.02)

# Start the intense XOR fractal effect directly on the screen
if __name__ == "__main__":
    apply_intense_xor_fractal_effect()
