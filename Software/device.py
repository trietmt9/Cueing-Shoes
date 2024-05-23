from PySide6.QtCore import QPoint, Qt, Slot
from PySide6.QtGui  import QColor 
from PySide6.QtBluetooth import QBluetooth, QBluetoothDeviceInfo, QBluetoothDeviceDiscoveryAgent, QLowEnergyController

class DeviceManeage(QBluetooth):
    def __init__(self):
        super(DeviceManeage, self).__init__()
        m_deviceDiscoveryAgent = QBluetoothDeviceDiscoveryAgent(self)
        m_deviceDiscoveryAgent.setLowEnergyDiscoveryTimeout(15000)
        m_deviceDiscoveryAgent.deviceDiscovered.connect(self.addDevice)
        m_deviceDiscoveryAgent.errorOccured.connect(self.errorOccured)
        m_deviceDiscoveryAgent.finished.connect(self.Scanfinished)
        m_deviceDiscoveryAgent.start(QBluetoothDeviceDiscoveryAgent.DiscoveryMethod.LowEnergyMethod)
    def addDevice(self, device):

    # If device is LowEnergy-device, add it to the list
        if device.coreConfigurations():QBluetoothDeviceInfo.LowEnergyCoreConfiguration
            devInfo = DeviceInfo(device)
            it = std::find_if(m_devices.begin(), m_devices.end(),
                                    [devInfo](DeviceInfo dev) {
                                        return devInfo.getAddress() == dev.getAddress()
                                    })
            if it == m_devices.end():
                m_devices.append(devInfo)
            else:
                oldDev = it
                it = devInfo
                del oldDev

            setInfo(tr("Low Energy device found. Scanning more..."))
            setIcon(IconProgress)
    #...