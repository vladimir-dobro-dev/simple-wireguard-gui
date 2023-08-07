#include <QStandardPaths>
#include <QDir>
#include <QSettings>

#include "serverlistmodel.h"
#include "sshcommands.h"


ServerListModel::ServerListModel(QObject *parent):
    QStandardItemModel(parent)
{
    QFileInfoList dirList = serverDirList();
    for (int i = 0; i < dirList.size(); ++i) {
        QFileInfo dir = dirList.at(i);

        QString serverIndex = dir.baseName();
        QStandardItem *itemServerIndex = new QStandardItem(serverIndex);
        setItem(i, 1, itemServerIndex);

        QSettings serverConfig(dir.absoluteFilePath() + "/serverConfig.ini", QSettings::IniFormat);
        QString serverName = serverConfig.value("serverName").toString();
        QStandardItem *itemServerName = new QStandardItem(serverName);
        setItem(i, 0, itemServerName);
    }
}


void ServerListModel::addServer(const QString &serverAddress, const QString &serverPort,
                                const QString &userName, const QString &userPassword,
                                const QString &serverName)
{
    QFileInfoList dirList = serverDirList();
    int newIndex = 0;
    if (dirList.empty()) {
        newIndex = 1;
    }
    else {
        QFileInfo lastDir = dirList.last();
        bool ok;
        int lastIndex = lastDir.fileName().toInt(&ok);
        if (ok) {
            newIndex = lastIndex + 1;
        }
    }

    QStringList paths = QStandardPaths::standardLocations(QStandardPaths::AppConfigLocation);
    QString newServerPath = paths.at(0) + "/servers/" + QString::number(newIndex);
    QDir configPath;
    configPath.mkdir(newServerPath);

    QSettings serverConfig(newServerPath + "/serverConfig.ini", QSettings::IniFormat);
    qDebug() << newServerPath;
    serverConfig.setValue("serverAddress", serverAddress);
    serverConfig.setValue("serverPort", serverPort);
    serverConfig.setValue("userName", userName);
    serverConfig.setValue("userPassword", userPassword);
    serverConfig.setValue("serverName", serverName);

    SSHCommands sshCommands(serverAddress, serverPort, userName, userPassword);
    sshCommands.execRemoteCommand("touch test123.txt");
}


QFileInfoList ServerListModel::serverDirList()
{
    QStringList paths = QStandardPaths::standardLocations(QStandardPaths::AppConfigLocation);
    QDir configPath(paths.at(0) + "/servers");
    configPath.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    configPath.setSorting(QDir::Name);

    return configPath.entryInfoList();
}
