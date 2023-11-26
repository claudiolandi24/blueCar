#include "validate.h"
#include "cartype.h"
#include "rbk/QStacker/qstacker.h"
#include "user.h"
#include <QRegularExpression>
#include <QTextStream>
#include "location.h"

Check::Check(bool ok_, QString value_) {
	ok    = ok_;
	value = value_;
}

Check::Check(bool ok_, QString value_, QString errMsg_)
    : Check(ok_, value_) {
	errMsg = errMsg_;
}

Check Validate::getValidatedString(const QString& string) {
	Q_UNUSED(string);
	return {false, {}};
};

QPair<bool, int> Validate::getValidatedInt(const QString& string) {
	Q_UNUSED(string);
	return {false, 0};
};

ValidateGeneralAlphaNum::ValidateGeneralAlphaNum() {
	conditionForValue = "; must contain only alphanumeric characters, max length 100";
}

Check ValidateGeneralAlphaNum::getValidatedString(const QString& string) {
	bool ok = isAlphanumeric(string, 100);
	if (!ok) {
		return {false, {}};
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

ValidateNumbPersons::ValidateNumbPersons() {
	conditionForValue = "; must be an integer >= 1 and <= 7";
}

QPair<bool, int> ValidateNumbPersons::getValidatedInt(const QString& string) {
	//claudio
	auto check = isNumericV2(string);
	if (!check.ok) {
		return {false, 0};
	}
	int n = check.value;
	if (n < 1 or n > 7) {
		return {false, 0};
	}
	return {true, n};
}

ValidateCarType::ValidateCarType(int minNumbPersons_) {
	minNumbPersons    = minNumbPersons_;
	okTypes           = CarType::getCarTypes(minNumbPersons);
	conditionForValue = "; must be " + CarType::asStringFullName(okTypes) + " (" + CarType::asStringInitial(okTypes) + ")";
}

QPair<bool, int> ValidateCarType::getValidatedInt(const QString& string) {
    qDebug().noquote() << "string = "<< string <<"\n"<<QStacker16Light();
	int typeId = CarType::getIdFromNameTolerant(string);
	if (!typeId) {
		// Type does not exist
		return {false, 0};
	}
	for (const auto& type : okTypes) {
		if (type.id == typeId) {
			// Type is ok: min number of persons satisfied
			return {true, typeId};
		}
	}
    // Type not ok: not enough number of persons for it
	return {false, 0};
}

ValidateLocation::ValidateLocation() {
	conditionForValue = "; must be 'Inner Circle', 'Middle Circle' or 'Outer Circle' (I, M or O)";
}

QPair<bool, int> ValidateLocation::getValidatedInt(const QString& string) {
	int locationId = Location::getLocationIdTolerant(string);
	if (!locationId) {
		return {false, 0};
	}
	return {true, locationId};
}

ValidateUsername::ValidateUsername() {
	conditionForValue = "; must contain only alphanumeric characters or '_', max length 50";
}

Check ValidateUsername::getValidatedString(const QString& string) {
	bool ok = isAlphanumeric(string, 50, {'_'});
	if (!ok) {
		return {false, QString()};
	}
	if (User::usernameExists(string)) {
		return {false, {}, "Username already in use, choose a different one"};
	}
	return {true, string};
}

ValidateDrivingLicense::ValidateDrivingLicense() {
	conditionForValue = "; must be alphanumeric string, length = 10";
}

Check ValidateDrivingLicense::getValidatedString(const QString& string) {
	bool ok = isAlphanumeric(string) and string.length() == 10;
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
- 1 symbol of these: !, ?, @, (, ), [, ], {, })";
}

Check ValidatePwd::getValidatedString(const QString& string) {
	bool ok = isValidPwd(string);
	if (!ok) {
		return {false, QString()};
	}
	return {true, string};
}

ValidateCreditCardNumber::ValidateCreditCardNumber() {
	conditionForValue = "must contain only digits, max length = 19";
}

//TODO
// remove all magic numbs
// for example here CONFIG <--- or define const for class <--- maybe better?
Check ValidateCreditCardNumber::getValidatedString(const QString& string) {
	bool ok = isNumeric(string, 19);
	if (!ok) {
		return {false, {}};
	}
	return {true, string};
}

ValidateCreditCardDate::ValidateCreditCardDate() {
	conditionForValue = "must have the format 'MM/AAAA'";
}

Check ValidateCreditCardDate::getValidatedString(const QString& string) {
	// Format for date is 'MM/YYYY'
	static QRegularExpression regexp("^\\d{2}/\\d{4}$");
	QRegularExpressionMatch   match = regexp.match(string);
	bool                      ok    = match.hasMatch() and match.captured(0) == string;
	if (!ok) {
		return {false, {}};
	}
	return {true, string};
}

ValidateCreditCardSecureCode::ValidateCreditCardSecureCode() {
	conditionForValue = "must contain only digits, max length = 4";
}

Check ValidateCreditCardSecureCode::getValidatedString(const QString& string) {
	bool ok = isNumeric(string, 4);
	if (!ok) {
		return {false, {}};
	}
	return {true, string};
}

QString getValidatedString(const QString& requestMsg, unique_ptr<Validate> validate) {
	while (true) {
		QTextStream(stdout) << requestMsg << validate.get()->conditionForValue << Qt::endl;
		QString value = QTextStream(stdin).readLine();
		value         = value.trimmed();
		auto res      = validate.get()->getValidatedString(value);

		if (res.ok) {
			return res.value;
		}
		if (!res.errMsg.isEmpty()) {
			QTextStream(stdout) << res.errMsg << "\n\n";
		} else {
			QTextStream(stdout) << "Invalid value " << value << "\n\n";
		}
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
		QTextStream(stdout) << "Invalid value " << value << "\n\n";
	}
}
