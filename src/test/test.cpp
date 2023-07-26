#include <iostream>
#include "Login.pb.h"
#include "Friend.pb.h"
#include "Group.pb.h"
#include "Depart.pb.h"
#include "ChatMsg.pb.h"
#include "offlinemessage.pb.h"
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

int test_depart(int argc, char **argv)
{
    MprpcApplication::Init(argc, argv);

    DepartProto::DepartServiceRpc_Stub stub(new MprpcChannel());

    // {
    //     DepartProto::CreateDepartRequest request;
    //     DepartProto::DepartInfo *depart = request.mutable_depart();
    //     depart->set_departname("test_2");
    //     depart->set_departdesc("test_code");

    //     DepartProto::CreateDepartResponse response;
    //     stub.CreateDepart(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc CreateDepart response success: "
    //                   << response.success() << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "rpc CreateDepart response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    // {
    //     DepartProto::AddDepartRequest request;
    //     request.set_departname("test_2");
    //     request.set_username("test_2");
    //     request.set_userrole("intendant");
    //     DepartProto::AddDepartResponse response;
    //     stub.AddDepart(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc AddDepart response success: "
    //                   << response.success() << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "rpc AddDepart response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    // {
    //     DepartProto::QueryDepartRequest request;
    //     request.set_username("test_2");
    //     DepartProto::QueryDepartResponse response;
    //     stub.QueryDepart(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         for (auto &val : response.departs())
    //         {
    //             std::cout << "============================"
    //                       << val.departname() << " "
    //                       << val.departdesc() << " "
    //                       << "============================";
    //             for (auto &user : val.departusers())
    //             {
    //                 std::cout << "=========================="
    //                           << user.username() << " "
    //                           << user.useremail() << " "
    //                           << user.userphone() << " "
    //                           << user.userrole() << " "
    //                           << "==========================";
    //             }
    //         }
    //         std::cout << "rpc QueryDepart response success: "
    //                   << response.success() << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "rpc QueryDepart response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    {
        DepartProto::QueryDepartUsersRequest request;
        request.set_username("test_2");
        request.set_departname("C++");
        DepartProto::QueryDepartUsersResponse response;
        stub.QueryDepartUsers(nullptr, &request, &response, nullptr);
        if (0 == response.result().errcode())
        {
            for (auto &user : response.departusername())
            {
                std::cout << "=========================="
                          << user << " "
                          << "==========================";
            }
            std::cout << "rpc QueryDepartUsers response success: "
                      << response.success() << std::endl;
        }
        else
        {
            std::cout << "rpc QueryDepartUsers response error: "
                      << response.result().errmsg() << std::endl;
        }
    }

    return 0;
}

