import QtQuick
import QtQuick.Layouts

import Dashboard
import Dashboard.Visualization

PanelFrame {

    ColumnLayout {

        anchors.fill: parent

        anchors.margins: 14

        spacing: 14

        SectionTitle {
            title: "3D VISUALIZATION"
        }

        Rectangle {

            Layout.fillWidth: true
            Layout.fillHeight: true

            radius: 8

            color: Theme.bgSecondary

            border.color: Theme.border

            border.width: 1

            clip: true

        VesselView {

            anchors.fill: parent

            roll: telemetry.roll || 0

            pitch: telemetry.pitch || 0

            yaw: telemetry.yaw || 0
}
        }
    }
}