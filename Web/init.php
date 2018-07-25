<?php

require_once ('./common.php');

class Init extends Common
{
    public function index()
    {
        $this->check();
    }

    public function checkVersion()
    {
        $this->appinfo = $this->getApp($this->params['app_type']);

        if(floatval($this->params['version_id']) < floatval($this->appinfo['version_id']))
        {
            return Response::json(1,"发现新版本",$this->appinfo);
        }else
        {
            $ad = $this->getAd();
            $arr = array('url'=> $this->appinfo['videoUrl'],'ad'=>$ad,'topup'=>$this->appinfo['topup'],'appinfo'=>$this->appinfo);
            json_encode($arr);
            return Response::json(2,"InitMessage",$arr);
        }
    }


    public function getApp($app_type)
    {
        $connect = Db::getInstance()->connect();
        $sql = "select * from db_Version where app_type='".$app_type."'";
        $ret = mysqli_query($connect,$sql);

        return mysqli_fetch_assoc($ret);
    }

    public function getAd()
    {
        $connect = Db::getInstance()->connect();
        $sql = "select * from db_Ad";
        $ret = mysqli_query($connect,$sql);

        $retarr = mysqli_fetch_all($ret);

        json_encode($retarr);

        return $retarr;
    }
}

$init = new Init();
$init->index();
$init->checkVersion();
