#pragma once
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class CDbUtil
{
public:
	CDbUtil();
	~CDbUtil();
	static const sql::SQLString DB_URL;
	static const sql::SQLString DB_USER;
	static const sql::SQLString DB_PASS;
	static const sql::SQLString DB_SCHEMA;
	//static 	sql::Connection* getConnection();
	//static void closeConnection();
	static sql::Connection* getConnection();
 
};

