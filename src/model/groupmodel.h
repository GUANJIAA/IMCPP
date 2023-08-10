#ifndef __GROUPMODEL_H__
#define __GROUPMODEL_H__

#include "group.h"

#include <vector>
#include <string>

class GroupModel
{
public:
    bool createGroup(Group &group);
    bool addGroup(std::string groupName, std::string userName, std::string userRole);
    std::vector<Group> queryGroup(std::string userName);
    Group queryGroupUsers(std::string groupName, std::string userName);
};

#endif