#include "Database.h"

#include <vector>
#include <sstream>
#include <iterator>

Database::Database()
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "pass", "login_pass", 3306, NULL, 0);
}

// Returns true if there is a login - password pair in db
bool Database::checkLoginPassword(std::string loginPassword)
{
	MYSQL_ROW row;
	MYSQL_RES* res;

	std::istringstream iss(loginPassword);
	std::vector<std::string> loginPass((std::istream_iterator<std::string>(iss)),
		std::istream_iterator<std::string>());

	std::string login = loginPass.at(0);
	std::string pass = loginPass.at(1);

	if (conn)
	{
		puts("Successful connection to database!");

		std::string query = "SELECT * FROM login_pass WHERE login = '" + login + "' AND pass = '" + pass + "'";
		const char* q = query.c_str();
		int qstate = mysql_query(conn, q);
		if (!qstate)
		{
			//printf("Query OK: %s", q);
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				printf("ID: %s, Login: %s, Password: %s\n", row[0], row[1], row[2]);
				return true;
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

	return false;
}
