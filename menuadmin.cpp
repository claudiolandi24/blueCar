#include "menuadmin.h"
#include "menumanagecar.h"
#include "menumanageuser.h"

MenuAdmin::MenuAdmin(string label_)
    : Menu(label_) {
	title = "ADMIN";
	addItem(make_unique<MenuManageCar>("Manage cars"));
	addItem(make_unique<MenuManageUser>("Manage users"));
	exitLabel = "Log out";
}
