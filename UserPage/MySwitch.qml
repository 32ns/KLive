import QtQuick 2.0
/******************************************************************
    根据宽度缩放大小,跟高度没关系
******************************************************************/
Item {
    id: toggleswitch

    property bool checked
    property int onwidth : background.width - knob.width + 2

    onCheckedChanged: {
        checked ? toggleswitch.state = "on" : toggleswitch.state = "off"
    }


    Rectangle {
        id: background
        width: parent.width - 2
        height: knob.height / 2
        color: checked ? "#64acea" : "#90343436"
        radius: height / 2
        anchors.centerIn: parent
    }

    Rectangle {
        id: knob
        height: parent.height * 0.4
        width: height
        radius: height / 2
        color: "white"
        border.width: 1
        border.color: "#55000000"
        anchors.verticalCenter: parent.verticalCenter
    }


    states: [
        State {
            name: "on"
            PropertyChanges { target: knob; x: onwidth }
        },
        State {
            name: "off"
            PropertyChanges { target: knob; x: 0 }
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "x"; easing.type: Easing.InOutQuad; duration: 200 }
    }

    MouseArea {
        anchors.fill: parent
        drag.target: knob; drag.axis: Drag.XAxis; drag.minimumX: 0; drag.maximumX: onwidth
        onClicked: checked = !checked
    }
}
