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

            text: "USV.HEADING"

            color: "#22d3ee"

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
        }

        //
        // CONNECT BUTTON
        //

        Button {

            text: "CONNECT"

            implicitHeight: 38

            implicitWidth: 120
        }

        //
        // CONNECTION STATUS
        //

        Rectangle {

            implicitWidth: 14

            implicitHeight: 14

            radius: 7

            color: "#22c55e"

            border.color: "#0f172a"

            border.width: 1
        }

        Text {

            text: "CONNECTED"

            color: "#22c55e"

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

            color: "#071122"

            border.color: "#16324a"

            Text {

                anchors.centerIn: parent

                text: Qt.formatTime(
                    new Date(),
                    "hh:mm:ss"
                ) + " UTC"

                color: "#dbeafe"

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

            color: "#071122"

            border.color: "#16324a"

            Text {

                anchors.centerIn: parent

                text: Qt.formatTime(
                    new Date(
                        Date.now() + (5.5 * 60 * 60 * 1000)
                    ),
                    "hh:mm:ss"
                ) + " IST"

                color: "#dbeafe"

                font.pixelSize: 14

                font.family: "monospace"
            }
        }
    }
}