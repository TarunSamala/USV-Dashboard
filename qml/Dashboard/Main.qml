import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Dashboard

ApplicationWindow {
    visible: true
    width: 1200
    height: 700
    title: "USV Dashboard"
    color: "#020617"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        // Header
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            color: "#111827"
            radius: 6

            Text {
                anchors.centerIn: parent
                text: "USV Dashboard"
                color: "white"
                font.pixelSize: 18
            }
        }

        // Top stats bar
        TopBar {
            Layout.fillWidth: true
            Layout.preferredHeight: 100
        }

        // Main content
        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 10

            // LEFT PANEL
            Rectangle {
                Layout.preferredWidth: 250
                Layout.fillHeight: true
                color: "#0b1220"
                radius: 8
                border.color: "#1f2937"
            }

            // CENTER PANEL (split into top + bottom)
            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 10

                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 250
                    color: "#020617"
                    border.color: "#1f2937"
                    radius: 8
                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#020617"
                    border.color: "#1f2937"
                    radius: 8
                }
            }

            // RIGHT PANEL
            Rectangle {
                Layout.preferredWidth: 250
                Layout.fillHeight: true
                color: "#0b1220"
                radius: 8
                border.color: "#1f2937"
            }
        }
    }
}