#ifndef __REDISDB_H__
#define __REDISDB_H__

#include "mysqldb.h"

#include <hiredis/hiredis.h>
#include <string>
#include <vector>

class RedisOpt
{
public:
    static RedisOpt *GetInstance()
    {
        static RedisOpt redisOpt;
        return &redisOpt;
    }

    bool setKeyValue(std::string opt);
    std::string getKeyValue(std::string opt);
    bool delKeyValue(std::string opt);

    bool LoginRun();
    bool MsgRun();

private:
    RedisOpt() {}
    ~RedisOpt() {}
    bool connect();
    bool release();

    redisContext *redisCon;
};

#endif