#ifndef MENULOGIN_H
#define MENULOGIN_H

#include "action.h"
#include "menu.h"
#include "user.h"
#include <QPair>
#include <QString>

class ActionLogin : public Action {
      public:
	ActionLogin(string label_)
	    : Action(label_){};
	void              run() override;
	QPair<bool, User> checkPwd(const QString& username, const QString& password);
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

void runApplication();

#endif // MENULOGIN_H
