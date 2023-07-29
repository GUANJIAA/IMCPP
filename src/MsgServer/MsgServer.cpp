#include "MsgServer.h"

#include "Group.pb.h"
#include "Depart.pb.h"
#include "Friend.pb.h"
#include "ChatMsg.pb.h"

MsgServer *MsgServer::instance()
{
    static MsgServer server;
    return &server;
}

MsgServer::MsgServer()
{
    _msgHandlerMap.insert({NEW_CONNECTION, bind(&MsgServer::newConnection, this, std::placeholders::_1, std::placeholders::_2)});

    _msgHandlerMap.insert({ONE_CHAT_MSG, bind(&MsgServer::oneChat, this, std::placeholders::_1, std::placeholders::_2)});
    // _msgHandlerMap.insert({DEL_CHAT_MSG, bind(&MsgServer::delChatMsg, this, std::placeholders::_1, std::placeholders::_2)});
    // _msgHandlerMap.insert({QUERY_CHAT_MSG, bind(&MsgServer::queryChatMsg, this, std::placeholders::_1, std::placeholders::_2)});

    // _msgHandlerMap.insert({ADD_FRIEND_MSG, bind(&MsgServer::addFriend, this, std::placeholders::_1, std::placeholders::_2)});
    // _msgHandlerMap.insert({DEL_FRIEND_MSG, bind(&MsgServer::delFriend, this, std::placeholders::_1, std::placeholders::_2)});

    // _msgHandlerMap.insert({GROUP_CHAT_MSG, bind(&MsgServer::groupChat, this, std::placeholders::_1, std::placeholders::_2)});
    // _msgHandlerMap.insert({CREATE_GROUP_MSG, bind(&MsgServer::createGroup, this, std::placeholders::_1, std::placeholders::_2)});
    // _msgHandlerMap.insert({ADD_GROUP_MSG, bind(&MsgServer::addGroup, this, std::placeholders::_1, std::placeholders::_2)});
    // _msgHandlerMap.insert({QUIT_GROUP_MSG, bind(&MsgServer::quitGroup, this, std::placeholders::_1, std::placeholders::_2)});

    // _msgHandlerMap.insert({DEPART_CHAT_MSG, bind(&MsgServer::departChat, this, std::placeholders::_1, std::placeholders::_2)});
    // _msgHandlerMap.insert({CREATE_DEPART_MSG, bind(&MsgServer::createDepart, this, std::placeholders::_1, std::placeholders::_2)});
    // _msgHandlerMap.insert({ADD_DEPART_MSG, bind(&MsgServer::addDepart, this, std::placeholders::_1, std::placeholders::_2)});
    // _msgHandlerMap.insert({QUIT_DEPART_MSG, bind(&MsgServer::quitDepart, this, std::placeholders::_1, std::placeholders::_2)});

    if (_redis.subscribeConnect())
    {
        _redis.init_notify_handler(bind(&MsgServer::handleRedisSubscribeMessage,
                                        this, std::placeholders::_1, std::placeholders::_2));
    }
}

void MsgServer::newConnection(const muduo::net::TcpConnectionPtr &tcpconn, Json::Value &data)
{
    std::string userName = data["userName"].asString();
    {
        std::lock_guard<std::mutex> lock(_connMutex);
        _userConnMap.insert({userName, tcpconn});
    }
    _redis.subscribe(userName);
}

void MsgServer::oneChat(const muduo::net::TcpConnectionPtr &tcpconn, Json::Value &data)
{
    std::string recvName = data["recvName"].asString();

    _userConnMap.insert({recvName, tcpconn});
    {
        std::lock_guard<std::mutex> lock(_connMutex);
        auto it = _userConnMap.find(recvName);
        std::string str = Json::FastWriter().write(data);
        if (it != _userConnMap.end())
        {
            it->second->send(str);
            // data["isRead"] = "true";
            return;
        }
        else if (_redis.ischannel(recvName))
        {
            _redis.publish(recvName, str);
            // data["isRead"] = "true";
        }
    }

    /*
        储存在redis的消息超过100条就提取出来保存
    */
}

MsgHandler MsgServer::getHandler(int msgid)
{
    auto it = _msgHandlerMap.find(msgid);
    if (it == _msgHandlerMap.end())
    {
        return [=](const muduo::net::TcpConnectionPtr &conn, Json::Value &data)
        {
            std::cout << "msgid: " << msgid << "can not find handler!";
        };
    }
    else
    {
        return _msgHandlerMap[msgid];
    }
}

void MsgServer::handleRedisSubscribeMessage(std::string name, std::string msg)
{
    std::lock_guard<std::mutex> lock(_connMutex);
    auto it = _userConnMap.find(name);
    if (it != _userConnMap.end())
    {
        it->second->send(msg);
        return;
    }
}