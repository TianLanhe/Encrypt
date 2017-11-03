#ifndef UI_SCREEN_FACTORY_H
#define UI_SCREEN_FACTORY_H

class UIScreen;
class UIControler;

class UIScreenFactory{

public:
    static UIScreenFactory* GetInstance();

    UIScreen* GetStartScreen(UIControler*);

private:
    UIScreenFactory();

    static UIScreenFactory* instance;

};

#endif
