#include "stdafx.h"
#include "CDbUtil.h"


CDbUtil::CDbUtil()
{
}


CDbUtil::~CDbUtil()
{
}
const sql::SQLString CDbUtil::DB_URL = "tcp://47.75.36.103:3333/test";
const sql::SQLString CDbUtil::DB_USER = "db_test";
const sql::SQLString CDbUtil::DB_PASS = "db_test";
const sql::SQLString CDbUtil::DB_SCHEMA = "test";

sql::Connection* CDbUtil::getConnection()
{
	sql::Driver *driver;
	sql::Connection *con;

	/* Create a connection */
	driver = get_driver_instance();
	con = driver->connect(CDbUtil::DB_URL, CDbUtil::DB_USER, CDbUtil::DB_PASS);
	/* Connect to the MySQL test database */
	//con->setSchema(CDbUtil::DB_SCHEMA);
	//con->setClientOption("OPT_CHARSET_NAME", "utf8");
	//sql::Statement* smt =con->createStatement();
	//smt->execute("set names utf8;");
	//delete smt;
	return con;
}


