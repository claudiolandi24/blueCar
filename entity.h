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

	static bool             idExistsActive(int id);
	static QPair<bool, int> getIdFromTerminal(const QString& operation);
	static void             setNotActiveInDb(long long id);
	static void             deleteAfterRequest();
};

#endif // ENTITY_H
