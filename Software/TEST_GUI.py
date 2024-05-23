from PyQt6 import QtWidgets
from PyQt6.QtWidgets import QApplication, QMainWindow 
import sys 

class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow,self).__init__()
        x_cordinate = 400
        y_cordinate = 80
        height = 1000
        width = 800
        self.setGeometry(x_cordinate, y_cordinate, width, height)
        self.setWindowTitle("BLE connection")
        self.__initUI()
    def __initUI(self):
        self.label = QtWidgets.QLabel(self)
        self.label.setText("Hello World!")
        self.label.move(370, 270)
        self.button1 = QtWidgets.QPushButton(self)
        self.button1.setText("Scanner")
        self.button1.clicked.connect(self.clicked)
        self.button1.move(370,300)
    def clicked(self):
        self.label.setText("You pressed the button")
        self.update()
    def update(self):
        self.label.adjustSize()
def mainWindow():
    
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
    
mainWindow()