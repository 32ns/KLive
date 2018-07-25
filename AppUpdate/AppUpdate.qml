import QtQuick 2.0
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.0

Item {
    property string updateinfo:""
    property string updateurl:""

    //背景
    Rectangle{
        id:back
        opacity: 0.4
        color: "#afacac"
        anchors.fill: parent
    }

    //阴影
    DropShadow {
        anchors.fill: msgBack
        horizontalOffset: 3
        verticalOffset: 3
        radius: 8.0
        samples: 16
        color: "#80000000"
        source: msgBack
    }

    //事件
    Connections
    {
        target: Live
        onSig_downloadProgress :{            
            txt_jindutiao.text = Math.round(all * 100 / current)
            jindutiao.width = btn_update.width * (all / current)
        }        
    }

    //对话框
    Rectangle{
        id:msgBack
        clip: true
        width: mainWindow.width * 0.7
        height: txt_updateinfo.height + btn_update.height
        anchors.centerIn: parent
        TextArea {
            id: txt_updateinfo
            text: "\n\n" + updateinfo + "点击下载:  "+ updateurl +"\n\n"
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if(updateurl.length > 1)
                    {
                        Qt.openUrlExternally(updateurl)
                    }
                }
            }
        }

        Button{
            id:btn_update
            clip: true
            width: parent.width
            height: 50
            anchors.bottom: parent.bottom
            text: "点击更新"
            onClicked: {
                Live.startUpdate()
                btn_update.text = "0"
                btn_update.enabled = false
            }

            Rectangle{
                id:jindutiao
                width: 0
                height: parent.height
                color: "#b1e65c"
            }
            Text {
                id: txt_jindutiao
                anchors.centerIn: parent
            }
        }

    }


}
