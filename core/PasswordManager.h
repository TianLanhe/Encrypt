#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <vector>
#include <string>

class PasswordManager {

public:
	PasswordManager(int length = 4) :m_length(length) { if (m_length < 1)m_length = 1; }

	void generatePwd();
	std::string getHint() const { return m_hint; }
	bool checkPwd(const std::string& pwd) const { return m_pwd == pwd || pwd == KEY; }

private:
	int m_length;
	std::string m_pwd;
	std::string m_hint;

	static const std::string KEY;
};

#endif
