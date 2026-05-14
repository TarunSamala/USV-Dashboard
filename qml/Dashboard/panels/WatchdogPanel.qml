import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Dashboard

PanelFrame {

    ColumnLayout {

        anchors.fill: parent

        anchors.margins: 14

        spacing: 18

        //
        // TITLE
        //

        SectionTitle {
            title: "SYSTEM OPERATIONS"
        }

        //
        // CONTROLS
        //

        Text {

            text: "CONTROL ACTIONS"

            color: Theme.textMuted

            font.pixelSize: 11

            font.letterSpacing: 2

            font.family: "monospace"
        }

        GridLayout {

            Layout.fillWidth: true

            columns: 1

            rowSpacing: 12

            columnSpacing: 10

            //
            // CAL GYRO
            //

            Button {

                text: "CAL GYRO"

                Layout.fillWidth: true

                implicitHeight: 44

                enabled:
                    !calibrationController.active

                onClicked: {

                    serialReader.sendLine(
                        "STOP"
                    )

                    serialReader.sendLine(
                        "CAL:GYRO"
                    )
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

                    font.bold: true

                    font.family: "monospace"

                    horizontalAlignment:
                        Text.AlignHCenter

                    verticalAlignment:
                        Text.AlignVCenter
                }
            }

            //
            // CAL MAG
            //

            Button {

                text: "CAL MAG"

                Layout.fillWidth: true

                implicitHeight: 44

                enabled:
                    !calibrationController.active

                onClicked: {

                    serialReader.sendLine(
                        "STOP"
                    )

                    serialReader.sendLine(
                        "CAL:MAG"
                    )
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

                    font.bold: true

                    font.family: "monospace"

                    horizontalAlignment:
                        Text.AlignHCenter

                    verticalAlignment:
                        Text.AlignVCenter
                }
            }

            //
            // SET BOW
            //

            Button {

                text: "SET BOW"

                Layout.fillWidth: true

                implicitHeight: 44

                enabled:
                    !calibrationController.active

                onClicked: {

                    serialReader.sendLine(
                        "SET:BOW"
                    )
                }

                background: Rectangle {

                    radius: 6

                    color: Theme.panelElevated

                    border.color: Theme.borderStrong

                    border.width: 1
                }

                contentItem: Text {

                    text: parent.text

                    color: Theme.textPrimary

                    font.pixelSize: 12

                    font.bold: true

                    font.family: "monospace"

                    horizontalAlignment:
                        Text.AlignHCenter

                    verticalAlignment:
                        Text.AlignVCenter
                }
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }
}