#pragma once

#include <fstream>
#include <set>
#include <string>
#include <iostream>


class Database
{
public:
	Database(std::string filename);
	bool checkLoginPassword(std::string loginPassword);

private:
	std::set<std::string> db;
};

