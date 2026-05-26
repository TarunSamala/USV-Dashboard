import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Dashboard

PanelFrame {

    ColumnLayout {

        anchors.fill: parent

        anchors.margins: 14

        spacing: 14

        //
        // TITLE
        //

        SectionTitle {
            title: "CALIBRATION"
        }

        //
        // CALIBRATION LABEL
        //

        //
        // BUTTON ROW
        //

        RowLayout {

            Layout.fillWidth: true

            spacing: 10

            //
            // GYRO
            //

            Button {

                text: "GYR"

                Layout.fillWidth: true

                implicitWidth: 72

                implicitHeight: 52

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
            // MAG
            //

            Button {

                text: "MAG"

                Layout.fillWidth: true

                implicitWidth: 72

                implicitHeight: 52

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
            // BOW
            //

            Button {

                text: "BOW"

                Layout.fillWidth: true

                implicitWidth: 72

                implicitHeight: 52

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

        //
        // STATUS INDICATOR
        //

        RowLayout {

            Layout.fillWidth: true

            spacing: 10

            //
            // STATUS DOT
            //

            Rectangle {

                width: 10

                height: 10

                radius: 5

                color:

                    calibrationController.error !== ""
                    ? "#ff4444"

                    :

                    calibrationController.warning !== ""
                    ? "#ffaa00"

                    :

                    calibrationController.success
                    ? "#00cc66"

                    :

                    calibrationController.active
                    ? "#33aaff"

                    :

                    "#666666"
            }

            //
            // STATUS TEXT
            //

            Text {

                Layout.fillWidth: true

                text:

                    calibrationController.error !== ""
                    ? "Calibration failed"

                    :

                    calibrationController.warning !== ""
                    ? "Completed with warnings"

                    :

                    calibrationController.success
                    ? "Task executed successfully"

                    :

                    calibrationController.active
                    ? calibrationController.title

                    :

                    "Idle"

                color:

                    calibrationController.error !== ""
                    ? "#ff5555"

                    :

                    calibrationController.warning !== ""
                    ? "#ffcc33"

                    :

                    calibrationController.success
                    ? "#33dd88"

                    :

                    calibrationController.active
                    ? "#33aaff"

                    :

                    Theme.textMuted

                font.pixelSize: 11

                font.bold:
                    calibrationController.active

                font.family: "monospace"

                wrapMode: Text.WordWrap
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }
}