#include "try.h"
#include "rbk/minMysql/min_mysql.h"
#include <QTextStream>
#include <iostream>

using namespace std;

extern DB db;
//using namespace Qt;

void tryQPrint() {
	QTextStream(stdout) << "Hello World" << Qt::endl;
	QTextStream(stdout) << "Hello World2" << Qt::endl;
}

#include "car.h"
void try0() {
//	QTextStream(stdout) << "type\n";
//	QString s = QTextStream(stdin).readLine();
//	QTextStream(stdout) << "value is '" << s << "'\n";
    
    
    
//    auto res = db.query("select * from db1.persons");
//    int b = 0;
//    Q_UNUSED(b);
    
    
//    cout << "insert number\n";
//    int n;
//    cin >> n;
    
    QTextStream(stdout) << "QT insert number\n";
    QString s = QTextStream(stdin).readLine();
    
    
    auto car = Car::getNewCarFromUser();
    car.saveToDb();
    
    
}
