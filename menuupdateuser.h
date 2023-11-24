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

class ActionUpdateUsername : public ActionUpdateUser {
      public:
	ActionUpdateUsername(string label_, User user_)
	    : ActionUpdateUser(label_, user_){};
	void run() override;
};

class ActionUpdatePwdHash : public ActionUpdateUser {
      public:
	ActionUpdatePwdHash(string label_, User user_)
	    : ActionUpdateUser(label_, user_){};
	void run() override;
};

class ActionUpdateNameOfUser : public ActionUpdateUser {
      public:
	ActionUpdateNameOfUser(string label_, User user_)
	    : ActionUpdateUser(label_, user_){};
	void run() override;
};

class ActionUpdateSurname : public ActionUpdateUser {
      public:
	ActionUpdateSurname(string label_, User user_)
	    : ActionUpdateUser(label_, user_){};
	void run() override;
};

class ActionUpdateAddress : public ActionUpdateUser {
      public:
	ActionUpdateAddress(string label_, User user_)
	    : ActionUpdateUser(label_, user_){};
	void run() override;
};

class ActionUpdateCreditCard : public ActionUpdateUser {
      public:
	ActionUpdateCreditCard(string label_, User user_)
	    : ActionUpdateUser(label_, user_){};
	void run() override;
};

class ActionUpdateDrivingLicense : public ActionUpdateUser {
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
