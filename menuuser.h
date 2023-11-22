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

class MenuUser : public Menu {
      public:
	MenuUser(string label_);
};

#endif // MENUUSER_H
