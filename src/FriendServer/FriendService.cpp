#include "FriendService.h"

bool FriendServer::AddFriend(std::string adminName, std::string peerName,
                             Friend::ResultCode *code)
{
    bool result = friendmodel.insert(adminName, peerName);
    if (result)
    {
        code->set_errcode(0);
        code->set_errmsg("AddFriend successful");
    }
    else
    {
        code->set_errcode(1);
        code->set_errmsg("AddFriend failed");
    }
    return result;
}

bool FriendServer::GetFriend(std::string adminName,
                             Friend::ResultCode *code,
                             std::vector<Friend::AdminInfo> &friends)
{
    bool result = false;
    std::vector<Admin> vec = friendmodel.query(adminName);
    if (vec.empty())
    {
        code->set_errcode(1);
        code->set_errmsg("GetFriend failed");
    }
    else
    {
        for (const auto &val : vec)
        {
            Friend::AdminInfo temp;
            temp.set_name(val.getName().c_str());
            temp.set_email(val.getEmail().c_str());
            temp.set_phone(val.getPhone().c_str());
            friends.push_back(temp);
        }
        result = true;
        code->set_errcode(0);
        code->set_errmsg("GetFriend successful");
    }
    return result;
}

bool FriendServer::DelFriend(std::string adminName, std::string peerName,
                             Friend::ResultCode *code)
{
    bool result = friendmodel.removal(adminName, peerName);
    if (result)
    {
        code->set_errcode(0);
        code->set_errmsg("DelFriend successful");
    }
    else
    {
        code->set_errcode(1);
        code->set_errmsg("DelFriend failed");
    }
    return result;
}

void FriendServer::AddFriend(::google::protobuf::RpcController *controller,
                             const ::Friend::AddFriendRequest *request,
                             ::Friend::AddFriendResponse *response,
                             ::google::protobuf::Closure *done)
{
    std::string adminName = request->adminname();
    std::string peerName = request->peername();

    Friend::ResultCode *code = response->mutable_result();
    bool result = AddFriend(adminName, peerName, code);

    response->set_success(result);

    done->Run();
}

void FriendServer::GetFriend(::google::protobuf::RpcController *controller,
                             const ::Friend::GetFriendRequest *request,
                             ::Friend::GetFriendResponse *response,
                             ::google::protobuf::Closure *done)
{
    std::string adminName = request->adminname();

    Friend::ResultCode *code = response->mutable_result();
    std::vector<Friend::AdminInfo> friends;
    bool result = GetFriend(adminName, code, friends);

    for (const auto &val : friends)
    {
        Friend::AdminInfo *temp = response->add_data();
        temp->set_name(val.name());
        temp->set_email(val.email());
        temp->set_phone(val.phone());
    }

    response->set_success(result);

    done->Run();
}

void FriendServer::DelFriend(::google::protobuf::RpcController *controller,
                             const ::Friend::DelFriendRequest *request,
                             ::Friend::DelFriendResponse *response,
                             ::google::protobuf::Closure *done)
{
    std::string adminName = request->adminname();
    std::string peerName = request->peername();

    Friend::ResultCode *code = response->mutable_result();
    bool result = DelFriend(adminName, peerName, code);

    response->set_success(result);

    done->Run();
}
