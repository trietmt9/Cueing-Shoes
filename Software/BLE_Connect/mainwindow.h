#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QLineEdit>
#include <QString>
#include <QDebug>
#include <QtWidgets>
#include <qregularexpression.h>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QBluetoothAddress>
#include <QLowEnergyController>
#include <QString>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ConnectButton_clicked();

    void on_ScanButton_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
