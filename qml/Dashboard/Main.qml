import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Dashboard

ApplicationWindow {

    visible: true

    width: 1600
    height: 900

    title: "USV.Heading"

    color: Theme.bgPrimary

    ColumnLayout {

        anchors.fill: parent

        anchors.margins: 10

        spacing: 10

        //
        // TOP CONTROL BAR
        //

        TopControlBar {

            Layout.fillWidth: true

            Layout.preferredHeight: 70
        }

        //
        // MAIN DASHBOARD AREA
        //

        RowLayout {

            Layout.fillWidth: true

            Layout.fillHeight: true

            spacing: 10

            //
            // LEFT COLUMN
            //

            OrientationPanel {

                Layout.preferredWidth: 320

                Layout.minimumWidth: 300

                Layout.maximumWidth: 340

                Layout.fillHeight: true
            }

            //
            // CENTER COLUMN
            //

            ColumnLayout {

                Layout.fillWidth: true

                Layout.fillHeight: true

                Layout.horizontalStretchFactor: 5

                spacing: 10

                //
                // 3D VISUALIZATION PANEL
                //

                PanelFrame {

                    Layout.fillWidth: true

                    Layout.fillHeight: true

                    Layout.verticalStretchFactor: 4

                    ColumnLayout {

                        anchors.fill: parent

                        anchors.margins: 14

                        spacing: 12

                        SectionTitle {
                            title: "3D VISUALIZATION"
                        }

                        Rectangle {

                            Layout.fillWidth: true

                            Layout.fillHeight: true

                            radius: 8

                            color: Theme.panelElevated

                            border.color: Theme.border

                            border.width: 1

                            Text {

                                anchors.centerIn: parent

                                text: "VESSEL VISUALIZATION"

                                color: Theme.textMuted

                                font.pixelSize: 18

                                font.family: "monospace"
                            }
                        }
                    }
                }

                //
                // EVENT LOGGER PANEL
                //

                PanelFrame {

                    Layout.fillWidth: true

                    Layout.fillHeight: true

                    Layout.preferredHeight: 240

                    Layout.minimumHeight: 220

                    Layout.maximumHeight: 280

                    Layout.verticalStretchFactor: 2

                    ColumnLayout {

                        anchors.fill: parent

                        anchors.margins: 14

                        spacing: 10

                        //
                        // HEADER ROW
                        //

                        RowLayout {

                            Layout.fillWidth: true

                            SectionTitle {
                                title: "EVENT LOG"
                            }

                            Item {
                                Layout.fillWidth: true
                            }

                            Button {

                                text: "CSV"

                                implicitWidth: 70

                                implicitHeight: 30

                                background: Rectangle {

                                    radius: 6

                                    color: Theme.panelElevated

                                    border.color: Theme.border

                                    border.width: 1
                                }

                                contentItem: Text {

                                    text: parent.text

                                    color: Theme.textPrimary

                                    font.pixelSize: 11

                                    font.family: "monospace"

                                    horizontalAlignment: Text.AlignHCenter

                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                            
                            Button {

                                text: csvLogger.logging
                                    ? "STOP"
                                    : "REC"

                                implicitWidth: 90

                                implicitHeight: 32

                                onClicked: {

                                    if (csvLogger.logging)
                                    {
                                        csvLogger.stopLogging()
                                    }
                                    else
                                    {
                                        csvLogger.startLogging()
                                    }
                                }

                                background: Rectangle {

                                    radius: 6

                                    color: csvLogger.logging
                                        ? "#220000"
                                        : Theme.panelElevated

                                    border.color: csvLogger.logging
                                                ? "#ff3b3b"
                                                : Theme.border

                                    border.width: 1
                                }

                                contentItem: Text {

                                    text: parent.text

                                    color: csvLogger.logging
                                        ? "#ff4d4d"
                                        : Theme.textPrimary

                                    font.pixelSize: 12

                                    font.bold: csvLogger.logging

                                    font.family: "monospace"

                                    horizontalAlignment: Text.AlignHCenter

                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                        }

                        //
                        // LOG VIEW
                        //

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

                                model: logger.logs

                                spacing: 4

                                clip: true

                                delegate: Text {

                                    text: modelData

                                    color: Theme.textSecondary

                                    font.pixelSize: 12

                                    font.family: "monospace"
                                }

                                ScrollBar.vertical: ScrollBar { }
                            }
                        }
                    }
                }
            }

            //
            // RIGHT COLUMN
            //

            ColumnLayout {

                Layout.preferredWidth: 420

                Layout.minimumWidth: 390

                Layout.maximumWidth: 440

                Layout.fillHeight: true

                Layout.horizontalStretchFactor: 2

                spacing: 10

                //
                // WATCHDOG PANEL
                //

                WatchdogPanel {

                    Layout.fillWidth: true

                    Layout.fillHeight: true

                    Layout.preferredHeight: 320

                    Layout.minimumHeight: 300

                    Layout.maximumHeight: 340
                }

                //
                // SENSOR MATRIX
                //

                SensorMatrixPanel {

                    Layout.fillWidth: true

                    Layout.fillHeight: true

                    Layout.verticalStretchFactor: 3
                }

                
            }
        }
    }
}