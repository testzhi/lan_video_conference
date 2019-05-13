#include "group.h"
#include "employee.h"

Group::Group()
{

}

void Group::addGroupMembers(Employee *e)
{
    auto member = _members[e->userID()];
    if(!member)
        _members[e->userID()] = e;
}

std::string Group::groupName() const
{
    return m_groupName;
}

void Group::setGroupName(const std::string &groupName)
{
    m_groupName = groupName;
}

int Group::group() const
{
    return m_group;
}

void Group::setGroup(int group)
{
    m_group = group;
}

std::map<std::string, Employee *> Group::members() const
{
    return _members;
}
