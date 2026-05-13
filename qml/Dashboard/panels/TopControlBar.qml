import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Dashboard

PanelFrame {

    implicitHeight: 72

    RowLayout {

        anchors.fill: parent

        anchors.margins: 14

        spacing: 14

        //
        // TITLE
        //

        Text {

            text: "USV.Heading"

            color: Theme.textPrimary

            font.pixelSize: 24

            font.bold: true

            font.family: "monospace"

            font.letterSpacing: 3
        }

        Item {
            Layout.fillWidth: true
        }

        //
        // PORT DROPDOWN
        //

        ComboBox {

            id: portBox

            model: [
                "/dev/ttyACM0",
                "/dev/ttyUSB0",
                "COM3",
                "COM4"
            ]

            implicitWidth: 180

            font.pixelSize: 13

            editable: false
        }

        //
        // BAUD RATE
        //

        ComboBox {

            id: baudBox

            model: [
                "9600",
                "57600",
                "115200"
            ]

            currentIndex: 2

            implicitWidth: 120

            font.pixelSize: 13
        }

        //
        // REFRESH BUTTON
        //

        Button {

            text: "REFRESH"

            implicitHeight: 38

            implicitWidth: 110

            background: Rectangle {

                radius: 6

                color: Theme.panelElevated

                border.color: Theme.border

                border.width: 1
            }

            contentItem: Text {

                text: parent.text

                color: Theme.textPrimary

                font.pixelSize: 12

                font.family: "monospace"

                horizontalAlignment: Text.AlignHCenter

                verticalAlignment: Text.AlignVCenter
            }
        }

        //
        // CONNECT BUTTON
        //

        Button {

            text: "CONNECT"

            implicitHeight: 38

            implicitWidth: 120

            background: Rectangle {

                radius: 6

                color: Theme.panelElevated

                border.color: Theme.border

                border.width: 1
            }

            contentItem: Text {

                text: parent.text

                color: Theme.textPrimary

                font.pixelSize: 12

                font.family: "monospace"

                horizontalAlignment: Text.AlignHCenter

                verticalAlignment: Text.AlignVCenter
            }
        }

        //
        // CONNECTION STATUS
        //

        Rectangle {

            implicitWidth: 14

            implicitHeight: 14

            radius: 7

            color: Theme.statusActive

            border.color: Theme.border

            border.width: 1
        }

        Text {

            text: "CONNECTED"

            color: Theme.textSecondary

            font.pixelSize: 13

            font.family: "monospace"
        }

        //
        // UTC TIME
        //

        Rectangle {

            implicitWidth: 140

            implicitHeight: 42

            radius: 6

            color: Theme.panelElevated

            border.color: Theme.border

            border.width: 1

            Text {

                anchors.centerIn: parent

                text: Qt.formatTime(
                    new Date(),
                    "hh:mm:ss"
                ) + " UTC"

                color: Theme.textPrimary

                font.pixelSize: 14

                font.family: "monospace"
            }
        }

        //
        // IST TIME
        //

        Rectangle {

            implicitWidth: 140

            implicitHeight: 42

            radius: 6

            color: Theme.panelElevated

            border.color: Theme.border

            border.width: 1

            Text {

                anchors.centerIn: parent

                text: Qt.formatTime(
                    new Date(
                        Date.now() + (5.5 * 60 * 60 * 1000)
                    ),
                    "hh:mm:ss"
                ) + " IST"

                color: Theme.textPrimary

                font.pixelSize: 14

                font.family: "monospace"
            }
        }
    }
}