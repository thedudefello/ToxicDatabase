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
    _fields_ = [("x", c_long), ("y", c_long)]

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

def invert_square(hdc, center_x, center_y, size, rotation):
    """Invert colors within a spinning square area."""
    # Calculate square vertices based on size and rotation
    half_size = size // 2
    vertices = [
        POINT(int(center_x + half_size * math.cos(rotation)), int(center_y + half_size * math.sin(rotation))),
        POINT(int(center_x + half_size * math.cos(rotation + math.pi / 2)), int(center_y + half_size * math.sin(rotation + math.pi / 2))),
        POINT(int(center_x + half_size * math.cos(rotation + math.pi)), int(center_y + half_size * math.sin(rotation + math.pi))),
        POINT(int(center_x + half_size * math.cos(rotation + 3 * math.pi / 2)), int(center_y + half_size * math.sin(rotation + 3 * math.pi / 2))),
    ]
    
    # Draw the square path
    gdi32.BeginPath(hdc)
    gdi32.MoveToEx(hdc, vertices[0].x, vertices[0].y, None)
    for i in range(1, len(vertices)):
        gdi32.LineTo(hdc, vertices[i].x, vertices[i].y)
    gdi32.LineTo(hdc, vertices[0].x, vertices[0].y)
    gdi32.EndPath(hdc)
    
    # Invert the colors within the square
    gdi32.BitBlt(hdc, center_x - half_size, center_y - half_size, size, size, hdc, center_x - half_size, center_y - half_size, 0x00550009)

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

def draw_wave(hdc, center_x, center_y, radius, thickness, color):
    """Draw a chaotic circular wave expanding outward from the center."""
    pen = gdi32.CreatePen(0, thickness, color)
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
    """Create an ultra-complex effect with pulsing, explosion fragments, spinning inverted squares, and chaotic ripple distortions."""
    base_size = 140  # Larger main triangle size
    triangle_x, triangle_y = screen_width // 2, screen_height // 2  # Initial triangle position
    speed_x, speed_y = 5, 3  # Increased movement speed
    last_pulse_time = time.time()
    fragments = []  # Store fragments
    waves = []  # Store expanding waves

    # Setup for spinning inverted squares
    square_size = 30
    square_distance = int(base_size * 1.4)  # Distance from triangle center
    square_positions = [0, math.pi / 2, math.pi, 3 * math.pi / 2]  # Initial positions
    square_rotations = [0, math.pi / 4, math.pi / 2, 3 * math.pi / 4]  # Initial rotation angles for each square

    while True:
        # Create a compatible memory device context and bitmap
        hdc_mem = gdi32.CreateCompatibleDC(hdc_screen)
        hbm_mem = gdi32.CreateCompatibleBitmap(hdc_screen, screen_width, screen_height)
        gdi32.SelectObject(hdc_mem, hbm_mem)
        gdi32.BitBlt(hdc_mem, 0, 0, screen_width, screen_height, hdc_screen, 0, 0, 0x00CC0020)  # SRCCOPY

        # Calculate pulsing triangle size and rotation angle
        pulse_size = base_size + int(30 * math.sin(time.time() * 4))  # Pulsing effect
        angle = time.time()  # Spinning angle
        triangle_color = get_rainbow_color(alpha=180)  # Dynamic color

        # Generate triangle vertices
        triangle_vertices = generate_triangle(triangle_x, triangle_y, pulse_size, angle)

        # Explosion pulse with chaotic waves and fragments
        current_time = time.time()
        if current_time - last_pulse_time >= 0.4:  # Faster pulse interval for more chaos
            # Add chaotic expanding waves
            for i in range(6):  # Create more waves with smaller sizes
                waves.append({
                    'radius': 0,
                    'thickness': 4 + i,
                    'color': get_rainbow_color(alpha=220 - i * 30, hue_shift=0.1 * i),
                    'start_time': current_time + 0.04 * i  # Stagger each wave slightly
                })

            # Generate explosion fragments
            for _ in range(12):
                direction_angle = random.uniform(0, 2 * math.pi)  # Fixed direction for outward movement
                fragment_speed = random.uniform(3, 9)
                fragment_size = random.randint(6, 16)  # Smaller fragment size for chaos
                fragment_hue_shift = random.uniform(0, 1)  # Store unique hue shift
                spin_speed = random.uniform(0.3, 0.6)  # Faster spin for chaos
                fragments.append({
                    'x': triangle_x,
                    'y': triangle_y,
                    'size': fragment_size,
                    'direction': direction_angle,  # Fixed direction for flying outward
                    'rotation': 0,  # Initial rotation angle for spinning
                    'speed': fragment_speed,
                    'spin_speed': spin_speed,  # Store spin speed for rotation
                    'hue_shift': fragment_hue_shift,  # Store hue shift for color cycling
                    'start_time': current_time
                })

            last_pulse_time = current_time

        # Update and draw each expanding wave
        for wave in waves[:]:
            elapsed_wave_time = current_time - wave['start_time']
            wave['radius'] = int(elapsed_wave_time * 180)  # Smaller, faster expansion
            if wave['radius'] > 180:  # Remove waves after they expand past this radius
                waves.remove(wave)
                continue
            wave_color = get_rainbow_color(alpha=max(0, 220 - int(elapsed_wave_time * 90)), hue_shift=0.2)
            draw_wave(hdc_mem, triangle_x, triangle_y, wave['radius'], wave['thickness'], wave_color)

        # Update and draw each fragment
        for fragment in fragments[:]:
            elapsed_time = current_time - fragment['start_time']
            fragment['x'] += int(fragment['speed'] * math.cos(fragment['direction']))
            fragment['y'] += int(fragment['speed'] * math.sin(fragment['direction']))
            fragment['rotation'] += fragment['spin_speed']
            fragment_color = get_rainbow_color(alpha=max(0, 200 - int(elapsed_time * 120)), hue_shift=fragment['hue_shift'])
            fragment_vertices = generate_triangle(fragment['x'], fragment['y'], fragment['size'], fragment['rotation'])
            draw_triangle(hdc_mem, fragment_vertices, fragment_color)

            # Remove fragment after it fades out
            if elapsed_time > 1.5:
                fragments.remove(fragment)

        # Draw the main triangle after waves and fragments
        draw_triangle(hdc_mem, triangle_vertices, triangle_color)

        # Draw spinning inverted squares on top of everything else
        for i, position in enumerate(square_positions):
            # Calculate each square's position and rotation angle
            square_x = triangle_x + int(square_distance * math.cos(position + angle))
            square_y = triangle_y + int(square_distance * math.sin(position + angle))
            square_rotation = square_rotations[i] + time.time() * 2  # Spin the squares continuously
            invert_square(hdc_mem, square_x, square_y, square_size, square_rotation)

        # Move triangle across the screen with increased speed
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
