pragma Singleton

import QtQuick

QtObject {

    //
    // BACKGROUNDS
    //

    readonly property color bgPrimary: "#050505"
    readonly property color bgSecondary: "#0b0b0b"

    //
    // PANELS
    //

    readonly property color panel: "#111111"
    readonly property color panelElevated: "#1c1c1c"

    //
    // BORDERS
    //

    readonly property color border: "#343434"
    readonly property color borderStrong: "#3a3a3a"

    //
    // TEXT
    //

    readonly property color textPrimary: "#f5f5f5"
    readonly property color textSecondary: "#a0a0a0"
    readonly property color textMuted: "#5a5a5a"

    //
    // RED ACCENT
    //

    readonly property color accentRed: "#dc2626"
    readonly property color accentRedDark: "#991b1b"

    //
    // STATUS
    //

    readonly property color statusActive: "#f5f5f5"
    readonly property color statusInactive: "#dc2626"
}