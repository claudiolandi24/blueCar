#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>

using namespace std;

class MenuItem {
      protected:
	

      public:
	string label;

	MenuItem(string label_);
	virtual ~MenuItem() = default;
	virtual void run()  = 0;
    void printEmptyLineSeparator();
};



#endif // MENUITEM_H
