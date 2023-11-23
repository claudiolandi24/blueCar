#include "try.h"
#include "rbk/minMysql/min_mysql.h"
#include "variadictable.h"
#include <QTextStream>
#include <iostream>
#include "car.h"


using namespace std;

extern DB db;
//using namespace Qt;

void tryQPrint() {
	QTextStream(stdout) << "Hello World" << Qt::endl;
	QTextStream(stdout) << "Hello World2" << Qt::endl;
}

void try1(){
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

void tryTableCar(){
    Car::printAllCarsAsTable();
}


void try0() {
	//tryTable();
    tryTableCar();


}
