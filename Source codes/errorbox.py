import ctypes
import random
import time
from threading import Thread
from ctypes import windll, byref, Structure, c_long
from ctypes.wintypes import RECT

# Load necessary Windows library functions
user32 = ctypes.windll.user32
gdi32 = ctypes.windll.gdi32

# Constants for message box types and positioning
MB_OK = 0x0
MB_ICONERROR = 0x10
MB_TOPMOST = 0x40000
SWP_NOSIZE = 0x0001
SWP_SHOWWINDOW = 0x0040

# Error message options for chaotic pop-ups
error_messages = [
    "System32.dll corrupted!",
    "Fatal error: Memory overflow.",
    "Unknown error at 0x004FF21.",
    "Registry access denied.",
    "Critical system failure!",
    "Error: Access Violation.",
    "Exception: STACK_OVERFLOW",
    "Alert: SYSTEM MALFUNCTION",
    "Fatal exception occurred!",
    "ERROR: 0x0000007B",
]

# Get the desktop window and its device context for GDI
hdesktop = user32.GetDesktopWindow()
hdc_screen = user32.GetWindowDC(hdesktop)
rect = RECT()
user32.GetWindowRect(hdesktop, byref(rect))
screen_width = rect.right - rect.left
screen_height = rect.bottom - rect.top

def shake_window(hwnd):
    """Shake the window by randomly changing its position."""
    for _ in range(30):  # Increase the number of shakes for extra chaos
        offset_x = random.randint(-15, 15)
        offset_y = random.randint(-15, 15)
        rect = ctypes.wintypes.RECT()
        user32.GetWindowRect(hwnd, ctypes.byref(rect))
        x = rect.left + offset_x
        y = rect.top + offset_y
        user32.SetWindowPos(hwnd, 0, x, y, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW)
        time.sleep(0.01)  # Faster shake speed

def close_window_after_delay(hwnd, delay=1.0):
    """Close the window after a short delay."""
    time.sleep(delay)
    user32.PostMessageW(hwnd, 0x0010, 0, 0)  # 0x0010 is WM_CLOSE message to close the window

def show_chaotic_message():
    """Create a chaotic message box with random error message."""
    # Randomly select an error message and corrupt it
    message = random.choice(error_messages)
    corrupted_message = "".join(
        random.choice("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()") 
        for _ in message
    )
    
    # Display the chaotic message box with error icon, top-most, random position
    x = random.randint(0, screen_width - 200)
    y = random.randint(0, screen_height - 100)
    hwnd = user32.MessageBoxW(0, corrupted_message, "Error", MB_OK | MB_ICONERROR | MB_TOPMOST)
    
    # Shake and close the window
    Thread(target=shake_window, args=(hwnd,)).start()
    Thread(target=close_window_after_delay, args=(hwnd,)).start()

def spawn_error_windows():
    """Continuously spawn error windows in separate threads for chaotic effect."""
    while True:
        Thread(target=show_chaotic_message, daemon=True).start()
        time.sleep(random.uniform(0.1, 0.5))  # Faster, more chaotic window spawning

def melt_screen():
    """Simulate a screen melting effect by gradually shifting random slices downwards and glitching sections."""
    while True:
        # Capture the current screen into a memory DC
        hdc_mem = gdi32.CreateCompatibleDC(hdc_screen)
        hbm_mem = gdi32.CreateCompatibleBitmap(hdc_screen, screen_width, screen_height)
        gdi32.SelectObject(hdc_mem, hbm_mem)
        gdi32.BitBlt(hdc_mem, 0, 0, screen_width, screen_height, hdc_screen, 0, 0, 0x00CC0020)  # SRCCOPY

        # Randomly select and shift down horizontal strips on the screen
        for _ in range(15):  # Increase number of melting strips
            strip_y = random.randint(0, screen_height - 30)
            strip_height = random.randint(5, 20)
            shift_down = random.randint(10, 40)
            dest_y = strip_y + shift_down
            if dest_y + strip_height > screen_height:
                dest_y = screen_height - strip_height
            gdi32.BitBlt(hdc_screen, 0, dest_y, screen_width, strip_height, hdc_mem, 0, strip_y, 0x00CC0020)  # SRCCOPY

        # Randomly select and shift vertical strips to add glitch effect
        for _ in range(10):
            strip_x = random.randint(0, screen_width - 30)
            strip_width = random.randint(5, 15)
            shift_right = random.randint(10, 20)
            dest_x = strip_x + shift_right
            if dest_x + strip_width > screen_width:
                dest_x = screen_width - strip_width
            gdi32.BitBlt(hdc_screen, dest_x, 0, strip_width, screen_height, hdc_mem, strip_x, 0, 0x00CC0020)  # SRCCOPY

        # Release resources for the memory DC and bitmap
        gdi32.DeleteObject(hbm_mem)
        gdi32.DeleteDC(hdc_mem)

        # Short delay for fast-paced melting and glitch effect
        time.sleep(0.03)

# Start the chaotic error window spawner and screen melting in separate threads
if __name__ == "__main__":
    Thread(target=spawn_error_windows, daemon=True).start()
    Thread(target=melt_screen, daemon=True).start()
    while True:
        time.sleep(1)  # Keep main thread alive
