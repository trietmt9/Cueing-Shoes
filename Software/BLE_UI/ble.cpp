#include "ble.h"

BLE::BLE() {}

void DeviceInfo::addDevice(const QBluetoothDeviceInfo &info)
{
    if (info.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) {
        auto devInfo = new DeviceInfo(info);
        auto it = std::find_if(devices.begin(), devices.end(),
                               [devInfo](DeviceInfo *dev) {
                                   return devInfo->getAddress() == dev->getAddress();
                               });
        if (it == devices.end()) {
            devices.append(devInfo);
        } else {
            auto oldDev = *it;
            *it = devInfo;
            delete oldDev;
        }
        emit devicesUpdated();
    }
}
