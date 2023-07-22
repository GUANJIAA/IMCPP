#include <iostream>
#include "Login.pb.h"
#include "Friend.pb.h"
#include "Group.pb.h"
#include "mprpcapplication.h"
#include "mprpcchannel.h"

#include <unistd.h>

int test_Login(int argc, char **argv)
{
    MprpcApplication::Init(argc, argv);

    LoginProto::UserServiceRpc_Stub stub(new MprpcChannel());

    // {
    //     LoginProto::RegisterRequest request;
    //     request.set_name("test_6");
    //     request.set_pwd("123456");
    //     request.set_email("xxxxxxxxxxxxxx123");
    //     request.set_phone("123456789");

    //     LoginProto::RegisterResponse response;

    //     stub.Register(nullptr, &request, &response, nullptr);

    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc login response success: "
    //                   << response.success() << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "rpc login response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    {
        LoginProto::RetrieveRequest request;
        request.set_name("test_2");
        request.set_pwd("123456789");
        request.set_email("2783688001@qq.com");
        request.set_phone("13926413813");

        LoginProto::RetrieveResponse response;

        stub.Retrieve(nullptr, &request, &response, nullptr);

        if (0 == response.result().errcode())
        {
            std::cout << "rpc login response success: "
                      << response.success() << std::endl;
        }
        else
        {
            std::cout << "rpc login response error: "
                      << response.result().errmsg() << std::endl;
        }
    }

    // sleep(10);

    // {
    //     LoginProto::LogoutRequest request;
    //     request.set_name("123");

    //     LoginProto::LogoutResponse response;

    //     stub.Logout(nullptr, &request, &response, nullptr);

    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc login response success: "
    //                   << response.success() << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "rpc login response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    return 0;
}

int test_friend(int argc, char **argv)
{
    MprpcApplication::Init(argc, argv);

    FriendProto::FriendServiceRpc_Stub stub(new MprpcChannel());

    // {
    //     FriendProto::DelFriendRequest request;
    //     request.set_adminname("test_3");
    //     request.set_peername("test_4");
    //     FriendProto::DelFriendResponse response;

    //     stub.DelFriend(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc DelFriend response success: "
    //                   << response.success() << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "rpc DelFriend response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    {
        FriendProto::GetFriendRequest request;
        request.set_adminname("test_1");
        FriendProto::GetFriendResponse response;

        stub.GetFriend(nullptr, &request, &response, nullptr);
        if (0 == response.result().errcode())
        {
            for (const auto &val : response.data())
            {
                std::cout << "==========================="
                          << val.name() << " "
                          << val.email() << " "
                          << val.phone() << " "
                          << "===========================";
            }
            std::cout << "rpc DelFriend response success: "
                      << response.success() << std::endl;
        }
        else
        {
            std::cout << "rpc DelFriend response error: "
                      << response.result().errmsg() << std::endl;
        }
    }

    return 0;
}

int test_group(int argc, char **argv)
{
    MprpcApplication::Init(argc, argv);

    GroupProto::GroupServiceRpc_Stub stub(new MprpcChannel());

    // {
    //     GroupProto::CreateGroupRequest request;
    //     GroupProto::GroupInfo *group = request.mutable_group();
    //     group->set_groupname("test_2");
    //     group->set_groupdesc("test_code");

    //     GroupProto::CreateGroupResponse response;
    //     stub.CreateGroup(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc DelFriend response success: "
    //                   << response.success() << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "rpc DelFriend response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    // {
    //     GroupProto::AddGroupRequest request;
    //     request.set_groupname("test_2");
    //     request.set_username("test_2");
    //     request.set_userrole("normal");
    //     GroupProto::AddGroupResponse response;
    //     stub.AddGroup(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc DelFriend response success: "
    //                   << response.success() << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "rpc DelFriend response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    // {
    //     GroupProto::QueryGroupRequest request;
    //     request.set_username("test_2");
    //     GroupProto::QueryGroupResponse response;
    //     stub.QueryGroup(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         for (auto &val : response.groups())
    //         {
    //             std::cout << "============================"
    //                       << val.groupname() << " "
    //                       << val.groupdesc() << " "
    //                       << "============================";
    //             for (auto &user : val.groupusers())
    //             {
    //                 std::cout << "=========================="
    //                           << user.username() << " "
    //                           << user.useremail() << " "
    //                           << user.userphone() << " "
    //                           << user.userrole() << " "
    //                           << "==========================";
    //             }
    //         }
    //         std::cout << "rpc DelFriend response success: "
    //                   << response.success() << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "rpc DelFriend response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    {
        GroupProto::QueryGroupUsersRequest request;
        request.set_username("test_2");
        request.set_groupname("C++");
        GroupProto::QueryGroupUsersResponse response;
        stub.QueryGroupUsers(nullptr, &request, &response, nullptr);
        if (0 == response.result().errcode())
        {
            for (auto &user : response.groupusername())
            {
                std::cout << "=========================="
                          << user << " "
                          << "==========================";
            }
            std::cout << "rpc DelFriend response success: "
                      << response.success() << std::endl;
        }
        else
        {
            std::cout << "rpc DelFriend response error: "
                      << response.result().errmsg() << std::endl;
        }
    }

    return 0;
}

int main(int argc, char **argv)
{
    // test_Login(argc, argv);
    // test_friend(argc, argv);
    test_group(argc, argv);
}