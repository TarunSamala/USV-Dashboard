import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Dashboard

ApplicationWindow {

    visible: true

    width: 1600
    height: 900

    title: "USV Dashboard"

    color: "#020617"

    RowLayout {

        anchors.fill: parent

        anchors.margins: 10

        spacing: 10

        // LEFT PANEL
        OrientationPanel {

            Layout.preferredWidth: 320

            Layout.fillHeight: true
        }

        // CENTER PANEL
        PanelFrame {

            Layout.fillWidth: true

            Layout.fillHeight: true

            ColumnLayout {

                anchors.fill: parent

                anchors.margins: 14

                spacing: 16

                SectionTitle {
                    title: "3D VISUALIZATION"
                }

                Rectangle {

                    Layout.fillWidth: true

                    Layout.fillHeight: true

                    radius: 6

                    color: "#050b16"

                    border.color: "#1e293b"

                    Text {

                        anchors.centerIn: parent

                        text: "MPU9250 / Vessel Visualization"

                        color: "#64748b"

                        font.pixelSize: 18

                        font.family: "monospace"
                    }
                }

                SectionTitle {
                    title: "EVENT LOG"
                }

                Rectangle {

                    Layout.fillWidth: true

                    Layout.preferredHeight: 180

                    radius: 6

                    color: "#050b16"

                    border.color: "#1e293b"

                    Text {

                        anchors.centerIn: parent

                        text: "Sensor logs / serial stream"

                        color: "#64748b"

                        font.pixelSize: 16

                        font.family: "monospace"
                    }
                }
            }
        }

        SensorMatrixPanel {

            Layout.preferredWidth: 420

            Layout.fillHeight: true
        }
        
    }
}