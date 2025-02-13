import ctypes
import time
import math
import random
import colorsys
from ctypes import windll, byref, Structure, c_long
from ctypes.wintypes import RECT, DWORD

# Define POINT structure for ctypes
class POINT(ctypes.Structure):
    _fields_ = [("x", c_long), ("y", c_long)]

# Load necessary GDI libraries
gdi32 = windll.gdi32
user32 = windll.user32
msimg32 = ctypes.WinDLL('msimg32')  # For AlphaBlend function

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
rotation_speed = 0.1  # Increase speed of rotation

# Take a screenshot of the screen to use as the background
hdc_mem = gdi32.CreateCompatibleDC(hdc_screen)
hbm_mem = gdi32.CreateCompatibleBitmap(hdc_screen, screen_width, screen_height)
gdi32.SelectObject(hdc_mem, hbm_mem)
gdi32.BitBlt(hdc_mem, 0, 0, screen_width, screen_height, hdc_screen, 0, 0, 0x00CC0020)  # Capture the screen

# Define a 3D geometric shape class with 2D circles at each corner and gradient color cycling
class Shape3D:
    def __init__(self, x, y, z, size, dx, dy):
        self.x = x
        self.y = y
        self.z = z
        self.size = size
        self.dx = dx  # Movement speed along the x-axis
        self.dy = dy  # Movement speed along the y-axis
        self.rotation_x = 0  # Rotation around x-axis
        self.rotation_y = 0  # Rotation around y-axis
        self.rotation_z = 0  # Rotation around z-axis
        self.color_hue = random.random()  # Initial hue for color cycling

    def update_position(self):
        # Update position and bounce off screen edges
        self.x += self.dx
        self.y += self.dy
        if self.x - self.size < 0 or self.x + self.size > screen_width:
            self.dx = -self.dx  # Reverse x-direction
        if self.y - self.size < 0 or self.y + self.size > screen_height:
            self.dy = -self.dy  # Reverse y-direction

    def update_rotation(self):
        # Update the rotation angles for continuous spinning
        self.rotation_x += rotation_speed  # Rotate shape around x-axis
        self.rotation_y += rotation_speed  # Rotate shape around y-axis
        self.rotation_z += rotation_speed  # Rotate shape around z-axis

        # Update color hue for gradient effect
        self.color_hue = (self.color_hue + 0.01) % 1.0

    def get_gradient_color(self, hue_offset=0):
        hue = (self.color_hue + hue_offset) % 1.0
        rgb = colorsys.hsv_to_rgb(hue, 1, 1)
        return int(rgb[2] * 255) << 16 | int(rgb[1] * 255) << 8 | int(rgb[0] * 255)  # RGB color

    def project_vertices(self):
        # 3D cube vertices relative to the center of the shape
        half_size = self.size / 2
        vertices = [
            (-half_size, -half_size, -half_size),
            (half_size, -half_size, -half_size),
            (half_size, half_size, -half_size),
            (-half_size, half_size, -half_size),
            (-half_size, -half_size, half_size),
            (half_size, -half_size, half_size),
            (half_size, half_size, half_size),
            (-half_size, half_size, half_size),
        ]

        # Rotation matrices for x, y, z rotations
        cos_rx, sin_rx = math.cos(self.rotation_x), math.sin(self.rotation_x)
        cos_ry, sin_ry = math.cos(self.rotation_y), math.sin(self.rotation_y)
        cos_rz, sin_rz = math.cos(self.rotation_z), math.sin(self.rotation_z)

        # Project the 3D vertices to 2D screen coordinates
        projected_points = []
        for vx, vy, vz in vertices:
            # Apply x rotation
            vy, vz = vy * cos_rx - vz * sin_rx, vy * sin_rx + vz * cos_rx
            # Apply y rotation
            vx, vz = vx * cos_ry + vz * sin_ry, vz * cos_ry - vx * sin_ry
            # Apply z rotation
            vx, vy = vx * cos_rz - vy * sin_rz, vx * sin_rz + vy * cos_rz

            # Perspective projection
            distance = 500  # Distance to the viewer
            scale = distance / (distance - (self.z + vz))
            screen_x = int(self.x + vx * scale)
            screen_y = int(self.y + vy * scale)
            projected_points.append(POINT(screen_x, screen_y))

        return projected_points

    def draw(self, hdc):
        # Get the 2D projection of vertices and draw the edges of the cube with gradient colors
        points = self.project_vertices()
        for i in range(4):
            color = self.get_gradient_color(hue_offset=i / 4)  # Gradual hue shift for each line
            brush = gdi32.CreateSolidBrush(color)
            gdi32.SelectObject(hdc, brush)
            
            for offset in range(-1, 2):  # Thicker lines with slight offsets
                gdi32.MoveToEx(hdc, points[i].x + offset, points[i].y + offset, None)
                gdi32.LineTo(hdc, points[(i + 1) % 4].x + offset, points[(i + 1) % 4].y + offset)
                gdi32.LineTo(hdc, points[i + 4].x + offset, points[i + 4].y + offset)
                gdi32.LineTo(hdc, points[(i + 1) % 4 + 4].x + offset, points[(i + 1) % 4 + 4].y + offset)
                gdi32.LineTo(hdc, points[i].x + offset, points[i].y + offset)

            # Clean up the brush after each line to apply the next gradient color
            gdi32.DeleteObject(brush)

        # Draw lines connecting the two "faces" of the cube
        for i in range(4):
            color = self.get_gradient_color(hue_offset=(i + 4) / 8)  # Further gradient for connecting lines
            brush = gdi32.CreateSolidBrush(color)
            gdi32.SelectObject(hdc, brush)
            gdi32.MoveToEx(hdc, points[i].x, points[i].y, None)
            gdi32.LineTo(hdc, points[i + 4].x, points[i + 4].y)
            gdi32.DeleteObject(brush)

        # Draw semi-transparent circles on each corner to create trailing effects
        for point in points:
            trail_color = self.get_gradient_color() | 0xA0000000  # Add alpha transparency
            trail_brush = gdi32.CreateSolidBrush(trail_color)
            gdi32.SelectObject(hdc, trail_brush)
            gdi32.Ellipse(hdc, point.x - 8, point.y - 8, point.x + 8, point.y + 8)
            gdi32.DeleteObject(trail_brush)

