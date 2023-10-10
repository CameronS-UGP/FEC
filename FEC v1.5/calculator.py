# Calculator
import jsh, session

def calculator(username):

    # This is the object for the json handler class
    locationsJSON = jsh.JSONFileHandler("data/locations.json")

    # Extracting the nicknames and setting up
    jsh.jsonExtraction(locationsJSON)

    curSession = session.Session(username)  # Creating object for the delivery session

    input(f"""
    Hi {curSession.username}! This script has been written to make your life easier when 
    totalling your fuel costs. You can use any realistic abbreviation for the location 
    names to make things quicker. For example instead of typing out 'Biggleswade', simply
    type 'bigs' or just 'bi' will do. Hit ENTER when you are ready to start.
    """)

    finished = False
    while not finished:
        flag = curSession.newSearch(locationsJSON)
        if flag == 'flag':
            finished = True

    print(f"\nThank you, {curSession.username}. Here are your details for this session.\nTotal Cost: £{curSession.totalCost:.2f}. Areas visited:")
    for location in curSession.locationsCount.keys():
        print(f"{location} {curSession.locationsCount[location]} time(s)")

    return {"total": curSession.totalCost}
