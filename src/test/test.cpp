#include <iostream>
#include "Login.pb.h"
#include "Friend.pb.h"
#include "mprpcapplication.h"
#include "mprpcchannel.h"

#include <unistd.h>

int test_Login(int argc, char **argv)
{
    MprpcApplication::Init(argc, argv);

    Login::UserServiceRpc_Stub stub(new MprpcChannel());

    // {
    //     Login::RegisterRequest request;
    //     request.set_name("test_6");
    //     request.set_pwd("123456");
    //     request.set_email("xxxxxxxxxxxxxx123");
    //     request.set_phone("123456789");

    //     Login::RegisterResponse response;

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
        Login::RetrieveRequest request;
        request.set_name("test_2");
        request.set_pwd("123456789");
        request.set_email("2783688001@qq.com");
        request.set_phone("13926413813");

        Login::RetrieveResponse response;

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
    //     Login::LogoutRequest request;
    //     request.set_name("123");

    //     Login::LogoutResponse response;

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

    Friend::FriendServiceRpc_Stub stub(new MprpcChannel());

    // {
    //     Friend::DelFriendRequest request;
    //     request.set_adminname("test_3");
    //     request.set_peername("test_4");
    //     Friend::DelFriendResponse response;

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
        Friend::GetFriendRequest request;
        request.set_adminname("test_1");
        Friend::GetFriendResponse response;

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


    return 0;
}

int main(int argc, char **argv)
{
    // test_Login(argc, argv);
    // test_friend(argc, argv);
    test_group(argc, argv);
}