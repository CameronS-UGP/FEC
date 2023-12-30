#include <iostream>
#include "initDB.h"

namespace nsInfo
{
	int Database::Initialise() 
	{
		int ret{};
		char* zErrMsg = 0;
		int rc;

		rc = sqlite3_open("test.db", &m_db);

		if (rc) {
			fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(m_db));
		}
		else {
			fprintf(stderr, "Opened database successfully\n");
		}
		sqlite3_close(m_db); //temp

		return rc;
	}


} //nsInfo