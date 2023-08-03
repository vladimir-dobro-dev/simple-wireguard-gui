import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: window
    width: 400
    height: 600
    visible: true

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: ServerListPage {}
    }
}
