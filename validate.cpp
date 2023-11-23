#include "validate.h"
#include <QTextStream>

QPair<bool, QString> Validate::getValidatedString(const QString& string) {
	Q_UNUSED(string);
	return {false, QString()};
};

QPair<bool, int> Validate::getValidatedInt(const QString& string) {
	Q_UNUSED(string);
	return {false, 0};
};

ValidateGeneralAlphaNum::ValidateGeneralAlphaNum() {
	conditionForValue = "; must contain only alphanumeric characters, max length 100";
}

QPair<bool, QString> ValidateGeneralAlphaNum::getValidatedString(const QString& string) {
	bool ok = isAlphanumeric(string, 100);
	if (!ok) {
		return {false, QString()};
	}
	return {true, string};
}

ValidatePositiveOrZeroInteger::ValidatePositiveOrZeroInteger() {
	conditionForValue = "; must be an integer >= 0";
}

QPair<bool, int> ValidatePositiveOrZeroInteger::getValidatedInt(const QString& string) {
	bool ok;
	int  n = string.toInt(&ok);
	if (!ok) {
		return {false, 0};
	}
	if (n < 0) {
		return {false, 0};
	}
	return {true, n};
}

ValidateCarType::ValidateCarType() {
	conditionForValue = "; must be ECO, MID-CLASS or DELUXE";
}

QPair<bool, int> ValidateCarType::getValidatedInt(const QString& string) {
	int typeId = getTypeId(string);
	if (!typeId) {
		return {false, 0};
	}
	return {true, typeId};
}

ValidateLocation::ValidateLocation() {
	conditionForValue = "; must be 'Inner Circle', 'Middle Circle' or 'Outer Circle'";
}

QPair<bool, int> ValidateLocation::getValidatedInt(const QString& string) {
	int locationId = getLocationId(string);
	if (!locationId) {
		return {false, 0};
	}
	return {true, locationId};
}

ValidateUsername::ValidateUsername() {
	conditionForValue = "; must contain only alphanumeric characters or '_', max length 50";
}

QPair<bool, QString> ValidateUsername::getValidatedString(const QString& string) {
	bool ok = isAlphanumeric(string, 50, {'_'});
	if (!ok) {
		return {false, QString()};
	}
	return {true, string};
}

ValidatePwd::ValidatePwd() {
	conditionForValue = R"(.
Allowed characters:
- letters
- digits
- any symbol of these: !, ?, @, (, ), [, ], {, }
  
Min length = 10
Max length = 100
  
And must contain at least the following:
- 1 upper-case letter
- 1 lowercase letter
- 1 digit
- 1 allowed symbol)";
}

QPair<bool, QString> ValidatePwd::getValidatedString(const QString& string) {
	bool ok = isValidPwd(string);
	if (!ok) {
		return {false, QString()};
	}
	return {true, string};
}

QString getValidatedString(const QString& requestMsg, unique_ptr<Validate> validate) {
	while (true) {
		QTextStream(stdout) << requestMsg << validate.get()->conditionForValue << Qt::endl;
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
		QTextStream(stdout) << requestMsg << validate.get()->conditionForValue << Qt::endl;
		QString value = QTextStream(stdin).readLine();
		//TODO
		//qDebug().noquote() << QSL("value = '%1'\n\n%2").arg(value).arg(QStacker16Light());
		value    = value.trimmed();
		auto res = validate.get()->getValidatedInt(value);

		if (res.first) {
			return res.second;
		}
		QTextStream(stdout) << "Invalid value" << value << "\n\n";
	}
}
