#ifndef SSHCOMMANDS_H
#define SSHCOMMANDS_H

#include <QObject>

#include <libssh/libssh.h>

class SSHCommands : public QObject
{
    Q_OBJECT
public:
    explicit SSHCommands(QObject *parent = nullptr);
    SSHCommands(QString serverAddress, QString userName,
                QString userPassword, QString sshPort,
                QObject *parent = nullptr);

    Q_INVOKABLE void execRemoteCommand(QString command);

signals:

private:
    QString m_serverAddress;
    QString m_userName;
    QString m_userPassword;
    int m_sshPort;
};

#endif // SSHCOMMANDS_H
