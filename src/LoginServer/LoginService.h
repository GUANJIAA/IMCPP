#ifndef __LOGINSERVICE_H__
#define __LOGINSERVICE_H__

#include "Login.pb.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"
#include "adminModel.h"

#include <iostream>
#include <string>

class LoginService : public Login::UserServiceRpc
{
public:
    bool Login(std::string name, std::string pwd,
               Login::ResultCode *code);

    bool Logout(std::string name, Login::ResultCode *code);

    bool Register(std::string name, std::string pwd,
                  std::string email, std::string phone,
                  Login::ResultCode *code);

    bool Retrieve(std::string name, std::string password,
                  std::string email, std::string phone,
                  Login::ResultCode *code);

    virtual void Login(::google::protobuf::RpcController *controller,
                       const ::Login::LoginRequest *request,
                       ::Login::LoginResponse *response,
                       ::google::protobuf::Closure *done) override;

    virtual void Logout(::google::protobuf::RpcController *controller,
                        const ::Login::LogoutRequest *request,
                        ::Login::LogoutResponse *response,
                        ::google::protobuf::Closure *done) override;

    virtual void Register(::google::protobuf::RpcController *controller,
                          const ::Login::RegisterRequest *request,
                          ::Login::RegisterResponse *response,
                          ::google::protobuf::Closure *done) override;

    virtual void Retrieve(::google::protobuf::RpcController *controller,
                          const ::Login::RetrieveRequest *request,
                          ::Login::RetrieveResponse *response,
                          ::google::protobuf::Closure *done) override;

private:
    AdminModel adminmodel;
};

#endif