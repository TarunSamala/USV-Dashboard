import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Dashboard

RowLayout {
    spacing: 10

    StatCard {
        Layout.fillWidth: true
        title: "Speed"
        value: powerModel.speed.toFixed(1)
        unit: "km/h"
    }

    StatCard {
        Layout.fillWidth: true
        title: "Battery"
        value: powerModel.battery.toFixed(1)
        unit: "%"
    }

    StatCard {
        Layout.fillWidth: true
        title: "Power"
        value: powerModel.powerHistory.length > 0
               ? powerModel.powerHistory[powerModel.powerHistory.length-1].toFixed(1)
               : "0"
        unit: "W"
    }
}