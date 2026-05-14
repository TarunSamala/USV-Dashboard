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

            model: runtime.availablePorts

            currentIndex:
                runtime.availablePorts.indexOf(
                    runtime.currentPort
                )

            onActivated: {

                runtime.currentPort =
                    currentText
            }

            implicitWidth: 220

            font.pixelSize: 13

            editable: false

            background: Rectangle {

                radius: 6

                color: Theme.panelElevated

                border.color: Theme.border

                border.width: 1
            }

            contentItem: Text {

                text: portBox.displayText

                color: Theme.textPrimary

                font.pixelSize: 12

                font.family: "monospace"

                verticalAlignment: Text.AlignVCenter

                leftPadding: 10
            }

            delegate: ItemDelegate {

                width: portBox.width

                contentItem: Text {

                    text: modelData

                    color: Theme.textPrimary

                    font.pixelSize: 12

                    font.family: "monospace"

                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {

                    color: hovered
                           ? "#252525"
                           : Theme.panelElevated
                }
            }

            popup: Popup {

                y: portBox.height + 4

                width: portBox.width

                implicitHeight: contentItem.implicitHeight

                padding: 2

                background: Rectangle {

                    radius: 6

                    color: Theme.panelElevated

                    border.color: Theme.border

                    border.width: 1
                }

                contentItem: ListView {

                    clip: true

                    implicitHeight: contentHeight

                    model: portBox.popup.visible
                           ? portBox.delegateModel
                           : null

                    currentIndex:
                        portBox.highlightedIndex
                }
            }
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

            background: Rectangle {

                radius: 6

                color: Theme.panelElevated

                border.color: Theme.border

                border.width: 1
            }

            contentItem: Text {

                text: baudBox.displayText

                color: Theme.textPrimary

                font.pixelSize: 12

                font.family: "monospace"

                verticalAlignment: Text.AlignVCenter

                leftPadding: 10
            }
        }

        //
        // REFRESH BUTTON
        //

        Button {

            text: "REFRESH"

            implicitHeight: 38

            implicitWidth: 110

            onClicked: {

                runtime.refreshPorts()
            }

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

            text: runtime.connected
                  ? "DISCONNECT"
                  : "CONNECT"

            implicitHeight: 38

            implicitWidth: 120

            onClicked: {

                //
                // DISCONNECT
                //

                if (runtime.connected)
                {
                    serialReader.disconnectPort()
                }

                //
                // CONNECT
                //

                else
                {
                    //
                    // Safety check
                    //

                    if (
                        runtime.currentPort === ""
                    )
                    {
                        console.log(
                            "No serial port selected"
                        )

                        return
                    }

                    console.log(
                        "Connecting to:",
                        runtime.currentPort
                    )

                    serialReader.connectPort(
                        runtime.currentPort
                    )
                }
            }

            background: Rectangle {

                radius: 6

                color: runtime.connected
                       ? "#220909"
                       : Theme.panelElevated

                border.color: runtime.connected
                              ? "#cc0000"
                              : Theme.border

                border.width: 1
            }

            contentItem: Text {

                text: parent.text

                color: runtime.connected
                       ? "#ff5555"
                       : Theme.textPrimary

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

            color: runtime.connected
                   ? Theme.statusActive
                   : Theme.statusInactive

            border.color: Theme.border

            border.width: 1
        }

        Text {

            text: runtime.connectionStatus

            color: Theme.textSecondary

            font.pixelSize: 13

            font.family: "monospace"
        }

        //
        // FIRMWARE VERSION
        //

        Rectangle {

            implicitWidth: 180

            implicitHeight: 42

            radius: 6

            color: Theme.panelElevated

            border.color: Theme.border

            border.width: 1

            Text {

                anchors.centerIn: parent

                text: runtime.firmwareVersion

                color: Theme.textPrimary

                font.pixelSize: 13

                font.family: "monospace"
            }
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