import threading
import pyautogui
import webbrowser
import pygetwindow
import time
import winreg as reg
import pickle

# Hàm lưu trạng thái
def save_state(state, filename="state.pkl"):
    with open(filename, "wb") as file:
        pickle.dump(state, file)

# Hàm khôi phục trạng thái
def load_state(filename="state.pkl"):
    try:
        with open(filename, "rb") as file:
            state = pickle.load(file)
        return state
    except FileNotFoundError:
        return None

# Ví dụ trạng thái
state = load_state() or {"step": 0}

try:
    if state["step"] == 0:
        # Bước 1
        pyautogui.moveTo(100, 100)
        state["step"] = 1
        save_state(state)

    if state["step"] == 1:
        # Bước 2
        pyautogui.click()
        state["step"] = 2
        save_state(state)

    # Các bước khác...

except Exception as e:
    print(f"Đã xảy ra lỗi: {e}")
    save_state(state)
