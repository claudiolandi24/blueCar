#ifndef FREECARVIEW_H
#define FREECARVIEW_H

#include "car.h"

class FreeCarView {
      public:
	FreeCarView() = default;
	static Car getCarFromSqlRow(const sqlRow& row);
};

#endif // FREECARVIEW_H
