import json
from PyQt6 import QtWidgets, QtCore
from src.option import Ui_OptionMenu

class OptionMenu(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.uic_setting = Ui_OptionMenu()
        self.uic_setting.setupUi(self)
        self.setWindowFlag(QtCore.Qt.WindowType.WindowStaysOnTopHint, True)
        self.setFixedSize(320, 240)
        self.load_setting()
        self.uic_setting.btnSave.clicked.connect(self.save_setting)

    def load_setting(self):
        with open("config.json", "r") as f:
            config = json.load(f)
            speed = config.get("speed", "normal")
        if speed == "slow":
            self.uic_setting.rbtnSlow.setChecked(True)
        elif speed == "normal":
            self.uic_setting.rbtnNormal.setChecked(True)
        elif speed == "fast":
            self.uic_setting.rbtnFast.setChecked(True)

    def save_setting(self):
        if self.uic_setting.rbtnSlow.isChecked():
            speed = "slow"
        elif self.uic_setting.rbtnNormal.isChecked():
            speed = "normal"
        elif self.uic_setting.rbtnFast.isChecked():
            speed = "fast"
        else:
            return
        with open("config.json", "w") as f:
            json.dump({"speed": speed}, f, indent=4) 