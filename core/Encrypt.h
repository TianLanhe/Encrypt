#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <vector>
#include <iostream>
#include <string>
#include "include/Task.h"

class EncryptData {

	friend std::ostream& operator<<(std::ostream&, const EncryptData&);
	friend std::istream& operator >> (std::istream&, EncryptData&);

public:
	EncryptData() :m_bValid(false) {}

	bool isValid() const { return m_bValid; }

	bool Encrypt(const std::string&);
	bool Decrypt(const std::string& pwd) { return Encrypt(pwd); }

	size_t size() const { return m_data.size(); }

private:
	bool m_bValid;
	std::vector<unsigned char> m_data;
};

class CalcTask : public Task {

public:
	typedef std::vector<unsigned char>::size_type size_type;
	typedef std::vector<unsigned char> vec;

public:
	CalcTask(vec* data = nullptr, size_type start = 0, size_type end = 0);

	void setPwd(const std::string& pwd) { m_pwd = pwd; }
	Status Run();

private:
	std::string m_pwd;
	size_type m_start;
	size_type m_end;
	vec* m_data;
};

#endif
