#ifndef VALIDATE_H
#define VALIDATE_H

#include "utilityfunctions.h"
#include <QPair>
#include <QString>

class Validate {
      public:
	virtual QPair<bool, QString> getValidatedString(const QString& string);
	virtual QPair<bool, int>     getValidatedInt(const QString& string);
	virtual ~Validate() = default;
};

class ValidateGeneralAlphaNum : public Validate {
	QPair<bool, QString> getValidatedString(const QString& string) override;
};

class ValidatePositiveOrZeroInteger : public Validate {
	QPair<bool, int> getValidatedInt(const QString& string) override;
};

class ValidateType : public Validate {
	QPair<bool, int> getValidatedInt(const QString& string) override;
};

class ValidateLocation : public Validate {
	QPair<bool, int> getValidatedInt(const QString& string) override;
};

QString getValidatedString(const QString& requestMsg, unique_ptr<Validate> validate);
int     getValidatedInt(const QString& requestMsg, unique_ptr<Validate> validate);

#endif // VALIDATE_H
