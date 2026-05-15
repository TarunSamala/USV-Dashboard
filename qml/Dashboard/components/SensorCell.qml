import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Dashboard

Rectangle {

    id: root

    property string title: "AX"

    property string value: "0.00"

    property string unit: "m/s²"

    property color valueColor: Theme.textPrimary

    radius: 8

    color: Theme.panelElevated

    border.color: Theme.border

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

            color: Theme.textMuted

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

            color: Theme.textMuted

            font.pixelSize: 9

            Layout.alignment: Qt.AlignHCenter
        }

        Item {
            Layout.fillHeight: true
        }
    }
}