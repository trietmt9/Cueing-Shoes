#ifndef DEVICEINFO_H
#define DEVICEINFO_H
#include <QObject>
#include <QString>

#include <QBluetoothDeviceInfo>

class DeviceInfo: public QObject
{
    Q_OBJECT
public:
    DeviceInfo(const QBluetoothDeviceInfo &device);
    QBluetoothDeviceInfo addDevice() const;
private:
    QBluetoothDeviceInfo m_device;
};

#endif // DEVICEINFO_H
