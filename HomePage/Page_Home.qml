import QtQuick 2.10
import QtQuick.Controls 2.3
import "../HomePage/RoomItem"
import "../HomePage/RoomList"
import "../HomePage/Video"

Item {
    id:m_page_home

    property alias depth : listStack.depth
    property var toast : null
    property bool isShowUserLogin : false   //标识是否已经显示了登陆窗口
    property string croomtitle : "" //当前房间名


    StackView{
        id:listStack
        anchors.fill: parent
        initialItem: "qrc:/HomePage/RoomList/List_RoomList.qml"
    }



    //Live事件
    Connections{
        target: Live

        onSig_RoomItemCreateSucceed : { //房间项创建成功            
            if(itemsum < 1)
            {
                mainWindow.currentItemTitle = "KLive"
                showToast("该房间没有主播在线!")
            }else
            {
                if(listStack.depth == 2)   //本来就在这页
                {
                    return;
                }
                listStack.push("qrc:/HomePage/RoomItem/List_RoomItemList.qml")
                listStack.currentItem.currentRoom = roomname
                mainWindow.currentItemTitle = croomtitle
                listStack.currentItem.forceActiveFocus()
            }
        }

        onSig_UserState : { //用户状态返回
            switch(state)
            {
                case 0 :    //没有登陆
                    if(!isShowUserLogin)
                    {
                        isShowUserLogin = true
                        listStack.push("qrc:/UserPage/UserLogin.qml")
                        mainWindow.currentItemTitle = "登陆"
                    }

                break;
                case 404 :     //用户或密码错误
                    if(!isShowUserLogin)
                    {
                        isShowUserLogin = true
                        listStack.push("qrc:/UserPage/UserLogin.qml")
                        mainWindow.currentItemTitle = "登陆"
                    }
                break;

                case 999 :
                    if(isShowUserLogin)
                    {
                       listStack.pop()
                    }

                    showToast("用户已过期")

                    listStack.push("qrc:/UserPage/UserTopUp.qml")
                    mainWindow.currentItemTitle = "用户充值"
                    listStack.currentItem.forceActiveFocus()

                break;

            }
        }

        onSig_Update : {
            listStack.push("qrc:/AppUpdate/AppUpdate.qml")
            listStack.currentItem.updateinfo = msg
            listStack.currentItem.updateurl = url
        }


    }


    //提示框
    function showToast(content) {
        if(toast) return;
        var component = Qt.createComponent("qrc:/GlobalQml/Toast.qml");
        if (component.status === Component.Ready) {
            toast = component.createObject(m_page_home);
            toast.text = content;
        }
    }


    //给main用来返回的
    function pop()
    {
        if(listStack.depth > 1)
        {
            listStack.pop()
            isShowUserLogin = false
        }
        if(listStack.depth == 1)
        {
            mainWindow.currentItemTitle = "KLive"
            Live.getRoomList()
        }
    }




}
