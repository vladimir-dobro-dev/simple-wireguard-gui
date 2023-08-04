import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import models

Page {
    id: root

    header: ToolBar {
        Label {
            text: qsTr("Server list")
            anchors.centerIn: parent
        }
    }

    ColumnLayout {
        anchors.fill: parent

        ListView {
            id: listView
            Layout.fillHeight: true
            Layout.fillWidth: true
            displayMarginBeginning: 40
            displayMarginEnd: 40

            model: ServerListModel {}
            delegate: ItemDelegate {
                width:  parent.width
                text: model.display
            }

            ScrollBar.vertical: ScrollBar {}
        }

        Button {
            id: addServerButton
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Add server")
            onClicked: {
                root.StackView.view.push("AddServerPage.qml")
            }
        }
    }
}
