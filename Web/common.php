<?php
/**
 * 公共接口
 * 401 参数不全
 * 402 连接数据出错
 */


require_once ('./response.php');
require_once ('./db.php');

class Common {

    public $params;
    public $ad;

    public function check()
    {
        $this->params['version_id'] = $version_id = isset($_POST['version_id'])? $_POST['version_id'] : '';
        $this->params['app_type'] = $app_type = isset($_POST['app_type'])? $_POST['app_type'] : '';
        $this->params['dt'] = $dt = isset($_POST['dt'])? $_POST['dt'] : '';
        $this->params['did'] = $did = isset($_POST['did'])? $_POST['did'] : '';
        $this->params['token'] = $token = isset($_POST['token'])? $_POST['token'] : '';

        if(empty($version_id) || empty($app_type) || empty($dt) || empty($did) || empty($token))
        {
            return Response::json(401,"参数不合法!");
        }




    }






}