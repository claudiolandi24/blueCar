#ifndef UTILITYFUNCTIONS_H
#define UTILITYFUNCTIONS_H

#include <QList>
#include <QPair>
#include <QString>
#include <memory>

using namespace std;

extern const int secondsPerHour;

QString getAvailabilityHuman(bool isFree);

bool isAlphanumeric(const QString& string, const QList<QChar>& extraAllowedChars = QList<QChar>());

class NumericCheck {
      public:
	bool ok    = false;
	int  value = 0;

	NumericCheck(bool ok_, int value_);
};

bool         isNumeric(const QString& string, int maxLength = 0);
NumericCheck isNumericV2(const QString& string);
/*
 * Allowed characters:
 * - letters
 * - digits
 * - any symbol of these: !, ?, @, (, ), [, ], {, }
 *
 * Min length = 10
 * Max length = 100
 *
 * And must contain at least the following:
 * - 1 upper-case letter
 * - 1 lowercase letter
 * - 1 digit
 * - 1 symbol of these: !, ?, @, (, ), [, ], {, }
 */
bool isValidPwd(const QString& string);
bool isAlphanumeric(const QString& string, int maxLen, const QList<QChar>& extraAllowedChars = QList<QChar>());

bool yesFromTerminal();

#endif // UTILITYFUNCTIONS_H
