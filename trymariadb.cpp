#include "trymariadb.h"
#include "rbk/minMysql/min_mysql.h"

void tryMariaDb(){
    DBConf conf;
	conf.host = "127.0.0.1";
	conf.user = "claudio";
	conf.pass = "claudio";
	conf.port = 3306;
    conf.defaultDB = "blueCar";
	DB db;
	db.setConf(conf);
    
    auto res = db.query("select * from type");
    
    [[maybe_unused]] int breakPoint = 0;
}
