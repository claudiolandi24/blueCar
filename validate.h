#ifndef VALIDATE_H
#define VALIDATE_H

#include "utilityfunctions.h"
#include <QPair>
#include <QString>

class Validate {
      public:
	QString conditionForValue;

	virtual ~Validate() = default;
	virtual QPair<bool, QString> getValidatedString(const QString& string);
	virtual QPair<bool, int>     getValidatedInt(const QString& string);
};

class ValidateGeneralAlphaNum : public Validate {
      public:
	ValidateGeneralAlphaNum();
	QPair<bool, QString> getValidatedString(const QString& string) override;
};

class ValidatePositiveOrZeroInteger : public Validate {
      public:
	ValidatePositiveOrZeroInteger();
	QPair<bool, int> getValidatedInt(const QString& string) override;
};

class ValidateCarType : public Validate {
      public:
	ValidateCarType();
	QPair<bool, int> getValidatedInt(const QString& string) override;
};

class ValidateLocation : public Validate {
      public:
	ValidateLocation();
	QPair<bool, int> getValidatedInt(const QString& string) override;
};

class ValidateUsername : public Validate {
      public:
	ValidateUsername();
	QPair<bool, QString> getValidatedString(const QString& string) override;
};

class ValidatePwd : public Validate {
      public:
	ValidatePwd();
	QPair<bool, QString> getValidatedString(const QString& string) override;
};

QString getValidatedString(const QString& requestMsg, unique_ptr<Validate> validate);
int     getValidatedInt(const QString& requestMsg, unique_ptr<Validate> validate);

#endif // VALIDATE_H
