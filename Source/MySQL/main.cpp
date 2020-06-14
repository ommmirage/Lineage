#include <mysql.h>
#include <iostream>

int qstate;

int main()
{
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "pass", "login_pass", 3306, NULL, 0);

	if (conn)
	{
		puts("Successful connection to database!");

		std::string query = "SELECT * FROM login_pass";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				printf("ID: %s, Login: %s, Password: %s\n", row[0], row[1], row[2]);
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

	return 0;
}