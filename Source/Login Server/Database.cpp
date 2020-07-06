#include "Database.h"

#include <vector>
#include <sstream>

Database::Database()
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "pass", "game_db", 3306, NULL, 0);
}

// Returns login if loginPassword pair is correct
std::string Database::checkLoginPassword(std::string loginPassword)
{
	MYSQL_ROW row;

	std::string login;
	std::string pass;

	std::istringstream iss(loginPassword);

	iss >> login >> pass;

	if (conn)
	{
		puts("Successful connection to database!");

		std::string query = "SELECT * FROM accounts WHERE login = '" + login + "' AND pass = '" + pass + "'";
		const char* q = query.c_str();
		int qstate = mysql_query(conn, q);
		if (!qstate)
		{
			MYSQL_RES* res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				printf("Login: %s, Password: %s\n", row[0], row[1]);
				return login;
			}
		}
		else
		{
			std::cout << "Query failed: " << mysql_error(conn) << std::endl;
		}
	}
	else
	{
		puts("Connection to database has failed!");
	}

	return "";
}

std::string Database::getCharacter(std::string login)
{
	MYSQL_ROW row;

	if (conn)
	{
		puts("Successful connection to database!");

		std::string query = "SELECT * FROM characters WHERE account_name = '" + login + "'";
		const char* q = query.c_str();
		int qstate = mysql_query(conn, q);

		if (!qstate)
		{
			MYSQL_RES* res = mysql_store_result(conn);
			std::ostringstream character{};

			while (row = mysql_fetch_row(res))
			{
				character << row[1] << " " << row[2] << " " << row[15] << " " << row[16];
				character << " " << row[17];
			}
			std::cout << "Database gave a string: " << character.str() << std::endl;
			
			return character.str();
		}
		else
		{
			std::cout << "Query failed: " << mysql_error(conn) << std::endl;
		}
	}
	else
	{
		puts("Connection to database has failed!");
	}

	return std::string();
}
