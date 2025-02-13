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

# Define RECT and POINT structures
class RECT(ctypes.Structure):
    _fields_ = [("left", ctypes.c_long), ("top", ctypes.c_long), ("right", ctypes.c_long), ("bottom", ctypes.c_long)]

class POINT(ctypes.Structure):
    _fields_ = [("x", ctypes.c_long), ("y", ctypes.c_long)]

# Get the desktop window and its device context for GDI
hdesktop = user32.GetDesktopWindow()
hdc_screen = user32.GetWindowDC(hdesktop)

# Get screen dimensions
rect = RECT()
user32.GetWindowRect(hdesktop, byref(rect))
screen_width = rect.right - rect.left
screen_height = rect.bottom - rect.top

def get_rainbow_color(alpha, hue_shift=0.0):
    """Generate a vivid rainbow color with transparency."""
    hue = (time.time() * 0.5 + hue_shift) % 1.0
    r, g, b = [int(c * 255) for c in colorsys.hsv_to_rgb(hue, 1.0, 1.0)]
    return DWORD((alpha << 24) | (r << 16) | (g << 8) | b)

def draw_triangle(hdc, vertices, fill_color):
    """Draw a filled triangle at the specified vertices."""
    fill_brush = gdi32.CreateSolidBrush(fill_color)
    gdi32.SelectObject(hdc, fill_brush)
    gdi32.BeginPath(hdc)
    gdi32.MoveToEx(hdc, vertices[0].x, vertices[0].y, None)
    gdi32.LineTo(hdc, vertices[1].x, vertices[1].y)
    gdi32.LineTo(hdc, vertices[2].x, vertices[2].y)
    gdi32.LineTo(hdc, vertices[0].x, vertices[0].y)
    gdi32.EndPath(hdc)
    gdi32.FillPath(hdc)
    gdi32.DeleteObject(fill_brush)

def draw_ripple(hdc, center_x, center_y, radius, color):
    """Draw a circular ripple expanding outward from the center."""
    pen = gdi32.CreatePen(0, 5, color)
    gdi32.SelectObject(hdc, pen)
    gdi32.Ellipse(hdc, center_x - radius, center_y - radius, center_x + radius, center_y + radius)
    gdi32.DeleteObject(pen)

def generate_triangle(center_x, center_y, size, angle):
    """Generate vertices for an equilateral triangle."""
    return [
        POINT(int(center_x + size * math.cos(angle)), int(center_y + size * math.sin(angle))),
        POINT(int(center_x + size * math.cos(angle + 2 * math.pi / 3)), int(center_y + size * math.sin(angle + 2 * math.pi / 3))),
        POINT(int(center_x + size * math.cos(angle + 4 * math.pi / 3)), int(center_y + size * math.sin(angle + 4 * math.pi / 3))),
    ]

def apply_ultra_complex_explosive_effect():
    """Create an ultra-complex effect with pulsing, explosion fragments, and ripple distortions."""
    base_size = 80  # Initial triangle size
    max_ripple_radius = 300  # Maximum ripple radius
    triangle_x, triangle_y = screen_width // 4, screen_height // 4  # Initial triangle position
    speed_x, speed_y = 2, 1  # Movement speed
    last_pulse_time = time.time()
    fragments = []  # Store fragments

    while True:
        # Create a compatible memory device context and bitmap
        hdc_mem = gdi32.CreateCompatibleDC(hdc_screen)
        hbm_mem = gdi32.CreateCompatibleBitmap(hdc_screen, screen_width, screen_height)
        gdi32.SelectObject(hdc_mem, hbm_mem)
        gdi32.BitBlt(hdc_mem, 0, 0, screen_width, screen_height, hdc_screen, 0, 0, 0x00CC0020)  # SRCCOPY

        # Calculate pulsing triangle size and rotation angle
        pulse_size = base_size + int(20 * math.sin(time.time() * 4))  # Pulsing effect
        angle = time.time()  # Spinning angle
        triangle_color = get_rainbow_color(alpha=180)  # Dynamic color

        # Generate triangle vertices
        triangle_vertices = generate_triangle(triangle_x, triangle_y, pulse_size, angle)
        draw_triangle(hdc_mem, triangle_vertices, triangle_color)

        # Explosion pulse with ripple and fragments
        current_time = time.time()
        if current_time - last_pulse_time >= 1:
            # Generate ripple effect
            ripple_radius = int((current_time - last_pulse_time) * 200)
            ripple_color = get_rainbow_color(alpha=100, hue_shift=0.2)
            draw_ripple(hdc_mem, triangle_x, triangle_y, ripple_radius, ripple_color)

            # Generate explosion fragments
            for _ in range(8):
                fragment_angle = random.uniform(0, 2 * math.pi)
                fragment_speed = random.uniform(2, 6)
                fragment_size = random.randint(10, 20)
                fragment_color = get_rainbow_color(alpha=180, hue_shift=random.uniform(0, 1))
                fragments.append({
                    'x': triangle_x,
                    'y': triangle_y,
                    'size': fragment_size,
                    'angle': fragment_angle,
                    'speed': fragment_speed,
                    'color': fragment_color,
                    'start_time': current_time
                })

            last_pulse_time = current_time

        # Update and draw each fragment
        for fragment in fragments[:]:
            elapsed_time = current_time - fragment['start_time']
            fragment['x'] += int(fragment['speed'] * math.cos(fragment['angle']))
            fragment['y'] += int(fragment['speed'] * math.sin(fragment['angle']))
            fragment_color = get_rainbow_color(alpha=max(0, 255 - int(elapsed_time * 100)), hue_shift=fragment['color'])
            fragment_vertices = generate_triangle(fragment['x'], fragment['y'], fragment['size'], fragment['angle'])
            draw_triangle(hdc_mem, fragment_vertices, fragment_color)

            # Remove fragment after it fades out
            if elapsed_time > 2:
                fragments.remove(fragment)

        # Move triangle across the screen
        triangle_x += speed_x
        triangle_y += speed_y
        if triangle_x > screen_width - base_size or triangle_x < base_size:
            speed_x = -speed_x
        if triangle_y > screen_height - base_size or triangle_y < base_size:
            speed_y = -speed_y

        # Copy the memory context to the screen
        gdi32.BitBlt(hdc_screen, 0, 0, screen_width, screen_height, hdc_mem, 0, 0, 0x00CC0020)

        # Clean up
        gdi32.DeleteObject(hbm_mem)
        gdi32.DeleteDC(hdc_mem)

        # Short delay for smooth animation
        time.sleep(0.02)

# Start the ultra-complex explosive effect directly on the screen
if __name__ == "__main__":
    apply_ultra_complex_explosive_effect()
