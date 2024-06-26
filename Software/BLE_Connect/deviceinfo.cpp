#include "deviceinfo.h"
DeviceInfo::DeviceInfo(const QBluetoothDeviceInfo &device):
    QObject(), m_device(device)
{
}

QBluetoothDeviceInfo DeviceInfo::addDevice() const
{
    return m_device;
}

