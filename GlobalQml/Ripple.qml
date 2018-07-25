import QtQuick 2.0

/******************************************************************
    纯 QtQuick 实现点击涟漪特效
    MouseArea {
        Ripple { }
    }
******************************************************************/
Item {
    id: ripple

    anchors.fill: parent

    property alias clip: backgroundLayer.clip
    property real radius: 0
    property color color: "#22000000"
    property real maxRadius: parent
                             ? Math.sqrt(parent.width * parent.width + parent.height * parent.height)
                             : Math.sqrt(width * width + height * height)
    property real radiusAnimationRate: 0.048
    property real radiusTailAnimationRate: 0.48
    property real opacityAnimationDuration: 800

    readonly property real diameter: radius * 2
    property real centerX
    property real centerY

    Connections {
        target: ripple.parent
        ignoreUnknownSignals: true

        onPressed: {
            start(mouse);
        }

        onReleased: {
            stop();
        }

        onExited: {
            stop();
        }

        onCanceled: {
            stop();
        }
    }

    state: "NORMAL"

    states: [
        State { name: "NORMAL" },
        State { name: "ACTIVE" }
    ]

    function start(mouse) {
        ripple.state = "ACTIVE";
        ripple.centerX = mouse.x;
        ripple.centerY = mouse.y;
    }

    function stop() {
        ripple.state = "NORMAL";
    }


    Rectangle {
        id: backgroundLayer
        anchors.fill: parent
        color: "transparent"
        clip: true

        Rectangle {
            id: circle
            x: ripple.centerX - ripple.radius
            y: ripple.centerY - ripple.radius
            height: diameter; width: diameter
            radius: ripple.radius
            color: ripple.color
        }
    }

    transitions: [
        Transition {
            from: "NORMAL"; to: "ACTIVE"
            SequentialAnimation {
                ScriptAction {
                    script: {
                        ripple.opacity = 1;
                    }
                }
                NumberAnimation {
                    id: radius_animation
                    target: ripple; properties: "radius"
                    from: 0; to: maxRadius
                    duration: maxRadius / radiusAnimationRate
                    easing { type: Easing.OutQuad }
                }
            }
        },
        Transition {
            from: "ACTIVE"; to: "NORMAL"
            ParallelAnimation {
                NumberAnimation {
                    id: radius_tail_animation
                    target: ripple; properties: "radius"
                    to: maxRadius
                    duration: maxRadius / radiusTailAnimationRate
                    easing { type: Easing.Linear }
                }
                NumberAnimation {
                    id: opacity_animation
                    target: ripple; properties: "opacity"
                    to: 0
                    duration: opacityAnimationDuration
                    easing { type: Easing.InQuad }
                }
            }
        }
    ]
}
