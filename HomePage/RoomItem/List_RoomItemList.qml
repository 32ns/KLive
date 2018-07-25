import QtQuick 2.10
import Qt.labs.settings 1.0

Item {
    id:m_list_roomitemlist

    property string currentRoom : ""    //记录当前房间

    onVisibleChanged: {
        if(visible)
        {
            mainHeader.visible = true
        }
    }

    Settings {
          id: settings
          property bool set_LeftBack
          property bool set_RightBack
      }

    GridView{
        id:lv_itemlist
        anchors.fill: parent
        model: model_roomItemModel
        cellWidth  : parent.width / 2
        cellHeight : cellWidth
        delegate: Item_ItemList{
            width: lv_itemlist.cellWidth - 2
            height: lv_itemlist.cellHeight - 2
            img: image
            title: name
            iindex: index
        }
        onFlickStarted: {   //滑动速度
            var sd = (Math.abs(verticalVelocity)+500);
            flick(0,verticalVelocity < 0 ? sd : -sd )
        }

        onDragEnded: {  //上下拉刷新
            if(originY > contentY )
            {
                Live.getRoomItem(currentRoom)
            }else if(contentHeight>height && contentY-originY > contentHeight-height)
            {
                Live.getRoomItem(currentRoom)
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
        pageHome.pop()
        listStack.currentItem.forceActiveFocus()
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
