#include "menuitem.h"
#include <iostream>

MenuItem::MenuItem(string label_) {
	label = label_;
}

void MenuItem::printEmptyLineSeparator() {
	cout << "\n\n";
}
