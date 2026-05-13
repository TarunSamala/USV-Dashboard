import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Dashboard


PanelFrame {

    ColumnLayout {

        anchors.fill: parent

        anchors.margins: 14

        spacing: 18

        // TITLE

        SectionTitle {
            title: "IMU NAVIGATION MODULE"
        }

        // HEALTH SECTION

        ColumnLayout {

            Layout.fillWidth: true

            spacing: 10

            Text {

                text: "HEALTH"

                color: Theme.textMuted

                font.pixelSize: 11

                font.letterSpacing: 2
            }

            StatusIndicator {
                label: "ESP32"
                active: true
            }

            StatusIndicator {
                label: "MPU6500"
                active: true
            }

            StatusIndicator {
                label: "BMM350"
                active: false
            }
        }

        Rectangle {

            Layout.fillWidth: true

            height: 1

            color: Theme.border
        }

        // CONNECTION SECTION

        ColumnLayout {

            Layout.fillWidth: true

            spacing: 10

            Text {

                text: "CONNECTION"

                color: Theme.textMuted

                font.pixelSize: 11

                font.letterSpacing: 2
            }

            StatusIndicator {
                label: "SERIAL STREAM"
                active: true
            }

            Text {

                text: "PORT : /dev/ttyACM0"

                color: Theme.textPrimary

                font.pixelSize: 13

                font.family: "monospace"
            }

            Text {

                text: "BAUD : 115200"

                color: Theme.textPrimary

                font.pixelSize: 13

                font.family: "monospace"
            }
        }

        Rectangle {

            Layout.fillWidth: true

            height: 1

            color: Theme.border
        }

        // TELEMETRY SECTION

        ColumnLayout {

            Layout.fillWidth: true

            spacing: 10

            Text {

                text: "TELEMETRY"

                color: Theme.textMuted

                font.pixelSize: 11

                font.letterSpacing: 2
            }

            Text {

                text: "PACKET RATE : 92 Hz"

                color: Theme.textPrimary

                font.pixelSize: 13

                font.family: "monospace"
            }

            Text {

                text: "LAST UPDATE : 14 ms"

                color: "#94a3b8"

                font.pixelSize: 13

                font.family: "monospace"
            }

            Text {

                text: "UPTIME : 01:14:22"

                color: Theme.textSecondary

                font.pixelSize: 13

                font.family: "monospace"
            }

            Text {

                text: "STATUS : HEALTHY"

                color: Theme.textPrimary

                font.pixelSize: 14

                font.bold: true

                font.family: "monospace"
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }
}