#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "blemaneger.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    BluetoothManager bluetoothManager;

    engine.rootContext()->setContextProperty("bluetoothManager", &bluetoothManager);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
