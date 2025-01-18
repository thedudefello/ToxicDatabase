import subprocess

with open('C:\\Users\\hp\\Desktop\\1234.txt', 'r') as file:
    passwords = file.readlines()
    for password in passwords:
        subprocess.run(['C:\\Program Files\\WinRAR\\WinRAR.exe', 'x', '-p' + password.strip(), 'C:\\Users\\hp\\Desktop\\cd.rar'])
