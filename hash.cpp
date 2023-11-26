#include "hash.h"
#include "config.h"
#include <QCryptographicHash>

QString getHash(const QString& string) {
	if (config::simulateHash) {
		return "HASH_OF_" + string;
	}

	QByteArray qbaString = string.toUtf8();
	QByteArray hash      = QCryptographicHash::hash(qbaString, QCryptographicHash::RealSha3_512);
	QString    strHash   = QString(hash.toHex());
	return strHash;
}
