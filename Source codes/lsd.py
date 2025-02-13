import ctypes
import time
import colorsys
import math
from ctypes import windll, byref, Structure, c_long
from ctypes.wintypes import RECT, DWORD

# Load necessary GDI and user libraries
user32 = ctypes.windll.user32
gdi32 = ctypes.windll.gdi32

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

def get_psychedelic_color():
    """Return a vivid, shifting psychedelic color for the spheres."""
    hue = (time.time() * 0.5) % 1.0
    r, g, b = [int(c * 255) for c in colorsys.hsv_to_rgb(hue, 1.0, 1.0)]
    return DWORD((255 << 24) | (r << 16) | (g << 8) | b)

def draw_sphere(hdc, x, y, radius, color):
    """Draw a solid, colored sphere at (x, y) with the given radius and color."""
    brush = gdi32.CreateSolidBrush(color)
    gdi32.SelectObject(hdc, brush)
    gdi32.Ellipse(hdc, x - radius, y - radius, x + radius, y + radius)
    gdi32.DeleteObject(brush)

def apply_orbiting_spheres_effect():
    """Display a central sphere with multiple orbiting spheres."""
    orbit_radius = 150  # Radius of the orbit around the central sphere
    sphere_radius = 40  # Radius of the central sphere
    small_sphere_radius = 15  # Radius of orbiting spheres
    num_spheres = 5  # Number of orbiting spheres

    while True:
        # Clear and create a memory context
        hdc_mem = gdi32.CreateCompatibleDC(hdc_screen)
        hbm_mem = gdi32.CreateCompatibleBitmap(hdc_screen, screen_width, screen_height)
        gdi32.SelectObject(hdc_mem, hbm_mem)
        gdi32.BitBlt(hdc_mem, 0, 0, screen_width, screen_height, hdc_screen, 0, 0, 0x00CC0020)  # SRCCOPY

        # Draw the central sphere in a vibrant color
        central_color = get_psychedelic_color()
        draw_sphere(hdc_mem, center_x, center_y, sphere_radius, central_color)

        # Calculate and draw each orbiting sphere
        for i in range(num_spheres):
            angle = time.time() * 2 + (i * (2 * math.pi / num_spheres))  # Angle for each orbiting sphere
            orbit_x = int(center_x + orbit_radius * math.cos(angle))
            orbit_y = int(center_y + orbit_radius * math.sin(angle))
            orbit_color = get_psychedelic_color()  # Unique color for each frame
            draw_sphere(hdc_mem, orbit_x, orbit_y, small_sphere_radius, orbit_color)

        # Copy the memory context to the screen
        gdi32.BitBlt(hdc_screen, 0, 0, screen_width, screen_height, hdc_mem, 0, 0, 0x00CC0020)

        # Clean up
        gdi32.DeleteObject(hbm_mem)
        gdi32.DeleteDC(hdc_mem)

        # Short delay for visible movement
        time.sleep(0.02)

# Start the orbiting spheres effect directly on the screen
if __name__ == "__main__":
    apply_orbiting_spheres_effect()
