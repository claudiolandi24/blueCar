#ifndef MENUUPDATEUSER_H
#define MENUUPDATEUSER_H

#include "action.h"
#include "menu.h"
#include "user.h"

class ActionUpdateUser : public Action {
      protected:
	void updateInDb();

      public:
	User user;
	ActionUpdateUser(string label_, User user_)
	    : Action(label_) {
		user = user_;
	};
};

class ActionUpdateUsername : ActionUpdateUser {
      public:
	ActionUpdateUsername(string label_, User user_)
	    : ActionUpdateUser(label_, user_){};
	void run() override;
};

class ActionUpdatePwdHash : ActionUpdateUser {
      public:
	ActionUpdatePwdHash(string label_, User user_)
	    : ActionUpdateUser(label_, user_){};
	void run() override;
};

class ActionUpdateNameOfUser : ActionUpdateUser {
      public:
	ActionUpdateNameOfUser(string label_, User user_)
	    : ActionUpdateUser(label_, user_){};
	void run() override;
};

class ActionUpdateSurname : ActionUpdateUser {
      public:
	ActionUpdateSurname(string label_, User user_)
	    : ActionUpdateUser(label_, user_){};
	void run() override;
};

class ActionUpdateAddress : ActionUpdateUser {
      public:
	ActionUpdateAddress(string label_, User user_)
	    : ActionUpdateUser(label_, user_){};
	void run() override;
};

class ActionUpdateCreditCard : ActionUpdateUser {
      public:
	ActionUpdateCreditCard(string label_, User user_)
	    : ActionUpdateUser(label_, user_){};
	void run() override;
};

class ActionUpdateDrivingLicense : ActionUpdateUser {
      public:
	ActionUpdateDrivingLicense(string label_, User user_)
	    : ActionUpdateUser(label_, user_){};
	void run() override;
};

class MenuUpdateUser : public Menu {
      public:
	User user;

	MenuUpdateUser(string label_, User user_);
};

#endif // MENUUPDATEUSER_H
