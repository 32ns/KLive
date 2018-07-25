## 介绍
	基于Qt QML的聚合直播盒子,实现了 采集,播放,用户注册,用户充值,到期续费,上滑下滑切换主播,主播下线自动跳过,
	自动在房间的第一个位置生成下载二唯码,添加屏蔽主播列表 等功能,
	已在Mac,ios,Android下测试适配
	交流群:93525134

## 重要声明:
	本程序中所演示的视频内容均来自第三方群内共享与本人无关,请慎重使用,或替换为您自己的播放源
  
## 播放源替换:
	在Platfrom目录下新建一个类,继承自Platfrom类,实现其中的两个方法并抛出信号即可
	
	public slots:
	virtual void getRoomList() = 0;   //获取房间列表
	virtual void getRoomItem(QString address) = 0;  //获取主播列表
	
	signals:
	void sig_GetRoomFinish(QList<PlatfromInfo> infolist); //获取房间完成信号
	void sig_GetRoomItemFinish(QList<PlatfromItem> itemlist);//获取主播列表完成信号
	
	
	
## 编译依赖:
	QtAV : 须自行下载安装 https://github.com/wang-bin/QtAV.git
	
## 程序部署:
	A.下载Qt SDK并安装QtAV播放库,搭建Mysql及PHP环境
	B.新建一个数据库Klive,并导入DATA目录下的SQL文件
	C.将Web目录下的所有文件放到PHP环境下
	D.运行程序,完成部署
	
## 目录结构	
	├── AppUpdate   //应用更新
	│
	├── Crypto	//加密解密
	│
	├── DATA	//数据库脚本
	│
	├── Global	//公共类
	│
	├── GlobalQml	//QML组件
	│
	├── HomePage	//主页QML
	│
	├── Model	//数据模型
	│
	├── NetWork	//网络相关
	│
	├── Pay		//支付相关
	│
	├── Platfrom	//直播源
	│
	├── QZXing	//二唯码生成
	│
	├── Res		//图片资源
	│
	├── UserPage	//用户页QML
	│
	├── Web		//PHP接口源码
	│
	├── android	//Android适配文件
	│
	├── img		//程序截图


![图片](https://github.com/32ns/KLive/blob/master/img/1.jpg)

![图片](https://github.com/32ns/KLive/blob/master/img/2.jpg)

![图片](https://github.com/32ns/KLive/blob/master/img/3.jpg)

![图片](https://github.com/32ns/KLive/blob/master/img/4.jpg)

![图片](https://github.com/32ns/KLive/blob/master/img/5.jpg)

![图片](https://github.com/32ns/KLive/blob/master/img/6.jpg)

