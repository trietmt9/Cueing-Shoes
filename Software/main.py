import sys
import cv2
from PyQt6.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton, QLabel, QTextEdit
from PyQt6.QtGui import QImage, QPixmap
from PyQt6.QtCore import QTimer, QThread, pyqtSignal
from PyQt6.QtBluetooth import QBluetoothDeviceDiscoveryAgent, QBluetoothDeviceInfo

class BLEScannerThread(QThread):
    devices_found = pyqtSignal(list)

    def __init__(self, parent=None):
        super().__init__(parent)
        self.agent = QBluetoothDeviceDiscoveryAgent()

    def run(self):
        devices = self.agent.discoveredDevices()
        devices_info = [(device.name(), device.address().toString()) for device in devices]
        self.devices_found.emit(devices_info)

class Camera:
    def __init__(self):
        self.cap = None

    def start(self):
        self.cap = cv2.VideoCapture(0)

    def get_frame(self):
        if self.cap:
            ret, frame = self.cap.read()
            if ret:
                return frame
        return None

    def release(self):
        if self.cap:
            self.cap.release()

class App(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

        # BLE Components
        self.ble_scanner_thread = BLEScannerThread()
        self.ble_scanner_thread.devices_found.connect(self.update_ble_devices_text)

        # Camera Components
        self.camera = Camera()
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update_video)

    def initUI(self):
        self.setWindowTitle('BLE Scanner and Camera App with PyQt6 and OpenCV')
        self.setGeometry(100, 100, 800, 600)

        self.layout = QVBoxLayout()

        # BLE Components
        self.ble_label = QLabel('BLE Devices:')
        self.layout.addWidget(self.ble_label)

        self.scan_button = QPushButton('Scan BLE')
        self.scan_button.clicked.connect(self.scan_ble)
        self.layout.addWidget(self.scan_button)

        self.ble_devices = QTextEdit()
        self.ble_devices.setReadOnly(True)
        self.layout.addWidget(self.ble_devices)

        # Camera Components
        self.open_camera_button = QPushButton('Open Camera')
        self.open_camera_button.clicked.connect(self.open_camera)
        self.layout.addWidget(self.open_camera_button)

        self.video_label = QLabel()
        self.layout.addWidget(self.video_label)

        self.setLayout(self.layout)

    def scan_ble(self):
        self.scan_button.setEnabled(False)
        self.ble_devices.clear()
        self.ble_scanner_thread.agent.start()
        self.ble_scanner_thread.start()

    def update_ble_devices_text(self, devices):
        device_text = "\n".join([f"{name} ({addr})" for name, addr in devices])
        self.ble_devices.setPlainText(device_text)
        self.scan_button.setEnabled(True)

    def open_camera(self):
        self.camera.start()
        self.timer.start(30)  # Update the camera feed every 30 ms

    def update_video(self):
        frame = self.camera.get_frame()
        if frame is not None:
            frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            height, width, channel = frame.shape
            bytesPerLine = channel * width
            qImg = QImage(frame.data, width, height, bytesPerLine, QImage.Format.Format_RGB888)
            self.video_label.setPixmap(QPixmap.fromImage(qImg))

    def closeEvent(self, event):
        self.timer.stop()
        self.camera.release()
        self.ble_scanner_thread.agent.stop()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = App()
    ex.show()
    sys.exit(app.exec())
