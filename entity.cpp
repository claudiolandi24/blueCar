#include "entity.h"
#include "rbk/minMysql/min_mysql.h"
#include <QString>

extern DB db;

bool Entity::entityIdExists(int id) {
	QString skel = R"(
select * from %1 where id = %2; 
)";
	auto    sql  = skel
	               .arg(table)
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
	               .arg(name)
	               .arg(operation);
	QTextStream(stdout) << msg << Qt::endl;
	QString rawInput = QTextStream(stdin).readLine();
	bool    ok;
	int     id = rawInput.toInt(&ok);
	if (!ok) {
		QTextStream(stdout) << "The inserted value is not a valid number" << Qt::endl;
		return {false, 0};
	}
	if (!entityIdExists(id)) {
		auto msg = QSL("No %1 with ID %2")
		               .arg(name)
		               .arg(id);
		QTextStream(stdout) << msg << Qt::endl;
		return {false, 0};
	}

	return {true, id};
}
