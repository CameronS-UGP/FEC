#ifndef SESSION_H_
#define SESSION_H_

#include <string>
#include <map>

namespace nsInfo
{

using TSessionMap = std::map<std::string, int>;


// A 'Session' refers to a delivery shift which is only used for the feature where
//  each delivery destination reached is totalled up
class Session
{
	std::string m_username;
	float m_totalCost{ 0.0 };

	/* A map of locations with number of times visited. It is calulated per session
	* and appended to each time the user searches with a location nickname
	  key = location name, value = times visited */
	TSessionMap m_locsVisited;

public:
	Session(const std::string& username) :
		m_username{ username }
	{

	}

	~Session()
	{
		m_username = "";
		m_locsVisited = {};
		m_totalCost = 0.0 ;
	}

	// Setters
	void SetUsername(const std::string username) 
	{ 
		m_username = username; 
	}

	// Getters
	std::string GetUsername() const
	{ 
		return m_username;
	}
	const TSessionMap& GetLocsVisited() const
	{ 
		return m_locsVisited;
	}
	float GetTotalCost() const
	{ 
		return m_totalCost;
	}
	
	//Printers
	void PrintLocsVisited();

	// Modifiers
	void AddTotalCost(const float tripCost)
	{
		m_totalCost += tripCost;
	}

	// Add the passed cost onto m_totalCost and increment the key in m_locsVisted
	// or push back a new key and value if not already present
	void AddTrip(const std::string trip, const float cost);

	// For running the search feature after the user provides a 'nickname' input
	nsMyTools::TSuccess requestTripSearch(const std::string searchInput);

}; //Class Session

// Non-Member functions
int totalCostCalculator(const std::string username);


} // nsInfo

#endif // SESSION_H_