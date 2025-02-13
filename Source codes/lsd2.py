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
center_x, center_y = screen_width // 2, screen_height // 2  # Center of the screen

def get_psychedelic_color(alpha, offset=0.0):
    """Return a DWORD color with a vivid, shifting psychedelic effect."""
    hue = (time.time() * 0.7 + offset) % 1.0  # Faster hue cycling for more chaos
    r, g, b = [int(c * 255) for c in colorsys.hsv_to_rgb(hue, 1.0, 1.0)]
    return DWORD((alpha << 24) | (r << 16) | (g << 8) | b)

def spherical_distortion(x, y, intensity=2.0):
    """Apply a spherical distortion for a slightly smaller effect."""
    dx, dy = x - center_x, y - center_y
    distance = math.sqrt(dx**2 + dy**2)
    max_dist = math.sqrt(center_x**2 + center_y**2)
    distort_factor = intensity * (0.5 + 0.5 * math.cos(distance / max_dist * math.pi))
    warped_x = int(center_x + dx * distort_factor)
    warped_y = int(center_y + dy * distort_factor)
    return warped_x, warped_y

def apply_psychedelic_spherical_effect():
    """Apply a smaller, highly chaotic spherical psychedelic effect with transparency."""
    while True:
        # Create a compatible memory device context and bitmap
        hdc_mem = gdi32.CreateCompatibleDC(hdc_screen)
        hbm_mem = gdi32.CreateCompatibleBitmap(hdc_screen, screen_width, screen_height)
        gdi32.SelectObject(hdc_mem, hbm_mem)
        gdi32.BitBlt(hdc_mem, 0, 0, screen_width, screen_height, hdc_screen, 0, 0, 0x00CC0020)  # SRCCOPY

        # Set pulsing alpha with high transparency for intense color effect
        pulse_alpha = 180 + int(75 * (0.5 + 0.5 * math.sin(time.time() * 8.0)))  # Faster pulse
        overlay_color = get_psychedelic_color(alpha=pulse_alpha)

        # Apply smaller and more chaotic spherical distortion
        for y in range(0, screen_height, 15):  # Smaller block size for intricate effect
            for x in range(0, screen_width, 15):
                warped_x, warped_y = spherical_distortion(x, y, intensity=2.0)  # Lower intensity for a tighter effect

                # Increase random chaos within distorted regions
                final_x = warped_x + random.randint(-20, 20)  # Larger random shifts
                final_y = warped_y + random.randint(-20, 20)

                # Copy the altered pixels back to the screen with chaotic randomness
                gdi32.BitBlt(hdc_screen, final_x, final_y, 15, 15, hdc_mem, x, y, 0x00CC0020)

        # AlphaBlend overlay for the intense, fast-pulsing psychedelic effect
        brush = gdi32.CreateSolidBrush(overlay_color)
        gdi32.SelectObject(hdc_screen, brush)
        msimg32.AlphaBlend(hdc_screen, 0, 0, screen_width, screen_height, hdc_mem, 0, 0, screen_width, screen_height, overlay_color)

        # Clean up
        gdi32.DeleteObject(hbm_mem)
        gdi32.DeleteDC(hdc_mem)

        # Extremely short delay for a highly chaotic, continuous effect
        time.sleep(0.01)

# Start the intense, smaller spherical psychedelic effect directly on the screen
if __name__ == "__main__":
    apply_psychedelic_spherical_effect()
