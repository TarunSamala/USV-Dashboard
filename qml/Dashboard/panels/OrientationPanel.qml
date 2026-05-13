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

            CompassWidget {

                Layout.alignment: Qt.AlignHCenter

                heading: telemetry.yaw
                }

    
            }
        }
    
