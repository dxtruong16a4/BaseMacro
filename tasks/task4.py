import time
import pyautogui
def printText():
    for i in range(11, 20):
        print("Task 4 - " + str(i))
    time.sleep(2)
    pyautogui.alert("Task 4 is finished.")

if __name__ == "__main__":
    printText()