import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls 1.4
import Qt.labs.settings 1.0

Item {

    property int vindex : -1     //在model中的索引

    onVindexChanged: {

        videoStack.currentIndex = vindex
    }

    ExclusiveGroup{ id: videoGroup }    //互斥

    Settings {
        id: settings
        property bool set_JieMa
        property bool set_LeftBack
        property bool set_RightBack
        property bool set_JmpError       
    }


    SwipeView{
        id:videoStack
        anchors.fill: parent
        orientation: Qt.Vertical
        Repeater {
          model: model_roomItemModel.rowCount()
          Loader {
              active: SwipeView.isCurrentItem || SwipeView.isNextItem || SwipeView.isPreviousItem
              sourceComponent: VideoShow{
                    url: model_roomItemModel.getUrl(videoStack.currentIndex)
                    nicheng: model_roomItemModel.getName(videoStack.currentIndex)
                    exclusiveGroup: videoGroup
              }
          }
        }

        onCurrentItemChanged: {
            if(currentItem.item)
            {
                currentItem.item.checked = true
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

    //翻页
    Keys.onUpPressed: {
        if(videoStack.currentIndex > 0)
        {
            videoStack.currentIndex--
        }
    }

    Keys.onDownPressed: {
        if(videoStack.currentIndex < model_roomItemModel.rowCount() - 1)
        {
            videoStack.currentIndex++
        }
    }


    function backitem()
    {
        pageHome.pop()
        listStack.currentItem.forceActiveFocus()
    }


    /******************************************************************
        如果左右滑动全关闭后滑动切换也会关闭
    ******************************************************************/
    MouseArea{
        anchors.fill: parent
        property var pos1

        onDoubleClicked: {
            backitem()
        }

        onPressed: {
            pos1 = mouseX
            if(settings.set_LeftBack || settings.set_RightBack)
            {
                if(pos1<20 || pos1> parent.width - 20)
                {
                    mouse.accepted = true
                }else
                {
                    mouse.accepted = false
                }
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