int test_offlineMsg(int argc, char **argv)
{
    MprpcApplication::Init(argc, argv);
    OfflineMessageProto::offlineMsgRpc_Stub stub(new MprpcChannel());

    // {
    //     OfflineMessageProto::addOfflineMsgRequest request;
    //     request.mutable_offlinemsg()->set_recvname("test_2");
    //     request.mutable_offlinemsg()->set_sendname("test_1");
    //     request.mutable_offlinemsg()->set_message("test_C++_code");
    //     OfflineMessageProto::addOfflineMsgResponse response;

    //     stub.AddOfflineMsg(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc AddOfflineMsg response success: "
    //                   << response.success() << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "rpc AddOfflineMsg response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    // {
    //     OfflineMessageProto::addOfflineGroupMsgRequest request;
    //     request.mutable_offlinegroupmsg()->set_groupname("test_2");
    //     request.mutable_offlinegroupmsg()->set_sendname("test_1");
    //     request.mutable_offlinegroupmsg()->set_message("test_C++_code");
    //     OfflineMessageProto::addOfflineGroupMsgResponse response;

    //     stub.AddOfflineGroupMsg(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc AddOfflineGroupMsg response success: "
    //                   << response.success() << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "rpc AddOfflineGroupMsg response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    // {
    //     OfflineMessageProto::addOfflineDepartMsgRequest request;
    //     request.mutable_offlinedepartmsg()->set_departname("test_2");
    //     request.mutable_offlinedepartmsg()->set_sendname("test_1");
    //     request.mutable_offlinedepartmsg()->set_message("test_C++_code");
    //     OfflineMessageProto::addOfflineDepartMsgResponse response;

    //     stub.AddOfflineDepartMsg(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc AddOfflineDepartMsg response success: "
    //                   << response.success() << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "rpc AddOfflineDepartMsg response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    // {
    //     OfflineMessageProto::delOfflineMsgRequest request;
    //     request.mutable_offlinemsg()->set_msgid(3);
    //     request.mutable_offlinemsg()->set_recvname("test_2");
    //     request.mutable_offlinemsg()->set_sendname("test_1");
    //     request.mutable_offlinemsg()->set_message("test_C++_code");
    //     OfflineMessageProto::delOfflineMsgResponse response;

    //     stub.DelOfflineMsg(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc DelOfflineMsg response success: "
    //                   << response.success() << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "rpc DelOfflineMsg response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    // {
    //     OfflineMessageProto::delOfflineGroupMsgRequest request;
    //     request.mutable_offlinegroupmsg()->set_msgid(3);
    //     request.mutable_offlinegroupmsg()->set_groupname("test_2");
    //     request.mutable_offlinegroupmsg()->set_sendname("test_1");
    //     request.mutable_offlinegroupmsg()->set_message("test_C++_code");
    //     OfflineMessageProto::delOfflineGroupMsgResponse response;

    //     stub.DelOfflineGroupMsg(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc DelOfflineGroupMsg response success: "
    //                   << response.success() << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "rpc DelOfflineGroupMsg response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    // {
    //     OfflineMessageProto::delOfflineDepartMsgRequest request;
    //     request.mutable_offlinedepartmsg()->set_msgid(2);
    //     request.mutable_offlinedepartmsg()->set_departname("test_2");
    //     request.mutable_offlinedepartmsg()->set_sendname("test_1");
    //     request.mutable_offlinedepartmsg()->set_message("test_C++_code");
    //     OfflineMessageProto::delOfflineDepartMsgResponse response;

    //     stub.DelOfflineDepartMsg(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc DelOfflineDepartMsg response success: "
    //                   << response.success() << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "rpc DelOfflineDepartMsg response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    {
        OfflineMessageProto::queryOfflineMsgRequest request;
        request.set_recvname("test_2");
        OfflineMessageProto::queryOfflineMsgResponse response;

        stub.QueryOfflineMsg(nullptr, &request, &response, nullptr);
        if (0 == response.result().errcode())
        {
            std::cout << "rpc QueryOfflineMsg response success: "
                      << response.success() << std::endl;
            for (const auto &val : response.offlinemsg())
            {
                std::cout << "========================="
                          << val.msgid() << " "
                          << val.recvname() << " "
                          << val.sendname() << " "
                          << val.message() << " "
                          << "=========================";
            }
        }
        else
        {
            std::cout << "rpc QueryOfflineMsg response error: "
                      << response.result().errmsg() << std::endl;
        }
    }

    {
        OfflineMessageProto::queryOfflineGroupMsgRequest request;
        request.set_username("test_2");
        OfflineMessageProto::queryOfflineGroupMsgResponse response;

        stub.QueryOfflineGroupMsg(nullptr, &request, &response, nullptr);
        if (0 == response.result().errcode())
        {
            std::cout << "rpc QueryOfflineGroupMsg response success: "
                      << response.success() << std::endl;
            for (const auto &val : response.offlinegroupmsg())
            {
                std::cout << "========================="
                          << val.msgid() << " "
                          << val.groupname() << " "
                          << val.sendname() << " "
                          << val.message() << " "
                          << "=========================";
            }
        }
        else
        {
            std::cout << "rpc QueryOfflineGroupMsg response error: "
                      << response.result().errmsg() << std::endl;
        }
    }

    {
        OfflineMessageProto::queryOfflineDepartMsgRequest request;
        request.set_username("test_2");
        OfflineMessageProto::queryOfflineDepartMsgResponse response;

        stub.QueryOfflineDepartMsg(nullptr, &request, &response, nullptr);
        if (0 == response.result().errcode())
        {
            std::cout << "rpc QueryOfflineDepartMsg response success: "
                      << response.success() << std::endl;
            for (const auto &val : response.offlinedepartmsg())
            {
                std::cout << "========================="
                          << val.msgid() << " "
                          << val.departname() << " "
                          << val.sendname() << " "
                          << val.message() << " "
                          << "=========================";
            }
        }
        else
        {
            std::cout << "rpc QueryOfflineDepartMsg response error: "
                      << response.result().errmsg() << std::endl;
        }
    }

    return 0;
}

