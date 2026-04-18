import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow{
    visible: true
    width: 1200
    height: 700
    title: "USV Dashboard"

    ColumnLayout {
        anchors.fill: parent
        spacing: 6

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            color: "#1e293b"

            Text{
                anchors.centerIn: parent
                text: "USV Dashboard"
                color: "white"
                font.pixelSize: 18
            }
        }

        RowLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 6

            Rectangle{
                Layout.preferredWidth: 250
                Layout.fillHeight: true
                color: "#0f172a"

                Text{
                    anchors.centerIn: parent
                    text: "Left Panel"
                    color: "white"
                }
            }

            Rectangle {

                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "#020617"

                Text{
                    anchors.centerIn: parent
                    text: "Speed: " + telemetry.speed + " km/h"
                    color: "White"
                }
            }
        }

        Rectangle{

            Layout.fillWidth: true
            Layout.preferredHeight: 120
            color: "#1e293b"

            Text {
                anchors.centerIn: parent
                text: "Battery: " + telemetry.battery.toFixed(1) + " %"
                color: "white"
            }
        }

    }
}