#include "validate.h"
#include <QTextStream>

QString getValidatedString(const QString& requestMsg, unique_ptr<Validate> validate) {
	while (true) {
		QTextStream(stdout) << requestMsg << Qt::endl;
		QString value = QTextStream(stdin).readLine();
		value         = value.trimmed();
		auto res      = validate.get()->getValidatedString(value);

		if (res.first) {
			return res.second;
		}
		QTextStream(stdout) << "Invalid value" << value << "\n\n";
	}
}

int getValidatedInt(const QString& requestMsg, unique_ptr<Validate> validate) {
	while (true) {
		QTextStream(stdout) << requestMsg << Qt::endl;
		QString value = QTextStream(stdin).readLine();
		//TODO
		//qDebug().noquote() << QSL("value = '%1'\n\n%2").arg(value).arg(QStacker16Light());
		value    = value.trimmed();
		auto res = validate.get()->getValidatedInt(value);

		if (res.first) {
			return res.second;
		}
		QTextStream(stdout) << "Invalid value" << value << "\n\n";
	}
}
