import QtQuick
import QtQuick.Layouts

RowLayout {

    property string label: "ESP32"
    property bool active: false

    spacing: 10

    Rectangle {
        width: 12
        height: 12

        radius: 6

        color: active
               ? "#22c55e"
               : "#ef4444"

        border.color: "#0f172a"
        border.width: 1
    }

    Text {
        text: label

        color: "#dbeafe"

        font.pixelSize: 13
        font.letterSpacing: 1
    }
}