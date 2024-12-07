from PyQt6 import QtCore
from utils.utils import check_connection

class ConnectionWorker(QtCore.QObject):
    connection_status = QtCore.pyqtSignal(bool)
    def __init__(self):
        super().__init__()
        self._running = True

    def run(self):
        while self._running:
            if check_connection():
                self.connection_status.emit(True)
            else:
                self.connection_status.emit(False)
            QtCore.QThread.msleep(5000)

    def stop(self):
        self._running = False