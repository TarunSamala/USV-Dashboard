import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Dashboard

Rectangle {
    id: root

    property string title: ""
    property string value: ""
    property string unit: ""

    radius: 10
    color: "#0b1220"

    border.color: "#1f2937"
    border.width: 1

    implicitHeight: 100
    Layout.minimumHeight: 100

    Column {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 6

        // Title
        Text {
            text: root.title
            color: "#6b7280"
            font.pixelSize: 11
        }

        // Value row
        Row {
            spacing: 6

            Text {
                text: root.value
                color: "#e5e7eb"
                font.pixelSize: 26
                font.bold: true
            }

            Text {
                text: root.unit
                color: "#9ca3af"
                font.pixelSize: 14
                anchors.bottom: parent.bottom
            }
        }
    }
}