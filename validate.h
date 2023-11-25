#ifndef VALIDATE_H
#define VALIDATE_H

#include "utilityfunctions.h"
#include <QPair>
#include <QString>

class Check {
public:
	bool    ok = false;
	QString value;
	QString errMsg;
    
    Check(bool ok_,QString value_);
    Check(bool ok_,QString value_,QString errMsg_);
};

class Validate {
      public:
	QString conditionForValue;

	virtual ~Validate() = default;
	virtual Check getValidatedString(const QString& string);
	virtual QPair<bool, int>     getValidatedInt(const QString& string);
};

class ValidateGeneralAlphaNum : public Validate {
      public:
	ValidateGeneralAlphaNum();
	Check getValidatedString(const QString& string) override;
};

class ValidatePositiveOrZeroInteger : public Validate {
      public:
	ValidatePositiveOrZeroInteger();
	QPair<bool, int> getValidatedInt(const QString& string) override;
};

class ValidateNumbPersons : public Validate {
      public:
	ValidateNumbPersons();
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
	Check getValidatedString(const QString& string) override;
};

class ValidatePwd : public Validate {
      public:
	ValidatePwd();
	Check getValidatedString(const QString& string) override;
};

class ValidateDrivingLicense : public Validate {
      public:
	ValidateDrivingLicense();
	Check getValidatedString(const QString& string) override;
};

class ValidateCreditCardNumber : public Validate {
      public:
	ValidateCreditCardNumber();
	Check getValidatedString(const QString& string) override;
};

class ValidateCreditCardDate : public Validate {
      public:
	ValidateCreditCardDate();
	Check getValidatedString(const QString& string) override;
};

class ValidateCreditCardSecureCode : public Validate {
      public:
	ValidateCreditCardSecureCode();
	Check getValidatedString(const QString& string) override;
};

QString
    getValidatedString(const QString& requestMsg, unique_ptr<Validate> validate);
int getValidatedInt(const QString& requestMsg, unique_ptr<Validate> validate);

#endif // VALIDATE_H
