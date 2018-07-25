import QtQuick 2.10
import QtQuick.Controls 2.3

Item {
    id: it_jm

    property alias text : txt_title.text
    property alias checked : sw_select.checked

    Text{
        id:txt_title
        color: "#2d2b2b"
        text: "标题:"
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: parent.height * 0.28
        font.family: mainFont.name
    }

    MySwitch {
        id: sw_select      
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        height: parent.height
        width: 40
    }

    Rectangle{width: parent.width; height: 1; anchors.bottom: parent.bottom;color:"black"; opacity: 0.05}
}
