#ifndef __OFFLINEMSGMODEL_H__
#define __OFFLINEMSGMODEL_H__

#include "offlinemessage.pb.h"

#include <vector>

class OfflineMsg
{
public:
    void setMsgId(int id) { msgid = id; }
    void setRecvName(const std::string &name) { recvName = name; }
    void setSendName(const std::string &name) { sendName = name; }
    void setMessage(const std::string &msg) { message = msg; }

    int getMsgId() { return msgid; }
    std::string getRecvName() { return recvName; }
    std::string getSendName() { return sendName; }
    std::string getMessage() { return message; }

private:
    int msgid;
    std::string recvName;
    std::string sendName;
    std::string message;
};

class OfflineGroupMsg
{
public:
    void setMsgId(int id) { msgid = id; }
    void setGroupName(const std::string &name) { groupName = name; }
    void setSendName(const std::string &name) { sendName = name; }
    void setMessage(const std::string &msg) { message = msg; }

    int getMsgId() { return msgid; }
    std::string getGroupName() { return groupName; }
    std::string getSendName() { return sendName; }
    std::string getMessage() { return message; }

private:
    int msgid;
    std::string groupName;
    std::string sendName;
    std::string message;
};

class OfflineDepartMsg
{
public:
    void setMsgId(int id) { msgid = id; }
    void setDepartName(const std::string &name) { departName = name; }
    void setSendName(const std::string &name) { sendName = name; }
    void setMessage(const std::string &msg) { message = msg; }

    int getMsgId() { return msgid; }
    std::string getDepartName() { return departName; }
    std::string getSendName() { return sendName; }
    std::string getMessage() { return message; }

private:
    int msgid;
    std::string departName;
    std::string sendName;
    std::string message;
};

class OfflineMsgModel : public OfflineMessageProto::offlineMsgRpc
{
public:
    bool addOfflineMsg(std::string recvName, std::string sendName,
                       std::string message);
    bool delOfflineMsg(int msgId, std::string recvName,
                       std::string sendName, std::string message);
    std::vector<OfflineMsg> queryOfflineMsg(std::string recvName);

    bool addOfflineGroupMsg(std::string groupName, std::string sendName,
                            std::string message);
    bool delOfflineGroupMsg(int msgId, std::string groupName,
                            std::string sendName, std::string message);
    std::vector<OfflineGroupMsg> queryOfflineGroupMsg(std::string userName);

    bool addOfflineDepartMsg(std::string departName, std::string sendName,
                             std::string message);
    bool delOfflineDepartMsg(int msgId, std::string departName,
                             std::string sendName, std::string message);
    std::vector<OfflineDepartMsg> queryOfflineDepartMsg(std::string userName);

private:
};

#endif