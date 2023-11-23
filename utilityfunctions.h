#ifndef UTILITYFUNCTIONS_H
#define UTILITYFUNCTIONS_H

#include <QList>
#include <QPair>
#include <QString>
#include <memory>

using namespace std;

int     getTypeId(QString type);
QString getTypeNameHuman(int id);
int     getLocationId(QString location);
QString getLocationNameHuman(int id);
QString getAvailabilityHuman(bool isFree);
bool    isAlphanumeric(const QString& string, const QList<QChar>& extraAllowedChars = QList<QChar>());
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

#endif // UTILITYFUNCTIONS_H
