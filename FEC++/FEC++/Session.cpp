#include "Session.h"

namespace nsInfo
{

// Function to call both SearchNickname and AddTrip


// Takes the location and fuel cost of a delivery and adds to the driver's session
void Session::AddTrip(const std::string trip, const float cost)
{

    // First, adds the single delivery cost to the total session cost
    m_totalCost += cost;

    // Second, iterated through locations dictonary

    auto it = m_locsVisited.find(trip);

    if (it == m_locsVisited.end())
    {
        m_locsVisited[trip] = 1;
    }
    else
    {
        m_locsVisited[trip]++;
    }
}

} // nsInfo