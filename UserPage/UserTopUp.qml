/******************************************************************
    用户充值
******************************************************************/
import QtQuick 2.0
import QtWebView 1.1

Item {

    WebView{
        anchors.fill: parent
        url: Live.getTopUpUrl()
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
