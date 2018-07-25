import QtQuick 2.10
import QtQuick.Controls 2.3


Item {

    property alias img : img_logo.source
    property alias title : txt_name.text
    property string iindex : ""

    Image {
        id: img_logo
        anchors.fill: parent

        Image {
            id: img_default
            anchors.fill: parent
            source: "qrc:/Res/load.jpg"
        }

        onStatusChanged: {
            if(img_logo.status == Image.Ready)
            {
                img_default.visible = false
            }
        }
    }

    Image {
        source: "qrc:/Res/RoomItemList/ic_live.png"
        width: parent.width * 0.1
        height: width * 0.5
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 10
    }


    Rectangle{
        id:txtback
        width: parent.width
        height: parent.height *0.1
        opacity: iindex == "0" ? 0.5 : 0.2
        color: "black"
        anchors.bottom: parent.bottom
    }

    Text {
        id: txt_name
        color: "white"
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: (txtback.height - height) / 2
        font.pointSize: parent.width * 0.045
        font.family: mainFont.name
    }

    MouseArea{
        anchors.fill: parent
        onClicked: {
            listStack.push("qrc:/HomePage/Video/VideoWindow.qml")
            listStack.currentItem.vindex = iindex
            listStack.currentItem.forceActiveFocus()
            mainHeader.visible = false
        }
    }

}
