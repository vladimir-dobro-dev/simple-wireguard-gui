import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import sshcommands

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
                }

                Label {
                    Layout.margins: 10
                    text: qsTr("User name")
                }
                TextField {
                    id: userName
                    Layout.margins: 10
                    Layout.fillWidth: true
                    text: "root"
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
                }

                Label {
                    Layout.margins: 10
                    text: qsTr("SSH port")
                }
                TextField {
                    id: sshPort
                    Layout.margins: 10
                    Layout.fillWidth: true
                    text: "22"
                }
            }
        }

        Button {
            id: installAdminPanelButton

            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Install admin panel")

            SSHCommands {
                id: sshCommands
            }

            onClicked: {
                sshCommands.execRemoteCommand("touch test4");
            }
        }
    }

}
