import pygetwindow
import pyautogui
import time

class Macro:
    def __init__(self):
        pass

    def is_window_open(self, window_name):
        return bool(pygetwindow.getWindowsWithTitle(window_name))

    def open_window(self, window_name):
        if not self.is_window_open(window_name):
            pyautogui.press('win')
            time.sleep(2)
            pyautogui.typewrite(window_name)
            pyautogui.press('enter')
            time.sleep(2)
            if not self.is_window_open(window_name):
                print(f"Failed to open window: {window_name}")

    def close_window(self, window_name):
        windows = pygetwindow.getWindowsWithTitle(window_name)
        if windows:
            window = windows[0]
            window.close()
            time.sleep(2)
            if self.is_window_open(window_name):
                print(f"Failed to close window: {window_name}")
        else:
            print(f"No window found with the title: {window_name}")
