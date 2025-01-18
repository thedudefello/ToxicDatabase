import ctypes
import time
import random
import math
from ctypes import windll, byref
from ctypes.wintypes import RECT, POINT

# Load necessary libraries
gdi32 = windll.gdi32
user32 = windll.user32
shell32 = windll.shell32

# Get the desktop window and its device context
hdesktop = user32.GetDesktopWindow()
hdc = user32.GetWindowDC(hdesktop)

# Get screen dimensions
rect = RECT()
user32.GetWindowRect(hdesktop, byref(rect))
width = rect.right - rect.left
height = rect.bottom - rect.top

# Load a collection of Windows icons
def load_windows_icons():
    icons = []
    for i in range(0, 50):  # Load the first 50 icons from shell32.dll
        icon_handle = shell32.ExtractIconW(0, "shell32.dll", i)
        if icon_handle:
            icons.append(icon_handle)
    return icons

# Function to get the cursor position
def get_cursor_position():
    point = POINT()
    user32.GetCursorPos(byref(point))
    return point.x, point.y

# Draw an icon that is influenced by independent gravity, movement, and distortion
def draw_independent_icon(hdc, icon_handle, icon_x, icon_y, cursor_x, cursor_y, velocity_x, velocity_y, gravity):
    icon_size = random.randint(24, 48)  # Random size between 24 and 48 pixels

    # Calculate distance from the cursor
    dx = cursor_x - icon_x
    dy = cursor_y - icon_y
    distance = (dx**2 + dy**2)**0.5

    # Apply gravity (independently)
    velocity_y += gravity

    # Calculate movement, including circular motion and explosion effect (independently)
    angle = math.atan2(dy, dx)
    velocity_x += math.cos(angle) * (distance * random.uniform(0.003, 0.007))  # Independent movement speed
    velocity_y += math.sin(angle) * (distance * random.uniform(0.003, 0.007))

    icon_x += int(velocity_x)
    icon_y += int(velocity_y)

    # Apply random independent distortions
    apply_independent_distortion(hdc, icon_x, icon_y, icon_size)

    # Draw the icon at the new position
    user32.DrawIconEx(hdc, icon_x, icon_y, icon_handle, icon_size, icon_size, 0, None, 3)

    return icon_x, icon_y, velocity_x, velocity_y  # Return the updated position and velocity

# Apply random distortions independently for each icon
def apply_independent_distortion(hdc, icon_x, icon_y, icon_size):
    for _ in range(random.randint(1, 3)):  # Fewer distortions per icon
        distortion_width = random.randint(10, icon_size)
        distortion_height = random.randint(10, icon_size)
        x1 = icon_x + random.randint(-distortion_width, distortion_width)
        y1 = icon_y + random.randint(-distortion_height, distortion_height)
        color = random.randint(0x000000, 0xFFFFFF)
        brush = create_brush(color)
        gdi32.PatBlt(hdc, x1, y1, distortion_width, distortion_height, brush)
        gdi32.DeleteObject(brush)

# Function to create the intense effect with independent icon behavior
def intense_independent_icons_effect(hdc, duration=15, fps=120):
    frame_duration = 1 / fps
    start_time = time.time()
    elapsed = 0

    # Load Windows icons
    icons = load_windows_icons()

    # Initialize random positions, velocities, and gravity for the icons
    icon_states = []
    for _ in icons:
        position = (random.randint(0, width), random.randint(0, height))
        velocity = (random.uniform(-2, 2), random.uniform(-2, 2))  # Slower initial velocities
        gravity = random.uniform(0.1, 0.3)  # Independent gravity for each icon
        icon_states.append((position, velocity, gravity))

    while elapsed < duration:
        frame_start_time = time.time()
        elapsed = time.time() - start_time

        # Get current cursor position
        cursor_x, cursor_y = get_cursor_position()

        # Draw each icon independently
        for i, icon_handle in enumerate(icons):
            position, velocity, gravity = icon_states[i]
            icon_x, icon_y = position
            velocity_x, velocity_y = velocity
            icon_x, icon_y, velocity_x, velocity_y = draw_independent_icon(
                hdc, icon_handle, icon_x, icon_y, cursor_x, cursor_y, velocity_x, velocity_y, gravity
            )
            icon_states[i] = ((icon_x, icon_y), (velocity_x, velocity_y), gravity)

        # Calculate the time taken and sleep to maintain the desired FPS
        frame_time = time.time() - frame_start_time
        if frame_time < frame_duration:
            time.sleep(frame_duration - frame_time)

# Function to create a brush with a specified color
def create_brush(color):
    return gdi32.CreateSolidBrush(color)

# Execute the intense independent icons effect
intense_independent_icons_effect(hdc)
