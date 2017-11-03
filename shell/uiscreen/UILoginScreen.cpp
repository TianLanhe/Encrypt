#include "UILoginScreen.h"
#include "UIMainScreen.h"
#include "../../core/PasswordManager.h"
#include <iostream>

using namespace std;

enum Code{
    LOGIN
};

void UILoginScreen::_PrintLoginMenu(){
    cout << endl;
    cout << "            ┌─────────欢迎使用加密解密程序──────┐              " << endl;
    cout << "            │  ┌─────────────────────┐  │              " << endl;
    cout << "            │  │                                          │  │              " << endl;
    cout << "            │  │无论文本图片视频音频，都能加加加解解解.   │  │              " << endl;
    cout << "            │  │密码随便设，就是别忘了. ^_^               │  │              " << endl;
    cout << "            │  │3.0版本来了，优化了界面，输入可带空格     │  │              " << endl;
    cout << "            │  └─────────────────────┘  │              " << endl;
    cout << "            │                                                  │              " << endl;
    cout << "            │              请选择： 1. 文件加密                │              " << endl;
    cout << "            │                       2. 文件解密                │              " << endl;
    cout << "            │                       3. 退出程序                │              " << endl;
    cout << "            │                                                  │              " << endl;
    cout << "            └─────────────────────────┘              " << endl;


    cout << endl;
    cout << "            ┌─────────欢迎使用加密解密程序──────┐              " << endl;
    cout << "            │                                                  │              " << endl;
    cout << "            │    程序设置了密码，请输入密码后使用.             │              " << endl;
    cout << "            │                                                  │              " << endl;
    cout << "            │              请选择： 1. 输入密码                │              " << endl;
    cout << "            │                       2. 退出程序                │              " << endl;
    cout << "            │                                                  │              " << endl;
    cout << "            └─────────────────────────┘              " << endl;
}

UIScreen* UILoginScreen::Transform(int code){
    switch(code){
    case LOGIN:
        return new UIMainScreen(m_controler);
    default:
        return nullptr;
    }
}

void UILoginScreen::Start(){
    _PrintLoginMenu();
    cout << "请输入正确选项并按回车确定:";

    int code = -1;
    while(cin >> code && code != 1 && code != 2)
        cout << "请输入正确的选项:";

    if(code != 1)
    {
        _SetReturnCode(UIControler::Stop);
    }else{
        _EnterPassword();
    }
}

void UILoginScreen::_EnterPassword(){
    PasswordManager pwdmgr;
    pwdmgr.generatePwd();

    cout << "密码提示：" << pwdmgr.getHint() << endl;

    string pwd;
    for(int try_time = 3; try_time != 0;--try_time){
        if(try_time == 3)
            cout << "请输入密码(按0退出程序)：";
        else
            cout << "抱歉，密码错误！" << endl << "你还有 " << try_time << " 次机会：";

        cin >> pwd;

        if(pwd == "0"){
            _SetReturnCode(UIControler::Stop);
            break;
        }else if(pwdmgr.checkPwd(pwd)){
            _SetReturnCode(LOGIN);
            break;
        }
    }
    _SetReturnCode(UIControler::Stop);
}
