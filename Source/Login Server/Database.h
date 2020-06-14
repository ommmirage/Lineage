#pragma once

#include <mysql.h>
#include <iostream>

class Database
{
public:
	Database();
	bool checkLoginPassword(std::string loginPassword);

private:
	MYSQL* conn;
};

