#include <iostream>
#include <sstream>
#include <cassert>
#include "db.h"

namespace nsInfo
{
	//Opens the sqlite database, returning an error if occured
	int Database::OpenDB()
	{
		int ret{0};
		int db_conn{0};

		db_conn = sqlite3_open(m_dir.c_str(), &m_pDB);

		if (db_conn) {
			std::cerr << "Error open DB " << sqlite3_errmsg(m_pDB) << std::endl;
			ret = -1;
		}
		else {
			std::cout << "Opened Database Successfully!" << std::endl;
			ret = 0;
		}
		
		return ret;
	}

	//Callback function for searching a nickname in the database
	//Takes in the Database object as well as the SQL Server results
	//Stores the 
	int nickCallback(void* data, int colCt, char** argv, char** azColName)
	{
		Database* pDatabase = reinterpret_cast<Database*>(data);
		assert(pDatabase);

		int argvSize = sizeof(argv) / sizeof(argv[0]);
		std::cout << "Column Count: " << colCt << "\nNumber of SELECT results: " << argvSize << std::endl;


		for (int i = 0; i < colCt; i++) {
			printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		}

		pDatabase->SetResult(69.69);

		std::cout << "Callback Finished" << std::endl;
		return 0;
	}

	/*Takes in a string from a user input and runs an SQL query searching for any instance of this
	* keyword. Returns  */
	float Database::SearchNickname(const std::string inputNickname) 
	{
		char* errMsg;

		std::ostringstream prepQuery;
		//prepQuery << "SELECT town, cost FROM locations WHERE nicknames LIKE '%" << inputNickname << "%';";
		prepQuery << "SELECT * FROM locations;";
		const std::string sqlQuery{prepQuery.str()};

		int rc = sqlite3_exec(m_pDB, sqlQuery.c_str(), nsInfo::nickCallback, (void*)this, &errMsg);

		if (rc != SQLITE_OK)
			std::cerr << "Error Code: " << rc << " - Error Msg: " << errMsg << std::endl;
		else {
			std::cout << "Operation OK!" << std::endl;
		}

		return m_result;
	}
} //nsInfo