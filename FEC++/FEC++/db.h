//class for accessing an sql database
#ifndef DB_H_
#define DB_H_

#include <string>
#include <vector>
#include "sqlite3/sqlite3.h"

namespace nsInfo
{

using TLocCostPair = std::pair<std::string, float>;
using TSqlSrchOutput = std::vector<TLocCostPair>;

class Database
{
	sqlite3* m_pDB{nullptr};
	std::string m_dir;
	float m_result{0.0};
	TSqlSrchOutput m_searchOutput;

public:
	Database(const std::string &dir) : 
		m_dir{dir}
	{

	}

	~Database()
	{
		Close();
	}

	void Close()
	{
		sqlite3_close(m_pDB);
		m_pDB = nullptr;
		m_dir = "";
		m_result = 0.0;
	}

	// Setters
	void SetResult(const float newRes) 
	{
		m_result = newRes;
	}

	//Getters
	float GetResult() const
	{
		return m_result;
	}
	const TSqlSrchOutput& GetSearchOutput() const
	{
		return m_searchOutput;
	}

	// Modifiers
	void appendSearchOutput(const TLocCostPair& locCostPair)
	{
		m_searchOutput.push_back(locCostPair);
	}

	int OpenDB();
	float SearchNickname(const std::string inputNickname);
	//int Callback(void* data, int colCt, char** argv, char** azColName);





};


} // nsInfo
#endif // !DB_H_
