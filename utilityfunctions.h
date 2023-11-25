#ifndef UTILITYFUNCTIONS_H
#define UTILITYFUNCTIONS_H

#include <QList>
#include <QPair>
#include <QString>
#include <memory>

using namespace std;

int     getLocationId(QString location);
QString getLocationNameHuman(int id);
QString getAvailabilityHuman(bool isFree);

namespace utility {
bool isAlphanumeric(const QString& string, const QList<QChar>& extraAllowedChars = QList<QChar>());

class Check {
      public:
	bool ok    = false;
	int  value = 0;

	Check(bool ok_, int value_);
};

bool isNumeric(const QString& string, int maxLength = 0);
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
} // namespace utility

#endif // UTILITYFUNCTIONS_H
