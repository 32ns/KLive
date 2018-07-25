import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import Qt.labs.settings 1.0
import "HomePage"
import "UserPage"

ApplicationWindow {
    id:mainWindow
    visible: true
    width: 720
    height: 1280
    title: qsTr("KLive")
    color: "black"

    background: Rectangle{ color: "#f5f0f0";anchors.fill: parent; }

    property alias currentItemTitle : lb_CurrentItem.text

    FontLoader{id:mainFont;source: "qrc:/Res/Font/android.ttf"}

    header:ToolBar{
        id:mainHeader

        ToolButton {
            id: toolButton_back
            height: parent.height
            width: height
            onClicked: {
                if(mainLoader.currentIndex!=0)
                {                    
                    mainLoader.currentIndex = 0
                    mainLoader.currentItem.forceActiveFocus()                    
                }else
                {
                    pageHome.pop()
                }
            }
            background: Image{
                width: toolButton_back.height * 0.4
                height: width
                anchors.centerIn: parent
                opacity: (pageHome.depth == 1) && mainLoader.currentIndex == 0 ? 0.0 : 1.0
                source: "qrc:/Res/HomePage/back.png"                
            }
        }

        Label {
            id:lb_CurrentItem
            anchors.centerIn: parent
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            font.pointSize: parent.height * 0.3
            text: "KLive"
            font.family: mainFont.name
        }

        ToolButton {
            id: toolButton_setup
            height: parent.height
            width: height
            anchors.right: parent.right
            onClicked: {
                mainLoader.setCurrentIndex(1)
                mainLoader.currentItem.forceActiveFocus()
            }
            background: Image{
                width: toolButton_back.height * 0.4
                height: width
                anchors.centerIn: parent
                opacity: toolButton_setup.pressed ? 0.4 : 0.6
                source: "qrc:/Res/HomePage/setup.png"
            }
        }
    }


    SwipeView{
        id:mainLoader
        interactive: false
        anchors.fill: parent
        Page_Home{
            id:pageHome
        }
        UserPage{
            id:pageUser
        }        
    }





}
