#ifndef MENUUPDATECAR_H
#define MENUUPDATECAR_H

#include "action.h"
#include "car.h"
#include "menu.h"

class ActionUpdateCar : public Action {
protected:
    void updateInDb();
    
      public:
	Car car;

	ActionUpdateCar(string label_, Car car_)
	    : Action(label_) {
		car = car_;
	};
};

class ActionUpdateType : public ActionUpdateCar {
      public:
	ActionUpdateType(string label_, Car car_)
	    : ActionUpdateCar(label_, car_){};
	void run() override;
};

class ActionUpdateLicensePlate : public ActionUpdateCar {
      public:
	ActionUpdateLicensePlate(string label_, Car car_)
	    : ActionUpdateCar(label_, car_){};
	void run() override;
};

class ActionUpdateBrand : public ActionUpdateCar {
      public:
	ActionUpdateBrand(string label_, Car car_)
	    : ActionUpdateCar(label_, car_){};
	void run() override;
};

class ActionUpdateNameOfCar : public ActionUpdateCar {
      public:
	ActionUpdateNameOfCar(string label_, Car car_)
	    : ActionUpdateCar(label_, car_){};
	void run() override;
};

class ActionUpdateLocation : public ActionUpdateCar {
      public:
	ActionUpdateLocation(string label_, Car car_)
	    : ActionUpdateCar(label_, car_){};
	void run() override;
};

class ActionUpdateDistanceTraveled : public ActionUpdateCar {
      public:
	ActionUpdateDistanceTraveled(string label_, Car car_)
	    : ActionUpdateCar(label_, car_){};
	void run() override;
};

class MenuUpdateCar : public Menu {
      public:
	Car car;

	MenuUpdateCar(string label_, Car car_);
};

#endif // MENUUPDATECAR_H
