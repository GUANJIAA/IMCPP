# *******************************************
# Host: 192.168.61.100
# Database: IMData
# Generation Time: 2023-07-19 15:29:00
# *******************************************

# -------------------------------------------
DROP DATABASE IF EXISTS IMData;

CREATE DATABASE IMData DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;

USE IMData;
# -------------------------------------------

# -------------------------------------------
DROP TABLE IF EXISTS `Admin`;

CREATE TABLE `Admin` (
	`id` MEDIUMINT(6) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '用户id', 
	`name` varchar(40) NOT NULL COMMENT '用户名',
	`pwd` char(32) NOT NULL COMMENT '密码',
	`status` enum('online','offline') CHARACTER SET latin1 DEFAULT 'offline' COMMENT '在线状态',
	`email` varchar(40) NOT NULL COMMENT '用户邮箱',
	`phone` varchar(40) NOT NULL COMMENT '手机号码',
	PRIMARY KEY (`id`),
	UNIQUE KEY `name` (`name`)
) ENGINE=INNODB DEFAULT CHARSET=utf8;

LOCK TABLES `Admin` WRITE;
INSERT INTO `Admin` VALUES (1,'test','123456','online','2783688001@qq.com','13926413813');
INSERT INTO `Admin` VALUES (2,'test_1','123456','online','2783688001@qq.com','13926413813');
UNLOCK TABLES;
# -------------------------------------------

# -------------------------------------------
DROP TABLE IF EXISTS `friend`;

CREATE TABLE `friend` (
	`username` varchar(40) NOT NULL COMMENT '用户姓名',
	`friendname` varchar(40) NOT NULL COMMENT '朋友姓名',
	KEY `username` (`username`, `friendname`)
) ENGINE=INNODB DEFAULT CHARSET=utf8;

LOCK TABLES `friend` WRITE;
INSERT INTO `friend` VALUES ('test_3','test_4');
UNLOCK TABLES;
# -------------------------------------------

# -------------------------------------------
DROP TABLE IF EXISTS `allgroup`;

CREATE TABLE `allgroup` (
	`id` int(11) NOT NULL AUTO_INCREMENT COMMENT '组id',
	`groupname` varchar(50) CHARACTER SET latin1 NOT NULL COMMENT '组名称',
	`groupdesc` varchar(200) CHARACTER SET latin1 DEFAULT '' COMMENT '组描述',
	PRIMARY KEY (`id`),
	UNIQUE KEY `groupname` (`groupname`)
) ENGINE=INNODB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;

LOCK TABLES `allgroup` WRITE;
INSERT INTO `allgroup` VALUES (1,'C++','default_1');
UNLOCK TABLES;
# -------------------------------------------

# -------------------------------------------
DROP TABLE IF EXISTS `groupuser`;

CREATE TABLE `groupuser` (
    `groupid` int(11) NOT NULL COMMENT '组id',
    `userid` int(11) NOT NULL COMMENT '用户id',
    `grouprole` enum('creator','normal') CHARACTER SET latin1 DEFAULT NULL COMMENT '用户权限',
    KEY `groupid` (`groupid`,`userid`)
) ENGINE=INNODB DEFAULT CHARSET=utf8;

LOCK TABLES `groupuser` WRITE;
INSERT INTO `groupuser` VALUES (1,1,'creator'),(1,2,'normal');
UNLOCK TABLES;
# -------------------------------------------