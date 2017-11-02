#include "Encrypt.h"
using namespace std;

int main(){
	EncryptData data;
	data.m_data.clear();
	data.m_bValid = true;
	for(int i=0;i<1000;++i)
		data.m_data.push_back(i);
	data.Encrypt("abcde");
	return 0;
}

