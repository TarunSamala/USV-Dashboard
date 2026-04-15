import QtQuick
import QtQuick.Controls

ApplicationWindows{
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
            font.pixelsize: 32
        }
    }
}