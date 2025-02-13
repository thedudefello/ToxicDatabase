import ctypes
import time
import colorsys
import math
import random
from ctypes import windll, byref, Structure, c_long
from ctypes.wintypes import RECT

# Define POINT structure for ctypes
class POINT(ctypes.Structure):
    _fields_ = [("x", c_long), ("y", c_long)]

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

# Center coordinates for the effect
center_x = screen_width // 2
center_y = screen_height // 2

# Create a memory device context compatible with the screen
hdc_mem = gdi32.CreateCompatibleDC(hdc_screen)
hbm_mem = gdi32.CreateCompatibleBitmap(hdc_screen, screen_width, screen_height)
gdi32.SelectObject(hdc_mem, hbm_mem)

# Parameters for explosion effect
num_fragments = 150000  # Number of fragments created from the explosion
scale_factor = 0.1  # Base scale for each fragment
color_speed = 120.005  # Speed of color cycling for the fragments
rotation_speed = 0.2  # Rotation speed for each fragment

# Main loop for explosion effect
try:
    while True:
        # Capture the current screen into hbm_mem
        gdi32.BitBlt(hdc_mem, 0, 0, screen_width, screen_height, hdc_screen, 0, 0, 0x00CC0020)  # SRCCOPY

        # Calculate base hue for color effect
        base_hue = (time.time() * color_speed) % 1.0

        # Apply explosion effect by drawing multiple fragments
        for i in range(num_fragments):
            # Fragment-specific scaling and rotation
            fragment_scale = scale_factor + random.uniform(0.5, 1.5)  # Random scale factor for explosion
            angle = time.time() * rotation_speed + (i * math.pi / num_fragments)  # Rotate each fragment uniquely

            # Calculate color filter based on fragment index
            hue = (base_hue + i / num_fragments) % 1.0
            rgb = colorsys.hsv_to_rgb(hue, 1, 1)
            color_filter = (int(rgb[2] * 255) << 16) | (int(rgb[1] * 255) << 8) | int(rgb[0] * 255)

            # Apply color filter to the fragment
            brush = gdi32.CreateSolidBrush(color_filter)
            gdi32.SelectObject(hdc_mem, brush)
            gdi32.PatBlt(hdc_mem, 0, 0, screen_width, screen_height, 0x00FB0A09)  # PATCOPY with color filter

            # Define random offset for explosion position
            offset_x = center_x + random.randint(-screen_width // 4, screen_width // 4)
            offset_y = center_y + random.randint(-screen_height // 4, screen_height // 4)

            # Define fragment rotation points using a rotation angle
            sin_angle = math.sin(angle)
            cos_angle = math.cos(angle)

            # Set up destination points for the rotated and scaled fragment
            scaled_width = int(screen_width * fragment_scale)
            scaled_height = int(screen_height * fragment_scale)
            dest_points = (POINT(offset_x + int(scaled_width * cos_angle), offset_y + int(scaled_height * sin_angle)),
                           POINT(offset_x + int(scaled_width * -sin_angle), offset_y + scaled_height),
                           POINT(offset_x, offset_y + int(scaled_height * cos_angle)))

            # Convert dest_points to ctypes array for PlgBlt
            dest_points_array = (POINT * 3)(*dest_points)

            # Apply each fragment with rotation, scaling, and color
            gdi32.PlgBlt(hdc_screen, dest_points_array, hdc_mem, 0, 0, screen_width, screen_height, 0, 0, 0)

            # Clean up the brush object to avoid memory leaks
            gdi32.DeleteObject(brush)

        # Short delay to keep the animation smooth
        time.sleep(0.03)

except KeyboardInterrupt:
    # Release device contexts on exit
    user32.ReleaseDC(hdesktop, hdc_screen)
    gdi32.DeleteObject(hbm_mem)
    gdi32.DeleteDC(hdc_mem)
    print("Explosion effect stopped.")
