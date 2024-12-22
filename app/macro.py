import pygetwindow
import pyautogui
import time

class Macro:
    def __init__(self):
        pass

    def is_window_open(self, window_name):
        windows = pygetwindow.getWindowsWithTitle(window_name)
        return any(window_name in win.title for win in windows)
    
    def wait_for_condition(self, condition_func, timeout=10):
        start = time.time()
        while time.time() - start < timeout:
            if condition_func():
                return True
            time.sleep(0.5)
        return False

    def open_window(self, window_name):
        if not self.is_window_open(window_name):
            pyautogui.press('win')
            time.sleep(0.5)
            pyautogui.typewrite(window_name)
            pyautogui.press('enter')
            if not self.wait_for_condition(lambda: self.is_window_open(window_name)):
                pyautogui.alert(f"Failed to open window: {window_name}")

    def close_window(self, window_name):
        windows = pygetwindow.getWindowsWithTitle(window_name)
        if windows:
            window = windows[0]
            window.close()
            if not self.wait_for_condition(lambda: not self.is_window_open(window_name)):
                pyautogui.alert(f"Failed to close window: {window_name}")
        else:
            pyautogui.alert(f"No window found with the title: {window_name}")