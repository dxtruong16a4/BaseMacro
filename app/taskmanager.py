import subprocess
from PyQt6.QtCore import pyqtSignal, QObject

class Task(QObject):
    task_completed = pyqtSignal(str)
    task_notified = pyqtSignal(str)
    _number_of_tasks = 0

    def __init__(self, name, id, elapsed_time=float("inf")):
        super().__init__()
        self.name = name
        self.id = id
        self.progress = 0
        self.is_interrupted = False
        self.completed = False
        self.total_time = 0
        self.elapsed_time = elapsed_time
        self.process = None
        Task._number_of_tasks += 1

    def set_elapsed_time(self, elapsed_time):
        self.elapsed_time = elapsed_time

    def is_completed(self):
        return self.completed

    def update_progress(self, progress):
        if not self.completed and not self.is_interrupted:
            self.progress = progress
            if self.progress >= 100:
                self.mark_as_completed()

    def mark_as_completed(self):
        self.completed = True
        self.progress = 100
        self.task_completed.emit(self.name)

    def interrupt_task(self):
        if not self.completed:
            self.is_interrupted = True

    def resume_task(self):
        if self.is_interrupted:
            self.is_interrupted = False

    def add_time(self, time):
        if not self.completed:
            self.total_time += time
            if self.total_time >= self.elapsed_time:
                self.mark_as_completed()

    def force_complete(self):
        self.mark_as_completed()

    def reset_progress(self):
        if not self.completed:
            self.progress = 0

    def run(self):
        """Run command line task."""
        if not hasattr(self, "file_path") or not self.file_path:
            self.task_notified.emit(f"Task '{self.name}' không có đường dẫn file để chạy.")
            return
        try:
            self.process = subprocess.Popen(
                ["python", self.file_path],
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True
            )
            stdout, stderr = self.process.communicate()
            if self.process.returncode == 0:
                self.task_notified.emit(f"Task '{self.name}' chạy thành công!")
                self.mark_as_completed()
            else:
                self.task_notified.emit(f"Task '{self.name}' gặp lỗi khi chạy:\n{stderr}")
                self.task_completed.emit(f"Error: {stderr}")

        except Exception as e:
            self.task_notified.emit(f"Task '{self.name}' gặp lỗi khi chạy: {str(e)}")
            self.task_completed.emit(f"Error: {str(e)}")

    def stop(self):
        """Stop command line task."""
        if self.process and self.process.poll() is None:
            self.task_notified.emit(f"Attempting to stop task '{self.name}'...")
            try:
                self.process.terminate()
                self.process.wait(timeout=5)
            except subprocess.TimeoutExpired:
                self.process.kill()
                self.task_notified.emit(f"Task '{self.name}' bị buộc dừng.")
            finally:
                self.task_notified.emit(f"Task '{self.name}' đã dừng.")
                self.task_completed.emit(f"Task '{self.name}' was stopped.")

    @classmethod
    def get_number_of_tasks(cls):
        return cls._number_of_tasks

    def __str__(self):
        return self.name

    def __eq__(self, other):
        if isinstance(other, Task):
            return (self.name == other.name and
                    self.progress == other.progress and self.completed == other.completed)
        return False