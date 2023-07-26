#include "redisdb.h"

#include "mprpcapplication.h"

#include <json/json.h>
#include <string.h>

bool RedisOpt::connect()
{
    std::string ip = MprpcApplication::GetInstance().GetConfig().Load("redisServerIp");
    std::string port = MprpcApplication::GetInstance().GetConfig().Load("redisServerPort");

    redisCon = redisConnect(ip.c_str(), atoi(port.c_str()));

    if (redisCon == nullptr || redisCon->err)
    {
        if (redisCon)
        {
            release();
        }
        return false;
    }
    return true;
}

bool RedisOpt::setKeyValue(std::string opt)
{
    if (redisCon != nullptr)
    {
        return false;
    }

    if (connect())
    {
        redisReply *reply = (redisReply *)redisCommand(redisCon, opt.c_str());
        freeReplyObject(reply);
        return true;
    }
    release();
    return false;
}

std::string RedisOpt::getKeyValue(std::string opt)
{
    if (redisCon != nullptr)
    {
        return "";
    }

    if (connect())
    {
        redisReply *reply = (redisReply *)redisCommand(redisCon, opt.c_str());
        std::string str;
        if (reply->type == REDIS_REPLY_STRING)
        {
            str = reply->str;
        }
        freeReplyObject(reply);
        return str;
    }
    release();
    return "";
}

bool RedisOpt::delKeyValue(std::string opt)
{
    if (redisCon != nullptr)
    {
        return false;
    }

    if (connect())
    {
        redisReply *reply = (redisReply *)redisCommand(redisCon, opt.c_str());
        freeReplyObject(reply);
        return true;
    }
    release();
    return false;
}

bool RedisOpt::LoginRun()
{
    if (connect())
    {
        char opt[1024] = {0};
        MySQL *mysql = connection_pool::GetInstance()->GetConnection();
        MYSQL_RES *res = mysql->query("select * from Admin a");

        MYSQL_ROW row;
        int i = 0;
        while ((row = mysql_fetch_row(res)) != nullptr)
        {
            Json::Value json;
            json["name"] = row[1];
            json["pwd"] = row[2];
            json["status"] = row[3];
            json["email"] = row[4];
            json["phone"] = row[5];
            sprintf(opt, "HSET LoginHash %s %s", json["name"], json);
            redisReply *reply = (redisReply *)redisCommand(redisCon, opt);
            freeReplyObject(reply);
            if (++i >= 50)
            {
                break;
            }
        }
        release();
        return true;
    }
    return false;
}

bool MsgRun()
{
}

bool RedisOpt::release()
{
    redisCon = nullptr;
    redisFree(redisCon);
}
