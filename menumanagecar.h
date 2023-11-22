#ifndef MENUMANAGECAR_H
#define MENUMANAGECAR_H

#include "action.h"
#include "menu.h"

class ActionAddCar : public Action {
      public:
	ActionAddCar(string label_)
	    : Action(label_){};
	void run() override;
};

class ActionUpdateCar : public Action {
      public:
	ActionUpdateCar(string label_)
	    : Action(label_){};
	void run() override;
};

class ActionRemoveCar : public Action {
      public:
	ActionRemoveCar(string label_)
	    : Action(label_){};
	void run() override;
};

class MenuManageCar : public Menu {
      protected:
	void actionBeforeShow() override;

      public:
	MenuManageCar(string label_);
};

#endif // MENUMANAGECAR_H
