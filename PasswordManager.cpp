#include "PasswordManager.h"
#include <ctime>

void PasswordManager::generatePwd() {
	std::vector<char> pwdVec;
	m_pwd.clear();
	srand(time(NULL));

	char ch;
	for (int i = 0; i != m_length; ++i) {
		ch = rand() % 52 + 65;
		if (ch > 90)
			ch += 6;
		pwdVec.push_back(ch);

		m_pwd.append(std::to_string(ch));
	}

	m_hint = std::string(pwdVec.begin(), pwdVec.end());
}
