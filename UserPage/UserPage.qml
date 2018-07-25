import QtQuick 2.10
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0

Item {

    property bool isok

    Settings {
          id: settings
          property alias set_JieMa : us_jiema.checked
          property alias set_LeftBack : us_leftback.checked
          property alias set_RightBack : us_rightback.checked
          property alias set_JmpError : us_jmperr.checked
      }    

    ColumnLayout{
        anchors.fill: parent


        /******************************************************************
            头像部分
        ******************************************************************/
        UserInfoBar{
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 0.3
            MouseArea{anchors.fill: parent}
        }

        /******************************************************************
            设置部分
        ******************************************************************/
        Column {
            Layout.fillWidth : true
            Layout.fillHeight: true
            Layout.topMargin: 20

            UserSetingsItem{
                id:us_jiema
                width: parent.width * 0.9
                height: 45
                text: "硬解码:"
                anchors.horizontalCenter: parent.horizontalCenter;
            }

            UserSetingsItem{
                id:us_jmperr
                width: parent.width * 0.9
                height: 45
                text: "错误跳过:"
                checked: true
                anchors.horizontalCenter: parent.horizontalCenter;
            }

            UserSetingsItem{
                id:us_leftback
                width: parent.width * 0.9
                height: 45
                checked: true
                text: "左滑返回:"
                anchors.horizontalCenter: parent.horizontalCenter;
            }

            UserSetingsItem{
                id:us_rightback
                width: parent.width * 0.9
                height: 45
                checked: true
                text: "右滑返回:"
                anchors.horizontalCenter: parent.horizontalCenter;
            }


        }

    }


    //后退
    Keys.onBackPressed: {
        backitem()
    }
    Keys.onEscapePressed: {
        backitem()
    }


    function backitem()
    {
        mainLoader.currentIndex = 0
        mainLoader.currentItem.forceActiveFocus()
    }

    MouseArea{
        anchors.fill: parent
        property var pos1
        onPressed: {
            pos1 = mouseX
            if(pos1<20 || pos1> parent.width - 20)
            {
                mouse.accepted = true
            }else
            {
                mouse.accepted = false
            }
        }

        onReleased: {
            if(settings.set_LeftBack  && pos1<20&&mouseX>40)
            {
                backitem()
            }
            else if(settings.set_RightBack  && pos1> parent.width - 20&& mouseX< parent.width - 40)
            {
                backitem()
            }
        }
    }

}
