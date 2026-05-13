import QtQuick
import Dashboard

Item {

    id: root

    property real heading: 0

    width: 260
    height: 260

    //
    // OUTER DIAL
    //

    Rectangle {

        anchors.fill: parent

        radius: width / 2

        color: "#0b0b0b"

        border.color: "#343434"

        border.width: 2
    }

    //
    // INNER DIAL
    //

    Rectangle {

        anchors.centerIn: parent

        width: parent.width - 18

        height: parent.height - 18

        radius: width / 2

        color: "#111111"

        border.color: "#1f1f1f"

        border.width: 1
    }

    //
    // OUTER TICK MARKS
    //

    Repeater {

        model: 72

        Rectangle {

            width: index % 2 === 0 ? 2 : 1

            height: index % 2 === 0 ? 12 : 6

            radius: 1

            color: index % 2 === 0
                   ? "#a0a0a0"
                   : "#5a5a5a"

            anchors.centerIn: parent

            transform: [

                Translate {
                    y: -root.width * 0.43
                },

                Rotation {
                    angle: index * 5
                    origin.x: 0
                    origin.y: root.width * 0.43
                }
            ]
        }
    }

    //
    // CARDINAL DIRECTIONS
    //

    Repeater {

        model: [

            { label: "N", angle: 0 },
            { label: "E", angle: 90 },
            { label: "S", angle: 180 },
            { label: "W", angle: 270 }
        ]

        Text {

            text: modelData.label

            color: modelData.label === "N"
                   ? "#dc2626"
                   : "#f5f5f5"

            font.pixelSize: 22

            font.bold: true

            font.family: "monospace"

            anchors.centerIn: parent

            transform: [

                Translate {
                    y: -root.width * 0.33
                },

                Rotation {
                    angle: modelData.angle
                    origin.x: 0
                    origin.y: root.width * 0.33
                }
            ]
        }
    }

    //
    // ROTATING NEEDLE
    //

    Item {

        anchors.fill: parent

        rotation: root.heading

        Behavior on rotation {

            NumberAnimation {

                duration: 120

                easing.type: Easing.InOutQuad
            }
        }

        //
        // NORTH NEEDLE
        //

        Rectangle {

            width: 4

            height: root.height * 0.28

            radius: 2

            color: "#dc2626"

            anchors.horizontalCenter: parent.horizontalCenter

            anchors.verticalCenter: parent.verticalCenter

            anchors.verticalCenterOffset: -height / 2
        }

        //
        // SOUTH NEEDLE
        //

        Rectangle {

            width: 4

            height: root.height * 0.16

            radius: 2

            color: "#4a4a4a"

            anchors.horizontalCenter: parent.horizontalCenter

            anchors.verticalCenter: parent.verticalCenter

            anchors.verticalCenterOffset: height / 2
        }
    }

    //
    // CENTER HUB
    //

    Rectangle {

        width: 20
        height: 20

        radius: 10

        color: "#d4d4d4"

        border.color: "#2a2a2a"

        border.width: 1

        anchors.centerIn: parent
    }

    Rectangle {

        width: 8
        height: 8

        radius: 4

        color: "#dc2626"

        anchors.centerIn: parent
    }

    //
    // DIGITAL HEADING DISPLAY
    //

    Rectangle {

        width: 110
        height: 40

        radius: 6

        color: "#141414"

        border.color: "#343434"

        border.width: 1

        anchors.horizontalCenter: parent.horizontalCenter

        anchors.bottom: parent.bottom

        anchors.bottomMargin: 16

        Text {

            anchors.centerIn: parent

            text: Math.round(root.heading) + "°"

            color: "#f5f5f5"

            font.pixelSize: 22

            font.bold: true

            font.family: "monospace"
        }
    }
}