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

		std::ostringstream charData{};
		std::string id;

		// Get id, nick and location

		std::string query = "SELECT * FROM characters WHERE account_name = '" + login + "'";
		const char* q = query.c_str();
		int qstate = mysql_query(conn, q);

		if (!qstate)
		{
			MYSQL_RES* res = mysql_store_result(conn);

			while (row = mysql_fetch_row(res))
			{
				id = row[1];
				charData << row[1] << " " << row[2] << " " << row[15] << " " << row[16];
				charData << " " << row[17];
			}

			// Get inventory

			query = "SELECT * FROM items WHERE owner_id = " + id;
			const char* q1 = query.c_str();
			qstate = mysql_query(conn, q1);

			if (!qstate)
			{
				res = mysql_store_result(conn);

				while (row = mysql_fetch_row(res))
				{
					charData << " " << row[1] << " " << row[2] << " " << row[3];
				}

				std::cout << "Database gave a string: " << charData.str() << std::endl;

				return charData.str();
			}
			else
			{
				std::cout << "Query failed: " << mysql_error(conn) << std::endl;
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

	return std::string();
}
