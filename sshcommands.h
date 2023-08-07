#ifndef SSHCOMMANDS_H
#define SSHCOMMANDS_H

#include <QString>
#include "libssh2.h"

class SSHCommands
{
public:
    SSHCommands(QString serverAddress, QString serverPort,
                QString userName, QString userPassword);

    int execRemoteCommand(QString command);
    int execRemoteCommand2(QString command);

signals:

private:
    int waitsocket(libssh2_socket_t socket_fd, LIBSSH2_SESSION *session);

    QString m_serverAddress;
    QString m_userName;
    QString m_userPassword;
    int m_serverPort;
};

#endif // SSHCOMMANDS_H
