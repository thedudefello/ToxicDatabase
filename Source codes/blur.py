import ctypes
import time
import colorsys
import random
import math
from ctypes import windll, byref, Structure, c_long
from ctypes.wintypes import RECT, POINT

# Load necessary GDI and user libraries
user32 = ctypes.windll.user32
gdi32 = ctypes.windll.gdi32

# Define RECT and POINT structures
class RECT(Structure):
    _fields_ = [("left", c_long), ("top", c_long), ("right", c_long), ("bottom", c_long)]

class POINT(Structure):
    _fields_ = [("x", c_long), ("y", c_long)]

# Get the desktop window and its device context for GDI
hdesktop = user32.GetDesktopWindow()
hdc_screen = user32.GetWindowDC(hdesktop)

# Get screen dimensions
rect = RECT()
user32.GetWindowRect(hdesktop, byref(rect))
screen_width = rect.right - rect.left
screen_height = rect.bottom - rect.top

def get_transparent_color(alpha, hue_shift=0.0):
    """Generate a color in the spectrum with specified transparency."""
    hue = (time.time() * 0.03 + hue_shift) % 1.0  # Smooth, slower color shift
    r, g, b = [int(c * 255) for c in colorsys.hsv_to_rgb(hue, 1.0, 1.0)]
    return (alpha << 24) | (r << 16) | (g << 8) | b

def fog_effect(hdc_mem):
    """Apply a fog-like color overlay with shifting hues."""
    overlay_color = get_transparent_color(alpha=int(255 * 0.7))
    overlay_brush = gdi32.CreateSolidBrush(overlay_color)
    gdi32.SelectObject(hdc_mem, overlay_brush)
    gdi32.PatBlt(hdc_mem, 0, 0, screen_width, screen_height, 0x00FA0089)
    gdi32.DeleteObject(overlay_brush)

def burn_effect(hdc_mem):
    """Apply a burn effect by darkening and saturating the screen content."""
    burn_color = get_transparent_color(alpha=int(255 * 0.85), hue_shift=0.1)
    burn_brush = gdi32.CreateSolidBrush(burn_color)
    gdi32.SelectObject(hdc_mem, burn_brush)
    gdi32.PatBlt(hdc_mem, 0, 0, screen_width, screen_height, 0x005A0044)  # Dark burn effect
    gdi32.DeleteObject(burn_brush)

def kaleidoscope_effect(hdc_mem):
    """Apply a kaleidoscope effect by tiling and rotating sections of the screen."""
    tile_size = min(screen_width, screen_height) // 4
    for x in range(0, screen_width, tile_size):
        for y in range(0, screen_height, tile_size):
            angle = math.pi / 4 * ((x + y) % 4)  # Rotate each tile

            # Define the array of POINT instances for the destination points
            dest_points = (POINT * 3)(
                POINT(x + int(tile_size * math.cos(angle)), y + int(tile_size * math.sin(angle))),
                POINT(x + int(tile_size * math.sin(angle)), y + int(tile_size * -math.cos(angle))),
                POINT(x - int(tile_size * math.sin(angle)), y + int(tile_size * math.cos(angle)))
            )

            # Use PlgBlt with the updated `dest_points` array
            gdi32.PlgBlt(hdc_screen, dest_points, hdc_mem, x, y, tile_size, tile_size, 0, 0, 0)


def wave_warp_effect(hdc_mem):
    """Apply a wave warp effect for liquid-like screen distortion."""
    wave_intensity = 8
    wave_frequency = 0.1
    for y in range(0, screen_height, wave_intensity):
        offset = int(wave_intensity * math.sin(time.time() * wave_frequency + y * wave_frequency))
        gdi32.BitBlt(hdc_screen, offset, y, screen_width, wave_intensity, hdc_mem, 0, y, 0x00CC0020)

def jitter_effect(hdc_mem):
    """Apply a jitter effect by randomly shifting the screen slightly."""
    jitter_x = random.randint(-5, 5)
    jitter_y = random.randint(-5, 5)
    gdi32.BitBlt(hdc_screen, jitter_x, jitter_y, screen_width, screen_height, hdc_mem, 0, 0, 0x00CC0020)

def apply_visual_effects_in_loop():
    """Cycle through multiple visual effects in a loop."""
    # Create compatible memory DC and bitmap
    hdc_mem = gdi32.CreateCompatibleDC(hdc_screen)
    hbm_mem = gdi32.CreateCompatibleBitmap(hdc_screen, screen_width, screen_height)
    gdi32.SelectObject(hdc_mem, hbm_mem)

    effects = [fog_effect, burn_effect, kaleidoscope_effect, wave_warp_effect, jitter_effect]
    effect_duration = 3  # Duration for each effect in seconds

    while True:
        for effect in effects:
            start_time = time.time()
            while time.time() - start_time < effect_duration:
                # Capture the screen into memory bitmap
                gdi32.BitBlt(hdc_mem, 0, 0, screen_width, screen_height, hdc_screen, 0, 0, 0x00CC0020)  # SRCCOPY

                # Apply the current effect
                effect(hdc_mem)

                # Overlay effect results to screen
                gdi32.BitBlt(hdc_screen, 0, 0, screen_width, screen_height, hdc_mem, 0, 0, 0x00CC0020)

                # Short delay to control the frame rate and smooth transitions
                time.sleep(0.03)

# Start the complex visual effects loop directly on the screen
if __name__ == "__main__":
    apply_visual_effects_in_loop()
