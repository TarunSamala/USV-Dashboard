import QtQuick
import QtQuick.Layouts

Column {

    property string label: ""

    property string value: ""

    property string unit: ""

    property color valueColor: "#e2e8f0"

    spacing: 2

    Text {

        text: label

        color: "#64748b"

        font.pixelSize: 10

        font.letterSpacing: 3

        font.family: "monospace"
    }

    Row {

        spacing: 6

        Text {

            text: value

            color: valueColor

            font.pixelSize: 36

            font.bold: true

            font.family: "monospace"
        }

        Text {

            text: unit

            color: "#38bdf8"

            font.pixelSize: 14

            font.family: "monospace"

            anchors.bottom: parent.bottom
        }
    }
}