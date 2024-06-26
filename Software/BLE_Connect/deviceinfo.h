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
    void setDevice(const QBluetoothDeviceInfo &device);
    QString getName() const { return m_device.name(); }
    QString getAddress() const;
    QBluetoothDeviceInfo addDevice() const;
private:
    QBluetoothDeviceInfo m_device;
};

#endif // DEVICEINFO_H
