#include "MsgServer.h"

#include "UserMsg.pb.h"
#include "Group.pb.h"
#include "Depart.pb.h"
#include "Friend.pb.h"
#include "ChatMsg.pb.h"

#include "mprpcchannel.h"

MsgServer *MsgServer::instance()
{
    static MsgServer server;
    return &server;
}

MsgServer::MsgServer()
{
    _msgHandlerMap.insert({NEW_CONNECTION, bind(&MsgServer::newConnection, this, std::placeholders::_1, std::placeholders::_2)});
    _msgHandlerMap.insert({QUERY_ADMININFO, bind(&MsgServer::queryAdminInfo, this, std::placeholders::_1, std::placeholders::_2)});
    _msgHandlerMap.insert({UPDATE_ADMININFO, bind(&MsgServer::updateAdminInfo, this, std::placeholders::_1, std::placeholders::_2)});

    _msgHandlerMap.insert({ONE_CHAT_MSG, bind(&MsgServer::oneChat, this, std::placeholders::_1, std::placeholders::_2)});
    _msgHandlerMap.insert({DEL_CHAT_MSG, bind(&MsgServer::delChatMsg, this, std::placeholders::_1, std::placeholders::_2)});
    _msgHandlerMap.insert({QUERY_CHAT_MSG, bind(&MsgServer::queryChatMsg, this, std::placeholders::_1, std::placeholders::_2)});
    _msgHandlerMap.insert({QUERY_OFFLINE_CHAT_MSG, bind(&MsgServer::queryOfflineChatMsg, this, std::placeholders::_1, std::placeholders::_2)});

    _msgHandlerMap.insert({ADD_FRIEND_MSG, bind(&MsgServer::addFriend, this, std::placeholders::_1, std::placeholders::_2)});
    _msgHandlerMap.insert({DEL_FRIEND_MSG, bind(&MsgServer::delFriend, this, std::placeholders::_1, std::placeholders::_2)});
    _msgHandlerMap.insert({QUERY_FRIEND_MSG, bind(&MsgServer::queryFriend, this, std::placeholders::_1, std::placeholders::_2)});

    _msgHandlerMap.insert({GROUP_CHAT_MSG, bind(&MsgServer::groupChat, this, std::placeholders::_1, std::placeholders::_2)});
    _msgHandlerMap.insert({CREATE_GROUP_MSG, bind(&MsgServer::createGroup, this, std::placeholders::_1, std::placeholders::_2)});
    _msgHandlerMap.insert({ADD_GROUP_MSG, bind(&MsgServer::addGroup, this, std::placeholders::_1, std::placeholders::_2)});
    _msgHandlerMap.insert({QUERY_GROUP_MSG, bind(&MsgServer::queryGroup, this, std::placeholders::_1, std::placeholders::_2)});
    _msgHandlerMap.insert({QUERY_GROUP_USERS_MSG, bind(&MsgServer::queryGroupUser, this, std::placeholders::_1, std::placeholders::_2)});

    _msgHandlerMap.insert({DEPART_CHAT_MSG, bind(&MsgServer::departChat, this, std::placeholders::_1, std::placeholders::_2)});
    _msgHandlerMap.insert({CREATE_DEPART_MSG, bind(&MsgServer::createDepart, this, std::placeholders::_1, std::placeholders::_2)});
    _msgHandlerMap.insert({ADD_DEPART_MSG, bind(&MsgServer::addDepart, this, std::placeholders::_1, std::placeholders::_2)});
    _msgHandlerMap.insert({QUERY_DEPART_USERS_MSG, bind(&MsgServer::queryDepartUser, this, std::placeholders::_1, std::placeholders::_2)});
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

    queryAdminInfo(tcpconn, data);

    queryFriend(tcpconn, data);
    queryGroup(tcpconn, data);
    queryDepartUser(tcpconn, data);

    /*
        查询离线消息
    */
}

