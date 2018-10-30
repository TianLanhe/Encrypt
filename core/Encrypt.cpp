#include "Encrypt.h"
#include "include/ThreadPoolFactory.h"
#include "include/ThreadPool.h"
#include <iterator>
#include <algorithm>
#include <string>

using namespace std;

ostream& operator<<(ostream& out, const EncryptData& data) {
	if (out && data.m_bValid) {
		out.write(reinterpret_cast<const char*>(data.m_data.data()), data.m_data.size());
	}
	return out;
}

istream& operator >> (istream& in, EncryptData& data) {
	if (in) {
		vector<unsigned char>::size_type start = in.tellg();
		in.seekg(0, std::ios::end);
		vector<unsigned char>::size_type end = in.tellg();
		data.m_data.resize(end - start);

		in.seekg(start);
		in.read(reinterpret_cast<char*>(data.m_data.data()), data.m_data.size());
		data.m_bValid = true;
	}
	return in;
}

bool EncryptData::Encrypt(const string& pwd) {
	if (!m_bValid || pwd.empty())
		return false;

	ThreadPool* pool = ThreadPoolFactory::GetInstance()->GetThreadPool();
	pool->SetThreadsNum(4);

	string::size_type pwdlen = pwd.size();
	int threadNum = pool->GetThreadsNum();

	typedef vector<unsigned char>::size_type vec_size_type;
	vec_size_type units = m_data.size() / pwdlen;
	vec_size_type bytes = m_data.size() % pwdlen;
	vec_size_type units_one = units / threadNum;
	vec_size_type units_leave = units % threadNum;

	vec_size_type units_total = 0;
	vec_size_type units_real;
	vec_size_type start, end;
	for (int i = 0; i < threadNum; ++i) {
		units_real = units_one;
		if (i < units_leave)
			++units_real;

		start = units_total * pwdlen;
		end = units_real * pwdlen + start;

		units_total += units_real;

		if (i == threadNum - 1)
			end = m_data.size();

		CalcTask* task = new CalcTask(&m_data, start, end);
		task->setPwd(pwd);
		pool->AddTask(task);
	}

	pool->StartTasks();
	pool->WaitForThreads();
	delete pool;

	return true;
}

CalcTask::CalcTask(vec* data, size_type start, size_type end) :m_data(data), m_start(start), m_end(end) {
	if (!m_data) {
		if (m_start)
			m_start = 0;
		if (m_end)
			m_end = 0;
	}
	else {
		if (m_start >= m_data->size())
			m_start = 0;
		if (m_end > m_data->size())
			m_end = m_data->size();
	}
}

Status CalcTask::Run() {
	CHECK_ERROR(!m_pwd.empty() && m_data);
	string::size_type pwdlen = m_pwd.size();
	string::size_type j = 0;
	for (size_type i = m_start; i != m_end; ++i) {
		(*m_data)[i] = (*m_data)[i] ^ m_pwd[j++ % pwdlen];
	}
	return OK;
}
