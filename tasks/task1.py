import time
import pyautogui
def printText():
    for i in range(1, 10):
        print("Task 1 - " + str(i))
    time.sleep(2)
    pyautogui.alert("Task 1 is finished.")

if __name__ == "__main__":
    printText()