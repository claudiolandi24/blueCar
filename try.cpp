#include "try.h"
#include "car.h"
#include "rbk/QStacker/qstacker.h"
#include "rbk/minMysql/min_mysql.h"
#include "user.h"
#include "variadictable.h"
#include <QTextStream>
#include <iostream>

using namespace std;

extern DB db;
//using namespace Qt;

void tryQPrint() {
	QTextStream(stdout) << "Hello World" << Qt::endl;
	QTextStream(stdout) << "Hello World2" << Qt::endl;
}

void try1() {
	//	QTextStream(stdout) << "type\n";
	//	QString s = QTextStream(stdin).readLine();
	//	QTextStream(stdout) << "value is '" << s << "'\n";

	//    auto res = db.query("select * from db1.persons");
	//    int b = 0;
	//    Q_UNUSED(b);

	//    cout << "insert number\n";
	//    int n;
	//    cin >> n;

	//    QTextStream(stdout) << "QT insert number\n";
	//    QString s = QTextStream(stdin).readLine();

	//    auto car = Car::getNewCarFromUser();
	//    car.saveToDb();
}

void tryTable() {
	// Tiny Table
	{
		VariadicTable<std::string, double, int, std::string> vt({"Name", "Weight", "Age", "Brother"},
		                                                        10);

		vt.addRow("Cody", 180.2, 40, "John");
		vt.addRow("David", 175.3, 38, "Andrew");
		vt.addRow("Robert", 140.3, 27, "Fande");

		vt.print(std::cout);
	}
}

void tryTableCar() {
	Car::printAllCarsAsTable();
}

#include <QCryptographicHash>
void tryHash() {
	QString    password     = "asd123";
	QByteArray passwordData = password.toUtf8(); // Convert the password to UTF-8 encoded bytes
	QByteArray hashedData   = QCryptographicHash::hash(passwordData, QCryptographicHash::Sha256);

	// Convert the hashed data to a hexadecimal string
	QString hashedPassword = QString(hashedData.toHex());
	qDebug() << hashedPassword;
}

void tryErrPrint() {
	qDebug().noquote() << "message: function a() failed" << QStacker16Light();
	qInfo().noquote() << "message: function b() failed" << QStacker16Light();
	qWarning().noquote() << "message: function c() failed" << QStacker16Light();
	qCritical().noquote() << "message: function d() failed" << QStacker16Light();
	//qFatal("fatal message") << "message: function e() failed" << QStacker16Light();
}

void printAllUsers(){
    User::printAllUsersAsTable();
}

void try0() {
	//tryTable();
	//tryTableCar();
	//tryHash();
	//tryErrPrint();
    //printAllUsers();
    
    assert(false);
    
}