void MsgServer::queryAdminInfo(const muduo::net::TcpConnectionPtr &tcpconn, Json::Value &data)
{
    std::string userName = data["userName"].asString();

    UserMsgProto::UserMsgServiceRpc_Stub stub(new MprpcChannel());
    UserMsgProto::QueryUserMsgRequest request;
    request.set_name(userName);
    UserMsgProto::QueryUserMsgResponse response;
    stub.QueryUserMsg(nullptr, &request, &response, nullptr);

    Json::Value result;
    result["msgid"] = NEW_CONNECTION;
    result["errcode"] = response.result().errcode();
    result["errmsg"] = response.result().errmsg();
    result["userName"] = response.usermsg().name();
    result["userPwd"] = response.usermsg().pwd();
    result["userEmail"] = response.usermsg().email();
    result["userPhone"] = response.usermsg().phone();

    std::string str = Json::FastWriter().write(result);
    tcpconn->send(str);
}

void MsgServer::updateAdminInfo(const muduo::net::TcpConnectionPtr &tcpconn, Json::Value &data)
{
    std::string userName = data["userName"].asString();
    std::string userPwd = data["userPwd"].asString();
    std::string userEmail = data["userEmail"].asString();
    std::string userPhone = data["userPhone"].asString();

    UserMsgProto::UserMsgServiceRpc_Stub stub(new MprpcChannel());
    UserMsgProto::UpdateUserMsgRequest request;
    UserMsgProto::UserInfo *userInfo = request.mutable_usermsg();
    userInfo->set_name(userName);
    userInfo->set_pwd(userPwd);
    userInfo->set_email(userEmail);
    userInfo->set_phone(userPhone);
    UserMsgProto::UpdateUserMsgResponse response;
    stub.UpdateUserMsg(nullptr, &request, &response, nullptr);

    Json::Value result;
    result["msgid"] = NEW_CONNECTION;
    result["errcode"] = response.result().errcode();
    result["errmsg"] = response.result().errmsg();

    std::string str = Json::FastWriter().write(result);
    tcpconn->send(str);
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
            data["isRead"] = "true";
        }
        else if (_redis.ischannel(recvName))
        {
            _redis.publish(recvName, str);
            data["isRead"] = "true";
        }
    }

    std::string sendName = data["sendName"].asString();
    std::string message = data["message"].asString();
    std::string isRead = data["isRead"].asString();
    ChatMessageProto::chatMsgRpc_Stub stub(new MprpcChannel());
    ChatMessageProto::addMsgRequest request;
    request.mutable_msg()->set_recvname(recvName);
    request.mutable_msg()->set_sendname(sendName);
    request.mutable_msg()->set_message(message);
    request.mutable_msg()->set_isread(isRead);
    ChatMessageProto::addMsgResponse response;
    stub.AddChatMsg(nullptr, &request, &response, nullptr);
    if (0 == response.result().errcode())
    {
        std::cout << "AddChatMsg success: "
                  << response.success() << std::endl;
    }
    else
    {
        std::cout << "AddChatMsg error: "
                  << response.result().errmsg() << std::endl;
    }
}

void MsgServer::delChatMsg(const muduo::net::TcpConnectionPtr &tcpconn, Json::Value &data)
{
    int msgId = data["msgId"].asInt();
    std::string recvName = data["recvName"].asString();
    std::string sendName = data["sendName"].asString();
    std::string message = data["message"].asString();

    ChatMessageProto::chatMsgRpc_Stub stub(new MprpcChannel());
    ChatMessageProto::delMsgRequest request;
    request.mutable_msg()->set_msgid(msgId);
    request.mutable_msg()->set_recvname(recvName);
    request.mutable_msg()->set_sendname(sendName);
    request.mutable_msg()->set_message(message);
    ChatMessageProto::delMsgResponse response;
    stub.DelChatMsg(nullptr, &request, &response, nullptr);
    Json::Value result;
    result["msgid"] = DEL_CHAT_MSG;
    result["errcode"] = response.result().errcode();
    result["errmsg"] = response.result().errmsg();
    std::string str = Json::FastWriter().write(result);
    tcpconn->send(str);
}

