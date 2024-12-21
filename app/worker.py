from PyQt6 import QtCore
import queue
from utils.utils import check_connection
from app.taskmanager import Task

class ConnectionWorker(QtCore.QObject):
    """Worker để kiểm tra kết nối mạng."""
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
    """Class chứa các signal của worker."""
    progress = QtCore.pyqtSignal(str)
    task_completed = QtCore.pyqtSignal()

class TaskWorker(QtCore.QRunnable):
    """Worker để chạy các task."""
    def __init__(self, queue: queue.Queue, signals: WorkerSignals):
        super().__init__()
        self.queue = queue
        self.signals = signals
        self.running = True

    def stop(self):
        """Dừng worker"""
        self.running = False

    def run(self):
        while self.running and not self.queue.empty():
            task = self.queue.get()
            if isinstance(task, Task):
                self.signals.progress.emit(f"Processing: {task.name}")
                task.run()
                if task.is_completed():
                    self.signals.progress.emit(f"Completed: {task.name}")
            self.queue.task_done()
        if self.queue.empty():
            self.signals.task_completed.emit()

# class UpdateLabelWorker(QtCore.QObject):
#     """Worker để cập nhật label."""
#     progress = QtCore.pyqtSignal(str)

#     def run(self, log):
#         self.progress.emit(log)