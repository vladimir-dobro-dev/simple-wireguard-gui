import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import models

Page {
    id: root

    header: ToolBar {
        Label {
            text: qsTr("Server settings")
            anchors.centerIn: parent
        }
    }

    ColumnLayout {
        anchors.left: parent.left
        anchors.right: parent.right

        Pane {
            Layout.fillWidth: true

            GridLayout {
                anchors.left: parent.left
                anchors.right: parent.right
                columns: 2

                Label {
                    Layout.margins: 10
                    text: qsTr("Server IP/URL address")
                }
                TextField {
                    id: serverAddress
                    Layout.margins: 10
                    Layout.fillWidth: true
                    text: "127.0.0.1"
                }

                Label {
                    Layout.margins: 10
                    text: qsTr("User name")
                }
                TextField {
                    id: userName
                    Layout.margins: 10
                    Layout.fillWidth: true
                    text: "ssh-user"
                }

                Label {
                    Layout.margins: 10
                    text: qsTr("User password")
                }
                TextField {
                    id: userPassword
                    Layout.margins: 10
                    Layout.fillWidth: true
                    echoMode: TextInput.PasswordEchoOnEdit
                    text: "19841981"
                }

                Label {
                    Layout.margins: 10
                    text: qsTr("SSH port")
                }
                TextField {
                    id: serverPort
                    Layout.margins: 10
                    Layout.fillWidth: true
                    text: "22"
                }

                Label {
                    Layout.margins: 10
                    text: qsTr("Server Name")
                }
                TextField {
                    id: serverName
                    Layout.margins: 10
                    Layout.fillWidth: true
                    text: "Server for work"
                }
            }
        }

        Button {
            id: installAdminPanelButton

            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Install admin panel")

            ServerListModel {
                id: serverListModel
            }

            onClicked: {
                serverListModel.addServer(serverAddress.text, serverPort.text,
                                          userName.text, userPassword.text,
                                          serverName.text);
            }
        }
    }
}
