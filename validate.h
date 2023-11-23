#ifndef VALIDATE_H
#define VALIDATE_H

#include <QString>
#include <QPair>
#include "utilityfunctions.h"

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

class ValidateGeneralAlphaNum : public Validate {
	QPair<bool, QString> getValidatedString(const QString& string) override {
		bool ok = isAlphanumeric(string, 100);
		if (!ok) {
			return {false, QString()};
		}
		return {true, string};
	}
};

class ValidatePositiveOrZeroInteger : public Validate {
	QPair<bool, int> getValidatedInt(const QString& string) override {
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
};

class ValidateType : public Validate {
	QPair<bool, int> getValidatedInt(const QString& string) override {
		int typeId = getTypeId(string);
		if (!typeId) {
			return {false, 0};
		}
		return {true, typeId};
	}
};

class ValidateLocation : public Validate {
	QPair<bool, int> getValidatedInt(const QString& string) override {
		int locationId = getLocationId(string);
		if (!locationId) {
			return {false, 0};
		}
		return {true, locationId};
	}
};

QString getValidatedString(const QString& requestMsg, unique_ptr<Validate> validate);
int     getValidatedInt(const QString& requestMsg, unique_ptr<Validate> validate);


#endif // VALIDATE_H
