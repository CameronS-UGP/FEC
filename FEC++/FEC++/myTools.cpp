#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

#include "myTools.h"

namespace nsMyTools
{

char POUND_SIGN = 156;

// Takes a string and checks if it can be converted to an float
// Returns a pair containing: First = success code (bool)
//  Second = the converted float, 0.0 is supplied if the conversion fails
TRetFloatPair stringToFloat(const std::string passedString)
{
	TSuccess ret{ false };
	float convFloat{ 0.0 };

	try { // tries to convert string to a float
		convFloat = std::stof(passedString);
		ret = true;
	}
	catch (const std::invalid_argument& err) {
		std::cerr << "Invalid argument: " << err.what() << std::endl;
	}
	catch (const std::out_of_range& err) {
		std::cerr << "Out of range: " << err.what() << std::endl;
	}

	TRetFloatPair retPair{ ret, convFloat };

	return retPair;
}

// Takes a string and checks if it can be converted to an int
// Returns a pair containing: First = success code (bool)
//  Second = the converted int, 0 is supplied if the conversion fails
TRetIntPair stringToInt(const std::string passedString)
{
	TSuccess ret{ false };
	int convInt{ 0 };

	try { // tries to convert string to an int
		convInt = std::stoi(passedString);
		ret = true;
	}
	catch (const std::invalid_argument& err) {
		std::cerr << "Invalid argument: " << err.what() << std::endl;
	}
	catch (const std::out_of_range& err) {
		std::cerr << "Out of range: " << err.what() << std::endl;
	}

	TRetIntPair retPair{ ret, convInt };

	return retPair;
}

// Removes whitespace from a std::string
// Takes a string to remove whitespace from and returns a string with whitespace removed

std::string removeWhitespace(std::string passedString)
{
	// Remove whitespace using erase-remove idiom and std::isspace
	passedString.erase(std::remove_if(passedString.begin(), passedString.end(), ::isspace),
		passedString.end());

	return passedString;
}

// Takes a string and returns it all lowercase

std::string lowerCase(std::string passedString)
{
	// Convert the string to lowercase using std::for_each and std::tolower
	std::for_each(passedString.begin(), passedString.end(), [](char& c) { c = std::tolower(c); });

	return passedString;
}


} //nsMyTools
