#include "DepartService.h"
#include "redisdb.h"

#include <iostream>

bool DepartService::CreateDepart(Depart &depart, DepartProto::ResultCode *code)
{
    bool result = departmodel.createDepart(depart);
    if (result)
    {
        code->set_errcode(0);
        code->set_errmsg("CreateDepart successful");
    }
    else
    {
        code->set_errcode(1);
        code->set_errmsg("CreateDepart failed");
    }
    return result;
}

bool DepartService::AddDepart(std::string departName,
                              std::string userName,
                              std::string userRole,
                              DepartProto::ResultCode *code)
{
    bool result = departmodel.addDepart(departName, userName, userRole);
    if (result)
    {
        code->set_errcode(0);
        code->set_errmsg("AddDepart successful");
    }
    else
    {
        code->set_errcode(1);
        code->set_errmsg("AddDepart failed");
    }
    return result;
}

bool DepartService::QueryDepart(std::string userName,
                                DepartProto::DepartInfo &Departs,
                                DepartProto::ResultCode *code)
{
    Depart departVec = departmodel.queryDepart(userName);
    bool result = false;
    if (departVec.getName() == "")
    {
        code->set_errcode(1);
        code->set_errmsg("QueryDepart failed");
    }
    else
    {
        Departs.set_departid(departVec.getId());
        Departs.set_departname(departVec.getName());
        Departs.set_departdesc(departVec.getDesc());
        for (auto &uval : departVec.getUsers())
        {
            DepartProto::DepartUser *info = Departs.add_departusers();
            info->set_username(uval.getName());
            info->set_useremail(uval.getEmail());
            info->set_userphone(uval.getPhone());
            info->set_userrole(uval.getRole());
        }
        result = true;
        code->set_errcode(0);
        code->set_errmsg("QueryDepart successful");
    }
    return result;
}

bool DepartService::QueryDepartUsers(std::string departName,
                                     std::string userName,
                                     std::vector<std::string> &departusers,
                                     DepartProto::ResultCode *code)
{
    departusers = departmodel.queryDepartUsers(departName, userName);
    if (departusers.empty())
    {
        code->set_errcode(1);
        code->set_errmsg("QueryDepartUsers failed");
        return false;
    }
    else
    {
        code->set_errcode(0);
        code->set_errmsg("QueryDepartUsers successed");
        return true;
    }
}

void DepartService::CreateDepart(::google::protobuf::RpcController *controller,
                                 const ::DepartProto::CreateDepartRequest *request,
                                 ::DepartProto::CreateDepartResponse *response,
                                 ::google::protobuf::Closure *done)
{
    DepartProto::DepartInfo departInfo = request->depart();
    Depart depart;
    depart.setName(departInfo.departname());
    depart.setDesc(departInfo.departdesc());

    DepartProto::ResultCode *code = response->mutable_result();
    bool result = CreateDepart(depart, code);

    response->set_success(result);
    done->Run();
}

void DepartService::AddDepart(::google::protobuf::RpcController *controller,
                              const ::DepartProto::AddDepartRequest *request,
                              ::DepartProto::AddDepartResponse *response,
                              ::google::protobuf::Closure *done)
{
    std::string departName = request->departname();
    std::string adminName = request->username();
    std::string role = request->userrole();

    DepartProto::ResultCode *code = response->mutable_result();
    bool result = AddDepart(departName, adminName, role, code);

    response->set_success(result);
    done->Run();
}

void DepartService::QueryDepart(::google::protobuf::RpcController *controller,
                                const ::DepartProto::QueryDepartRequest *request,
                                ::DepartProto::QueryDepartResponse *response,
                                ::google::protobuf::Closure *done)
{
    std::string adminName = request->username();

    DepartProto::ResultCode *code = response->mutable_result();
    DepartProto::DepartInfo departs;
    bool result = QueryDepart(adminName, departs, code);

    response->mutable_departs()->set_departid(departs.departid());
    response->mutable_departs()->set_departname(departs.departname());
    response->mutable_departs()->set_departdesc(departs.departdesc());
    for (auto &user : departs.departusers())
    {
        DepartProto::DepartUser *tempuser = response->mutable_departs()->add_departusers();
        tempuser->set_username(user.username());
        tempuser->set_useremail(user.useremail());
        tempuser->set_userphone(user.userphone());
        tempuser->set_userrole(user.userrole());
    }

    response->set_success(result);

    done->Run();
}

void DepartService::QueryDepartUsers(::google::protobuf::RpcController *controller,
                                     const ::DepartProto::QueryDepartUsersRequest *request,
                                     ::DepartProto::QueryDepartUsersResponse *response,
                                     ::google::protobuf::Closure *done)
{
    std::string adminName = request->username();
    std::string departName = request->departname();
    DepartProto::ResultCode *code = response->mutable_result();
    std::vector<std::string> departusers;
    bool result = QueryDepartUsers(departName, adminName, departusers, code);
    for (auto &val : departusers)
    {
        std::string *temp = response->add_departusername();
        temp->swap(val);
    }
    response->set_success(result);

    done->Run();
}