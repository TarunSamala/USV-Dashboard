import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {

    id: root

    property string title: "AX"

    property string value: "0.00"

    property string unit: "m/s²"

    property color valueColor: "#22d3ee"

    radius: 8

    color: "#191d27"

    border.color: "#2a3140"

    border.width: 1

    Layout.fillWidth: true

    Layout.fillHeight: true

    implicitWidth: 100

    implicitHeight: 78

    ColumnLayout {

        anchors.fill: parent

        anchors.margins: 8

        spacing: 2

       
        // TITLE
       

        Text {

            text: root.title

            color: "#5d7b96"

            font.pixelSize: 10

            font.letterSpacing: 2

            Layout.alignment: Qt.AlignHCenter
        }

        Item {
            Layout.fillHeight: true
        }

       
        // VALUE
       

        Text {

            text: root.value

            color: root.valueColor

            font.pixelSize: 20

            font.bold: true

            font.family: "monospace"

            Layout.alignment: Qt.AlignHCenter
        }

       
        // UNIT
       

        Text {

            text: root.unit

            color: "#6b91ac"

            font.pixelSize: 9

            Layout.alignment: Qt.AlignHCenter
        }

        Item {
            Layout.fillHeight: true
        }
    }
}