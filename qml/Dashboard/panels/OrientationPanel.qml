import QtQuick
import QtQuick.Layouts
import Dashboard

PanelFrame {

    ColumnLayout {

        anchors.fill: parent

        anchors.margins: 14

        spacing: 24

        //
        // ORIENTATION
        //

        SectionTitle {
            title: "ORIENTATION"
        }

        TelemetryValue {

            label: "ROLL"

            value: telemetry.roll.toFixed(2)

            unit: "deg"

            valueColor: "#f5f5f5"
        }

        TelemetryValue {

            label: "PITCH"

            value: telemetry.pitch.toFixed(2)

            unit: "deg"

            valueColor: "#d4d4d4"
        }

        TelemetryValue {

            label: "YAW"

            value: telemetry.yaw.toFixed(2)

            unit: "deg"

            valueColor: "#ff3b30"
        }

        //
        // COMPASS
        //

        SectionTitle {
            title: "COMPASS"
        }

        CompassWidget {

            Layout.alignment: Qt.AlignHCenter

            heading: telemetry.yaw
        }
    }
}