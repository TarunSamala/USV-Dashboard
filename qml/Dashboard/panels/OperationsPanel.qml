import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Dashboard

PanelFrame {

    ColumnLayout {

        anchors.fill: parent

        anchors.margins: 12

        spacing: 14

        //
        // TITLE
        //

        SectionTitle {
            title: "ACTIVE OPERATIONS"
        }

        //
        // ACTIVE TASK BOX
        //

        Rectangle {

            Layout.fillWidth: true

            implicitHeight: 150

            radius: 6

            color: Theme.panelElevated

            border.color: Theme.border

            border.width: 1

            ColumnLayout {

                anchors.fill: parent

                anchors.margins: 12

                spacing: 10

                //
                // TASK LABEL
                //

                Text {

                    text: "ACTIVE TASK"

                    color: Theme.textMuted

                    font.pixelSize: 10

                    font.family: "monospace"

                    font.letterSpacing: 3
                }

                //
                // TASK TITLE
                //

                Text {

                    text:
                        calibrationController.title

                    color: Theme.textPrimary

                    font.pixelSize: 20

                    font.bold: true

                    font.family: "monospace"

                    wrapMode: Text.WordWrap
                }

                //
                // TASK INFO
                //

                Text {

                    text:
                        calibrationController.instruction

                    color: Theme.textSecondary

                    font.pixelSize: 12

                    font.family: "monospace"

                    wrapMode: Text.WordWrap

                    Layout.fillWidth: true
                }

                //
                // PROGRESS BAR
                //

                Rectangle {

                    Layout.fillWidth: true

                    implicitHeight: 10

                    radius: 5

                    color: "#202020"

                    border.color: Theme.border

                    border.width: 1

                    Rectangle {

                        width:
                            parent.width
                            * (
                                calibrationController.progress
                                / 100.0
                            )

                        height: parent.height

                        radius: 5

                        color: "#ff2b2b"
                    }
                }

                //
                // PROGRESS TEXT
                //

                Text {

                    text:
                        calibrationController.progress
                        + "%"

                    color: Theme.textMuted

                    font.pixelSize: 11

                    font.family: "monospace"
                }
            }
        }

        //
        // SYSTEM EVENTS
        //

        SectionTitle {
            title: "SYSTEM EVENTS"
        }

        Rectangle {

            Layout.fillWidth: true

            Layout.fillHeight: true

            radius: 6

            color: Theme.panelElevated

            border.color: Theme.border

            border.width: 1

            ListView {

                anchors.fill: parent

                anchors.margins: 10

                spacing: 6

                clip: true

                model: systemLogger.logs

                delegate: Text {

                    width:
                        ListView.view.width

                    text: modelData

                    color:
                        modelData.includes("ERR")
                        ? "#ff4d4d"
                        : Theme.textSecondary

                    font.pixelSize: 11

                    font.family: "monospace"

                    wrapMode: Text.WrapAnywhere
                }

                ScrollBar.vertical:
                    ScrollBar { }
            }
        }
    }
}