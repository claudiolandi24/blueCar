#include "entity.h"
#include "rbk/minMysql/min_mysql.h"
#include <QString>

extern DB db;

QString Entity::entityName;
QString Entity::entityTable;

bool Entity::idExists(int id) {
	QString skel = R"(
select * from %1 where id = %2; 
)";
	auto    sql  = skel
	               .arg(entityTable)
	               .arg(id);
	auto res = db.query(sql);
	if (res.empty()) {
		return false;
	}
	return true;
}

QPair<bool, int> Entity::getIdFromTerminal(const QString& operation) {
	if (operation != "update" and operation != "remove") {
		//TODO log error
		return {false, 0};
	}

	QString msgSkel = R"(Insert the ID of the %1 you want to %2.
Insert 0 (zero) to cancel this operation)";
	auto    msg     = msgSkel
	               .arg(entityName)
	               .arg(operation);
	QTextStream(stdout) << msg << Qt::endl;
	QString rawInput = QTextStream(stdin).readLine();
	bool    ok;
	int     id = rawInput.toInt(&ok);
	if (!ok) {
		QTextStream(stdout) << "The inserted value is not a valid number" << Qt::endl;
		return {false, 0};
	}
	if (!idExists(id)) {
		auto msg = QSL("No %1 with ID %2")
		               .arg(entityName)
		               .arg(id);
		QTextStream(stdout) << msg << Qt::endl;
		return {false, 0};
	}

	return {true, id};
}

void Entity::deleteFromDb(int id) {
	QString sql = QSL("DELETE FROM %1 WHERE id = %2;")
            .arg(entityTable)
            .arg(id);
	db.query(sql);
}

void Entity::deleteAfterRequest() {
	auto id = getIdFromTerminal("remove");
	if (!id.first) {
		QTextStream(stdout) << "Remove operation cancelled" << Qt::endl;
		return;
	}
	deleteFromDb(id.second);
    //Car/User
    QString entityNameFirstUpper = entityName;
    entityNameFirstUpper[0]=entityNameFirstUpper[0].toUpper();
    auto msg = QSL("%1 removed successfully").arg(entityNameFirstUpper);
	QTextStream(stdout) << msg << Qt::endl;
}


