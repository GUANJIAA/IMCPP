#include "DepartService.h"

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
                              std::vector<DepartProto::DepartInfo> &Departs,
                              DepartProto::ResultCode *code)
{
    std::vector<Depart> departVec = departmodel.queryDepart(userName);
    bool result = false;
    if (departVec.empty())
    {
        code->set_errcode(1);
        code->set_errmsg("QueryDepart failed");
    }
    else
    {
        for (auto &gval : departVec)
        {
            DepartProto::DepartInfo temp;
            temp.set_departid(gval.getId());
            temp.set_departname(gval.getName());
            temp.set_departdesc(gval.getDesc());
            for (auto &uval : gval.getUsers())
            {
                DepartProto::DepartUser *info = temp.add_departusers();
                info->set_username(uval.getName());
                info->set_useremail(uval.getEmail());
                info->set_userphone(uval.getPhone());
                info->set_userrole(uval.getRole());
            }
            // std::cout << temp.departid() << "============="
            //           << temp.departname() << "==============="
            //           << temp.departdesc() << "===========";
            Departs.push_back(temp);
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
    std::vector<DepartProto::DepartInfo> departs;
    bool result = QueryDepart(adminName, departs, code);

    for (auto &val : departs)
    {
        DepartProto::DepartInfo *temp = response->add_departs();
        temp->set_departid(val.departid());
        temp->set_departname(val.departname());
        temp->set_departdesc(val.departdesc());
        for (auto &user : val.departusers())
        {
            DepartProto::DepartUser *tempuser = temp->add_departusers();
            tempuser->set_username(user.username());
            tempuser->set_useremail(user.useremail());
            tempuser->set_userphone(user.userphone());
            tempuser->set_userrole(user.userrole());
        }
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