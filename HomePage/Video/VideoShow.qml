import QtQuick 2.10
import QtQuick.Controls 1.4
import QtQuick.Controls 2.3
import QtAV 1.7

Item {

    id:m_videoshow
    focus: true

    property alias url : player.source
    property alias nicheng : txt_nc.text


    Component.onDestruction: {
        player.stop()
    }

    Component.onCompleted: {

        if(Live.checkUserDate())
        {
            backitem()
            backitem()
        }
    }


    /******************************************************************
        互斥-为了只播放一个窗口
    ******************************************************************/
    property bool checked: false
    property ExclusiveGroup exclusiveGroup: null

    onExclusiveGroupChanged: {
        if (exclusiveGroup)
        {
            exclusiveGroup.bindCheckable(m_videoshow)
        }
    }


    /******************************************************************
        播放暂停
    ******************************************************************/
    onCheckedChanged: {
        if(checked)
        {
            player.play()
            console.log("当前播放:"+url)
        }else
        {
            player.pause()
            videoOutput.visible = true
        }

    }

    /******************************************************************
        背景
    ******************************************************************/
    Rectangle{
        anchors.fill: parent
        color: "black"
    }


    /******************************************************************
        视频输出
    ******************************************************************/
    VideoOutput2{
        id:videoOutput
        visible: false
        anchors.fill: parent
        source: player
        fillMode: VideoOutput.Stretch

    }


    /******************************************************************
        播放器
    ******************************************************************/
    AVPlayer{
        id:player
        onError: {
            if(videoStack.currentIndex < model_roomItemModel.rowCount() && settings.set_JmpError)
            {
                videoStack.currentIndex++
            }
        }

        onStatusChanged: {
            switch(status)
            {
            case MediaPlayer.Loaded : {
                busyIndicator.visible = false
                videoOutput.visible = true
            }break;

            }
        }


        onSourceChanged: {
            switch(Qt.platform.os)
            {
            case "windows" :  settings.set_JieMa ? videoCodecPriority = ["D3D11"] : videoCodecPriority = ["FFmpeg"]
                break
            case "osx" :  settings.set_JieMa ? videoCodecPriority = ["VideoToolbox"] : videoCodecPriority = ["FFmpeg"]
                break
            case "android" :  settings.set_JieMa ? videoCodecPriority = ["MediaCodec"] : videoCodecPriority = ["FFmpeg"]
                break
            case "ios" :  settings.set_JieMa ? videoCodecPriority = ["VideoToolbox"] : videoCodecPriority = ["FFmpeg"]
                break

            default : videoCodecPriority = ["FFmpeg"]
                break
            }
        }




    }



    /******************************************************************
        加载标识
    ******************************************************************/
    //缓冲标识
    BusyIndicator {
        id: busyIndicator
        width: parent.width * 0.2
        height: width
        anchors.centerIn: parent
    }


    /******************************************************************
        昵称
    ******************************************************************/
    Text {
        id: txt_nc
        color: "#f3f2f2"
        opacity: 0.6
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 20
        font.family: mainFont.name
    }

    /******************************************************************
        直播标识
    ******************************************************************/
    Rectangle{
    id:img_live
    anchors.top: parent.top
    anchors.right: parent.right
    anchors.rightMargin: 10
    anchors.topMargin: 20
    width: parent.width * 0.08
    height: width * 0.5
    radius: width / 2
    color: "red"
    Text{
        anchors.centerIn: parent
        font.pointSize: parent.height * 0.5
        text: "KLive"
        color: "white"
        font.family: mainFont.name
    }

    SequentialAnimation{
        id:liveAnimation
        running: true
       loops: -1

        NumberAnimation {
            target: img_live
            property: "opacity"
            to: 0.1
            duration: 1500
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: img_live
            property: "opacity"
            to: 1.0
            duration: 2500
            easing.type: Easing.InOutQuad
            }
        }

    }



}
