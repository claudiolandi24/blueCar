#include "menuuser.h"
#include <iostream>

void ActionRentCar::run() {
	cout << "running rent car" << endl;
	printEmptyLineSeparator();
};

MenuUser::MenuUser(string label_)
    : Menu(label_) {
	title = "USER";
	addItem(make_unique<ActionRentCar>("Rent car"));
	exitLabel = "Log out";
}
