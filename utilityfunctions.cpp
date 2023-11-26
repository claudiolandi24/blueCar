#include "utilityfunctions.h"
#include "rbk/QStacker/qstacker.h"
#include "rbk/defines/stringDefine.h"
#include <QDebug>
#include <QTextStream>
#include <memory>
#include <iostream>

const int secondsPerHour = 3600;
const int secondsPerMinute = 60;

QString getAvailabilityHuman(bool isFree) {
	if (isFree) {
		return "free";
	} else {
		return "rented";
	}
}

bool isAlphanumeric(const QString& string, const QList<QChar>& extraAllowedChars) {
	for (const QChar& c : string) {
		bool ok = c.isLetterOrNumber() or extraAllowedChars.contains(c);
		if (!ok) {
			return false;
		}
	}
	return true;
}

bool isNumeric(const QString& string, int maxLength) {
	if (maxLength and string.length() > maxLength) {
		return false;
	}

	for (const auto& c : string) {
		if (!c.isDigit()) {
			return false;
		}
	}
	return true;
}

NumericCheck::NumericCheck(bool ok_, int value_) {
	ok    = ok_;
	value = value_;
}

NumericCheck isNumericV2(const QString& string) {
	bool ok;
	int  n = string.toInt(&ok);
	if (!ok) {
		return {false, 0};
	}
	return {true, n};
}

bool isValidPwd(const QString& string) {
	if (string.length() < 10 or string.length() > 100) {
		return false;
	}

	bool hasLowerCase = false;
	bool hasUpperCase = false;
	bool hasDigit     = false;
	bool hasSymbol    = false;

	QString symbols = "!?@()[]{}";
	for (const auto& c : string) {
		if (c.isLower()) {
			hasLowerCase = true;
		} else if (c.isUpper()) {
			hasUpperCase = true;
		} else if (c.isDigit()) {
			hasDigit = true;
		} else if (symbols.contains(c)) {
			hasSymbol = true;
		} else {
			return false;
		}
	}
	bool ok = hasLowerCase and hasUpperCase and hasDigit and hasSymbol;
	return ok;
}

bool isAlphanumeric(const QString& string, int maxLen, const QList<QChar>& extraAllowedChars) {
	bool ok = isAlphanumeric(string, extraAllowedChars) and string.length() <= maxLen;
	return ok;
}

bool yesFromTerminal() {
	QString answer = QTextStream(stdin).readLine();
	answer         = answer.toLower();

	if (answer == "yes" or answer == "y") {
		return true;
	}
	return false;
}

void printEmptyLineSeparator() {
       cout << "\n\n";
}