void MsgServer::queryChatMsg(const muduo::net::TcpConnectionPtr &tcpconn, Json::Value &data)
{
    std::string recvName = data["recvName"].asString();

    ChatMessageProto::chatMsgRpc_Stub stub(new MprpcChannel());
    ChatMessageProto::queryMsgRequest request;
    request.set_recvname(recvName);
    ChatMessageProto::queryMsgResponse response;
    stub.QueryChatMsg(nullptr, &request, &response, nullptr);
    Json::Value result;
    result["msgid"] = QUERY_CHAT_MSG;
    result["errcode"] = response.result().errcode();
    result["errmsg"] = response.result().errmsg();
    for (auto &val : response.msg())
    {
        Json::Value chatmsg;
        chatmsg["msgId"] = val.msgid();
        chatmsg["recvName"] = val.recvname();
        chatmsg["sendName"] = val.sendname();
        chatmsg["message"] = val.message();
        result["chatmsgs"].append(chatmsg);
    }
    std::string str = Json::FastWriter().write(result);
    tcpconn->send(str);
}

void MsgServer::queryOfflineChatMsg(const muduo::net::TcpConnectionPtr &tcpconn, Json::Value &data)
{
    std::string recvName = data["recvName"].asString();

    ChatMessageProto::chatMsgRpc_Stub stub(new MprpcChannel());
    ChatMessageProto::queryOfflineMsgRequest request;
    request.set_recvname(recvName);
    ChatMessageProto::queryOfflineMsgResponse response;
    stub.QueryOfflineMsg(nullptr, &request, &response, nullptr);
    Json::Value result;
    result["msgid"] = QUERY_OFFLINE_CHAT_MSG;
    result["errcode"] = response.result().errcode();
    result["errmsg"] = response.result().errmsg();
    for (auto &val : response.msg())
    {
        Json::Value chatmsg;
        chatmsg["msgId"] = val.msgid();
        chatmsg["recvName"] = val.recvname();
        chatmsg["sendName"] = val.sendname();
        chatmsg["message"] = val.message();
        result["chatmsgs"].append(chatmsg);
    }
    std::string str = Json::FastWriter().write(result);
    tcpconn->send(str);
}

void MsgServer::addFriend(const muduo::net::TcpConnectionPtr &tcpconn, Json::Value &data)
{
    std::string userName = data["userName"].asString();
    std::string peerName = data["peerName"].asString();

    FriendProto::FriendServiceRpc_Stub stub(new MprpcChannel());
    FriendProto::AddFriendRequest request;
    request.set_adminname(userName);
    request.set_peername(peerName);
    FriendProto::AddFriendResponse response;
    stub.AddFriend(nullptr, &request, &response, nullptr);
    Json::Value result;
    result["msgid"] = ADD_FRIEND_MSG;
    result["errcode"] = response.result().errcode();
    result["errmsg"] = response.result().errmsg();
    std::string str = Json::FastWriter().write(result);
    tcpconn->send(str);
}

void MsgServer::delFriend(const muduo::net::TcpConnectionPtr &tcpconn, Json::Value &data)
{
    std::string userName = data["userName"].asString();
    std::string peerName = data["peerName"].asString();

    FriendProto::FriendServiceRpc_Stub stub(new MprpcChannel());
    FriendProto::DelFriendRequest request;
    request.set_adminname(userName);
    request.set_peername(peerName);
    FriendProto::DelFriendResponse response;
    stub.DelFriend(nullptr, &request, &response, nullptr);
    Json::Value result;
    result["msgid"] = DEL_FRIEND_MSG;
    result["errcode"] = response.result().errcode();
    result["errmsg"] = response.result().errmsg();
    std::string str = Json::FastWriter().write(result);
    tcpconn->send(str);
}

