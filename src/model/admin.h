#ifndef __ADMIN_H__
#define __ADMIN_H__

#include <string>

class Admin
{
public:
    Admin(int id = -1, std::string name = "",
          std::string password = "", std::string status = "offline",
          std::string email = "", std::string phone = "")
        : m_id(id), m_name(name), m_password(password),
          m_status(status), m_email(email), m_phone(phone) {}

    void setId(uint32_t id) { m_id = id; }
    void setName(std::string name) { m_name = name; }
    void setPassword(std::string password) { m_password = password; }
    void setStatus(std::string status) { m_status = status; }
    void setEmail(std::string email) { m_email = email; }
    void setPhone(std::string phone) { m_phone = phone; }

    uint32_t getId() const { return m_id; }
    const std::string &getName() const { return m_name; }
    const std::string &getPassword() const { return m_password; }
    const std::string &getStatus() const { return m_status; }
    const std::string &getEmail() const { return m_email; }
    const std::string &getPhone() const { return m_phone; }

private:
    uint32_t m_id;
    std::string m_name;
    std::string m_password;
    std::string m_status;
    std::string m_email;
    std::string m_phone;
};

#endif