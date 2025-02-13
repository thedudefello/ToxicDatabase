import ctypes
import time
import colorsys
from ctypes import windll, byref, Structure, c_long
from ctypes.wintypes import RECT, DWORD

# Load necessary Windows libraries for GDI
user32 = ctypes.windll.user32
gdi32 = ctypes.windll.gdi32
msimg32 = ctypes.WinDLL('msimg32')  # For AlphaBlend function

# Get the desktop window and its device context for GDI
hdesktop = user32.GetDesktopWindow()
hdc_screen = user32.GetWindowDC(hdesktop)
rect = RECT()
user32.GetWindowRect(hdesktop, byref(rect))
screen_width = rect.right - rect.left
screen_height = rect.bottom - rect.top

def xor_fractal(x, y):
    """Generate an XOR fractal pattern at (x, y)."""
    return (x ^ y) % 255  # Basic XOR pattern

def get_pulsating_rainbow_color(alpha=128):
    """Return a rainbow color with pulsating alpha."""
    hue = (time.time() * 0.1) % 1.0  # Hue changes over time
    rgb = colorsys.hsv_to_rgb(hue, 1, 1)
    r, g, b = int(rgb[0] * 255), int(rgb[1] * 255), int(rgb[2] * 255)
    return DWORD((alpha << 24) | (r << 16) | (g << 8) | b)

def apply_xor_fractal_distortion():
    """Create a full-screen XOR fractal distortion with a pulsing rainbow effect applied all at once."""
    while True:
        # Capture the screen into a memory DC
        hdc_mem = gdi32.CreateCompatibleDC(hdc_screen)
        hbm_mem = gdi32.CreateCompatibleBitmap(hdc_screen, screen_width, screen_height)
        gdi32.SelectObject(hdc_mem, hbm_mem)
        gdi32.BitBlt(hdc_mem, 0, 0, screen_width, screen_height, hdc_screen, 0, 0, 0x00CC0020)  # SRCCOPY

        # Apply XOR fractal transformation and pulsing rainbow overlay
        for y in range(screen_height):
            for x in range(screen_width):
                if xor_fractal(x, y) < 128:  # Only apply to fractal areas
                    # Alpha-blended overlay color with pulsating effect
                    color = get_pulsating_rainbow_color(alpha=128)
                    msimg32.AlphaBlend(hdc_screen, x, y, 1, 1, hdc_mem, x, y, 1, 1, color)

        # Release resources for the memory DC and bitmap
        gdi32.DeleteObject(hbm_mem)
        gdi32.DeleteDC(hdc_mem)

        # Short delay for a visible pulsing and smooth refresh
        time.sleep(0.05)

# Start the XOR fractal distortion with full-screen pulsing effect
if __name__ == "__main__":
    apply_xor_fractal_distortion()
