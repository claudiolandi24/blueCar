#ifndef ENTITY_H
#define ENTITY_H

#include "qpair.h"
#include <QString>

class Entity {
      public:
    QString name;
    QString table;
    
    
	Entity() = default;

	bool entityIdExists(int id);
    QPair<bool, int> getIdFromTerminal(const QString& operation);
};

#endif // ENTITY_H
