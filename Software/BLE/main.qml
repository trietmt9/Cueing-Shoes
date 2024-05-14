import QtQuick 2.15
import QtQuick.Controls 2.15
import QtMultimedia
import QtMultimedia 5.15

ApplicationWindow {
    visible: true
    width: 1920
    height: 1080
    title: "Bluetooth Scanner"

    Button {
        text: "Scan for Bluetooth Devices"
        anchors.right: parent
        onClicked: bluetoothManager.startScan()
    }
    Item {
        width: 640
        height: 480
        CaptureSession {
            camera: Camera {
                id: camera

                focusMode: Camera.FocusModeAutoNear
                customFocusPoint: Qt.point(
                                      0.2,
                                      0.2) // Focus relative to top-left corner
            }
            videoOutput: videoOutput
        }

        VideoOutput {
            id: videoOutput
            anchors.fill: parent
            Component.onCompleted: {
                camera.start()
            }
        }
    }
}
