#ifndef GROUP_H
#define GROUP_H

#include <map>

class Employee;

class Group
{
public:
    Group();
    Group(int gid, std::string gname)
        :m_group(gid), m_groupName(gname)
    {}
    void addGroupMembers(Employee *e);

    std::string groupName() const;
    void setGroupName(const std::string &groupName);
    int group() const;
    void setGroup(int group);

    std::map<std::string, Employee *> members() const;

private:
    std::map<std::string, Employee*> _members;
    int m_group;
    std::string m_groupName;
};

#endif // GROUP_H
