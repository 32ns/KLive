import QtQuick 2.0

Rectangle{
    id:m_mybutton

    signal clicked(var mouse)

    property alias text : txt_title.text
    property color defaultColor : "#C85A41"
    property color pressedColor : "#A7462F"
    property color textColor : "white"
    property alias fontSize : txt_title.font.pointSize

    implicitWidth: 150
    implicitHeight: 50

    color: ma_mouse.pressed ? pressedColor : defaultColor

    Text {
        id : txt_title
        anchors.centerIn: parent
        color: "white"
        font.family: mainFont.name
        text: qsTr("Button")
    }

    MouseArea{
        id:ma_mouse
        anchors.fill: parent
        Ripple{}

        onClicked: {
            m_mybutton.clicked(mouse)
        }
    }
}
