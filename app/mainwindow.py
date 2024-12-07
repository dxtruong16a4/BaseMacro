import json
from PyQt6 import QtWidgets, QtCore, QtGui
from src.auto import Ui_MainWindow
from src.config import root_dir
from .optionmenu import OptionMenu
from .worker import ConnectionWorker

class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        self.uic = Ui_MainWindow()
        self.uic.setupUi(self)
        self.setFixedSize(592, 296)
        # Actions
        self.uic.actionAdd.triggered.connect(self.add_task)        
        self.uic.actionPlay.triggered.connect(self.play)
        self.uic.actionStop.triggered.connect(self.stop)
        self.uic.actionSetting.triggered.connect(self.show_setting)
        self.uic.actionPin.triggered.connect(self.pin_window)
        # Button Actions        
        
        # Flag
        self.pinFlag = False
        self.setting_flag = False
        self.isPlaying = False
        # Other Attributes        
        self.speed = json.load(open("config.json"))["speed"]
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
        # Start Thread
        self.setup_connection_worker()
        self.start_connection_worker()

    def setup_connection_worker(self):
        self.connection_thread = QtCore.QThread()
        self.connection_worker = ConnectionWorker()
        self.connection_worker.moveToThread(self.connection_thread)
        self.connection_worker.connection_status.connect(self.update_connection_status)
        self.connection_thread.started.connect(self.connection_worker.run)
    
    def lock_position(self):
        self.move(0, QtWidgets.QApplication.primaryScreen().availableGeometry().height() - self.height() - 30)

    def start_connection_worker(self):
        self.connection_thread.start()

    def stop_threads(self):
        self.connection_worker.stop()
        self.connection_thread.quit()
        self.connection_thread.wait()
    
    def update_connection_status(self, is_connected):
        self.sceneConnect.clear()
        if is_connected:
            self.sceneConnect.addPixmap(self.connected_pixmap)
        else:
            self.sceneConnect.addPixmap(self.disconnected_pixmap)

    def add_task(self):
        pass

    def play(self):
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
        pass

    def stop(self):
        self.stop_animation()
        self.stop_task()

    def stop_animation(self):
        if self.playing_movie.state() in (QtGui.QMovie.MovieState.Running, QtGui.QMovie.MovieState.Paused):
            self.isPlaying = False
            self.uic.lblCurrentTask.setText("Current Task:")
            self.scenePlaying.clear()
            self.playing_movie.stop()
            self.uic.actionPlay.setIcon(QtGui.QIcon(root_dir + "/assets/play.png"))

    def stop_task(self):
        pass

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

    def show_setting(self):
        self.setting_flag = True
        self.setting_win = OptionMenu()
        self.setting_win.show()

    def moveEvent(self, event):
        if self.pinFlag:
            self.lock_position()
    
    def closeEvent(self, event):        
        if self.setting_flag:
            self.setting_win.close()
            self.setting_flag = False
        self.stop_threads()
        event.accept()
