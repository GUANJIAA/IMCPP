#ifndef __FRIENDSERVICE_H__
#define __FRIENDSERVICE_H__

#include "Friend.pb.h"
#include "friendmodel.h"
#include "admin.h"

#include <string>
#include <vector>

class FriendServer : public Friend::FriendServiceRpc
{
public:
    bool AddFriend(std::string adminName, std::string peerName,
                   Friend::ResultCode *code);

    bool GetFriend(std::string adminName, Friend::ResultCode *code,
                   std::vector<Friend::AdminInfo> &friends);

    bool DelFriend(std::string adminName, std::string peerName,
                   Friend::ResultCode *code);

    virtual void AddFriend(::google::protobuf::RpcController *controller,
                           const ::Friend::AddFriendRequest *request,
                           ::Friend::AddFriendResponse *response,
                           ::google::protobuf::Closure *done) override;

    virtual void GetFriend(::google::protobuf::RpcController *controller,
                           const ::Friend::GetFriendRequest *request,
                           ::Friend::GetFriendResponse *response,
                           ::google::protobuf::Closure *done) override;

    virtual void DelFriend(::google::protobuf::RpcController *controller,
                           const ::Friend::DelFriendRequest *request,
                           ::Friend::DelFriendResponse *response,
                           ::google::protobuf::Closure *done) override;

private:
    FriendModel friendmodel;
};

#endif