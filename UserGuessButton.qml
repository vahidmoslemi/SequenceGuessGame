import QtQuick 2.0

Item {
    id:mainItem
    property string label_text: "My Button"
    signal clicked(real xPosition, real yPosition)

    Rectangle{
        id: btn
        width: 90
        height: 90
        color: "#4AB8F2"
        Text {
            id: label
            text: qsTr(label_text)
            anchors.horizontalCenter: btn.horizontalCenter
            anchors.verticalCenter: btn.verticalCenter
            font.pixelSize: 20
        }
        MouseArea{
            id: mouseEventHadler
            anchors.fill: parent
            onPressedChanged: {
                if(pressed)
                {
                    btn.color = Qt.lighter("gray");
                }
                else
                {
                    btn.color = "#4AB8F2";
                }
            }
            onClicked: mainItem.clicked(mouse.x,mouse.y)
        }
    }
}
