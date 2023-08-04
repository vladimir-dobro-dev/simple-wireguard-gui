#include <QDebug>

#include "sshcommands.h"

SSHCommands::SSHCommands(QObject *parent)
    : QObject{parent}
{

}


SSHCommands::SSHCommands(QString serverAddress, QString userName, QString userPassword, QString sshPort, QObject *parent)
    : QObject{parent}
{
    m_serverAddress = serverAddress;
    m_userName = userName;
    m_userPassword = userPassword;
    m_sshPort = sshPort.toInt();
}


void SSHCommands::execRemoteCommand(QString command)
{
    m_serverAddress = "localhost";
    m_sshPort = 22;
    m_userName = "ssh-user";
    m_userPassword = "19841981";

    ssh_session session = ssh_new();
    if (session == NULL)
        return;

    ssh_options_set(session, SSH_OPTIONS_HOST, m_serverAddress.toLocal8Bit().constData());
//    ssh_options_set(session, SSH_OPTIONS_PORT, m_sshPort);

    int connection = ssh_connect(session);
    if (connection != SSH_OK) {
        qDebug() << ssh_get_error(session);
        ssh_free(session);
        return;
    }

    int auth = ssh_userauth_password(session,
                                     m_userName.toLocal8Bit().constData(),
                                     m_userPassword.toLocal8Bit().constData());
    if (auth != SSH_AUTH_SUCCESS) {
        qDebug() << ssh_get_error(session);
        ssh_disconnect(session);
        ssh_free(session);
        return;
    }

    ssh_channel channel;
    int rc;

    channel = ssh_channel_new(session);
    if (channel == NULL)
        return;

    rc = ssh_channel_open_session(channel);
    if (rc != SSH_OK) {
        ssh_channel_free(channel);
        return;
    }

    int exec = ssh_channel_request_exec(channel, command.toLocal8Bit().constData());
    if (exec != SSH_OK) {
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        return;
    }

    ssh_channel_close(channel);
    ssh_channel_free(channel);
    ssh_disconnect(session);
    ssh_free(session);
}
