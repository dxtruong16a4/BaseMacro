import sys
import os
from PyQt6 import QtWidgets
from app.mainwindow import MainWindow

if __name__ == "__main__":    
    app = QtWidgets.QApplication(sys.argv)
    main_win = MainWindow()
    app.aboutToQuit.connect(main_win.stop_threads)
    main_win.show()
    sys.exit(app.exec())