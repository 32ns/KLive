import QtQuick 2.10
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.0

Item {

    property alias logo : img_logo.source
    property string platformTitle : ""
    property string platformName : ""
    property string allSum : ""

    //Logo
    Item{
        id:itm_logo
        height: parent.height - parent.height * 0.5
        width: height
        anchors.centerIn: parent
        anchors.verticalCenterOffset: - (txt_name.height) / 2

        //图标
        Image{
            id:img_logo
            visible: false
            anchors.fill: parent
        }

        //遮罩物
        Rectangle{
            id: mask
            anchors.fill: parent
            radius: 10
        }

        //遮罩
        OpacityMask {
            anchors.fill: parent
            source: img_logo
            maskSource: mask
        }


        //加载器
        BusyIndicator {
            id: busyIndicator
            running: false
            anchors.centerIn: parent
            width: img_logo.width
            height: img_logo.height
        }
    }

    //阴影
    DropShadow {
        anchors.fill: itm_logo
        horizontalOffset: 0
        verticalOffset: 0
        radius: 8.0
        samples: 25
        color: "#50000000"
        source: itm_logo
    }





    Text {
        id: txt_name
        color: "#3a3939"
        opacity: 0.9
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: height / 2
        font.pointSize: 10
        font.family: mainFont.name
        text: platformTitle +" ("+allSum+")"
    }




    MouseArea{
        anchors.fill: parent
        onClicked: {
            busyIndicator.running = true
            Live.getUserState(platformName)
            m_page_home.croomtitle = platformTitle
        }
    }


    Connections{
        target: Live
        onSig_RoomItemCreateSucceed : { //房间项目创建成功
            busyIndicator.running = false
        }

        onSig_UserState : {
            switch(state)
            {

            case 999 :
                busyIndicator.running = false
            break;

            }
        }


    }

}
