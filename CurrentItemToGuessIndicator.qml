import QtQuick 2.0

Item {
    property int isActive: 1
    Rectangle{
        id:activeIndicator
        width: 90
        height: 5
        color: (isActive?"#C06A15":"white");
    }
}
