#include <iostream>
#include <iomanip>

#include "myTools.h"
#include "Session.h"
#include "db.h"

namespace nsInfo
{

// directory to the database which is used each time a database
//  object is created. i.e. for accessing the SQL database
std::string FEC_DB_DIR{ "data/FEC_DB.db" };

// main program loop function to be written here

// It will:
// initialise a new object for Database and Session
// call
// Ask for user input here

int totalCostCalculator(const std::string username)
{
    Session session{ username }; //creating session object
    
    std::cout << "Hi " << session.GetUsername() << "! \n"
        << "This script has been written to make your life easier when \n"
        << "totalling your fuel costs. You can use any realistic abbreviation for the location \n"
        << "names to make things quicker. For example instead of typing out 'Biggleswade', simply \n"
        << "type 'bigs' or just 'bi' will do."
        << std::endl;

    bool running{ true };
    while (running) {
        std::string searchInput;
        //ask user for input
        std::cout << "\nType 'EXIT' in CAPS to finish\n"
            << "Enter location name or a nickname:" << std::endl;
        std::getline(std::cin, searchInput);
        //std::cin >> searchInput;

        if (searchInput == "EXIT") {
            running = false;
        }
        else { // continue
            // sanitise input
            searchInput = nsMyTools::removeWhitespace(searchInput);
            searchInput = nsMyTools::lowerCase(searchInput);

            //std::cout << "After sanitisation: " << searchInput << std::endl;

            // then check if user has entered at least 2 characters
            // a singular char could return too many results
            if (searchInput.length() < 2) {
                std::cout << "Input too short, please enter at least 2 characters." << std::endl;
                // loops round so user can retry their input
            }
            else { // begin search
                //send to nickname search feature
                session.requestTripSearch(searchInput);
            }
        } 
    } //endof loop

    // output the total to 2 decimal places
    std::cout << "Thank you " << session.GetUsername() << " . Here are you details for this shift.\n"
        << "Total Cost: " << nsMyTools::POUND_SIGN << std::fixed << std::setprecision(2) 
        << session.GetTotalCost() << ". Areas visited:" << std::endl;
    session.PrintLocsVisited();

    return 0;
}

void Session::PrintLocsVisited()
{
    int totalDeliveries{ 0 };

    for (auto it = m_locsVisited.begin(); it != m_locsVisited.end(); ++it) {
        int timesVisited{ it->second };
        totalDeliveries += timesVisited; 

        // determining whether to use plural or singular
        std::string times;
        if (timesVisited > 1) {
            times = "times";
        }
        else {
            times = { "time" };
        }

        std::cout << it->first << " " << timesVisited << " " << times << std::endl;
    }

    std::cout << "Total Deliveries: " << totalDeliveries << std::endl;
}

// Function to be called for each search 
// it takes user input, returns .....
// creates the db object
// call SearchNickname, once a successful status is returned it will
    // check the amount of pair entries in the searchOutput obj var
    // if too little/too many ask the user to try again -> later feature to give them options instead
    // singular result: run Addtrip, passing the contents of the pair as separate parameters.
nsMyTools::TSuccess Session::requestTripSearch(const std::string searchInput)
{
    nsMyTools::TSuccess ret{};

    // Initialise db connection
    nsInfo::Database database{ "data/FEC_DB.db" };
    database.OpenDB();

    // run search sequence, passing user's input
    database.SearchNickname(searchInput);

    int noOfSearchResults = database.GetSearchOutputSize();

    // check if there a multiple search results
    if (noOfSearchResults == 1) {
        // correct ammount
        //extracting info into separate vars for readability
        std::string  location{ database.GetSearchOutput().at(0).first };
        float        cost    { database.GetSearchOutput().at(0).second };
        // add to trip total
        this->AddTrip(location, cost);
        std::cout << "Found " << location << " @ " << nsMyTools::POUND_SIGN 
            << std::fixed << std::setprecision(2) << cost << "." << std::endl;
        ret = true;
    }
    else if (noOfSearchResults > 1) {
        // too many search results
        std::cout << "You received too many search results, "
            << "please enter a less ambiguous abbreviation." << std::endl;
        ret = false;
    }
    else if (noOfSearchResults == 0) {
        // no search results
        std::cout << "No location found for that abbreviation, please try again." << std::endl;
        ret = false;
    }
    else {
        std::cerr << "Unknown error occured searching for a location, please try again." << std::endl;
        ret = false;
    }

    return ret;
}


// Takes the location and fuel cost of a delivery and adds to the driver's session
void Session::AddTrip(const std::string location, const float cost)
{

    // First, adds the single delivery cost to the total session cost
    m_totalCost += cost;

    // Second, looks for a instance of the location in the locsVisted map
    auto it = m_locsVisited.find(location);

    if (it == m_locsVisited.end()) 
    { // if no instance found, then add it and set its value (times visited) to 1
        m_locsVisited[location] = 1;
    }
    else
    { // increment value (times visited) of existing key (location)
        m_locsVisited[location]++;
    }
}

} // nsInfo