#include "database.h"

DB db;

void initDb(){
    DBConf conf;
	conf.host = "127.0.0.1";
	conf.user = "claudio";
	conf.pass = "claudio";
	conf.port = 3306;
    conf.defaultDB = "blueCar";
	db.setConf(conf);
}
