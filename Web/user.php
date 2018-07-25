<?php

require_once ('./response.php');
require_once ('./db.php');
require_once ('./common.php');

class User extends Common {

    //检测是登陆还是注册
    public function typeCheck()
    {
        $username = $username = isset($_POST['user'])? $_POST['user'] : '';
        $password = isset($_POST['password'])? $_POST['password'] : '';

        if(empty($username)|| empty($password))
        {
            return Response::json(402,'获取用户信息失败!');
        }


        $type = isset($_POST['type'])? $_POST['type'] : '';
        if(empty($type))
        {
            return Response::json(403,'获取类型失败!');
        }else{

            if($type == "login")
            {
                $this->userlogin($username,$password);

            }else if($type = 'reg')
            {
                $this->userReg($username,$password);
            }
        }

    }

    //用户登陆
    public function userlogin($username,$password)
    {

        $sql = "select * from db_User where username = '$username' and password = '$password'";

        try{
            $connect = Db::getInstance()->connect();
        }catch (Exception $e)
        {
            return Response::json(405,'连接数据出错!');
        }

        $result = mysqli_query($connect,$sql);
        $users = array();

        while ($user = mysqli_fetch_assoc($result))
        {
            $users[] = $user;
        }

        if($users)
        {
            return Response::json(200,"获取用户信息成功",$users);
        }else
        {
            return Response::json(404,'无此用户!');
        }
    }

    //用户注册
    public function userReg($username,$password)
    {
        try{
            $connect = Db::getInstance()->connect();
        }catch (Exception $e)
        {
            return Response::json(405,'连接数据出错!');
        }

        //检测设备是否已注册
        $devid = $this->params['did'];
        $userNameSQL = "select * from db_User where deviceid='$devid'";
        $resultSet = mysqli_query($connect,$userNameSQL);
        if($us = mysqli_fetch_assoc($resultSet)){
            return Response::json(204,"该设备已经注册!",$us);
        }


        //检测用户名是否被占用
        $userNameSQL = "select * from db_User where userName='$username'";
        $resultSet = mysqli_query($connect,$userNameSQL);
        if(mysqli_num_rows($resultSet)>0){
            return Response::json(203,"用户名已经被占用!");
        }



        //用户注册
        $mm=60*10;//PHP的时间是按秒算的
        $ctimer = date('Y-m-d H:i:s',time());
        $etimer = date('Y-m-d H:i:s',strtotime($ctimer)+$mm);
        $devid = $this->params['did'];
        $sql = "insert into db_User (username,`password`,begintimer,endtimer,regtimer,deviceid) values('$username','$password','$ctimer','$etimer','$ctimer','$devid')";

        $result = mysqli_query($connect,$sql);

        if($result)
        {
            $sql = "select * from db_User where username = '$username' and password = '$password'";
            $resultuser = mysqli_query($connect,$sql);
            $users = array();
            while ($user = mysqli_fetch_assoc($resultuser))
            {
                $users[] = $user;
            }
            return Response::json(201,"注册成功!",$users);
        }else{
            return Response::json(202,"注册失败!");
        }
    }


}

$User = new User();
$User->check();
$User->typeCheck();