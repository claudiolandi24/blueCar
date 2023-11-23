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

class ValidateType : public Validate {
public:
    ValidateType();
	QPair<bool, int> getValidatedInt(const QString& string) override;
};


class ValidateLocation : public Validate {
public:
    ValidateLocation();
	QPair<bool, int> getValidatedInt(const QString& string) override;
};

QString getValidatedString(const QString& requestMsg, unique_ptr<Validate> validate);
int     getValidatedInt(const QString& requestMsg, unique_ptr<Validate> validate);

#endif // VALIDATE_H
