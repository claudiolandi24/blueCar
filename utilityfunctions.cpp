#include "utilityfunctions.h"
#include "rbk/QStacker/qstacker.h"
#include "rbk/defines/stringDefine.h"
#include <QDebug>
#include <QTextStream>
#include <memory>

int getTypeId(QString type) {
	type = type.trimmed();
	type = type.toLower();
	if (type == "eco") {
		return 1;
	} else if (type == "mid-class") {
		return 2;
	} else if (type == "deluxe") {
		return 3;
	} else {
		return 0;
	}
}

QString getTypeNameHuman(int id) {
	if (id == 1) {
		return "ECO";
	} else if (id == 2) {
		return "MID-CLASS";
	} else if (id == 3) {
		return "DELUXE";
	} else
		return QString();
}

int getLocationId(QString location) {
	location = location.trimmed();
	location = location.toLower();
	if (location == "inner circle") {
		return 1;
	} else if (location == "middle circle") {
		return 2;
	} else if (location == "outer circle") {
		return 3;
	} else {
		return 0;
	}
}

QString getLocationNameHuman(int id) {
	if (id == 1) {
		return "Inner Circle";
	} else if (id == 2) {
		return "Middle Circle";
	} else if (id == 3) {
		return "Outer Circle";
	} else
		return QString();
}

QString getAvailabilityHuman(bool isFree) {
	if (isFree) {
		return "free";
	} else {
		return "rented";
	}
}

bool isAlphanumeric(const QString& string) {
	for (const QChar& c : string) {
		if (!c.isLetterOrNumber()) {
			return false;
		}
	}
	return true;
}

bool isAlphanumeric(const QString& string, int maxLen) {
	bool ok = isAlphanumeric(string) and string.length() <= maxLen;
	return ok;
}


