#ifndef BLUETOOTHMANAGER_H
#define BLUETOOTHMANAGER_H

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QStringList>

class BluetoothManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList devices READ devices NOTIFY devicesChanged)

public:
    explicit BluetoothManager(QObject *parent = nullptr);
    ~BluetoothManager();

    QStringList devices() const;

public
        slots:
    void startScan();

    signals:
    void devicesChanged();

private:
    QBluetoothDeviceDiscoveryAgent *m_deviceDiscoveryAgent;
    QStringList m_devices;
};

#endif // BLUETOOTHMANAGER_H
