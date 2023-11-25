#ifndef MENUUSER_H
#define MENUUSER_H

#include "action.h"
#include "menu.h"

class ActionRentCar : public Action {
      public:
	ActionRentCar(string label_)
	    : Action(label_){};
	void run() override;
};

class ActionUnsubscribe : public Action {
      public:
	long long loggedUserId = 0;

	ActionUnsubscribe(string label_, long long loggedUserId_)
	    : Action(label_) {
		loggedUserId = loggedUserId_;
	};
	void run() override;
};

class MenuUser : public Menu {
      public:
	long long loggedUserId = 0;

	MenuUser(string label_, long long loggedUserId_);
};

#endif // MENUUSER_H
