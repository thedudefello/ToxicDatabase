import ctypes
import time
import random
import string
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

# Create a memory device context compatible with the screen
hdc_mem = gdi32.CreateCompatibleDC(hdc_screen)
hbm_mem = gdi32.CreateCompatibleBitmap(hdc_screen, screen_width, screen_height)
gdi32.SelectObject(hdc_mem, hbm_mem)

# Parameters for text and bouncer
text_count = 500  # More text for extreme chaos
shake_intensity = 50  # Intense shake
bouncer_size = 50  # Size of the bouncer box
bouncer_x, bouncer_y = random.randint(0, screen_width - bouncer_size), random.randint(0, screen_height - bouncer_size)
bouncer_dx, bouncer_dy = 15, 12  # Increased speed of bouncer
hue = 0  # Initial hue for color cycling

# Function to generate random encrypted text
def generate_encrypted_text(length=10):
    return ''.join(random.choices(string.ascii_letters + string.digits + "!@#$%^&*()", k=length))

# Generate random encrypted text pieces and their positions
text_positions = [(random.randint(0, screen_width), random.randint(0, screen_height), generate_encrypted_text()) for _ in range(text_count)]
infected_message = "Zenny Has Infected Your Computer"

# Add multiple instances of the "infected" message in random positions
for _ in range(50):  # Increase the message instances for chaos
    x = random.randint(0, screen_width)
    y = random.randint(0, screen_height)
    text_positions.append((x, y, infected_message))

# Main loop for chaotic effect
try:
    while True:
        # Apply screen shake by offsetting the drawing context
        shake_offset_x = random.randint(-shake_intensity, shake_intensity)
        shake_offset_y = random.randint(-shake_intensity, shake_intensity)

        # Clear the screen with black
        gdi32.PatBlt(hdc_screen, 0, 0, screen_width, screen_height, 0x00FF0062)  # BLACKNESS

        # Draw rapidly changing encrypted text scattered across the screen
        for i, (x, y, text) in enumerate(text_positions):
            # Slightly move each text position to create a glitch effect
            text_x = x + shake_offset_x + random.randint(-5, 5)
            text_y = y + shake_offset_y + random.randint(-5, 5)
            color_text_hue = (hue + i * 0.05) % 1  # Slightly offset hue for each text for rainbow effect
            rgb_text = colorsys.hsv_to_rgb(color_text_hue, 1, 1)
            color_text = (int(rgb_text[2] * 255) << 16) | (int(rgb_text[1] * 255) << 8) | int(rgb_text[0] * 255)
            gdi32.SetTextColor(hdc_screen, color_text)
            gdi32.TextOutA(hdc_screen, text_x, text_y, text.encode('utf-8'), len(text))

        # Update the hue for rainbow colors for the bouncer
        hue += 0.1  # Faster color cycling
        if hue > 1:
            hue = 0
        rgb = colorsys.hsv_to_rgb(hue, 1, 1)
        color = (int(rgb[2] * 255) << 16) | (int(rgb[1] * 255) << 8) | int(rgb[0] * 255)

        # Draw the rainbow bouncer with collisions and chaotic movement
        gdi32.SetBkColor(hdc_screen, color)
        gdi32.ExtFloodFill(hdc_screen, bouncer_x, bouncer_y, color, 1)

        # Update bouncer position with collision detection and random jumps
        bouncer_x += bouncer_dx + random.randint(-5, 5)  # Randomize movement
        bouncer_y += bouncer_dy + random.randint(-5, 5)

        # Check for screen bounds and reverse direction on collision
        if bouncer_x <= 0 or bouncer_x + bouncer_size >= screen_width:
            bouncer_dx = -bouncer_dx
        if bouncer_y <= 0 or bouncer_y + bouncer_size >= screen_height:
            bouncer_dy = -bouncer_dy

        # Blit the updated memory context to the screen
        gdi32.BitBlt(hdc_screen, 0, 0, screen_width, screen_height, hdc_mem, 0, 0, 0x00CC0020)  # SRCCOPY

        # Short delay for high-speed frame update
        time.sleep(0.005)  # Faster frame rate for more chaos

except KeyboardInterrupt:
    # Release device contexts on exit
    user32.ReleaseDC(hdesktop, hdc_screen)
    gdi32.DeleteObject(hbm_mem)
    gdi32.DeleteDC(hdc_mem)
    print("Effect stopped.")
