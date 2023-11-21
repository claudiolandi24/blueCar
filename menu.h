#ifndef MENU_H
#define MENU_H

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
	virtual ~MenuItem();
	virtual void run() = 0;
};

class Menu : public MenuItem {
      protected:
	string            title;
	vector<MenuItem*> items;
	string            exitLabel = "Back";

	void addItem(MenuItem* item);
	void show();
	int  askForOption();
	~Menu();

      public:
	Menu(string label_)
	    : MenuItem(label_){};
	void run() override;
};

class MenuLogin : public Menu {
      public:
	MenuLogin(string label_);
};

class Action : public MenuItem {
      public:
	Action(string s)
	    : MenuItem(s){};
	~Action();
	void run() override;
};

class Action1 : public Action {
      public:
	Action1(string s)
	    : Action(s){};
	~Action1();
	void run() override;
};

class Action2 : public Action {
      public:
	Action2(string s)
	    : Action(s){};
	~Action2();
	void run() override;
};

void tryMenu();
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
