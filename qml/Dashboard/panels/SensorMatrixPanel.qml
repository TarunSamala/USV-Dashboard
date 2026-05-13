import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Dashboard

PanelFrame {

    ColumnLayout {

        anchors.fill: parent

        anchors.margins: 14

        spacing: 18

        //
        // TITLE
        //

        SectionTitle {
            title: "IMU SENSOR MATRIX"
        }

        
        // ACCELEROMETER
        

        ColumnLayout {

            Layout.fillWidth: true

            spacing: 8

            Text {

                text: "ACCELEROMETER"

                color: "#5d7b96"

                font.pixelSize: 11

                font.letterSpacing: 2
            }

            GridLayout {

                columns: 3

                Layout.fillWidth: true

                columnSpacing: 8

                rowSpacing: 8

                SensorCell {
                    title: "AX"
                    value: telemetry.accelX.toFixed(2)
                    unit: "m/s²"
                    valueColor: "#22d3ee"
                }

                SensorCell {
                    title: "AY"
                    value: telemetry.accelY.toFixed(2)
                    unit: "m/s²"
                    valueColor: "#22d3ee"
                }

                SensorCell {
                    title: "AZ"
                    value: telemetry.accelZ.toFixed(2)
                    unit: "m/s²"
                    valueColor: "#22d3ee"
                }
            }
        }

        
        // GYROSCOPE
        

        ColumnLayout {

            Layout.fillWidth: true

            spacing: 8

            Text {

                text: "GYROSCOPE"

                color: "#5d7b96"

                font.pixelSize: 11

                font.letterSpacing: 2
            }

            GridLayout {

                columns: 3

                Layout.fillWidth: true

                columnSpacing: 8

                rowSpacing: 8

                SensorCell {
                    title: "GX"
                    value: telemetry.gyroX.toFixed(2)
                    unit: "rad/s"
                    valueColor: "#4ade80"
                }

                SensorCell {
                    title: "GY"
                    value: telemetry.gyroY.toFixed(2)
                    unit: "rad/s"
                    valueColor: "#4ade80"
                }

                SensorCell {
                    title: "GZ"
                    value: telemetry.gyroZ.toFixed(2)
                    unit: "rad/s"
                    valueColor: "#4ade80"
                }
            }
        }

        
        // MAGNETOMETER
        

        ColumnLayout {

            Layout.fillWidth: true

            spacing: 8

            Text {

                text: "MAGNETOMETER"

                color: "#5d7b96"

                font.pixelSize: 11

                font.letterSpacing: 2
            }

            GridLayout {

                columns: 3

                Layout.fillWidth: true

                columnSpacing: 8

                rowSpacing: 8

                SensorCell {
                    title: "MX"
                    value: telemetry.magX.toFixed(1)
                    unit: "µT"
                    valueColor: "#fb923c"
                }

                SensorCell {
                    title: "MY"
                    value: telemetry.magY.toFixed(1)
                    unit: "µT"
                    valueColor: "#fb923c"
                }

                SensorCell {
                    title: "MZ"
                    value: telemetry.magZ.toFixed(1)
                    unit: "µT"
                    valueColor: "#fb923c"
                }
            }
        }

        
    }
}