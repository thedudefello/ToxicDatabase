import ctypes
import math
import time
import random
from ctypes import wintypes
import win32api, win32gui

# Load GDI, User32, and msimg32 (for AlphaBlend) libraries
user32 = ctypes.windll.user32
gdi32 = ctypes.windll.gdi32
msimg32 = ctypes.windll.LoadLibrary("msimg32")

# Screen dimensions
screen_width = user32.GetSystemMetrics(0)
screen_height = user32.GetSystemMetrics(1)

# Get device context for screen
hdc_screen = win32gui.GetDC(0)

# Constants for chaotic animation
num_layers = random.randint(10, 20)
num_blooms = random.randint(5, 15)
alpha_level = 255  # Full opacity for vivid colors
layer_offset_variation = random.randint(5, 20)

# Define BLENDFUNCTION for AlphaBlend with full alpha
class BLENDFUNCTION(ctypes.Structure):
    _fields_ = [('BlendOp', ctypes.c_byte),
                ('BlendFlags', ctypes.c_byte),
                ('SourceConstantAlpha', ctypes.c_byte),
                ('AlphaFormat', ctypes.c_byte)]

blend_function = BLENDFUNCTION(BlendOp=0, BlendFlags=0, SourceConstantAlpha=alpha_level, AlphaFormat=0)
msimg32.AlphaBlend.argtypes = [
    wintypes.HDC, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int,
    wintypes.HDC, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int,
    BLENDFUNCTION
]

# Function to generate super vibrant colors
def get_chaotic_color(hue):
    hue = (hue + random.uniform(-60, 60)) % 360
    brightness = 255  # Max brightness for vivid colors
    min_color = 200  # Minimum color intensity for vibrance

    # Convert hue to RGB for vivid color effect
    c = brightness
    x = int(c * (1 - abs((hue / 60) % 2 - 1)))

    if 0 <= hue < 60:
        r, g, b = c, x, min_color
    elif 60 <= hue < 120:
        r, g, b = x, c, min_color
    elif 120 <= hue < 180:
        r, g, b = min_color, c, x
    elif 180 <= hue < 240:
        r, g, b = min_color, x, c
    elif 240 <= hue < 300:
        r, g, b = x, min_color, c
    else:
        r, g, b = c, min_color, x

    return win32api.RGB(r, g, b)

# Draw a petal with given rotation and color
def draw_petal(hdc, center_x, center_y, angle, length, width, color):
    end_x = int(center_x + length * math.cos(angle))
    end_y = int(center_y + length * math.sin(angle))

    control1_x = int(center_x + (length / random.uniform(1.5, 5)) * math.cos(angle + random.uniform(-math.pi / 4, math.pi / 4)))
    control1_y = int(center_y + (length / random.uniform(1.5, 5)) * math.sin(angle + random.uniform(-math.pi / 4, math.pi / 4)))
    control2_x = int(center_x + (length / random.uniform(1.5, 3)) * math.cos(angle - random.uniform(-math.pi / 4, math.pi / 4)))
    control2_y = int(center_y + (length / random.uniform(1.5, 3)) * math.sin(angle - random.uniform(-math.pi / 4, math.pi / 4)))

    side1_x = int(center_x + (length / random.uniform(1, 2)) * math.cos(angle + random.uniform(-math.pi / 12, math.pi / 12)))
    side1_y = int(center_y + (length / random.uniform(1, 2)) * math.sin(angle + random.uniform(-math.pi / 12, math.pi / 12)))
    side2_x = int(center_x + (length / random.uniform(1, 2)) * math.cos(angle - random.uniform(-math.pi / 12, math.pi / 12)))
    side2_y = int(center_y + (length / random.uniform(1, 2)) * math.sin(angle - random.uniform(-math.pi / 12, math.pi / 12)))

    points = [
        (center_x, center_y),
        (control1_x, control1_y),
        (side1_x, side1_y),
        (end_x, end_y),
        (side2_x, side2_y),
        (control2_x, control2_y)
    ]
    polygon_points = (ctypes.wintypes.POINT * len(points))(*[ctypes.wintypes.POINT(p[0], p[1]) for p in points])
    brush = gdi32.CreateSolidBrush(color)
    old_brush = gdi32.SelectObject(hdc, brush)

    gdi32.Polygon(hdc, ctypes.byref(polygon_points), len(points))
    gdi32.SelectObject(hdc, old_brush)
    gdi32.DeleteObject(brush)

# Function to draw a floral center
def draw_floral_center(hdc, center_x, center_y):
    num_center_petals = random.randint(8, 15)  # Small petals in the center
    petal_radius = random.randint(5, 10)  # Radius for central petals
    for i in range(num_center_petals):
        angle = i * (2 * math.pi / num_center_petals) + random.uniform(-0.1, 0.1)
        x = int(center_x + petal_radius * math.cos(angle))
        y = int(center_y + petal_radius * math.sin(angle))
        color = get_chaotic_color(random.randint(0, 360))  # Vibrant color for each stamen

        # Draw a small circular "petal" to represent the floral center
        brush = gdi32.CreateSolidBrush(color)
        old_brush = gdi32.SelectObject(hdc, brush)
        gdi32.Ellipse(hdc, x - 3, y - 3, x + 3, y + 3)
        gdi32.SelectObject(hdc, old_brush)
        gdi32.DeleteObject(brush)

# Main function to draw spinning blooms with a floral center
def bloom_lotus():
    hue_offset = random.randint(0, 360)
    rotation_angle = random.uniform(-0.2, 0.2)
    spin_speed = 0.1  # Control the speed of spinning

    bloom_positions = [(random.randint(0, screen_width), random.randint(0, screen_height)) for _ in range(num_blooms)]
    move_interval = random.randint(20, 50)

    cycle_count = 0
    while True:
        hue_offset += random.randint(10, 30)
        for (center_x, center_y) in bloom_positions:
            # Draw the floral center first
            draw_floral_center(hdc_screen, center_x, center_y)
            
            for layer in range(num_layers):
                petal_length = random.randint(20, 100) + layer * random.randint(10, 30)
                petal_width = random.randint(10, 30) + layer * random.randint(5, 15)
                num_petals = random.randint(8, 20)
                layer_hue = hue_offset + layer * random.randint(15, 45)
                color = get_chaotic_color(layer_hue)

                for i in range(num_petals):
                    # Adjust angle to create a spinning effect
                    angle = i * (2 * math.pi / num_petals) + (layer * random.uniform(0, math.pi / 4))
                    angle += rotation_angle + (cycle_count * spin_speed)  # Apply spin
                    draw_petal(hdc_screen, center_x, center_y, angle, petal_length, petal_width, color)

        rotation_angle += random.uniform(-0.05, 0.05)

        # Update bloom positions periodically
        if cycle_count % move_interval == 0:
            bloom_positions = [(random.randint(0, screen_width), random.randint(0, screen_height)) for _ in range(num_blooms)]
            move_interval = random.randint(20, 50)

        cycle_count += 1
        time.sleep(random.uniform(0.01, 0.04))

# Start the chaotic, spinning animation
bloom_lotus()
