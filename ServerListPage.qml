import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

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

            delegate: Label {
                text: "10"
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
