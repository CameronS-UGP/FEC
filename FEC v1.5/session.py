# Session

class Session:

    def __init__(self, username):
        self.username = username
        self.locationsCount = {}  # A dictionaries of locations with number of times visited (key = location name, value = times visited)
        self.totalCost = 0.0

    def newSearch(self, locationsJSON):
        print("Type 'EXIT' in CAPS to finish.\nEnter location name/nickname:")
        searchInput = input()

        if searchInput == 'EXIT':
            return 'flag'

        location, cost = locationSearcher(locationsJSON, searchInput)
        if location:
            self.addTotal(location, cost)

            print(f"Found: {location} @ £{cost:.2f}")

        print()

    # Total

    # Takes the location and fuel cost of a delivery and adds to the driver's session
    def addTotal(self, location, cost):
        # First, adds the single delivery cost to the total session cost
        self.totalCost += cost

        # Second, iterated through locations dictonairy
        if location in self.locationsCount.keys():
            self.locationsCount[location] += 1
        else:
            self.locationsCount[location] = 1


# Search

# NOTE: Possible solution to index nick bank and use to faster find the fuel cost in the location dictionary?
#       Use the full location names as indexes?

# Takes the user's input and references against the nickname bank
# If the user inputs a valid location (nickname), the location and fuel cost is returned
# If it's invalid, error is returned
def locationSearcher(passedJSONObj, searchInput):
    # search is not case or whitespace sensitive
    searchInput = searchInput.lower().strip()
    # First does a preliminary check against the nickname bank
    if searchInput in passedJSONObj.nickList:  # Possibly redundant - not been timed
        # If found, will now search through dictionary
        print("Valid term -> finding fuel cost..")
        # Loops through locations looking for matching term
        for location, data in passedJSONObj.jsonFile.items():
            # Checks for term in location's list of nicknames
            if searchInput in data['nickname']:
                return location, data['cost']
    else:
        print("Invalid term, location not found")
        return False, None