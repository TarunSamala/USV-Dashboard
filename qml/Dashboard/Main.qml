import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Dashboard

ApplicationWindow {

    visible: true

    width: 1600
    height: 900

    title: "IMU NAVIGATION MODULE"

    color: Theme.bgPrimary

    ColumnLayout {

        anchors.fill: parent

        anchors.margins: 10

        spacing: 10

        //
        // TOP BAR
        //

        TopControlBar {

            Layout.fillWidth: true

            Layout.preferredHeight: 70
        }

        //
        // MAIN DASHBOARD
        //

        RowLayout {

            Layout.fillWidth: true

            Layout.fillHeight: true

            spacing: 10

            //
            // ====================================
            // LEFT COLUMN
            // ====================================
            //

            ColumnLayout {

                Layout.preferredWidth: 280

                Layout.minimumWidth: 260

                Layout.maximumWidth: 300

                Layout.fillHeight: true

                spacing: 10

                //
                // ORIENTATION
                //

                OrientationPanel {

                    Layout.fillWidth: true

                    Layout.preferredHeight: 410

                    Layout.maximumHeight: 410
                }

                //
                // SENSOR MATRIX
                //

                SensorMatrixPanel {

                    Layout.fillWidth: true

                    Layout.fillHeight: true
                }
            }

            //
            // ====================================
            // CENTER COLUMN
            // ====================================
            //

            ColumnLayout {

                Layout.fillWidth: true

                Layout.fillHeight: true

                Layout.horizontalStretchFactor: 5

                spacing: 10

                //
                // 3D VISUALIZATION
                //

                VisualizationPanel {

                    Layout.fillWidth: true

                    Layout.fillHeight: true

                    Layout.verticalStretchFactor: 5
                }

                //
                // EVENT LOGGER
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
                        // HEADER
                        //

                        RowLayout {

                            Layout.fillWidth: true

                            SectionTitle {
                                title: "EVENT LOG"
                            }

                            Item {
                                Layout.fillWidth: true
                            }

                            //
                            // CSV BUTTON
                            //

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

                                    horizontalAlignment:
                                        Text.AlignHCenter

                                    verticalAlignment:
                                        Text.AlignVCenter
                                }
                            }

                            //
                            // REC BUTTON
                            //

                            Button {

                                text:
                                    csvLogger.logging
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

                                    color:
                                        csvLogger.logging
                                        ? "#220000"
                                        : Theme.panelElevated

                                    border.color:
                                        csvLogger.logging
                                        ? "#ff3b3b"
                                        : Theme.border

                                    border.width: 1
                                }

                                contentItem: Text {

                                    text: parent.text

                                    color:
                                        csvLogger.logging
                                        ? "#ff4d4d"
                                        : Theme.textPrimary

                                    font.pixelSize: 12

                                    font.bold:
                                        csvLogger.logging

                                    font.family: "monospace"

                                    horizontalAlignment:
                                        Text.AlignHCenter

                                    verticalAlignment:
                                        Text.AlignVCenter
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

                                ScrollBar.vertical:
                                    ScrollBar { }
                            }
                        }
                    }
                }
            }

            //
            // ====================================
            // RIGHT COLUMN
            // ====================================
            //

            ColumnLayout {

                Layout.preferredWidth: 420

                Layout.minimumWidth: 390

                Layout.maximumWidth: 440

                Layout.fillHeight: true

                Layout.horizontalStretchFactor: 2

                spacing: 10

                //
                // CALIBRATION
                //

                WatchdogPanel {

                    Layout.fillWidth: true

                    Layout.preferredHeight: 140

                    Layout.maximumHeight: 140
                }

                //
                // ACTIVE OPERATIONS
                //

                OperationsPanel {

                    Layout.fillWidth: true

                    Layout.fillHeight: true
                }
            }
        }
    }
}