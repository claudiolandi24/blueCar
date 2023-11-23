#ifndef MENUUPDATECAR_H
#define MENUUPDATECAR_H

#include "action.h"
#include "car.h"
#include "menu.h"

class ActionUpdateCar : public Action {
      public:
    Car car;
    
	ActionUpdateCar(string label_, Car car_)
	    : Action(label_){car=car_;};
	void run() override;
};

class ActionUpdateType : public ActionUpdateCar {
      public:
	ActionUpdateType(string label_, Car car_)
	    : ActionUpdateCar(label_, car_){};
	void run() override;
};

class ActionUpdateLicensePlate : public Action {
      public:
	ActionUpdateLicensePlate(string label_)
	    : Action(label_){};
	void run() override;
};

class ActionUpdateBrand : public Action {
      public:
	ActionUpdateBrand(string label_)
	    : Action(label_){};
	void run() override;
};

class ActionUpdateName : public Action {
      public:
	ActionUpdateName(string label_)
	    : Action(label_){};
	void run() override;
};

class ActionUpdateLocation : public Action {
      public:
	ActionUpdateLocation(string label_)
	    : Action(label_){};
	void run() override;
};

class ActionUpdateDistanceTraveled : public Action {
      public:
	ActionUpdateDistanceTraveled(string label_)
	    : Action(label_){};
	void run() override;
};

class MenuUpdateCar : public Menu {
      public:
	Car car;

	MenuUpdateCar(string label_, Car car_);
};

#endif // MENUUPDATECAR_H
