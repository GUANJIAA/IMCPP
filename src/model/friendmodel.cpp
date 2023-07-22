#include "friendmodel.h"

#include "mysqldb.h"

bool FriendModel::insert(std::string adminName, std::string peerName)
{
    char sql[1024] = {0};
    sprintf(sql, "insert into `friend` values ('%s','%s')",
            adminName.c_str(), peerName.c_str());

    MySQL *mysql = connection_pool::GetInstance()->GetConnection();
    bool result = false;
    if (mysql->update(sql))
    {
        result = true;
    }
    connection_pool::GetInstance()->ReleaseConnection(mysql);
    return result;
}

std::vector<Admin> FriendModel::query(std::string adminName)
{
    char sql[1024] = {0};
    sprintf(sql, "select * from `Admin` a inner join `friend` f on f.friendname\
            = a.name where f.username = '%s'",
            adminName.c_str());

    MySQL *mysql = connection_pool::GetInstance()->GetConnection();
    std::vector<Admin> vec;
    MYSQL_RES *res = mysql->query(sql);
    if (res != nullptr)
    {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res)) != nullptr)
        {
            Admin admin;
            admin.setId(atoi(row[0]));
            admin.setName(row[1]);
            admin.setPassword(row[2]);
            admin.setStatus(row[3]);
            admin.setEmail(row[4]);
            admin.setPhone(row[5]);
            vec.push_back(admin);
        }
        mysql_free_result(res);
    }
    connection_pool::GetInstance()->ReleaseConnection(mysql);
    return vec;
}

bool FriendModel::removal(std::string adminName, std::string peerName)
{
    char sql[1024] = {0};
    sprintf(sql, "delete from `friend` where `username` = '%s' and `friendname` = '%s'",
            adminName.c_str(), peerName.c_str());

    MySQL *mysql = connection_pool::GetInstance()->GetConnection();
    bool result = false;
    if (mysql->update(sql))
    {
        result = true;
    }
    connection_pool::GetInstance()->ReleaseConnection(mysql);
    return result;
}