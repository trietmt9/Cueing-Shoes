import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Bluetooth Scanner"

    Button {
        text: "Scan for Bluetooth Devices"
        anchors.centerIn: parent
        onClicked: bluetoothManager.startScan()
    }

    ListView {
        id: deviceList
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width
        model: bluetoothManager.devices
        delegate: Text {
            text: modelData
        }
    }
}
