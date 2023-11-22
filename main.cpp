#include "menulogin.h"
#include "trymariadb.h"
#include <QCoreApplication>
#include <iostream>
#include "try.h"
#include "database.h"

using namespace std;

int main(int argc, char* argv[]) {
	//QCoreApplication a(argc, argv);
    
    initDb();

	//cout << "ciao ciao!" << endl;

	//tryMariaDb();

	//tryMenu();
    
    try0();
    

	//return a.exec();
}
