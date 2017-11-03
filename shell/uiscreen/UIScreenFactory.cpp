#include "../include/UIScreenFactory.h"
#include "UILoginScreen.h"

UIScreenFactory* UIScreenFactory::instance = new UIScreenFactory();

UIScreenFactory* UIScreenFactory::GetInstance(){
    return instance;
}

UIScreen* UIScreenFactory::GetStartScreen(UIControler* controler){
    return new UILoginScreen(controler);
}
