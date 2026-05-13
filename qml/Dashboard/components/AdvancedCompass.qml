import QtQuick
import QtQuick.Shapes
import Dashboard
Item {

    id: root

    width: 320
    height: 320

    //
    // INPUT HEADING
    // 0 = NORTH
    // 90 = EAST
    // 180 = SOUTH
    // 270 = WEST
    //

    property real heading: 0

    //
    // COLORS
    //

    readonly property color backgroundColor: "#111827"
    readonly property color dialColor: "#1f2937"
    readonly property color tickColor: "#94a3b8"
    readonly property color textColor: "#e5e7eb"
    readonly property color northColor: "#ef4444"
    readonly property color accentColor: "#38bdf8"

    //
    // HELPERS
    //

    function normalize(v) {

        let n = v % 360

        if (n < 0)
            n += 360

        return n
    }

    function directionText(v) {

        const dirs = [
            "N", "NE", "E", "SE",
            "S", "SW", "W", "NW"
        ]

        return dirs[Math.round(normalize(v) / 45) % 8]
    }

    //
    // OUTER BODY
    //

    Rectangle {

        anchors.fill: parent

        radius: width / 2

        color: root.backgroundColor

        border.width: 2
        border.color: "#334155"
    }

    //
    // INNER DIAL
    //

    Rectangle {

        id: dial

        anchors.centerIn: parent

        width: parent.width - 24
        height: width

        radius: width / 2

        color: root.dialColor

        border.width: 1
        border.color: "#475569"
    }

    //
    // TICKS
    //

    Repeater {

        model: 72

        Rectangle {

            required property int index

            property int deg: index * 5

            property bool major: deg % 30 === 0

            width: major ? 3 : 1
            height: major ? 18 : 8

            radius: 2

            color: major
                   ? "#f8fafc"
                   : "#64748b"

            anchors.centerIn: dial

            antialiasing: true

            transform: [

                Rotation {

                    angle: parent.deg

                    origin.x: width / 2
                    origin.y: dial.height / 2
                },

                Translate {

                    y: -dial.height * 0.44
                }
            ]
        }
    }

    //
    // DEGREE LABELS
    //

    Repeater {

        model: 12

        Text {

            required property int index

            property int deg: index * 30

            visible: deg !== 0
                     && deg !== 90
                     && deg !== 180
                     && deg !== 270

            text: deg

            color: "#94a3b8"

            font.pixelSize: 12
            font.bold: true

            anchors.centerIn: dial

            transform: [

                Rotation {

                    angle: deg

                    origin.x: 0
                    origin.y: dial.height * 0.34
                },

                Translate {

                    y: -dial.height * 0.34
                }
            ]
        }
    }

    //
    // CARDINAL DIRECTIONS
    //

    Repeater {

        model: [

            { label: "N", angle: 0, color: "#ef4444" },
            { label: "E", angle: 90, color: "#f8fafc" },
            { label: "S", angle: 180, color: "#f8fafc" },
            { label: "W", angle: 270, color: "#f8fafc" }
        ]

        Text {

            required property var modelData

            text: modelData.label

            color: modelData.color

            font.pixelSize: 24
            font.bold: true

            anchors.centerIn: dial

            transform: [

                Rotation {

                    angle: modelData.angle

                    origin.x: 0
                    origin.y: dial.height * 0.39
                },

                Translate {

                    y: -dial.height * 0.39
                }
            ]
        }
    }

    //
    // NEEDLE LAYER
    // ONLY THIS ROTATES
    //

    Item {

        id: needleLayer

        anchors.fill: dial

        rotation: root.heading

        transformOrigin: Item.Center

        Behavior on rotation {

            NumberAnimation {

                duration: 180

                easing.type: Easing.OutCubic
            }
        }

        //
        // NORTH RED NEEDLE
        //

        Shape {

            width: 28
            height: 120

            anchors.centerIn: parent

            y: -40

            ShapePath {

                strokeWidth: 1
                strokeColor: "#ffffff40"

                fillColor: root.northColor

                startX: width / 2
                startY: 0

                PathLine {
                    x: width
                    y: height
                }

                PathLine {
                    x: width / 2
                    y: height - 20
                }

                PathLine {
                    x: 0
                    y: height
                }

                PathLine {
                    x: width / 2
                    y: 0
                }
            }
        }

        //
        // SOUTH NEEDLE
        //

        Shape {

            width: 20
            height: 90

            anchors.centerIn: parent

            y: 50

            rotation: 180

            opacity: 0.7

            ShapePath {

                strokeWidth: 1
                strokeColor: "#ffffff20"

                fillColor: "#475569"

                startX: width / 2
                startY: 0

                PathLine {
                    x: width
                    y: height
                }

                PathLine {
                    x: width / 2
                    y: height - 18
                }

                PathLine {
                    x: 0
                    y: height
                }

                PathLine {
                    x: width / 2
                    y: 0
                }
            }
        }

        //
        // CENTER CAP
        //

        Rectangle {

            anchors.centerIn: parent

            width: 22
            height: 22

            radius: 11

            color: "#cbd5e1"

            border.width: 3
            border.color: "#334155"
        }

        Rectangle {

            anchors.centerIn: parent

            width: 8
            height: 8

            radius: 4

            color: root.accentColor
        }
    }

    //
    // DIGITAL READOUT
    //

    Rectangle {

        width: 120
        height: 54

        radius: 10

        color: "#0f172a"

        border.width: 1
        border.color: "#334155"

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 18

        Column {

            anchors.centerIn: parent

            spacing: -2

            Text {

                text: root.normalize(root.heading).toFixed(1) + "°"

                color: root.accentColor

                font.pixelSize: 24
                font.bold: true
                font.family: "monospace"

                anchors.horizontalCenter: parent.horizontalCenter
            }

            Text {

                text: root.directionText(root.heading)

                color: "#f8fafc"

                font.pixelSize: 13
                font.bold: true

                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}