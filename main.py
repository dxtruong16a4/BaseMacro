import sys
import os
from PyQt6 import QtWidgets
from app.mainwindow import MainWindow

if __name__ == "__main__":
    
    app = QtWidgets.QApplication(sys.argv)
    main_win = MainWindow()
    main_win.show()
    sys.exit(app.exec())