import QtQuick
import Dashboard

Text {

    property string title: ""

    text: "// " + title

    color: Theme.textSecondary

    font.pixelSize: 11

    font.letterSpacing: 4

    font.family: "monospace"
}