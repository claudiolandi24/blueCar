#ifndef MENU_H
#define MENU_H

#include <memory>
#include <string>
#include <vector>

using namespace std;

class MenuItem {
      protected:
	void printEmptyLineSeparator();

      public:
	string label;

	//MenuItem();
	MenuItem(string label_);
	virtual ~MenuItem() = default;
	virtual void run()  = 0;
};

class ItemVector {
      private:
	vector<unique_ptr<MenuItem>> items;

      public:
	/*
	 * Must be:
	 * 1 <= itemNumber <= this->size()
	 *
	 * I.e., indexing starts from 1, so that "itemNumber" is the same as the number linked to the
	 * item when the menu is printed (in Menu::show())
	 */
	unique_ptr<MenuItem>& getItemByItemNumber(unsigned long itemNumber) {
		//TODO check range valid
		unsigned long index = itemNumber - 1;
		return items[index];
	}
	void push_back(unique_ptr<MenuItem>& item) {
		items.push_back(move(item));
	}
	unsigned long size() {
		return items.size();
	}
};

class Menu : public MenuItem {
      protected:
	string     title;
	ItemVector items;
	string     exitLabel = "Back";

	void addItem(unique_ptr<MenuItem> item);
	void show();
	int  askForOption();

      public:
	Menu(string label_)
	    : MenuItem(label_){};
	void run() override;
};

class MenuLogin : public Menu {
      public:
	MenuLogin(string label_);
};

class MenuAdmin : public Menu {
      public:
	MenuAdmin(string label_);
};

class MenuUser : public Menu {
      public:
	MenuUser(string label_);
};

class MenuManageCar : public Menu {
      public:
	MenuManageCar(string label_);
};

class MenuManageUser : public Menu {
      public:
	MenuManageUser(string label_);
};

class Action : public MenuItem {
      public:
	Action(string label_)
	    : MenuItem(label_){};
};

class ActionLogin : public Action {
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

class ActionShowCars : public Action {
      public:
	ActionShowCars(string label_)
	    : Action(label_){};
	void run() override;
};

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

class ActionRentCar : public Action {
      public:
	ActionRentCar(string label_)
	    : Action(label_){};
	void run() override;
};

void tryMenu();
//
//void tryMenu() {
//	/*
//    string s("ciao");
//	Action mi(s);
//	auto a = Action1("Action 1");
//    */

//	MenuLogin ml("");
//	ml.run();
//}

//void pippo(){}

#endif // MENU_H
