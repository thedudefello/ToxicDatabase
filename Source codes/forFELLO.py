import os
import subprocess
import time

# Function to write a script to a file
def write_script(filename, content):
    with open(filename, 'w') as file:
        file.write(content)

# Function to run a script
def run_script(filename):
    subprocess.Popen(["python", filename])

# Define each script as a string
scripts = {
    "complex_shake.py": '''
import ctypes
import random
import time
import math

# Define RECT structure manually
class RECT(ctypes.Structure):
    _fields_ = [("left", ctypes.c_long),
                ("top", ctypes.c_long),
                ("right", ctypes.c_long),
                ("bottom", ctypes.c_long)]

user32 = ctypes.windll.user32
hwnd = user32.GetForegroundWindow()

def complex_shake(hwnd):
    rect = RECT()
    user32.GetWindowRect(hwnd, ctypes.byref(rect))
    x, y = rect.left, rect.top

    angle = 0
    while True:
        intensity = random.randint(10, 30)
        offset_x = int(math.cos(angle) * intensity)
        offset_y = int(math.sin(angle) * intensity)
        angle += random.uniform(0.1, 1.0)
        
        user32.SetWindowPos(hwnd, 0, x + offset_x, y + offset_y, 0, 0, 0x0001)
        time.sleep(0.02)
        if random.random() > 0.9:
            time.sleep(0.1)  # Random pause to make the shake feel sporadic

if __name__ == "__main__":
    complex_shake(hwnd)
''',

    "gradient_color_change.py": '''
import ctypes
import random
import time

user32 = ctypes.windll.user32
gdi32 = ctypes.windll.gdi32
hwnd = user32.GetForegroundWindow()

def gradient_color_change(hwnd):
    hdc = user32.GetDC(hwnd)
    width = user32.GetSystemMetrics(0)
    height = user32.GetSystemMetrics(1)
    colors = [0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00, 0xFF00FF, 0x00FFFF]

    while True:
        for color1, color2 in zip(colors, colors[1:] + colors[:1]):
            for i in range(100):
                blend = ((color1 * (100 - i) + color2 * i) // 100) & 0xFFFFFF
                gdi32.SetBkColor(hdc, blend)
                for y in range(0, height, 10):
                    user32.RedrawWindow(hwnd, None, None, 0x0400)
                time.sleep(0.01)

    user32.ReleaseDC(hwnd, hdc)

if __name__ == "__main__":
    gradient_color_change(hwnd)
''',

    "animated_xor_fractals.py": '''
import ctypes
import time
import math

user32 = ctypes.windll.user32
gdi32 = ctypes.windll.gdi32
hwnd = user32.GetForegroundWindow()

def animated_xor_fractals(hwnd):
    hdc = user32.GetDC(hwnd)
    width = user32.GetSystemMetrics(0)
    height = user32.GetSystemMetrics(1)

    scale = 1
    while True:
        for x in range(0, width, 10):
            for y in range(0, height, 10):
                color = (x * scale ^ y * scale) & 0xFFFFFF
                gdi32.SetPixel(hdc, x, y, color)
        scale += 1
        if scale > 20:
            scale = 1  # Reset to loop the animation
        time.sleep(0.1)

    user32.ReleaseDC(hwnd, hdc)

if __name__ == "__main__":
    animated_xor_fractals(hwnd)
''',

    "wave_radial_explosion.py": '''
import ctypes
import random
import math
import time

user32 = ctypes.windll.user32
gdi32 = ctypes.windll.gdi32
hwnd = user32.GetForegroundWindow()

def wave_radial_explosion(hwnd):
    hdc = user32.GetDC(hwnd)
    width = user32.GetSystemMetrics(0)
    height = user32.GetSystemMetrics(1)
    cx, cy = width // 2, height // 2
    frequency = 0.1

    while True:
        color = random.randint(0, 0xFFFFFF)
        for r in range(0, min(width, height) // 2, 10):
            offset = int(math.sin(time.time() * frequency) * 50)
            gdi32.Ellipse(hdc, cx - r + offset, cy - r, cx + r - offset, cy + r)
            user32.RedrawWindow(hwnd, None, None, 0x0400)
        time.sleep(0.05)

    user32.ReleaseDC(hwnd, hdc)

if __name__ == "__main__":
    wave_radial_explosion(hwnd)
''',

    "saturation_cycle.py": '''
import ctypes
import time

user32 = ctypes.windll.user32
gdi32 = ctypes.windll.gdi32
hwnd = user32.GetForegroundWindow()

def saturation_cycle(hwnd):
    hdc = user32.GetDC(hwnd)
    colors = [0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00, 0xFF00FF, 0x00FFFF]
    
    while True:
        for color in colors:
            for i in range(1, 101):
                color_blend = (color * i // 100) & 0xFFFFFF
                gdi32.SetBkColor(hdc, color_blend)
                user32.RedrawWindow(hwnd, None, None, 0x0400)
                time.sleep(0.02)

    user32.ReleaseDC(hwnd, hdc)

if __name__ == "__main__":
    saturation_cycle(hwnd)
''',

    "rotating_shadow_cubes.py": '''
import ctypes
import random
import time
import math

user32 = ctypes.windll.user32
gdi32 = ctypes.windll.gdi32
hwnd = user32.GetForegroundWindow()

def rotating_shadow_cubes(hwnd):
    hdc = user32.GetDC(hwnd)
    width = user32.GetSystemMetrics(0)
    height = user32.GetSystemMetrics(1)
    angle = 0

    while True:
        cube_size = 50
        for i in range(0, 360, 45):
            x = int(width / 2 + 150 * math.cos(math.radians(i + angle)))
            y = int(height / 2 + 150 * math.sin(math.radians(i + angle)))
            gdi32.Rectangle(hdc, x, y, x + cube_size, y + cube_size)
            gdi32.Ellipse(hdc, x + 10, y + 10, x + 40, y + 40)  # Shadow effect
        angle += 10
        if angle > 360:
            angle = 0
        time.sleep(0.05)

    user32.ReleaseDC(hwnd, hdc)

if __name__ == "__main__":
    rotating_shadow_cubes(hwnd)
'''
}

# Write each script to its respective file
for filename, script_content in scripts.items():
    write_script(filename, script_content)

# Run each script with a 1-second delay in between
for filename in scripts.keys():
    run_script(filename)
    time.sleep(1)

# Optionally, remove the scripts after execution (comment out if you want to keep them)
for filename in scripts.keys():
    os.remove(filename)
