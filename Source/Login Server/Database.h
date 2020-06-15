#pragma once

#include <mysql.h>
#include <iostream>

class Database
{
public:
	Database();
	std::string checkLoginPassword(std::string loginPassword);
	std::string getCharacter(std::string login);

private:
	MYSQL* conn;
};

