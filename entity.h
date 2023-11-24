#ifndef ENTITY_H
#define ENTITY_H

#include "qpair.h"
#include <QString>

class Entity {
      public:
	static QString entityName;
	static QString entityTable;

	Entity() = default;

	static bool             idExists(int id);
	static QPair<bool, int> getIdFromTerminal(const QString& operation);
};

#endif // ENTITY_H
