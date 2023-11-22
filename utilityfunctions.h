#ifndef UTILITYFUNCTIONS_H
#define UTILITYFUNCTIONS_H

#include <QPair>
#include <QString>
#include <memory>

using namespace std;

class Validate {
      public:
	virtual QPair<bool, QString> getValidatedString(const QString& string) {
		Q_UNUSED(string);
		return {false, QString()};
	};
	virtual QPair<bool, int> getValidatedInt(const QString& string) {
		Q_UNUSED(string);
		return {false, 0};
	};
	virtual ~Validate() = default;
};

QString getValidatedString(const QString& requestMsg, unique_ptr<Validate> validate);
int     getValidatedInt(const QString& requestMsg, unique_ptr<Validate> validate);

int  getTypeId(QString type);
int  getLocationId(QString location);
bool isAlphanumeric(const QString& string);
bool isAlphanumeric(const QString& string, int maxLen);

#endif // UTILITYFUNCTIONS_H
