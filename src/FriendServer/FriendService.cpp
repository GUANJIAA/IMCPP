#include "FriendService.h"

bool FriendService::AddFriend(std::string adminName, std::string peerName,
                              FriendProto::ResultCode *code)
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

bool FriendService::GetFriend(std::string adminName,
                              FriendProto::ResultCode *code,
                              std::vector<FriendProto::AdminInfo> &friends)
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
            FriendProto::AdminInfo temp;
            temp.set_name(val.getName());
            temp.set_email(val.getEmail());
            temp.set_status(val.getStatus());
            temp.set_phone(val.getPhone());
            temp.set_desc(val.getDesc());
            temp.set_departname(val.getDepartName());
//            std::cout<<val.getStatus()<<":"<<val.getDesc()<<":"<<val.getDepartName()<<std::endl;
            friends.push_back(temp);
        }
        result = true;
        code->set_errcode(0);
        code->set_errmsg("GetFriend successful");
    }
    return result;
}

bool FriendService::DelFriend(std::string adminName, std::string peerName,
                              FriendProto::ResultCode *code)
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

void FriendService::AddFriend(::google::protobuf::RpcController *controller,
                              const ::FriendProto::AddFriendRequest *request,
                              ::FriendProto::AddFriendResponse *response,
                              ::google::protobuf::Closure *done)
{
    std::string adminName = request->adminname();
    std::string peerName = request->peername();

    FriendProto::ResultCode *code = response->mutable_result();
    bool result = AddFriend(adminName, peerName, code);

    response->set_success(result);
    done->Run();
}

void FriendService::GetFriend(::google::protobuf::RpcController *controller,
                              const ::FriendProto::GetFriendRequest *request,
                              ::FriendProto::GetFriendResponse *response,
                              ::google::protobuf::Closure *done)
{
    std::string adminName = request->adminname();

    FriendProto::ResultCode *code = response->mutable_result();
    std::vector<FriendProto::AdminInfo> friends;
    bool result = GetFriend(adminName, code, friends);

    for (const auto &val : friends)
    {
        FriendProto::AdminInfo *temp = response->add_data();
        temp->set_name(val.name());
        temp->set_email(val.email());
        temp->set_phone(val.phone());
        temp->set_status(val.status());
        temp->set_desc(val.desc());
        temp->set_departname(val.departname());
    }

    response->set_success(result);

    done->Run();
}

void FriendService::DelFriend(::google::protobuf::RpcController *controller,
                              const ::FriendProto::DelFriendRequest *request,
                              ::FriendProto::DelFriendResponse *response,
                              ::google::protobuf::Closure *done)
{
    std::string adminName = request->adminname();
    std::string peerName = request->peername();

    FriendProto::ResultCode *code = response->mutable_result();
    bool result = DelFriend(adminName, peerName, code);

    response->set_success(result);

    done->Run();
}
