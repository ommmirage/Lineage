#include "Database.h"

Database::Database(std::string filename)
{
	std::ifstream file;
	file.open(filename);
	if (file.is_open())
	{
		std::string line;

		while (getline(file, line))
		{
			db.insert(line);
		}
	}
}

// Returns true if the is a login - password pair in db
bool Database::checkLoginPassword(std::string loginPassword)
{
	return (db.find(loginPassword) == db.end());
}
