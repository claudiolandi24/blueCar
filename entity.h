#ifndef ENTITY_H
#define ENTITY_H

#include "qpair.h"
#include <QString>

/*
 * Entity = Car or User
 */
class Entity {
      public:
	static QString entityName;
	static QString table;

	Entity() = default;

	static bool             idExists(int id);
	static QPair<bool, int> getIdFromTerminal(const QString& operation);
	static void             deleteFromDb(int id);
	static void             deleteAfterRequest();
};

#endif // ENTITY_H
