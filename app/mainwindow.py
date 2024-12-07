import json
from PyQt6 import QtWidgets, QtCore, QtGui
from src.auto import Ui_MainWindow
from .optionmenu import OptionMenu
from .worker import ConnectionWorker

class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        self.uic = Ui_MainWindow()
        self.uic.setupUi(self)
        self.uic.actionSetting.triggered.connect(self.show_setting)
        self.uic.actionPin.triggered.connect(self.pin_window)
        self.setFixedSize(592, 296)
        # Other Attributes
        self.pinFlag = False
        self.speed = json.load(open("config.json"))["speed"]
        self.old_position = self.pos()
        # Scene
        self.scene = QtWidgets.QGraphicsScene()
        self.uic.gvConnect.setScene(self.scene)
        self.connected_pixmap = QtGui.QPixmap("assets/connected.png")
        self.disconnected_pixmap = QtGui.QPixmap("assets/disconnected.png")
        # Start Thread
        self.setup_connection_worker()
        self.start_connection_worker()

    def setup_connection_worker(self):
        self.connection_thread = QtCore.QThread()
        self.connection_worker = ConnectionWorker()
        self.connection_worker.moveToThread(self.connection_thread)
        self.connection_worker.connection_status.connect(self.update_connection_status)
        self.connection_thread.started.connect(self.connection_worker.run)

    def start_connection_worker(self):
        self.connection_thread.start()

    def show_setting(self):
        self.setting_win = OptionMenu()
        self.setting_win.setFixedSize(320, 240)
        self.setting_win.show()

    def pin_window(self):
        if self.pinFlag:
            self.setWindowFlag(QtCore.Qt.WindowType.WindowStaysOnTopHint, False)
            self.pinFlag = False
            self.move(self.old_position)
        else:
            self.old_position = self.pos()
            self.setWindowFlag(QtCore.Qt.WindowType.WindowStaysOnTopHint, True)
            self.pinFlag = True
            self.lock_position()
        self.show()

    def lock_position(self):
        self.move(0, QtWidgets.QApplication.primaryScreen().availableGeometry().height() - self.height() - 40)

    def moveEvent(self, event):
        if self.pinFlag:
            self.lock_position()

    def stop_threads(self):
        self.connection_worker.stop()
        self.connection_thread.quit()
        self.connection_thread.wait()
    
    def update_connection_status(self, is_connected):
        self.scene.clear()
        if is_connected:
            self.scene.addPixmap(self.connected_pixmap)
        else:
            self.scene.addPixmap(self.disconnected_pixmap)