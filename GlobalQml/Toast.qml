import QtQuick 2.10
import QtGraphicalEffects 1.0

Item{
    id:m_toast

    property double toastWidth : width * 0.4
    property double toastHeight : toastWidth * 0.2
    property alias text :txt_nr.text

    signal toasFinish();

    onToastHeightChanged: {
        txt_nr.font.pointSize = toastHeight * 0.27
    }

    Component.onCompleted: {
        animation_show.start()
    }

    anchors.fill: parent

    Item{
        id:tostitem
        opacity: 0.0
        width: toastWidth
        height: toastHeight
        anchors.centerIn: parent

        Rectangle{
            id:tostBack
            radius: 2
            color: "#2B2B2D"
            anchors.fill: parent
        }

        DropShadow {
            anchors.fill: tostBack
            horizontalOffset: 2
            verticalOffset: 2
            radius: 8.0
            samples: 10
            color: "#90000000"
            source: tostBack
        }


        Text {
            id: txt_nr
            color: "#FAFBFD"
            font.bold: true
            anchors.centerIn: parent
        }

    }


    SequentialAnimation{
        id:animation_show

        ParallelAnimation{

            NumberAnimation {
                target: tostitem
                property: "anchors.verticalCenterOffset"
                from: m_toast.height / 3
                to: 0
                duration: 250
                easing.type: Easing.OutQuad
            }


            NumberAnimation {
                target: tostitem
                property: "opacity"
                from: 0.0
                to: 1.0
                duration: 150
                easing.type: Easing.OutQuad
            }
        }


        PauseAnimation { duration: 2000 }


        ParallelAnimation{

            NumberAnimation {
                target: tostitem
                property: "anchors.verticalCenterOffset"
                from: 0
                to: -(m_toast.height / 3)
                duration: 250
                easing.type: Easing.OutQuad
            }


            NumberAnimation {
                target: tostitem
                property: "opacity"
                from: 1.0
                to: 0.0
                duration: 150
                easing.type: Easing.OutQuad
            }
        }


        onStopped: {
            toasFinish()
            m_toast.destroy()
        }


    }




}
