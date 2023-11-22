#ifndef MENULOGIN_H
#define MENULOGIN_H

#include "action.h"
#include "menu.h"

class ActionLogin : public Action {
      public:
	ActionLogin(string label_)
	    : Action(label_){};
	void run() override;
};

class ActionRegister : public Action {
      public:
	ActionRegister(string label_)
	    : Action(label_){};
	void run() override;
};

class MenuLogin : public Menu {
      public:
	MenuLogin(string label_);
};

void tryMenu();

#endif // MENULOGIN_H
