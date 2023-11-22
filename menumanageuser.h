#ifndef MENUMANAGEUSER_H
#define MENUMANAGEUSER_H

#include "action.h"
#include "menu.h"

class ActionAddUser : public Action {
      public:
	ActionAddUser(string label_)
	    : Action(label_){};
	void run() override;
};

class ActionUpdateUser : public Action {
      public:
	ActionUpdateUser(string label_)
	    : Action(label_){};
	void run() override;
};

class ActionRemoveUser : public Action {
      public:
	ActionRemoveUser(string label_)
	    : Action(label_){};
	void run() override;
};

class ActionShowUsers : public Action {
      public:
	ActionShowUsers(string label_)
	    : Action(label_){};
	void run() override;
};

class MenuManageUser : public Menu {
      public:
	MenuManageUser(string label_);
};

#endif // MENUMANAGEUSER_H
