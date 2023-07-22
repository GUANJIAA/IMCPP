#ifndef __GROUPMODEL_H__
#define __GROUPMODEL_H__

#include "group.h"

#include <vector>
#include <string>

class GroupModel
{
public:
    bool createGroup(Group &group);
    bool addGroup(std::string groupName, std::string userName, std::string role);
    std::vector<Group> queryGroup(std::string userName);
    std::vector<std::string> queryGroupUsers(std::string groupName, std::string userName);
};

#endif