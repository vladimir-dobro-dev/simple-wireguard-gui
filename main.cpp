#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStandardPaths>
#include <QDir>

#include "serverlistmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    app.setApplicationName("Simple wireguard");

    QStringList paths = QStandardPaths::standardLocations(QStandardPaths::AppConfigLocation);
    QDir configPath(paths.at(0) + "/servers");
    if (!configPath.exists()) {
        configPath.mkpath(configPath.path());
    }

    qmlRegisterType<ServerListModel>("models", 1, 0, "ServerListModel");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/simple-wireguard-gui/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