# Initialize the main shape in the center and four smaller shapes in each corner
main_shape = Shape3D(center_x, center_y, 0, 300, 8, 8)  # Center shape
corner_shapes = [
    Shape3D(150, 150, 0, 100, random.choice([-6, 6]), random.choice([-6, 6])),  # Top-left
    Shape3D(screen_width - 150, 150, 0, 100, random.choice([-6, 6]), random.choice([-6, 6])),  # Top-right
    Shape3D(150, screen_height - 150, 0, 100, random.choice([-6, 6]), random.choice([-6, 6])),  # Bottom-left
    Shape3D(screen_width - 150, screen_height - 150, 0, 100, random.choice([-6, 6]), random.choice([-6, 6])),  # Bottom-right
]

# Main loop for effect
try:
    while True:
        # Draw the screenshot background with alpha blending
        msimg32.AlphaBlend(hdc_screen, 0, 0, screen_width, screen_height, hdc_mem, 0, 0, screen_width, screen_height, DWORD(0x00FF0000))

        # Update and draw the main shape in the center
        main_shape.update_position()
        main_shape.update_rotation()
        main_shape.draw(hdc_screen)

        # Update and draw each corner shape
        for shape in corner_shapes:
            shape.update_position()
            shape.update_rotation()
            shape.draw(hdc_screen)

        # Minimal delay for very high FPS
        time.sleep(0.001)

except KeyboardInterrupt:
    # Release device contexts on exit
    user32.ReleaseDC(hdesktop, hdc_screen)
    gdi32.DeleteObject(hbm_mem)
    gdi32.DeleteDC(hdc_mem)
    print("3D geometric effect with color gradients stopped.")
