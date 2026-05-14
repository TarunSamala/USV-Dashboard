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
        // QUICK ACTIONS
        //

        ColumnLayout {

            Layout.fillWidth: true

            spacing: 10

            Text {

                text: "CONTROL ACTIONS"

                color: Theme.textMuted

                font.pixelSize: 11

                font.letterSpacing: 2

                font.family: "monospace"
            }

            GridLayout {

                columns: 2

                columnSpacing: 10

                rowSpacing: 10

                Layout.fillWidth: true

                //
                // CAL GYRO
                //

                Button {

                    text: "CAL GYRO"

                    Layout.fillWidth: true

                    implicitHeight: 40

                    onClicked: {

                        serialReader.sendLine(
                            "CAL:GYRO"
                        )

                        logger.addLog(
                            "TX > CAL:GYRO"
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

                    implicitHeight: 40

                    onClicked: {

                        serialReader.sendLine(
                            "CAL:MAG"
                        )

                        logger.addLog(
                            "TX > CAL:MAG"
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

                    implicitHeight: 40

                    onClicked: {

                        serialReader.sendLine(
                            "SET:BOW"
                        )

                        logger.addLog(
                            "TX > SET:BOW"
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

                //
                // CLEAR BOW
                //

                Button {

                    text: "CLR BOW"

                    Layout.fillWidth: true

                    implicitHeight: 40

                    onClicked: {

                        serialReader.sendLine(
                            "SET:BOW:CLEAR"
                        )

                        logger.addLog(
                            "TX > SET:BOW:CLEAR"
                        )
                    }

                    background: Rectangle {

                        radius: 6

                        color: Theme.panelElevated

                        border.color: Theme.accentRed

                        border.width: 1
                    }

                    contentItem: Text {

                        text: parent.text

                        color: Theme.accentRed

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
        }

        //
        // DIVIDER
        //

        Rectangle {

            Layout.fillWidth: true

            height: 1

            color: Theme.border
        }

        //
        // MANUAL COMMAND
        //

        ColumnLayout {

            Layout.fillWidth: true

            spacing: 10

            Text {

                text: "MANUAL COMMAND"

                color: Theme.textMuted

                font.pixelSize: 11

                font.letterSpacing: 2

                font.family: "monospace"
            }

            //
            // INPUT CONTAINER
            //

            Rectangle {

                Layout.fillWidth: true

                implicitHeight: 42

                radius: 6

                color: Theme.bgSecondary

                border.color: Theme.border

                border.width: 1

                RowLayout {

                    anchors.fill: parent

                    anchors.leftMargin: 10

                    anchors.rightMargin: 10

                    spacing: 8

                    Text {

                        text: ">"

                        color: Theme.textMuted

                        font.pixelSize: 14

                        font.family: "monospace"
                    }

                    TextField {

                        id: commandInput

                        Layout.fillWidth: true

                        placeholderText:
                            "ENTER SERIAL COMMAND"

                        placeholderTextColor:
                            Theme.textMuted

                        color: Theme.textPrimary

                        font.pixelSize: 13

                        font.family: "monospace"

                        background: Item {}

                        onAccepted: {

                            if (text.length <= 0)
                                return

                            serialReader.sendLine(
                                text
                            )

                            logger.addLog(
                                "TX > " + text
                            )

                            text = ""
                        }
                    }
                }
            }

            //
            // SEND BUTTON
            //

            Button {

                text: "SEND COMMAND"

                Layout.fillWidth: true

                implicitHeight: 40

                onClicked: {

                    if (
                        commandInput.text.length <= 0
                    )
                        return

                    serialReader.sendLine(
                        commandInput.text
                    )

                    logger.addLog(
                        "TX > "
                        + commandInput.text
                    )

                    commandInput.text = ""
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
        }

        Item {
            Layout.fillHeight: true
        }
    }
}