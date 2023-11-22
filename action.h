#ifndef ACTION_H
#define ACTION_H

#include "menuitem.h"

class Action : public MenuItem {
      public:
	Action(string label_)
	    : MenuItem(label_){};
};

#endif // ACTION_H
