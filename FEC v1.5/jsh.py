# JSON File Handler

import json

class JSONFileHandler:

    def __init__(self, jsonFilePath):
        self.jsonPath = jsonFilePath    # File directory path
        self.jsonFile = None                # converted json as a dict
        self.usefulKeys = ["nickname", "cost"]
        self.nickList = []  # For quicker searching

        self.openJSONFile()

    # Opens JSON file and converts to python dict
    # Dumps: Dict -> JSON (Dump for file writing)
    # Load: JSON -> Dict
    def openJSONFile(self):
        with open(self.jsonPath, "r") as json_file:
            self.jsonFile = json.load(json_file)
            json_file.close()

    # Writes new data to JSON file, taking a Python dict
    def writeJSONFile(self, newData):
        with open(self.jsonPath, "w") as json_file:
            json.dump(newData, json_file)

            json_file.close()


# Goes through the parsed JSON and splits the nicknames into a list
# Also populates the nicknames list attribute
def jsonExtraction(passedJSONObj):
    # This loop goes through the location names
    for location, data in passedJSONObj.jsonFile.items():
        # print(f"Key: {location}\n    Value: {data}")

        # Then convert the nicknames into a list, adding the full loc name first
        splitNicks = [location.lower().strip()]  # not case or whitespace sensitive
        splitNicks.extend(data['nickname'].split(','))
        passedJSONObj.nickList.extend(splitNicks)  # add to the quick search list
        passedJSONObj.jsonFile[location]['nickname'] = splitNicks  # replace the string value with a list

        # print(f"Splitnicks: {splitNicks}")





