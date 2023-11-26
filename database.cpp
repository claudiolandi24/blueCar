#include "database.h"
#include "config.h"

DB db;

void initDb() {
	DBConf conf;
	conf.host      = config::mariaDbHost.toUtf8();
	conf.user      = config::mariaDbUser.toUtf8();
	conf.pass      = config::mariaDbPwd.toUtf8();
	conf.port      = config::mariaDbPort;
	conf.defaultDB = config::mariaDbDefaultDb.toUtf8();
	db.setConf(conf);
}
