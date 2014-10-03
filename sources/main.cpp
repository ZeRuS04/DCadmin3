#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include "AdminBackend.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    AdminBackend admin;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("admin", &admin);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
