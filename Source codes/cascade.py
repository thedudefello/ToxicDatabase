import ctypes
import time
import colorsys
from ctypes import windll, byref
from ctypes.wintypes import RECT

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

# Center coordinates for the tunnel
center_x = screen_width // 2
center_y = screen_height // 2

# Create a memory device context compatible with the screen
hdc_mem = gdi32.CreateCompatibleDC(hdc_screen)
hbm_mem = gdi32.CreateCompatibleBitmap(hdc_screen, screen_width, screen_height)
gdi32.SelectObject(hdc_mem, hbm_mem)

# Tunnel parameters
max_radius = min(screen_width, screen_height) // 2
layer_count = 20  # Number of layers in the tunnel
depth_speed = 0.05  # Speed of tunnel depth effect
hue_offset = 0  # Initial hue for color cycling

# Main loop for tunneling effect
try:
    while True:
        # Clear the screen
        gdi32.PatBlt(hdc_mem, 0, 0, screen_width, screen_height, 0x00FF0062)  # BLACKNESS

        # Draw concentric circles with changing colors and shrinking sizes
        for i in range(layer_count):
            # Calculate radius for the current layer
            radius = max_radius * (1 - (i / layer_count) * depth_speed) % max_radius

            # Calculate color for the current layer
            layer_hue = (hue_offset + i * 0.05) % 1  # Slightly offset hue for each layer
            rgb = colorsys.hsv_to_rgb(layer_hue, 1, 1)
            color = (int(rgb[2] * 255) << 16) | (int(rgb[1] * 255) << 8) | int(rgb[0] * 255)
            gdi32.SetBkColor(hdc_mem, color)
            
            # Create brush and pen for the layer
            brush = gdi32.CreateSolidBrush(color)
            pen = gdi32.CreatePen(0, 1, color)
            gdi32.SelectObject(hdc_mem, brush)
            gdi32.SelectObject(hdc_mem, pen)

            # Draw the circle
            gdi32.Ellipse(hdc_mem, center_x - int(radius), center_y - int(radius),
                          center_x + int(radius), center_y + int(radius))

            # Clean up GDI objects
            gdi32.DeleteObject(brush)
            gdi32.DeleteObject(pen)

        # Blit the updated memory context to the screen
        gdi32.BitBlt(hdc_screen, 0, 0, screen_width, screen_height, hdc_mem, 0, 0, 0x00CC0020)  # SRCCOPY

        # Update hue offset for color cycling
        hue_offset += 0.01
        if hue_offset > 1:
            hue_offset = 0

        # Short delay for high-speed frame update
        time.sleep(0.01)

except KeyboardInterrupt:
    # Release device contexts on exit
    user32.ReleaseDC(hdesktop, hdc_screen)
    gdi32.DeleteObject(hbm_mem)
    gdi32.DeleteDC(hdc_mem)
    print("Tunnel effect stopped.")
