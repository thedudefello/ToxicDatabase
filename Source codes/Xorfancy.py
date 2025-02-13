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
    """Apply an intense XOR fractal effect with chaotic movement, spinning, and shaking."""
    rotation_angle = 0  # Initial rotation angle
    scale_factor = 1.0  # Initial scale factor

    while True:
        # Create a compatible memory device context and bitmap
        hdc_mem = gdi32.CreateCompatibleDC(hdc_screen)
        hbm_mem = gdi32.CreateCompatibleBitmap(hdc_screen, screen_width, screen_height)
        gdi32.SelectObject(hdc_mem, hbm_mem)
        gdi32.BitBlt(hdc_mem, 0, 0, screen_width, screen_height, hdc_screen, 0, 0, 0x00CC0020)  # SRCCOPY

        # Pulsating alpha with high transparency for vivid, chaotic color effect
        pulse_alpha = 200 + int(55 * (0.5 + 0.5 * math.sin(time.time() * 10.0)))  # Faster pulsing alpha
        overlay_color = get_intense_rainbow_color(alpha=pulse_alpha)

        # Spin, zoom, and shake
        rotation_angle += 0.1  # Increase rotation for spinning
        scale_factor = 1.0 + 0.1 * math.sin(time.time() * 2.0)  # Scale for zooming in and out
        shake_x = random.randint(-5, 5)  # Shake offset x
        shake_y = random.randint(-5, 5)  # Shake offset y

        # Apply XOR fractal effect across the screen with random warps
        for y in range(0, screen_height, 10):
            for x in range(0, screen_width, 10):
                if xor_fractal(x, y) < 128:  # Only apply in fractal regions
                    # Calculate warped position with rotation and scaling
                    centered_x = (x - screen_width / 2) * scale_factor
                    centered_y = (y - screen_height / 2) * scale_factor
                    rotated_x = int(centered_x * math.cos(rotation_angle) - centered_y * math.sin(rotation_angle))
                    rotated_y = int(centered_x * math.sin(rotation_angle) + centered_y * math.cos(rotation_angle))

                    # Offset back to screen center and add shake
                    final_x = rotated_x + screen_width // 2 + shake_x
                    final_y = rotated_y + screen_height // 2 + shake_y

                    # Copy the altered pixels back to the screen with random shifts
                    gdi32.BitBlt(hdc_screen, final_x, final_y, 10, 10, hdc_mem, x, y, 0x00CC0020)

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