int test_chatMsg(int argc, char **argv)
{
    MprpcApplication::Init(argc, argv);
    ChatMessageProto::chatMsgRpc_Stub stub(new MprpcChannel());

    // {
    //     ChatMessageProto::addMsgRequest request;
    //     request.mutable_msg()->set_recvname("test_2");
    //     request.mutable_msg()->set_sendname("test_1");
    //     request.mutable_msg()->set_message("test_C++_code");
    //     ChatMessageProto::addMsgResponse response;

    //     stub.AddChatMsg(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc AddChatMsg response success: "
    //                   << response.success() << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "rpc AddChatMsg response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    // {
    //     ChatMessageProto::addGroupMsgRequest request;
    //     request.mutable_groupmsg()->set_groupname("test_2");
    //     request.mutable_groupmsg()->set_sendname("test_1");
    //     request.mutable_groupmsg()->set_message("test_C++_code");
    //     ChatMessageProto::addGroupMsgResponse response;

    //     stub.AddGroupChatMsg(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc AddGroupChatMsg response success: "
    //                   << response.success() << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "rpc AddGroupChatMsg response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    // {
    //     ChatMessageProto::addDepartMsgRequest request;
    //     request.mutable_departmsg()->set_departname("test_2");
    //     request.mutable_departmsg()->set_sendname("test_1");
    //     request.mutable_departmsg()->set_message("test_C++_code");
    //     ChatMessageProto::addDepartMsgResponse response;

    //     stub.AddDepartChatMsg(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc AddDepartChatMsg response success: "
    //                   << response.success() << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "rpc AddDepartChatMsg response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    // {
    //     ChatMessageProto::addDepartMsgRequest request;
    //     request.mutable_departmsg()->set_departname("test_2");
    //     request.mutable_departmsg()->set_sendname("test_1");
    //     request.mutable_departmsg()->set_message("test_C++_code");
    //     ChatMessageProto::addDepartMsgResponse response;

    //     stub.AddDepartChatMsg(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc AddDepartChatMsg response success: "
    //                   << response.success() << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "rpc AddDepartChatMsg response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    // {
    //     ChatMessageProto::delMsgRequest request;
    //     request.mutable_msg()->set_msgid(3);
    //     request.mutable_msg()->set_recvname("test_2");
    //     request.mutable_msg()->set_sendname("test_1");
    //     request.mutable_msg()->set_message("test_C++_code");
    //     ChatMessageProto::delMsgResponse response;

    //     stub.DelChatMsg(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc DelChatMsg response success: "
    //                   << response.success() << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "rpc DelChatMsg response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    // {
    //     ChatMessageProto::delGroupMsgRequest request;
    //     request.mutable_groupmsg()->set_msgid(3);
    //     request.mutable_groupmsg()->set_groupname("test_2");
    //     request.mutable_groupmsg()->set_sendname("test_1");
    //     request.mutable_groupmsg()->set_message("test_C++_code");
    //     ChatMessageProto::delGroupMsgResponse response;

    //     stub.DelGroupChatMsg(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc DelGroupChatMsg response success: "
    //                   << response.success() << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "rpc DelGroupChatMsg response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    // {
    //     ChatMessageProto::delDepartMsgRequest request;
    //     request.mutable_departmsg()->set_msgid(2);
    //     request.mutable_departmsg()->set_departname("test_2");
    //     request.mutable_departmsg()->set_sendname("test_1");
    //     request.mutable_departmsg()->set_message("test_C++_code");
    //     ChatMessageProto::delDepartMsgResponse response;

    //     stub.DelDepartChatMsg(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc DelDepartChatMsg response success: "
    //                   << response.success() << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "rpc DelDepartChatMsg response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    // {
    //     ChatMessageProto::queryMsgRequest request;
    //     request.set_recvname("test_1");
    //     ChatMessageProto::queryMsgResponse response;

    //     stub.QueryChatMsg(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc QueryChatMsg response success: "
    //                   << response.success() << std::endl;
    //         for (const auto &val : response.msg())
    //         {
    //             std::cout << "========================="
    //                       << val.msgid() << " "
    //                       << val.recvname() << " "
    //                       << val.sendname() << " "
    //                       << val.message() << " "
    //                       << "=========================";
    //         }
    //     }
    //     else
    //     {
    //         std::cout << "rpc QueryChatMsg response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    // {
    //     ChatMessageProto::queryOfflineMsgRequest request;
    //     request.set_recvname("test_2");
    //     ChatMessageProto::queryOfflineMsgResponse response;

    //     stub.QueryOfflineMsg(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc QueryOfflineMsg response success: "
    //                   << response.success() << std::endl;
    //         for (const auto &val : response.msg())
    //         {
    //             std::cout << "========================="
    //                       << val.msgid() << " "
    //                       << val.recvname() << " "
    //                       << val.sendname() << " "
    //                       << val.message() << " "
    //                       << "=========================";
    //         }
    //     }
    //     else
    //     {
    //         std::cout << "rpc QueryOfflineMsg response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    // {
    //     ChatMessageProto::queryGroupMsgRequest request;
    //     request.set_username("test_3");
    //     ChatMessageProto::queryGroupMsgResponse response;

    //     stub.QueryGroupChatMsg(nullptr, &request, &response, nullptr);
    //     if (0 == response.result().errcode())
    //     {
    //         std::cout << "rpc QueryGroupChatMsg response success: "
    //                   << response.success() << std::endl;
    //         for (const auto &val : response.groupmsg())
    //         {
    //             std::cout << "========================="
    //                       << val.msgid() << " "
    //                       << val.groupname() << " "
    //                       << val.sendname() << " "
    //                       << val.message() << " "
    //                       << "=========================";
    //         }
    //     }
    //     else
    //     {
    //         std::cout << "rpc QueryGroupChatMsg response error: "
    //                   << response.result().errmsg() << std::endl;
    //     }
    // }

    {
        ChatMessageProto::queryDepartMsgRequest request;
        request.set_username("test_3");
        ChatMessageProto::queryDepartMsgResponse response;

        stub.QueryDepartChatMsg(nullptr, &request, &response, nullptr);
        if (0 == response.result().errcode())
        {
            std::cout << "rpc QueryDepartChatMsg response success: "
                      << response.success() << std::endl;
            for (const auto &val : response.departmsg())
            {
                std::cout << "========================="
                          << val.msgid() << " "
                          << val.departname() << " "
                          << val.sendname() << " "
                          << val.message() << " "
                          << "=========================";
            }
        }
        else
        {
            std::cout << "rpc QueryDepartChatMsg response error: "
                      << response.result().errmsg() << std::endl;
        }
    }

    return 0;
}

int main(int argc, char **argv)
{
    // test_Login(argc, argv);
    // test_friend(argc, argv);
    // test_group(argc, argv);
    // test_depart(argc, argv);
    // test_offlineMsg(argc, argv);
    test_chatMsg(argc, argv);
    return 0;
}