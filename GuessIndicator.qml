import QtQuick 2.0

Item {
    property string result_color: "red"
    Rectangle{
        id: rect
        width: 90
        height: 90
        color: result_color
        border.color: Qt.lighter("yellow")
        border.width: 1
    }
}
