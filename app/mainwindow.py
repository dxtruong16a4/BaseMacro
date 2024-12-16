import json
import os
import queue
from PyQt6 import QtWidgets, QtCore, QtGui
from src.auto import Ui_MainWindow
from src.config import root_dir
from .optionmenu import OptionMenu
from .worker import ConnectionWorker, WorkerSignals, TaskWorker, Task

class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        self.uic = Ui_MainWindow()
        self.uic.setupUi(self)
        self.setFixedSize(592, 296)
        # Tasks
        self.tasks = []
        # Actions
        self.uic.actionAdd.triggered.connect(self.add_task)        
        self.uic.actionPlay.triggered.connect(self.play_task_performed)
        self.uic.actionStop.triggered.connect(self.stop_task_performed)
        self.uic.actionSetting.triggered.connect(self.show_setting)
        self.uic.actionPin.triggered.connect(self.pin_window)
        # Button Actions
        self.uic.btnUp.clicked.connect(self.move_up)
        self.uic.btnDown.clicked.connect(self.move_down)
        self.uic.btnRemove.clicked.connect(self.remove_task)
        self.uic.btnClear.clicked.connect(self.clear_all_task)
        # Flag
        self.pinFlag = False
        self.setting_flag = False
        self.isPlaying = False
        # Other Attributes        
        self.speed = json.load(open("config.json"))["app"]["speed"]
        self.old_position = self.pos()
        # Scene Connection
        self.sceneConnect = QtWidgets.QGraphicsScene()
        self.uic.gvConnect.setScene(self.sceneConnect)
        self.connected_pixmap = QtGui.QPixmap("assets/connected.png")
        self.disconnected_pixmap = QtGui.QPixmap("assets/disconnected.png")
        # Scene playing
        self.scenePlaying = QtWidgets.QGraphicsScene()
        self.uic.gvProgress.setScene(self.scenePlaying)
        self.playing_movie = QtGui.QMovie("assets/playing.gif")
        # Queue
        self.queue = queue.Queue()
        # QThreadPool
        self.threadpool = QtCore.QThreadPool()
        # Thread
        self.setup_connection_worker()
        self.start_connection_worker()

    def setup_connection_worker(self):
        self.connection_thread = QtCore.QThread()
        self.connection_worker = ConnectionWorker()
        self.connection_worker.moveToThread(self.connection_thread)
        self.connection_worker.connection_status.connect(self.update_connection_status)
        self.connection_thread.started.connect(self.connection_worker.run)

    def update_connection_status(self, is_connected):
        self.sceneConnect.clear()
        if is_connected:
            self.sceneConnect.addPixmap(self.connected_pixmap)
        else:
            self.sceneConnect.addPixmap(self.disconnected_pixmap)

    def start_connection_worker(self):
        self.connection_thread.start()

    def stop_threads(self):
        self.connection_worker.stop()
        self.connection_thread.quit()
        self.connection_thread.wait()

    def update_loggers(self, log):
        self.uic.textBrowser.setText(self.uic.textBrowser.toPlainText() + log + "\n")

    def add_task(self):
        files, _ = QtWidgets.QFileDialog.getOpenFileNames(self, "Select Python Files", "", "Python Files (*.py)")
        if files:
            for index, file in enumerate(files):
                file_name = os.path.basename(file).replace('.py', '')
                row_position = self.uic.tableTask.rowCount()
                self.uic.tableTask.insertRow(row_position)
                self.uic.tableTask.setItem(row_position, 0, QtWidgets.QTableWidgetItem(file_name))
                self.uic.lblNotification.setText(self.uic.lblNotification.text() + f"{file_name} added. ")
                task = Task(name=file_name, id=index)
                task.file_path = file
                task.task_notified.connect(self.update_loggers)
                task.task_completed.connect(self.remove_task)
                self.queue.put(task)
                self.tasks.append(task)

    def play_task_performed(self):
        self.play_animation()
        self.play_task()

    def play_animation(self):
        self.isPlaying = not self.isPlaying
        if self.isPlaying:            
            self.uic.lblCurrentTask.setText("Playing...")
            self.scenePlaying.clear()
            self.movie_label = QtWidgets.QLabel()
            self.movie_label.setMovie(self.playing_movie)
            self.proxy_widget = QtWidgets.QGraphicsProxyWidget()
            self.proxy_widget.setWidget(self.movie_label)
            self.scenePlaying.addItem(self.proxy_widget)
            self.playing_movie.start()
            self.uic.actionPlay.setIcon(QtGui.QIcon(root_dir + "/assets/pause.png"))
        else:
            self.uic.lblCurrentTask.setText("Paused")
            self.scenePlaying.clear()
            self.playing_movie.setPaused(True)
            self.uic.actionPlay.setIcon(QtGui.QIcon(root_dir + "/assets/play.png"))
    
    def play_task(self):
            if not self.queue.empty():
                signals = WorkerSignals()
                taskworker = TaskWorker(self.queue, signals)
                self.threadpool.start(taskworker)
            else:
                self.uic.lblNotification.setText("Queue is empty. Please add some tasks.")

    def stop_task_performed(self):
        self.stop_animation()
        self.stop_task()

    def stop_animation(self):
        if self.playing_movie.state() in (QtGui.QMovie.MovieState.Running, QtGui.QMovie.MovieState.Paused):
            self.isPlaying = False
            self.uic.lblCurrentTask.setText("")
            self.scenePlaying.clear()
            self.playing_movie.stop()
            self.uic.actionPlay.setIcon(QtGui.QIcon(root_dir + "/assets/play.png"))

    def stop_task(self):
        for task in self.tasks:
            if hasattr(task, 'stop'):
                task.stop()
        self.uic.lblNotification.setText("All tasks stopped.")

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
        self.move(0, QtWidgets.QApplication.primaryScreen().availableGeometry().height() - self.height() - 30)

    def show_setting(self):
        self.stop_task_performed()
        self.setting_flag = True
        self.setting_win = OptionMenu()
        self.setting_win.show()

    def move_up(self):
        current_row = self.uic.tableTask.currentRow()
        if current_row > 0:
            task_current = self.queue.queue[current_row]
            task_above = self.queue.queue[current_row - 1]
            self.queue.queue[current_row - 1], self.queue.queue[current_row] = task_current, task_above
            self.uic.tableTask.insertRow(current_row - 1)
            for column in range(self.uic.tableTask.columnCount()):
                self.uic.tableTask.setItem(current_row - 1, column, self.uic.tableTask.takeItem(current_row + 1, column))
            self.uic.tableTask.removeRow(current_row + 1)
            self.uic.tableTask.setCurrentCell(current_row - 1, 0)

    def move_down(self):
        current_row = self.uic.tableTask.currentRow()
        if current_row < self.uic.tableTask.rowCount() - 1:
            task_current = self.queue.queue[current_row]
            task_below = self.queue.queue[current_row + 1]
            self.queue.queue[current_row], self.queue.queue[current_row + 1] = task_below, task_current
            self.uic.tableTask.insertRow(current_row + 2)
            for column in range(self.uic.tableTask.columnCount()):
                self.uic.tableTask.setItem(current_row + 2, column, self.uic.tableTask.takeItem(current_row, column))
            self.uic.tableTask.removeRow(current_row)
            self.uic.tableTask.setCurrentCell(current_row + 1, 0)

    def remove_task(self, task_name):
        """Xóa task khỏi tableTask khi hoàn thành"""
        for row in range(self.uic.tableTask.rowCount()):
            item = self.uic.tableTask.item(row, 0)
            if item and item.text() == task_name:
                self.uic.tableTask.removeRow(row)
                break
        self.tasks = [task for task in self.tasks if task.name != task_name]
        self.uic.lblNotification.setText(f"Task {task_name} completed and removed.")

    def clear_all_task(self):
        self.queue.queue.clear()
        self.uic.tableTask.setRowCount(0)

    def moveEvent(self, event):
        if self.pinFlag:
            self.lock_position()
    
    def closeEvent(self, event):        
        if self.setting_flag:
            self.setting_win.close()
            self.setting_flag = False
        self.stop_threads()
        event.accept()
