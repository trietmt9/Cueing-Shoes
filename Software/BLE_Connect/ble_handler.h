#ifndef BLE_HANDLER_H
#define BLE_HANDLER_H

#include <QBluetoothDeviceInfo>
#include <QBluetoothUuid>
#include <QLowEnergyService>
#include <QLowEnergyController>
#include <deviceinfo.h>
#include <QMetaEnum>
class BLE_Handler : public QObject
{
    Q_OBJECT
public:
    // Bluetooth State
    enum BluetoothState
    {
        IDLE = 0,
        SCANNING,
        SCAN_FINISHED,
        CONNECTING,
        CONNECTED,
        DISCONNECTED,
        SERVICE_FOUND,
        ACQUIRE_DATA,
        ERROR
    };
    Q_ENUM(BluetoothState)

    BLE_Handler();
    ~BLE_Handler();

    void BLE_Write(QByteArray data);
    void setState(BLE_Handler::BluetoothState newState);
    BLE_Handler::BluetoothState getState() const;
    void getDeviceList(QList<QString> &ListDevices);
    void Device_Disconnect();
    void setService_Name(const QString &NewService_Name);
};

#endif // BLE_HANDLER_H
