#ifndef MENUMANAGEUSER_H
#define MENUMANAGEUSER_H

#include "action.h"
#include "menu.h"
#include <QString>

enum Actor {
	Admin,
	NormalUser,
	Null
};

class ActionAddUser : public Action {
      private:
	QString title();
	QString confirmationMsg();

      public:
	Actor actor = Actor::Null;

	ActionAddUser(string label_, Actor actor_)
	    : Action(label_) {
		actor = actor_;
	};
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

class MenuManageUser : public Menu {
      protected:
	void actionBeforeShow() override;

      public:
	MenuManageUser(string label_);
};

#endif // MENUMANAGEUSER_H
