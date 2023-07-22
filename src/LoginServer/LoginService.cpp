#include "LoginService.h"
#include "mysqldb.h"
#include "admin.h"
#include "logger.h"

#include <iostream>

bool LoginService::Login(std::string name, std::string pwd, LoginProto::ResultCode *code)
{
    Admin admin = adminmodel.query(name);
    if (admin.getName() == name && admin.getPassword() == pwd)
    {
        if (admin.getStatus() == "online")
        {
            code->set_errcode(2);
            code->set_errmsg("The user is already logged in");
            return false;
        }
        else
        {
            admin.setStatus("online");
            adminmodel.updateState(admin);
        }
    }
    else
    {
        code->set_errcode(1);
        code->set_errmsg("The user does not exist or the password is incorrect");
        return false;
    }

    code->set_errcode(0);
    code->set_errmsg("Login successful");
    return true;
}

bool LoginService::Logout(std::string name, LoginProto::ResultCode *code)
{
    Admin admin = adminmodel.query(name);
    if (admin.getStatus() == "offline")
    {
        code->set_errcode(1);
        code->set_errmsg("Account has been logged out");
        return false;
    }
    else
    {
        admin.setStatus("offline");
        adminmodel.updateState(admin);
        code->set_errcode(0);
        code->set_errmsg("Account logged out successful");
    }
    return true;
}

bool LoginService::Register(std::string name, std::string pwd,
                            std::string email, std::string phone,
                            LoginProto::ResultCode *code)
{
    Admin admin;
    admin.setName(name);
    admin.setPassword(pwd);
    admin.setStatus("offline");
    admin.setEmail(email);
    admin.setPhone(phone);

    bool state = adminmodel.insert(admin);
    if (state)
    {
        code->set_errcode(0);
        code->set_errmsg("Registration successful");
    }
    else
    {
        code->set_errcode(1);
        code->set_errmsg("Registration failed");
    }
    return state;
}

bool LoginService::Retrieve(std::string name, std::string password,
                            std::string email, std::string phone,
                            LoginProto::ResultCode *code)
{
    Admin admin = adminmodel.query(name);
    if (admin.getName() == name &&
        admin.getEmail() == email &&
        admin.getPhone() == phone)
    {
        admin.setPassword(password);
        if (!adminmodel.update(admin))
        {
            code->set_errcode(1);
            code->set_errmsg("Retrieve failed");
        }
        else
        {
            code->set_errcode(0);
            code->set_errmsg("Retrieve successed");
        }
    }
    else
    {
        code->set_errcode(1);
        code->set_errmsg("Retrieve failed info error");
    }
    return true;
}

void LoginService::Login(::google::protobuf::RpcController *controller,
                         const ::LoginProto::LoginRequest *request,
                         ::LoginProto::LoginResponse *response,
                         ::google::protobuf::Closure *done)
{
    std::string name = request->name();
    std::string pwd = request->pwd();

    LoginProto::ResultCode *code = response->mutable_result();
    bool login_result = Login(name, pwd, code);

    response->set_success(login_result);

    done->Run();
}

void LoginService::Logout(::google::protobuf::RpcController *controller,
                          const ::LoginProto::LogoutRequest *request,
                          ::LoginProto::LogoutResponse *response,
                          ::google::protobuf::Closure *done)
{
    std::string name = request->name();

    LoginProto::ResultCode *code = response->mutable_result();
    bool login_result = Logout(name, code);
    response->set_success(login_result);

    done->Run();
}

void LoginService::Register(::google::protobuf::RpcController *controller,
                            const ::LoginProto::RegisterRequest *request,
                            ::LoginProto::RegisterResponse *response,
                            ::google::protobuf::Closure *done)
{
    std::string name = request->name();
    std::string pwd = request->pwd();
    std::string email = request->email();
    std::string phone = request->phone();

    LoginProto::ResultCode *code = response->mutable_result();
    bool login_result = Register(name, pwd, email, phone, code);
    response->set_success(login_result);

    done->Run();
}

void LoginService::Retrieve(::google::protobuf::RpcController *controller,
                            const ::LoginProto::RetrieveRequest *request,
                            ::LoginProto::RetrieveResponse *response,
                            ::google::protobuf::Closure *done)
{
    std::string name = request->name();
    std::string password = request->pwd();
    std::string email = request->email();
    std::string phone = request->phone();

    LoginProto::ResultCode *code = response->mutable_result();
    bool login_result = Retrieve(name, password, email, phone, code);
    response->set_success(login_result);

    done->Run();
}