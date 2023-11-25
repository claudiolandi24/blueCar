#ifndef MENULOGIN_H
#define MENULOGIN_H

#include "action.h"
#include "menu.h"
#include "user.h"
#include <QString>
#include <QPair>

class ActionLogin : public Action {
      private:
    QPair<bool,User> checkPwd(const QString& username, const QString& password);
    
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

void runApplication();

#endif // MENULOGIN_H
