from PyQt6 import QtCore
from utils.utils import check_connection
from app.taskmanager import Task

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

class WorkerSignals(QtCore.QObject):
    """Tín hiệu để giao tiếp giữa luồng và main thread."""
    progress = QtCore.pyqtSignal(str)

class TaskWorker(QtCore.QRunnable):
    """Worker để xử lý từng task từ hàng đợi."""
    def __init__(self, queue, signals):
        super().__init__()
        self.queue = queue
        self.signals = signals

    def run(self):
        while not self.queue.empty():
            task_data = self.queue.get()
            if isinstance(task_data, Task):
                task = task_data
            else:
                task = Task(name=task_data)
            self.signals.progress.emit(f"Processing: {task}")
            task.run()
            self.signals.progress.emit(f"Completed: {task}")
            self.queue.task_done()