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

QString getValidatedString(const QString& requestMsg, unique_ptr<Validate> validate) {
	while (true) {
		QTextStream(stdout) << requestMsg << Qt::endl;
		QString value = QTextStream(stdin).readLine();
		value         = value.trimmed();
		auto res      = validate.get()->getValidatedString(value);

		if (res.first) {
			return res.second;
		}
		QTextStream(stdout) << "Invalid value" << value << "\n\n";
	}
}

int getValidatedInt(const QString& requestMsg, unique_ptr<Validate> validate) {
	while (true) {
		QTextStream(stdout) << requestMsg << Qt::endl;
		QString value = QTextStream(stdin).readLine();
		qDebug().noquote() << QSL("value = '%1'\n\n%2").arg(value).arg(QStacker16Light());
		value    = value.trimmed();
		auto res = validate.get()->getValidatedInt(value);

		if (res.first) {
			return res.second;
		}
		QTextStream(stdout) << "Invalid value" << value << "\n\n";
	}
}
