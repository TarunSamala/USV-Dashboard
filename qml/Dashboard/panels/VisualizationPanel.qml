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

                //
                // Use display (calibration-offset) values
                // so CAL BOW immediately resets the vessel
                // to its reference orientation.
                //

                roll:  telemetry.displayRoll  || 0
                pitch: telemetry.displayPitch || 0
                yaw:   telemetry.displayYaw   || 0
            }
        }
    }
}
