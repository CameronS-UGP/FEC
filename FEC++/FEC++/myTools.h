#ifndef MYTOOLS_H_
#define MYTOOLS_H_

namespace nsMyTools
{
using TSuccess = bool;
using TRetFloatPair = std::pair<TSuccess, float>;
using TRetIntPair = std::pair<TSuccess, int>;
using TRetStrPair = std::pair<TSuccess, std::string>;

TRetFloatPair stringToFloat(const std::string passedString);
TRetIntPair stringToInt(const std::string passedString);

std::string removeWhitespace(std::string passedString);
std::string lowerCase(std::string passedString);

// Global variables
extern char POUND_SIGN; // to contain the 156 ASCII value for '£'

}


#endif // !MYTOOLS_H_
