#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <vector>
#include <string>

class PasswordManager{

public:
    PasswordManager(int length = 4):m_length(length){ m_length < 1 && m_length = 1; }

    void generatePwd();
    std::string getHint() const { return m_hint; }
    bool checkPwd(const std::string& pwd) const { return m_pwd == pwd; }

    std::string getPwd() const { return m_pwd; }

private:
    int m_length;
    std::vector<char> m_pwdVec;
    std::string m_pwd;
    std::string m_hint;
};

#endif
