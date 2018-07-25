import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Item {
    id:m_list_roomlist

    ColumnLayout{
        anchors.fill: parent

        SwipeView{
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 0.25

            Repeater{
                model: model_Ad
                Image{
                    source: img
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            if(url.length > 0)
                            {
                                Qt.openUrlExternally(url)
                            }
                        }
                    }
                }
            }

        }

        GridView{
            id:lv_roomlist
            clip: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: model_Room
            cellWidth  : parent.width / 4
            cellHeight : cellWidth
            delegate: Item_RoomItem{
                width: parent.width / 4
                height: lv_roomlist.cellHeight
                logo: image
                platformTitle: platform
                platformName: address
                allSum: anchor
            }

            onFlickStarted: {   //滑动速度
                var sd = (Math.abs(verticalVelocity)+500);
                flick(0,verticalVelocity < 0 ? sd : -sd )
            }

            onDragEnded: {  //上下拉刷新
                if(originY > contentY )
                {
                    Live.getRoomList()
                }else if(contentHeight>height && contentY-originY > contentHeight-height)
                {
                    Live.getRoomList()
                }
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

}
