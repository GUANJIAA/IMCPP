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
	`desc`  varchar(500) DEFAULT 'Test' NOT NULL COMMENT '用户描述',
	`depart` varchar(40) DEFAULT 'DEFAULT' NOT NULL COMMENT '所属部门',
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
	`groupdesc` varchar(200) CHARACTER SET latin1 DEFAULT 'Test' COMMENT '组描述',
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
    `groupname` varchar(50) NOT NULL COMMENT '组名称',
    `username` varchar(50) NOT NULL COMMENT '用户名称',
    `userrole` enum('creator','normal') CHARACTER SET latin1 DEFAULT 'normal' NOT NULL COMMENT '用户权限',
    KEY `groupname` (`groupname`,`username`)
) ENGINE=INNODB DEFAULT CHARSET=utf8;

LOCK TABLES `groupuser` WRITE;
INSERT INTO `groupuser` VALUES ('C++','test_4','creator'),('C++','test_3','normal');
UNLOCK TABLES;
# -------------------------------------------

# -------------------------------------------
DROP TABLE IF EXISTS `alldepart`;

CREATE TABLE `alldepart` (
	`id` int(11) NOT NULL AUTO_INCREMENT COMMENT '部门id',
	`departname` varchar(50) CHARACTER SET latin1 NOT NULL COMMENT '部门名称',
	`departdesc` varchar(200) CHARACTER SET latin1 DEFAULT 'Test' COMMENT '部门描述',
	PRIMARY KEY (`id`),
	UNIQUE KEY `departname` (`departname`)
) ENGINE=INNODB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;

LOCK TABLES `alldepart` WRITE;
INSERT INTO `alldepart` VALUES (1,'C++','default_1');
UNLOCK TABLES;
# -------------------------------------------

# -------------------------------------------
DROP TABLE IF EXISTS `departuser`;

CREATE TABLE `departuser` (
    `departname` varchar(50) NOT NULL COMMENT '部门名称',
    `username` varchar(50) NOT NULL COMMENT '用户名称',
    `userrole` enum('intendant','employee') CHARACTER SET latin1 DEFAULT NULL COMMENT '用户权限',
    KEY `departname` (`departname`,`username`)
) ENGINE=INNODB DEFAULT CHARSET=utf8;

LOCK TABLES `departuser` WRITE;
INSERT INTO `departuser` VALUES ('C++','test_4','intendant'),('C++','test_3','employee');
UNLOCK TABLES;
# -------------------------------------------

# -------------------------------------------
DROP TABLE IF EXISTS `chatmessage`;
 
CREATE TABLE `chatmessage`(
	`msgid` int(11) NOT NULL AUTO_INCREMENT COMMENT '消息id',
	`recvname` varchar(50) NOT NULL COMMENT '接收者名称',
	`sendname` varchar(50) NOT NULL COMMENT '发送者名称',
	`message` varchar(500) NOT NULL COMMENT '消息',
	`isread` enum('true','false') DEFAULT 'false' COMMENT '是否为离线消息',
	PRIMARY KEY (`msgid`)
) ENGINE=INNODB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;

LOCK TABLES `chatmessage` WRITE;

INSERT INTO `chatmessage`(`recvname`,`sendname`,`message`,`isread`) VALUES ('test_2','test_1','test_code','true');

UNLOCK TABLES;

# -------------------------------------------

# -------------------------------------------
DROP TABLE IF EXISTS `chatgroupmessage`;

CREATE TABLE `chatgroupmessage`(
	`msgid` int(11) NOT NULL AUTO_INCREMENT COMMENT '消息id',
	`groupname` varchar(50) NOT NULL,
	`sendname` varchar(50) NOT NULL,
	`message` varchar(500) NOT NULL,
	PRIMARY KEY (`msgid`)
) ENGINE=INNODB DEFAULT CHARSET=utf8;

LOCK TABLES `chatgroupmessage` WRITE;

INSERT INTO `chatgroupmessage`(`groupname`,`sendname`,`message`) VALUES ('test_2','test_2','test_code');

UNLOCK TABLES;
# -------------------------------------------

# -------------------------------------------
DROP TABLE IF EXISTS `chatdepartmessage`;

CREATE TABLE `chatdepartmessage`(
	`msgid` int(11) NOT NULL AUTO_INCREMENT COMMENT '消息id',
	`departname` varchar(50) NOT NULL,
	`sendname` varchar(50) NOT NULL,
	`message` varchar(500) NOT NULL,
	PRIMARY KEY (`msgid`)
) ENGINE=INNODB DEFAULT CHARSET=utf8;

LOCK TABLES `chatdepartmessage` WRITE;

INSERT INTO `chatdepartmessage`(`departname`,`sendname`,`message`) VALUES ('test_2','test_2','test_code');

UNLOCK TABLES;
# -------------------------------------------