void MsgServer::queryFriend(const muduo::net::TcpConnectionPtr &tcpconn, Json::Value &data)
{
    std::string userName = data["userName"].asString();

    FriendProto::FriendServiceRpc_Stub stub(new MprpcChannel());
    FriendProto::GetFriendRequest request;
    request.set_adminname(userName);
    FriendProto::GetFriendResponse response;
    stub.GetFriend(nullptr, &request, &response, nullptr);
    Json::Value result;
    result["msgid"] = QUERY_FRIEND_MSG;
    result["errcode"] = response.result().errcode();
    result["errmsg"] = response.result().errmsg();
    for (auto &val : response.data())
    {
        result["Friend"].append(val.name());
    }
    std::string str = Json::FastWriter().write(result);
    tcpconn->send(str);
}

void MsgServer::groupChat(const muduo::net::TcpConnectionPtr &tcpcon, Json::Value &data) {}

void MsgServer::createGroup(const muduo::net::TcpConnectionPtr &tcpconn, Json::Value &data)
{
    std::string groupName = data["groupName"].asString();
    std::string groupDesc = data["groupDesc"].asString();

    GroupProto::GroupServiceRpc_Stub stub(new MprpcChannel());
    GroupProto::CreateGroupRequest request;
    GroupProto::GroupInfo *group = request.mutable_group();
    group->set_groupname("C++_test");
    group->set_groupdesc("test_C++_group_desc");
    GroupProto::CreateGroupResponse response;
    stub.CreateGroup(nullptr, &request, &response, nullptr);
    Json::Value result;
    result["msgid"] = CREATE_GROUP_MSG;
    result["errcode"] = response.result().errcode();
    result["errmsg"] = response.result().errmsg();
    std::string str = Json::FastWriter().write(result);
    tcpconn->send(str);
}

void MsgServer::addGroup(const muduo::net::TcpConnectionPtr &tcpconn, Json::Value &data)
{
    std::string groupName = data["groupName"].asString();
    std::string userName = data["userName"].asString();
    std::string userRole = data["userRole"].asString();

    GroupProto::GroupServiceRpc_Stub stub(new MprpcChannel());
    GroupProto::AddGroupRequest request;
    request.set_groupname(groupName);
    request.set_username(userName);
    request.set_userrole(userRole);
    GroupProto::AddGroupResponse response;
    stub.AddGroup(nullptr, &request, &response, nullptr);
    Json::Value result;
    result["msgid"] = ADD_GROUP_MSG;
    result["errcode"] = response.result().errcode();
    result["errmsg"] = response.result().errmsg();
    std::string str = Json::FastWriter().write(result);
    tcpconn->send(str);
}

void MsgServer::queryGroup(const muduo::net::TcpConnectionPtr &tcpconn, Json::Value &data)
{
    std::string userName = data["userName"].asString();

    GroupProto::GroupServiceRpc_Stub stub(new MprpcChannel());
    GroupProto::QueryGroupRequest request;
    request.set_username(userName);
    GroupProto::QueryGroupResponse response;
    stub.QueryGroup(nullptr, &request, &response, nullptr);
    Json::Value result;
    result["msgid"] = QUERY_GROUP_MSG;
    result["errcode"] = response.result().errcode();
    result["errmsg"] = response.result().errmsg();
    for (auto &val : response.groups())
    {
        Json::Value group;
        group["groupName"] = val.groupname();
        group["groupDesc"] = val.groupdesc();
        for (auto &user : val.groupusers())
        {
            Json::Value userInfo;
            userInfo["userName"] = user.username();
            userInfo["userEmail"] = user.useremail();
            userInfo["userPhone"] = user.userphone();
            userInfo["userRole"] = user.userrole();
            group["users"].append(userInfo);
        }
        result["groups"].append(group);
    }
    std::string str = Json::FastWriter().write(result);
    tcpconn->send(str);
}

