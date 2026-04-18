import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Dashboard

RowLayout {
    spacing: 10

    // Depth Raw
    StatCard {
        Layout.fillWidth: true
        title: "Depth Raw"
        value: depthModel.depthRaw.toFixed(2)
        unit: "m"
    }

    // Depth Corrected
    StatCard {
        Layout.fillWidth: true
        title: "Depth Corrected"
        value: depthModel.depthCorrected.toFixed(2)
        unit: "m"
    }

    // Speed km/h
    StatCard {
        Layout.fillWidth: true
        title: "Speed"
        value: powerModel.speed.toFixed(1)
        unit: "km/h"
    }

    // Speed knots
    StatCard {
        Layout.fillWidth: true
        title: "Speed Knots"
        value: powerModel.speedKnots.toFixed(2)
        unit: "kn"
    }

    // Battery
    StatCard {
        Layout.fillWidth: true
        title: "Battery"
        value: powerModel.battery.toFixed(1)
        unit: "%"
    }
}