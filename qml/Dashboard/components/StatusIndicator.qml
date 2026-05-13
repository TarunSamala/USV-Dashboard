import QtQuick
import QtQuick.Layouts
import Dashboard
RowLayout {

    property string label: "ESP32"
    property bool active: false

    spacing: 10

    Rectangle {
        width: 12
        height: 12

        radius: 6

        color: active
               ? Theme.statusActive
               : Theme.statusInactive

        border.color: Theme.border
        border.width: 1
    }

    Text {
        text: label

        color: Theme.textSecondary

        font.pixelSize: 13
        font.letterSpacing: 1
    }
}