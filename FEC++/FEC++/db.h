//Script to initialise/fill in location names data
#ifndef INIT_DB_H_
#define INIT_DB_H_

#include <string>
#include "sqlite3/sqlite3.h"

namespace nsInfo
{

class Database
{
	sqlite3* m_db{nullptr};
	char m_dir;
	//float m_totalCost{ 0.0 };

public:
	Database(const char& dir) : 
		m_dir{dir}
	{

	}



	~Database()
	{
		Close();
	}

	void Close()
	{
		sqlite3_close(m_db);
		m_db = nullptr;
	}

	int Initialise();





};


} //nsInfo
#endif // !INIT_DB_H_
