#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "sshcommands.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<SSHCommands>("sshcommands", 1, 0, "SSHCommands");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/simple-wireguard-gui/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
