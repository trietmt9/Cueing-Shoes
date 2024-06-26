#ifndef BLE_HANDLER_H
#define BLE_HANDLER_H
#include <QBluetoothDeviceDiscoveryAgent>
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

private slots:
    /* Slots for scanning BLE devices */
    void addDevice(const QBluetoothDeviceInfo &device);
    void scanFinish();
    void scanError(QBluetoothDeviceDiscoveryAgent::Error newError);

    /* Slots for control the BLE */
    void serviceDiscovered(const QBluetoothUuid &gatt);
    void serviceScanFinished();
    void controlError(QLowEnergyController::Error);
    void deviceConnect();
    void deviceDisconnect();
    void errorOccurred(QLowEnergyController::Error newError);

    /* Slots for BLE services */
    void serviceStateChanged(QLowEnergyService::ServiceState);
    void updateData(const QLowEnergyCharacteristic &cha, const QByteArray &value);
    void confirmedDescriptionWrite(const QLowEnergyDescriptor &des, const QByteArray &value);
    void searchCharacteristic();
public slots:

    /* Slots for user */
    void startScan();
    void ConnectToDevice(int i);
signals:

    /* Signals for user */
    void statusChange(const QString &status);
    void newData(QByteArray data);
    void changedState(BLE_Handler::BluetoothState newState);

private:
    QLowEnergyController *m_control;
    QString m_service_name;
    QBluetoothUuid current_gatt;

    QBluetoothDeviceDiscoveryAgent *m_device_discovery_agent;
    DeviceInfo *current_device;
    QVector<qint16> m_Measurements;

    QLowEnergyService *m_service;
    QLowEnergyDescriptor m_notificationDesTx;
    QLowEnergyDescriptor m_notificationDesRx;
    QLowEnergyService *m_UARTService;
    bool m_foundUARTService;
    BLE_Handler::BluetoothState m_state;

    QLowEnergyCharacteristic m_readCharacteristic;
    QLowEnergyCharacteristic m_writeCharacteristic;
    QLowEnergyService::WriteMode m_writeMode;

};

#endif // BLE_HANDLER_H
