<?php

/*
 * 数据库单例模式
 */

class Db {
    static private $_instance;
    static private $_connectSource;

    static public function getInstance()
    {
        if(!(self::$_instance instanceof self))
        {
            self::$_instance = new self();
        }
        return self::$_instance;
    }
    /*连接数据库*/
    public function connect()
    {
        if(!self::$_connectSource)
        {
            self::$_connectSource = mysqli_connect('127.0.0.1','root','12345678','klive',3306);
            if(!self::$_connectSource)
            {
                throw new Exception('mysql connect error'.mysqli_error());
            }
            mysqli_set_charset(self::$_connectSource,"utf8");
        }

        return self::$_connectSource;
    }


}
