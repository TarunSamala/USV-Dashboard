import QtQuick

Item {

    id: root

    property real heading: 0

    width: 260
    height: 260

    Rectangle {

        anchors.fill: parent

        radius: width / 2

        color: "#050b16"

        border.color: "#1e293b"

        border.width: 2
    }

    // OUTER RING
    Repeater {

        model: 72

        Rectangle {

            width: index % 2 === 0 ? 2 : 1
            height: index % 2 === 0 ? 14 : 8

            color: "#94a3b8"

            radius: 1

            anchors.centerIn: parent

            y: 10

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

    // CARDINAL DIRECTIONS
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
                   ? "#ef4444"
                   : "#e2e8f0"

            font.pixelSize: 24

            font.bold: true

            font.family: "monospace"

            anchors.centerIn: parent

            transform: [

                Translate {
                    y: -root.width * 0.34
                },

                Rotation {
                    angle: modelData.angle
                    origin.x: 0
                    origin.y: root.width * 0.34
                }
            ]
        }
    }

    // ROTATING NEEDLE
    Item {

        anchors.fill: parent

        rotation: root.heading

        Behavior on rotation {

            NumberAnimation {

                duration: 120

                easing.type: Easing.InOutQuad
            }
        }

        Rectangle {

            width: 4

            height: root.height * 0.30

            radius: 2

            color: "#22d3ee"

            anchors.horizontalCenter: parent.horizontalCenter

            anchors.verticalCenter: parent.verticalCenter

            anchors.verticalCenterOffset: -height / 2
        }

        Rectangle {

            width: 4

            height: root.height * 0.18

            radius: 2

            color: "#334155"

            anchors.horizontalCenter: parent.horizontalCenter

            anchors.verticalCenter: parent.verticalCenter

            anchors.verticalCenterOffset: height / 2
        }
    }

    // CENTER HUB
    Rectangle {

        width: 22
        height: 22

        radius: 11

        color: "#e2e8f0"

        anchors.centerIn: parent
    }

    Rectangle {

        width: 10
        height: 10

        radius: 5

        color: "#22d3ee"

        anchors.centerIn: parent
    }

    // DIGITAL HEADING
    Rectangle {

        width: 120
        height: 42

        radius: 6

        color: "#020617"

        border.color: "#1e293b"

        anchors.horizontalCenter: parent.horizontalCenter

        anchors.bottom: parent.bottom

        anchors.bottomMargin: 18

        Text {

            anchors.centerIn: parent

            text: Math.round(root.heading) + "°"

            color: "#e2e8f0"

            font.pixelSize: 24

            font.bold: true

            font.family: "monospace"
        }
    }
}