import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Dashboard

ApplicationWindow {

    visible: true

    width: 1400
    height: 800

    title: "USV Heading"

    color: "#020617"

    RowLayout {

        anchors.fill: parent

        anchors.margins: 10

        spacing: 10

        OrientationPanel {

            Layout.preferredWidth: 320

            Layout.fillHeight: true
        }

        PanelFrame {

            Layout.fillWidth: true

            Layout.fillHeight: true
        }

        PanelFrame {

            Layout.preferredWidth: 320

            Layout.fillHeight: true
        }
    }
}