void MsgServer::queryGroupUser(const muduo::net::TcpConnectionPtr &tcpconn, Json::Value &data)
{
    std::string userName = data["userName"].asString();
    std::string groupName = data["groupName"].asString();

    GroupProto::GroupServiceRpc_Stub stub(new MprpcChannel());
    GroupProto::QueryGroupUsersRequest request;
    request.set_username(userName);
    request.set_groupname(groupName);
    GroupProto::QueryGroupUsersResponse response;
    stub.QueryGroupUsers(nullptr, &request, &response, nullptr);
    Json::Value result;
    result["msgid"] = QUERY_GROUP_USERS_MSG;
    result["errcode"] = response.result().errcode();
    result["errmsg"] = response.result().errmsg();
    for (auto &user : response.groupusername())
    {
        Json::Value userInfo;
        userInfo["userName"] = user;
        result["users"].append(userInfo);
    }
    std::string str = Json::FastWriter().write(result);
    tcpconn->send(str);
}

void MsgServer::departChat(const muduo::net::TcpConnectionPtr &tcpconn, Json::Value &data)
{
}

void MsgServer::createDepart(const muduo::net::TcpConnectionPtr &tcpconn, Json::Value &data)
{
    std::string departName = data["departName"].asString();
    std::string departDesc = data["departDesc"].asString();

    DepartProto::DepartServiceRpc_Stub stub(new MprpcChannel());
    DepartProto::CreateDepartRequest request;
    DepartProto::DepartInfo *depart = request.mutable_depart();
    depart->set_departname(departName);
    depart->set_departdesc(departDesc);
    DepartProto::CreateDepartResponse response;
    stub.CreateDepart(nullptr, &request, &response, nullptr);
    Json::Value result;
    result["msgid"] = CREATE_DEPART_MSG;
    result["errcode"] = response.result().errcode();
    result["errmsg"] = response.result().errmsg();
    std::string str = Json::FastWriter().write(result);
    tcpconn->send(str);
}

void MsgServer::addDepart(const muduo::net::TcpConnectionPtr &tcpconn, Json::Value &data)
{
    std::string departName = data["departName"].asString();
    std::string userName = data["userName"].asString();
    std::string userRole = data["userRole"].asString();

    DepartProto::DepartServiceRpc_Stub stub(new MprpcChannel());
    DepartProto::AddDepartRequest request;
    request.set_departname(departName);
    request.set_username(userName);
    request.set_userrole(userRole);
    DepartProto::AddDepartResponse response;
    stub.AddDepart(nullptr, &request, &response, nullptr);
    Json::Value result;
    result["msgid"] = ADD_DEPART_MSG;
    result["errcode"] = response.result().errcode();
    result["errmsg"] = response.result().errmsg();
    std::string str = Json::FastWriter().write(result);
    tcpconn->send(str);
}

void MsgServer::queryDepartUser(const muduo::net::TcpConnectionPtr &tcpconn, Json::Value &data)
{
    std::string userName = data["userName"].asString();
    std::string departName = data["departName"].asString();

    DepartProto::DepartServiceRpc_Stub stub(new MprpcChannel());
    DepartProto::QueryDepartUsersRequest request;
    request.set_departname(departName);
    request.set_username(userName);
    DepartProto::QueryDepartUsersResponse response;
    stub.QueryDepartUsers(nullptr, &request, &response, nullptr);
    Json::Value result;
    result["msgid"] = QUERY_DEPART_USERS_MSG;
    result["errcode"] = response.result().errcode();
    result["errmsg"] = response.result().errmsg();
    for (auto &user : response.departusername())
    {
        Json::Value userInfo;
        userInfo["userName"] = user;
        result["users"].append(userInfo);
    }
    std::string str = Json::FastWriter().write(result);
    tcpconn->send(str);
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