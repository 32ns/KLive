import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {

    Connections{
        target: Live
        onSig_UserState : {
           switch(state)
           {

           case 888 :
               txt_username.text = Live.getUserInfo_username()
               txt_endtimer.text = Live.getUserInfo_endtimer()
               break;

           case 999 :
               txt_username.text = Live.getUserInfo_username()
               txt_endtimer.text = Live.getUserInfo_endtimer()
               break;

           }
        }

    }

    Rectangle{
        id:back
        anchors.fill: parent
        color: "#6aabe8"
    }


    Column{
        anchors.fill: parent

        Item{width: parent.width;height: parent.height * 0.17}
        Loader{
            sourceComponent: tx_img
            height: parent.height * 0.4
            width: height
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Item{width: parent.width;height: parent.height * 0.08}

        Text {
            id: txt_username
            color: "white"
            font.pointSize: 12
            font.family: mainFont.name
            text: Live.getUserInfo_username()
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Item{width: parent.width;height: 4}

        Text {
            id: txt_endtimer
            color: "white"
            font.pointSize: 12
            font.family: mainFont.name
            text: Live.getUserInfo_endtimer()
            anchors.horizontalCenter: parent.horizontalCenter
        }

    }


    Component{
        id:tx_img
        Item{
            anchors.fill: parent
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle{
                anchors.fill: parent
                radius: width / 2
                border.width: 2
                border.color: "#20000000"
            }

            Image {
                id: img_touxiang
                source: "qrc:/Res/load.jpg"
                visible: false
            }

            Rectangle{
                id:imgmask
                visible: false
                radius: width / 2
                width: parent.width - 4
                height: parent.height - 4
            }

            OpacityMask {
                width: imgmask.width
                height: imgmask.height
                source: img_touxiang
                maskSource: imgmask
                anchors.centerIn: parent
            }

        }

    }

}
