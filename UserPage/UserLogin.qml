import QtQuick 2.10
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import "../GlobalQml"

Item {
    id:m_userlogin
    focus: true
    state: "LoginState"

    Timer{
        id:timer
        interval: 3000
        onTriggered: txt_tishi.text = ""
    }


    //背景
    Rectangle{
        id:back
        color: "#2B3238"
        anchors.fill: parent
    }

    Text {
        id: txt_tishi
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.1
        color: "#C85A41"
        font.pointSize: 14
        font.family: mainFont.name
    }


    Column{
        id: cl_Column
        spacing: 5
        width: parent.width * 0.8
        height: parent.height * 0.4
        anchors.centerIn: parent


        Rectangle{
            width: parent.width
            height: 50
            Row{
                anchors.fill: parent
                Image {
                    id: img_icouser
                    opacity: 0.7
                    height: parent.height * 0.7
                    fillMode: Image.PreserveAspectFit
                    width: height * 2
                    source: "qrc:/Res/UserPage/user.png"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Rectangle{width: 1; height: parent.height ; color: "black"; opacity: 0.2}
                TextField{
                    id:tf_user
                    height: parent.height
                    width: parent.width - img_icouser.width - 1
                    background: Item{}
                    selectByMouse: true
                    placeholderText: "请输入用户名"
                    maximumLength: 20
                    font.capitalization: Font.AllLowercase
                    font.pointSize: height * 0.25
                }
            }
        }
        Rectangle{            
            width: parent.width
            height: 50
            Row{
                anchors.fill: parent
                Image {
                    id: img_icopass
                    opacity: 0.7
                    height: parent.height * 0.7
                    fillMode: Image.PreserveAspectFit
                    width: height * 2
                    source: "qrc:/Res/UserPage/password.png"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Rectangle{width: 1; height: parent.height ; color: "black"; opacity: 0.2}
                TextField{
                    id:tf_pass
                    height: parent.height
                    width: parent.width - img_icouser.width - 1
                    background: Item{}
                    echoMode: TextInput.Password
                    selectByMouse: true
                    placeholderText: "请输入密码"
                    maximumLength: 20
                    font.pointSize: height * 0.25
                }
            }
        }

        Rectangle{
            id:rl_reposs
            width: parent.width
            height: 50
            visible: false
            Row{
                anchors.fill: parent
                Image {
                    id: img_icorepass
                    opacity: 0.7
                    height: parent.height * 0.7
                    fillMode: Image.PreserveAspectFit
                    width: height * 2
                    source: "qrc:/Res/UserPage/password.png"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Rectangle{width: 1; height: parent.height ; color: "black"; opacity: 0.2}
                TextField{
                    id:tf_repass
                    height: parent.height
                    width: parent.width - img_icouser.width - 1
                    background: Item{}
                    echoMode: TextInput.Password
                    selectByMouse: true
                    placeholderText: "请输再次入密码"
                    maximumLength: 20
                    font.capitalization: Font.AllLowercase
                    font.pointSize: height * 0.25
                }
            }
        }


        MyButton{
            id:btn_button
            width: parent.width
            height: 50
            fontSize: height * 0.3
            text: "登陆"
            onClicked: {

                if(m_userlogin.state == "LoginState")
                {
                    f_login()
                }else if(m_userlogin.state == "RegisterState")
                {
                    f_regist()
                }

            }

        }

    }




    Row{
        width: parent.width * 0.5
        height: 50
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height * 0.2

        Text{
            width: parent.width / 2
            height: parent.height
            text: "登陆"
            font.family: mainFont.name
            font.pointSize: 15
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: "#f1f0f0"
            MouseArea{
                anchors.fill: parent
                onClicked: m_userlogin.state = "LoginState"
            }
        }
        Text{
            width: parent.width / 2
            height: parent.height
            text: "注册"
            font.family: mainFont.name
            font.pointSize: 15
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: "#f1f0f0"
            MouseArea{
                anchors.fill: parent
                onClicked: m_userlogin.state = "RegisterState"
            }
        }
    }




    //登陆
    function f_login()
    {
        if(tf_user.text.trim()=="" || tf_pass.text.trim()=="")
        {
            f_showtishi("用户名或密码不能为空!")
            return;
        }

        if(tf_user.text.trim().length < 5 || tf_pass.text.trim().length < 5)
        {
            f_showtishi("用户名和密码都应大于5位!")
            return;
        }
        Live.loginUser(tf_user.text.trim(),Live.getPassCrypto(tf_pass.text.trim()))
    }

    //注册
    function f_regist()
    {
        if(tf_user.text.trim()=="" || tf_pass.text.trim()=="")
        {
            f_showtishi("用户名或密码不能为空!")
            return;
        }
        if(tf_user.text.trim().length < 5 || tf_pass.text.trim().length < 5)
        {
            f_showtishi("用户名和密码都应大于5位!")
            return;
        }
        if(tf_pass.text.trim() != tf_repass.text.trim())
        {
            f_showtishi("两次密码不相同!请重新输入");
            return;
        }

        Live.regUser(tf_user.text.trim(),tf_pass.text.trim())
    }

    //显示提示
    function f_showtishi(title)
    {
        txt_tishi.text = title
        timer.start()
    }








    states: [
        State {
            name: "LoginState"
            PropertyChanges {
                target: rl_reposs
                visible : false
            }
            PropertyChanges {
                target: btn_button
                text : "登陆"
            }
        },
        State {
            name: "RegisterState"
            PropertyChanges {
                target: rl_reposs
                visible : true
            }
            PropertyChanges {
                target: btn_button
                text : "注册"
            }
        }
    ]






    Connections{
        target: Live
        onSig_UserState : {
           switch(state)
           {

           case 203 :

               txt_tishi.text = title

           break;

           case 204 :
               txt_tishi.text = title
           break;

           case 404 :
               txt_tishi.text = title
           break;

           case 888 :
               backitem()
               break;

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
