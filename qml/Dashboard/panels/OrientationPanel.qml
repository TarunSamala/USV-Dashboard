import QtQuick
import QtQuick.Layouts
import Dashboard

PanelFrame {

    ColumnLayout {

        anchors.fill: parent

        anchors.margins: 14

        spacing: 24

        SectionTitle {
            title: "ORIENTATION"
        }

        TelemetryValue {

            label: "ROLL"

            value: telemetry.roll.toFixed(2)

            unit: "deg"

            valueColor: "#22d3ee"
        }

        TelemetryValue {

            label: "PITCH"

            value: telemetry.pitch.toFixed(2)

            unit: "deg"

            valueColor: "#4ade80"
        }

        TelemetryValue {

            label: "YAW"

            value: telemetry.yaw.toFixed(2)

            unit: "deg"

            valueColor: "#f97316"
        }

        SectionTitle {
            title: "COMPASS"
        }

        Rectangle {

            Layout.fillWidth: true

            Layout.preferredHeight: 220

            color: "#020617"

            border.color: "#1e293b"

            radius: 6

            Item {

                anchors.centerIn: parent

                width: 180
                height: 180

                Rectangle {

                    anchors.fill: parent

                    radius: width / 2

                    color: "#081121"

                    border.color: "#38bdf8"

                    border.width: 2
                }

                Text {

                    text: "N"

                    color: "#ef4444"

                    anchors.horizontalCenter: parent.horizontalCenter

                    anchors.top: parent.top

                    anchors.topMargin: 10

                    font.bold: true

                    font.pixelSize: 16
                }

                Text {

                    text: telemetry.yaw.toFixed(0) + "°"

                    anchors.centerIn: parent

                    color: "#e2e8f0"

                    font.pixelSize: 28

                    font.bold: true

                    font.family: "monospace"
                }

                Rectangle {

                    width: 4

                    height: 70

                    radius: 2

                    color: "#22d3ee"

                    anchors.centerIn: parent

                    transform: Rotation {

                        origin.x: 2
                        origin.y: 55

                        angle: telemetry.yaw
                    }
                }
            }
        }
    }
}