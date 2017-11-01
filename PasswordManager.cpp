#include "PasswordManager.h"
#include <ctime>

void PasswordManager::generatePwd(){
    m_pwdVec.clear();
    m_pwd.clear();
    srand(time(NULL));

    char ch;
    for(int i = 0;i != m_length;++i){
            ch = rand() % 52 + 65;
            if(ch > 90)
                ch += 6;
            m_pwdVec.push_back(ch);

            m_pwd.append(std::to_string(ch));
    }

    m_hint = std::string(m_pwdVec.begin(),m_pwdVec.end());
}
