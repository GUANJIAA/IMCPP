#include "GroupService.h"

#include <iostream>

bool GroupService::CreateGroup(Group &group, GroupProto::ResultCode *code)
{
    bool result = groupmodel.createGroup(group);
    if (result)
    {
        code->set_errcode(0);
        code->set_errmsg("CreateGroup successful");
    }
    else
    {
        code->set_errcode(1);
        code->set_errmsg("CreateGroup failed");
    }
    return result;
}

bool GroupService::AddGroup(std::string groupName,
                            std::string userName,
                            std::string userRole,
                            GroupProto::ResultCode *code)
{
    bool result = groupmodel.addGroup(groupName, userName, userRole);
    if (result)
    {
        code->set_errcode(0);
        code->set_errmsg("AddGroup successful");
    }
    else
    {
        code->set_errcode(1);
        code->set_errmsg("AddGroup failed");
    }
    return result;
}

bool GroupService::QueryGroup(std::string userName,
                              std::vector<GroupProto::GroupInfo> &Groups,
                              GroupProto::ResultCode *code)
{
    std::vector<Group> groupVec = groupmodel.queryGroup(userName);
    bool result = false;
    if (groupVec.empty())
    {
        code->set_errcode(1);
        code->set_errmsg("QueryGroup failed");
    }
    else
    {
        for (auto &gval : groupVec)
        {
            GroupProto::GroupInfo temp;
            temp.set_groupid(gval.getId());
            temp.set_groupname(gval.getName());
            temp.set_groupdesc(gval.getDesc());
            for (auto &uval : gval.getUsers())
            {
                GroupProto::GroupUser *info = temp.add_groupusers();
                info->set_username(uval.getName());
                info->set_useremail(uval.getEmail());
                info->set_userphone(uval.getPhone());
                info->set_userrole(uval.getRole());
            }
            // std::cout << temp.groupid() << "============="
            //           << temp.groupname() << "==============="
            //           << temp.groupdesc() << "===========";
            Groups.push_back(temp);
        }
        result = true;
        code->set_errcode(0);
        code->set_errmsg("QueryGroup successful");
    }
    return result;
}

bool GroupService::QueryGroupUsers(std::string groupName,
                                   std::string userName,
                                   std::vector<std::string> &groupusers,
                                   GroupProto::ResultCode *code)
{
    groupusers = groupmodel.queryGroupUsers(groupName, userName);
    if (groupusers.empty())
    {
        code->set_errcode(1);
        code->set_errmsg("QueryGroupUsers failed");
        return false;
    }
    else
    {
        code->set_errcode(0);
        code->set_errmsg("QueryGroupUsers successed");
        return true;
    }
}

void GroupService::CreateGroup(::google::protobuf::RpcController *controller,
                               const ::GroupProto::CreateGroupRequest *request,
                               ::GroupProto::CreateGroupResponse *response,
                               ::google::protobuf::Closure *done)
{
    GroupProto::GroupInfo groupInfo = request->group();
    Group group;
    group.setName(groupInfo.groupname());
    group.setDesc(groupInfo.groupdesc());

    GroupProto::ResultCode *code = response->mutable_result();
    bool result = CreateGroup(group, code);

    response->set_success(result);
    done->Run();
}

void GroupService::AddGroup(::google::protobuf::RpcController *controller,
                            const ::GroupProto::AddGroupRequest *request,
                            ::GroupProto::AddGroupResponse *response,
                            ::google::protobuf::Closure *done)
{
    std::string groupName = request->groupname();
    std::string adminName = request->username();
    std::string role = request->userrole();

    GroupProto::ResultCode *code = response->mutable_result();
    bool result = AddGroup(groupName, adminName, role, code);

    response->set_success(result);
    done->Run();
}

void GroupService::QueryGroup(::google::protobuf::RpcController *controller,
                              const ::GroupProto::QueryGroupRequest *request,
                              ::GroupProto::QueryGroupResponse *response,
                              ::google::protobuf::Closure *done)
{
    std::string adminName = request->username();

    GroupProto::ResultCode *code = response->mutable_result();
    std::vector<GroupProto::GroupInfo> groups;
    bool result = QueryGroup(adminName, groups, code);

    for (auto &val : groups)
    {
        GroupProto::GroupInfo *temp = response->add_groups();
        temp->set_groupid(val.groupid());
        temp->set_groupname(val.groupname());
        temp->set_groupdesc(val.groupdesc());
        for (auto &user : val.groupusers())
        {
            GroupProto::GroupUser *tempuser = temp->add_groupusers();
            tempuser->set_username(user.username());
            tempuser->set_useremail(user.useremail());
            tempuser->set_userphone(user.userphone());
            tempuser->set_userrole(user.userrole());
        }
    }

    response->set_success(result);

    done->Run();
}

void GroupService::QueryGroupUsers(::google::protobuf::RpcController *controller,
                                   const ::GroupProto::QueryGroupUsersRequest *request,
                                   ::GroupProto::QueryGroupUsersResponse *response,
                                   ::google::protobuf::Closure *done)
{
    std::string adminName = request->username();
    std::string groupName = request->groupname();
    GroupProto::ResultCode *code = response->mutable_result();
    std::vector<std::string> groupusers;
    bool result = QueryGroupUsers(groupName, adminName, groupusers, code);
    for (auto &val : groupusers)
    {
        std::string *temp = response->add_groupusername();
        temp->swap(val);
    }
    response->set_success(result);

    done->Run();
}