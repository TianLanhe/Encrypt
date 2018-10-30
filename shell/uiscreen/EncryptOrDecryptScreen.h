#ifndef UI_ENCRYPT_OR_DECRYPT_SCREEN_H
#define UI_ENCRYPT_OR_DECRYPT_SCREEN_H

#include "../include/UIScreen.h"
#include <string>

class EncryptOrDecryptScreen : public UIScreen {

public:
	EncryptOrDecryptScreen(const std::string& oper, UIControler* controler) :UIScreen(controler), m_oper(oper) {}

public:
	void Start();

private:
	std::string _GetPassword(char ch = '\0');
	void _adjustOutputFileName(const std::string&, std::string&);

protected:
	std::string m_oper;

	enum Code {
		MAIN, THIS_OPERATION
	};

};

#endif
