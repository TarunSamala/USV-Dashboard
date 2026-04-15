import QtQuick
import QtQuick.Controls

ApplicationWindow{
    visible: true
    width: 1200
    height: 700
    title: "USV Dashboard"

    Rectangle {
        anchors.fill: parent
        color: "#0f172a"

        Text{
            anchors.centerIn: parent
            text: "USV Dashboard"
            color: "white"
            font.pixelSize: 32
        }
    }
}