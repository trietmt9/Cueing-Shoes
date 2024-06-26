#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowTitle(tr("Blutooth Window"));
    ui->setupUi(this);
    m_deviceDiscoveryAgent ->setLowEnergyDiscoveryTimeout(15000);
    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &MainWindow::AddDevice);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ConnectButton_clicked()
{

}


void MainWindow::on_ScanButton_clicked()
{

}

void MainWindow::AddDevice(const QBluetoothDeviceInfo &device)
{



}
