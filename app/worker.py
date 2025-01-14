from PyQt6 import QtCore
import queue
from utils.utils import check_connection
from app.taskmanager import Task
from app.macro import Macro

class ConnectionWorker(QtCore.QObject):
    """Connection worker."""
    connection_status = QtCore.pyqtSignal(bool)

    def __init__(self):
        super().__init__()
        self._running = True
        self._mutex = QtCore.QMutex()
        self._wait_condition = QtCore.QWaitCondition()
        self._last_status = None

    def run(self):
        while self._running:
            self._mutex.lock()
            current_status = check_connection()
            if current_status != self._last_status:
                self.connection_status.emit(current_status)
                self._last_status = current_status
            self._wait_condition.wait(self._mutex, 5000)
            self._mutex.unlock()

    def stop(self):
        self._mutex.lock()
        self._running = False
        self._wait_condition.wakeAll()
        self._mutex.unlock()

class WorkerSignals(QtCore.QObject):
    """Signals of worker."""
    progress = QtCore.pyqtSignal(str)
    task_completed = QtCore.pyqtSignal()

class TaskWorker(QtCore.QRunnable):
    """Task worker."""
    def __init__(self, queue: queue.Queue, signals: WorkerSignals):
        super().__init__()
        self.queue = queue
        self.signals = signals
        self.running = True

    def stop(self):
        self.running = False

    def run(self):
        while self.running and not self.queue.empty():
            task = self.queue.get()
            if isinstance(task, Task):
                self.signals.progress.emit(task.name)
                task.run()
                if task.is_completed():
                    self.signals.progress.emit(task.name)
            self.queue.task_done()
        if self.queue.empty():
            self.signals.task_completed.emit()

class LongTask(Macro):
    """Long task."""