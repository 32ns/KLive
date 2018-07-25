
基于Qt开发的聚合直播盒子源码,已完成基本的 采集 播放 用户注册 和 支付功能,应该是现有直播盒子中最好用的了



重要声明:
  	本程序中所演示的视频内容均来自第三方群内共享与本人无关,请慎重使用,或替换为您自己的播放源
  
播放源替换:
		在Platfrom目录下新建一个类,继承自Platfrom类并实现其中的两个方法即可
		virtual void getRoomList() = 0;   //获取房间列表
		virtual void getRoomItem(QString address) = 0;  //获取主播列表
