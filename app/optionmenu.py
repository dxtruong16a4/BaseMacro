import json
from PyQt6 import QtWidgets, QtCore, QtGui
from src.option import Ui_OptionMenu

class OptionMenu(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.uic_setting = Ui_OptionMenu()
        self.uic_setting.setupUi(self)
        self.setWindowFlag(QtCore.Qt.WindowType.WindowStaysOnTopHint, True)
        self.setFixedSize(320, 240)
        self.load_setting()
        self.load_shortcut()
        self.uic_setting.btnSave.clicked.connect(self.save_setting)

    def load_setting(self):
        with open("config.json", "r") as f:
            config = json.load(f)
            speed = config.get("app", {}).get("speed", "normal")
        if speed == "slow":
            self.uic_setting.rbtnSlow.setChecked(True)
        elif speed == "normal":
            self.uic_setting.rbtnNormal.setChecked(True)
        elif speed == "fast":
            self.uic_setting.rbtnFast.setChecked(True)

    def load_shortcut(self):
        with open("config.json", "r") as f:
            config = json.load(f)
            app_config = config.get("app", {})
            add_shortcut = app_config.get("add_shortcut", "Ctrl+O")
            play_shortcut = app_config.get("play_shortcut", "Ctrl+P")
            stop_shortcut = app_config.get("stop_shortcut", "Ctrl+Shift+P")
            setting_shortcut = app_config.get("setting_shortcut", "Ctrl+I")
            self.uic_setting.keyAddShortcut.setKeySequence(QtGui.QKeySequence(add_shortcut))   
            self.uic_setting.keyPlayShortcut.setKeySequence(QtGui.QKeySequence(play_shortcut))
            self.uic_setting.keyStopShortcut.setKeySequence(QtGui.QKeySequence(stop_shortcut))
            self.uic_setting.keySettingShortcut.setKeySequence(QtGui.QKeySequence(setting_shortcut))

    def save_setting(self):
        if self.uic_setting.rbtnSlow.isChecked():
            speed = "slow"
        elif self.uic_setting.rbtnNormal.isChecked():
            speed = "normal"
        elif self.uic_setting.rbtnFast.isChecked():
            speed = "fast"
        else:
            return
        with open("config.json", "r") as f:
            config = json.load(f)
        config["app"]["speed"] = speed
        with open("config.json", "w") as f:
            json.dump(config, f, indent=4)