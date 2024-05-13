#include <blemaneger.h>
#include <QBluetoothDeviceInfo>

BluetoothManager::BluetoothManager(QObject *parent)
    : QObject(parent), m_deviceDiscoveryAgent(new QBluetoothDeviceDiscoveryAgent(this))
{
    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, [this](const QBluetoothDeviceInfo &info) {
                m_devices.append(info.name() + " (" + info.address().toString() + ")");
                emit devicesChanged();
            });

    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished,
            m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deleteLater);
}

BluetoothManager::~BluetoothManager() {}

QStringList BluetoothManager::devices() const {
    return m_devices;
}

void BluetoothManager::startScan() {
    m_devices.clear();
    emit devicesChanged();
    m_deviceDiscoveryAgent->start();
}
