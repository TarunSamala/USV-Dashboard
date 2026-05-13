import QtQuick
import QtQuick.Layouts
import Dashboard
Column {

    property string label: ""

    property string value: ""

    property string unit: ""

    property color valueColor: Theme.textPrimary

    spacing: 2

    Text {

        text: label

        color: Theme.textMuted

        font.pixelSize: 22

        font.letterSpacing: 3

        font.family: "monospace"
    }

    Row {

        spacing: 6

        Text {

            text: value

            color: Theme.textMuted

            font.pixelSize: 44

            font.bold: true

            font.family: "monospace"
        }

        Text {

            text: unit

            color: Theme.textMuted

            font.pixelSize: 22

            font.family: "monospace"

            anchors.bottom: parent.bottom
        }
    }
}