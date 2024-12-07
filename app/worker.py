from PyQt6 import QtCore
from utils.utils import check_connection

class ConnectionWorker(QtCore.QObject):
    connection_status = QtCore.pyqtSignal(bool)

    def __init__(self):
        super().__init__()
        self._running = True
        self._mutex = QtCore.QMutex()
        self._wait_condition = QtCore.QWaitCondition()

    def run(self):
        while self._running:
            self._mutex.lock()
            if check_connection():
                self.connection_status.emit(True)
            else:
                self.connection_status.emit(False)
            self._wait_condition.wait(self._mutex, 5000)
            self._mutex.unlock()

    def stop(self):
        self._mutex.lock()
        self._running = False
        self._wait_condition.wakeAll()
        self._mutex.unlock()

class TaskWorker(QtCore.QThread):
    task_finished = QtCore.pyqtSignal()

    def __init__(self, parent=None):
        super(TaskWorker, self).__init__(parent)
        self.is_running = True

    def run(self):
        while self.is_running:
            pass
        self.task_finished.emit()

    def stop(self):
        self.is_running = False