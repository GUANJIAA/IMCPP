#include "offlinemsgmodel.h"

#include "mysqldb.h"

bool OfflineMsgModel::addOfflineMsg(std::string recvName, std::string sendName,
                                    std::string message)
{
    char sql[1024] = {0};
    sprintf(sql, "insert into `offlinemessage`(`recvname`,`sendname`,`message`) values ('%s','%s','%s')",
            recvName.c_str(), sendName.c_str(), message.c_str());

    MySQL *mysql = connection_pool::GetInstance()->GetConnection();
    bool result = false;
    if (mysql->update(sql))
    {
        result = true;
    }
    connection_pool::GetInstance()->ReleaseConnection(mysql);
    return result;
}

bool OfflineMsgModel::delOfflineMsg(int msgId, std::string recvName,
                                    std::string sendName, std::string message)
{
    char sql[1024] = {0};
    sprintf(sql, "DELETE FROM `offlinemessage` WHERE `msgid` = %d \
            `recvname` = '%s' AND `sendname` = '%s' AND `message` = '%s'",
            msgId, recvName.c_str(), sendName.c_str(), message.c_str());

    MySQL *mysql = connection_pool::GetInstance()->GetConnection();
    bool result = false;
    if (mysql->update(sql))
    {
        result = true;
    }
    connection_pool::GetInstance()->ReleaseConnection(mysql);
    return result;
}

std::vector<OfflineMsg> OfflineMsgModel::queryOfflineMsg(std::string recvName)
{
    char sql[1024] = {0};
    sprintf(sql, "SELECT * FROM `offlinemessage` WHERE `recvname` = '%s'",
            recvName.c_str());

    std::vector<OfflineMsg> offlineMsgVec;
    MySQL *mysql = connection_pool::GetInstance()->GetConnection();
    MYSQL_RES *res = mysql->query(sql);
    if (res != nullptr)
    {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res)) != nullptr)
        {
            OfflineMsg temp;
            temp.setMsgId(atoi(row[0]));
            temp.setRecvName(row[1]);
            temp.setSendName(row[2]);
            temp.setMessage(row[3]);
            offlineMsgVec.push_back(temp);
        }
        mysql_free_result(res);
    }
    connection_pool::GetInstance()->ReleaseConnection(mysql);
    return offlineMsgVec;
}

bool OfflineMsgModel::addOfflineGroupMsg(std::string groupName, std::string sendName,
                                         std::string message)
{
    char sql[1024] = {0};
    sprintf(sql, "insert into `offlinegroupmessage`(`groupname`,`sendname`,`message`) values ('%s','%s','%s')",
            groupName.c_str(), sendName.c_str(), message.c_str());

    MySQL *mysql = connection_pool::GetInstance()->GetConnection();
    bool result = false;
    if (mysql->update(sql))
    {
        result = true;
    }
    connection_pool::GetInstance()->ReleaseConnection(mysql);
    return result;
}

bool OfflineMsgModel::delOfflineGroupMsg(int msgId, std::string groupName,
                                         std::string sendName, std::string message)
{
    char sql[1024] = {0};
    sprintf(sql, "DELETE FROM `offlinegroupmessage` WHERE `msgid` = %d \
            AND `groupname` = '%s' AND `sendname` = '%s' AND `message` = '%s'",
            msgId, groupName.c_str(), sendName.c_str(), message.c_str());

    MySQL *mysql = connection_pool::GetInstance()->GetConnection();
    bool result = false;
    if (mysql->update(sql))
    {
        result = true;
    }
    connection_pool::GetInstance()->ReleaseConnection(mysql);
    return result;
}

std::vector<OfflineGroupMsg> OfflineMsgModel::queryOfflineGroupMsg(std::string userName)
{
    char sql[1024] = {0};
    sprintf(sql, "select o.msgid,o.groupname,o.sendname,o.message from `offlinegroupmessage` o\
            inner join `groupuser` a on o.groupname = a.groupname where a.username = '%s'",
            userName.c_str());

    std::vector<OfflineGroupMsg> offlineGroupMsgVec;
    MySQL *mysql = connection_pool::GetInstance()->GetConnection();
    MYSQL_RES *res = mysql->query(sql);
    if (res != nullptr)
    {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res)) != nullptr)
        {
            OfflineGroupMsg temp;
            temp.setMsgId(atoi(row[0]));
            temp.setGroupName(row[1]);
            temp.setSendName(row[2]);
            temp.setMessage(row[3]);
            offlineGroupMsgVec.push_back(temp);
        }
        mysql_free_result(res);
    }
    connection_pool::GetInstance()->ReleaseConnection(mysql);
    return offlineGroupMsgVec;
}

bool OfflineMsgModel::addOfflineDepartMsg(std::string departName, std::string sendName,
                                          std::string message)
{
    char sql[1024] = {0};
    sprintf(sql, "insert into `offlinedepartmessage`(`departname`,`sendname`,`message`) values ('%s','%s','%s')",
            departName.c_str(), sendName.c_str(), message.c_str());

    MySQL *mysql = connection_pool::GetInstance()->GetConnection();
    bool result = false;
    if (mysql->update(sql))
    {
        result = true;
    }
    connection_pool::GetInstance()->ReleaseConnection(mysql);
    return result;
}

bool OfflineMsgModel::delOfflineDepartMsg(int msgId, std::string departName,
                                          std::string sendName, std::string message)
{
    char sql[1024] = {0};
    sprintf(sql, "DELETE FROM `offlinedepartmessage` WHERE `msgid` = %d \
            AND `departname` = '%s' AND `sendname` = '%s' AND `message` = '%s'",
            msgId, departName.c_str(), sendName.c_str(), message.c_str());

    MySQL *mysql = connection_pool::GetInstance()->GetConnection();
    bool result = false;
    if (mysql->update(sql))
    {
        result = true;
    }
    connection_pool::GetInstance()->ReleaseConnection(mysql);
    return result;
}

std::vector<OfflineDepartMsg> OfflineMsgModel::queryOfflineDepartMsg(std::string userName)
{
    char sql[1024] = {0};
    sprintf(sql, "select o.msgid,o.departname,o.sendname,o.message from `offlinedepartmessage` o\
            inner join `departuser` a on o.departname = a.departname where a.username = '%s'",
            userName.c_str());

    std::vector<OfflineDepartMsg> offlineDepartMsgVec;
    MySQL *mysql = connection_pool::GetInstance()->GetConnection();
    MYSQL_RES *res = mysql->query(sql);
    if (res != nullptr)
    {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res)) != nullptr)
        {
            OfflineDepartMsg temp;
            temp.setMsgId(atoi(row[0]));
            temp.setDepartName(row[1]);
            temp.setSendName(row[2]);
            temp.setMessage(row[3]);
            offlineDepartMsgVec.push_back(temp);
        }
        mysql_free_result(res);
    }
    connection_pool::GetInstance()->ReleaseConnection(mysql);
    return offlineDepartMsgVec;
}