#ifndef SERVERLISTMODEL_H
#define SERVERLISTMODEL_H

#include <QStandardItemModel>
#include <QObject>
#include <QFileInfoList>

class ServerListModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit ServerListModel(QObject *parent = nullptr);

    Q_INVOKABLE void addServer(const QString &serverAddress, const QString &serverPort,
                               const QString &userName, const QString &userPassword,
                               const QString &serverName);

private:
    QFileInfoList serverDirList();
};

#endif // SERVERLISTMODEL_H
