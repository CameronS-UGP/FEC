#include <iostream>
#include "db.h"

namespace nsInfo
{
	int Database::Initialise() 
	{
		int ret{0};
		char* zErrMsg = 0;
		int sqlRet;

		sqlRet = sqlite3_open(&m_dir, &m_db);

		if (sqlRet) {
			fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(m_db));
		}
		else {
			fprintf(stderr, "Opened database successfully\n");
		}
		

		
		
		sqlite3_close(m_db); //temp

		return ret;
	}


} //nsInfo