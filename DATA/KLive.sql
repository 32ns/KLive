/*
 Navicat Premium Data Transfer

 Source Server         : localhost
 Source Server Type    : MySQL
 Source Server Version : 80011
 Source Host           : localhost:3306
 Source Schema         : KLive

 Target Server Type    : MySQL
 Target Server Version : 80011
 File Encoding         : 65001

 Date: 25/07/2018 20:59:12
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for db_Ad
-- ----------------------------
DROP TABLE IF EXISTS `db_Ad`;
CREATE TABLE `db_Ad` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `title` varchar(255) DEFAULT NULL,
  `img` varchar(255) DEFAULT NULL,
  `url` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of db_Ad
-- ----------------------------
BEGIN;
INSERT INTO `db_Ad` VALUES (1, '百度', 'https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1523925125048&di=69e94da316cc91d06224da3cd30d7ef9&imgtype=0&src=http%3A%2F%2Fimg.zcool.cn%2Fcommunity%2F01054859bcc50ca801212fb70eb265.jpg%402o.jpg', '');
INSERT INTO `db_Ad` VALUES (2, '腾讯', 'https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1523925043121&di=ebb38a366ca78877c9cadc227dc40663&imgtype=0&src=http%3A%2F%2Fimg.zcool.cn%2Fcommunity%2F01552558b8f112a801219c775f7936.jpg', '');
COMMIT;

-- ----------------------------
-- Table structure for db_Pay
-- ----------------------------
DROP TABLE IF EXISTS `db_Pay`;
CREATE TABLE `db_Pay` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `sum` varchar(10) DEFAULT NULL,
  `day` int(10) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of db_Pay
-- ----------------------------
BEGIN;
INSERT INTO `db_Pay` VALUES (1, '30.00', 30);
COMMIT;

-- ----------------------------
-- Table structure for db_PayFailure
-- ----------------------------
DROP TABLE IF EXISTS `db_PayFailure`;
CREATE TABLE `db_PayFailure` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `username` varchar(50) DEFAULT NULL,
  `sum` varchar(50) NOT NULL,
  `msg` varchar(255) DEFAULT NULL,
  `paydate` datetime DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for db_PaySucceed
-- ----------------------------
DROP TABLE IF EXISTS `db_PaySucceed`;
CREATE TABLE `db_PaySucceed` (
  `id` tinyint(4) NOT NULL AUTO_INCREMENT,
  `username` varchar(60) NOT NULL,
  `sum` varchar(20) NOT NULL,
  `paydate` datetime DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for db_User
-- ----------------------------
DROP TABLE IF EXISTS `db_User`;
CREATE TABLE `db_User` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(64) DEFAULT NULL,
  `password` varchar(255) DEFAULT NULL,
  `begintimer` datetime DEFAULT NULL,
  `endtimer` datetime DEFAULT NULL,
  `regtimer` datetime DEFAULT NULL,
  `deviceid` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of db_User
-- ----------------------------
BEGIN;
INSERT INTO `db_User` VALUES (5, 'made47', 'YJcdzMwfh  UPdEQs7AxPw==', '2018-05-13 12:29:43', '2019-05-31 23:57:46', '2018-05-13 12:29:43', ' uQCRnPr7dWgx5a/PcOexndzqe8qZkzMpNiEcc9a8Lk=');
COMMIT;

-- ----------------------------
-- Table structure for db_Version
-- ----------------------------
DROP TABLE IF EXISTS `db_Version`;
CREATE TABLE `db_Version` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `app_type` varchar(20) NOT NULL,
  `version_id` float(10,2) DEFAULT NULL,
  `app_url` varchar(255) DEFAULT NULL,
  `message` varchar(255) DEFAULT NULL,
  `videoUrl` varchar(255) NOT NULL,
  `topup` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of db_Version
-- ----------------------------
BEGIN;
INSERT INTO `db_Version` VALUES (1, 'android', 1.01, 'http://127.0.0.1:8888/update/klive.apk', '替换播放源', 'rd', 'http://127.0.0.1:8888/pay.html');
INSERT INTO `db_Version` VALUES (2, 'ios', 1.00, 'http://127.0.0.1:8888/update/klive.apk', '不知道更新了点什么', 'rd', 'http://127.0.0.1:8888/pay.html');
COMMIT;

SET FOREIGN_KEY_CHECKS = 1;
