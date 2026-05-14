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
            title: "ORIENTATION"
        }

        //
        // ROLL
        //

        ColumnLayout {

            spacing: 4

            Text {

                text: "ROLL"

                color: Theme.textMuted

                font.pixelSize: 18

                font.family: "monospace"

                font.letterSpacing: 3
            }

            RowLayout {

                spacing: 6

                Text {

                    text:
                        Number(
                            telemetry.roll
                        ).toFixed(2)

                    color: Theme.textPrimary

                    font.pixelSize: 44

                    font.bold: true

                    font.family: "monospace"
                }

                Text {

                    text: "deg"

                    color: Theme.textMuted

                    font.pixelSize: 18

                    font.family: "monospace"
                }
            }
        }

        //
        // PITCH
        //

        ColumnLayout {

            spacing: 4

            Text {

                text: "PITCH"

                color: Theme.textMuted

                font.pixelSize: 18

                font.family: "monospace"

                font.letterSpacing: 3
            }

            RowLayout {

                spacing: 6

                Text {

                    text:
                        Number(
                            telemetry.pitch
                        ).toFixed(2)

                    color: Theme.textPrimary

                    font.pixelSize: 44

                    font.bold: true

                    font.family: "monospace"
                }

                Text {

                    text: "deg"

                    color: Theme.textMuted

                    font.pixelSize: 18

                    font.family: "monospace"
                }
            }
        }

        //
        // YAW
        //

        ColumnLayout {

            spacing: 4

            Text {

                text: "YAW"

                color: Theme.textMuted

                font.pixelSize: 18

                font.family: "monospace"

                font.letterSpacing: 3
            }

            RowLayout {

                spacing: 6

                Text {

                    text:
                        Number(
                            telemetry.yaw
                        ).toFixed(2)

                    color: Theme.textPrimary

                    font.pixelSize: 44

                    font.bold: true

                    font.family: "monospace"
                }

                Text {

                    text: "deg"

                    color: Theme.textMuted

                    font.pixelSize: 18

                    font.family: "monospace"
                }
            }
        }

        //
        // OPERATIONS PANEL
        //

        OperationsPanel {

            Layout.fillWidth: true

            Layout.fillHeight: true
        }
    }
}