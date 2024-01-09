#include <iostream>
#include <sstream>
#include <cassert>
#include <stdexcept>
#include <typeinfo>

#include "myTools.h"
#include "db.h"

namespace nsInfo
{

// Opens the sqlite database, returning an error if occured
int Database::OpenDB()
{
	nsMyTools::TSuccess ret{ false };
	int db_conn{ 0 };

	db_conn = sqlite3_open(m_dir.c_str(), &m_pDB);

	if (db_conn) {
		std::cerr << "Error open DB " << sqlite3_errmsg(m_pDB) << std::endl;
		ret = false;
	}
	else {
		//std::cout << "Opened Database Successfully!" << std::endl;
		ret = true;
	}
		
	return ret;
}

// Callback function for searching a nickname in the database
// Takes in the Database object as well as the SQL Server results
// Validates, then stores the result in the designated member vector
int nickCallback(void* data, int colCt, char** argv, char** azColName)
{
	int ret{-1};

	Database* pDatabase = reinterpret_cast<Database*>(data);
	assert(pDatabase);

	// First, checks if the SQL database has returned the correct amount of columns
	if (colCt == 2) {
		// argv[0] = location name, argv[1] = trip cost

		// attempts to convert the trip cost, which is passed as a C-string to a float
		nsMyTools::TRetFloatPair stofRet = nsMyTools::stringToFloat(argv[1]);

		// pushes converted SQL result onto the m_searchOutput vector if successfully converted
		// to a float
		if (stofRet.first == true) {
			// pair stofRet contains { bool success, float convertedFloat }
			TLocCostPair locCostPair{ argv[0], stofRet.second };
			// sending the location name and corresponding trip cost to the searchOutput
			pDatabase->AppendSearchOutput(locCostPair);
			
			ret = 0; // operation is success
			//std::cout << "Callback successful" << std::endl;
		}
		else {
			std::cerr << "Error: Could not obtain valid trip cost" << std::endl;
		}

	}
	else {
		std::cerr << "Error: Incorrect Columns received." << std::endl;
	}

	return ret;
}

/* Takes in a string from a user input and runs an SQL query searching for any instance of this
*  keyword. *Returns success 0 or failure -1 */
float Database::SearchNickname(const std::string inputNickname) 
{
	nsMyTools::TSuccess ret{ false };
	char* errMsg;

	std::ostringstream prepQuery;
	prepQuery << "SELECT town, cost FROM locations WHERE nicknames LIKE '%" << inputNickname << "%';";
	//prepQuery << "SELECT * FROM locations;";
	const std::string sqlQuery{prepQuery.str()};

	int sqlSuccess = sqlite3_exec(m_pDB, sqlQuery.c_str(), nsInfo::nickCallback, (void*)this, &errMsg);

	if (sqlSuccess != SQLITE_OK) {
		std::cerr << "Error Code: " << sqlSuccess << " - Error Msg: " << errMsg << std::endl;
		ret = false;
	}
	else {
		//std::cout << "Operation OK!" << std::endl;
		ret = true;
	}

	return ret;
}

} //nsInfo