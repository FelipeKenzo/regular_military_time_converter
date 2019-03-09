#include <iostream>
#include <stdexcept>
#include <string>
#include <regex>
#include <algorithm>

std::string regexSearch(std::string str, std::regex reg);
bool isDumbTime(std::string input);
std::string processInputString(std::string input);
int getHours(std::string str);
std::string getMinutes(std::string str);
void convertToNormal(std::string input, std::string timeString, std::string* convertedTimeString);
void convertToDumb(std::string timeString, std::string* convertedTimeString);

int main()
{
	std::cout << "===Time converter!===\n";
	while (1) {
		std::cout << "Input: ";

		std::string input;
		std::getline(std::cin, input);

		std::string timeString = processInputString(input);
		std::string convertedTimeString = "";
		
		if (timeString != "") {
			int hours = getHours(timeString);

			if (isDumbTime(input)) {
				convertToNormal(input, timeString, &convertedTimeString);
			}
			else {
				convertToDumb(timeString, &convertedTimeString);
			}

			if (convertedTimeString != "")
				std::cout << "Output: " << convertedTimeString << "\n";
		}
		else {
			std::cout << "Please, enter a valid input.\n";
		}

		std::cout << "\n";
	}
	return 0;
}

std::string regexSearch(std::string str, std::regex reg)
{
	std::smatch match;
	std::regex_search(str, match, reg);

	return match.str();
}

bool isDumbTime(std::string input)
{
	std::regex dumbTime("[AaPp]\\s*\\.?\\s*[Mm]\\.?");

	return regexSearch(input, dumbTime) != "";
}

std::string processInputString(std::string input)
{
	std::regex time("(\\d?\\s*\\d\\s*:\\s*\\d\\s*\\d)");
	std::string processedString = regexSearch(input, time);

	processedString.erase(std::remove(processedString.begin(), processedString.end(), ' '),
		processedString.end());

	return processedString;
}

int getHours(std::string str) {
	return stoi(str.substr(0, str.find(":")));
}

std::string getMinutes(std::string str) {
	return str.substr(str.find(":"), str.length());
}

void convertToNormal(std::string input, std::string timeString, std::string* convertedTimeString) {
	int hours = getHours(timeString);

	if (hours > 12 || hours < 1) {
		std::cout << "Please, enter a valid input.\n";
		return;
	}

	std::regex am("[Aa]");
	if (regexSearch(input, am) != "") {
		if (hours == 12)
			*convertedTimeString = "00" + getMinutes(timeString);
		else if (hours < 10)
			*convertedTimeString = "0" + std::to_string(hours) + getMinutes(timeString);
		else
			*convertedTimeString = std::to_string(hours) + getMinutes(timeString);
	}
	else
		if (hours == 12)
			*convertedTimeString = "12" + getMinutes(timeString);
		else
			*convertedTimeString = std::to_string(hours + 12) + getMinutes(timeString);
}

void convertToDumb(std::string timeString, std::string* convertedTimeString) {
	int hours = getHours(timeString);

	if (hours > 24) {
		std::cout << "please, enter a valid input.\n";
		return;
	}
	else if (hours == 0 || hours == 24)
		*convertedTimeString = "12" + getMinutes(timeString) + " a.m.";
	else if (hours < 12)
		*convertedTimeString = std::to_string(hours) + getMinutes(timeString) + " a.m.";
	else if (hours == 12)
		*convertedTimeString = "12" + getMinutes(timeString) + " p.m.";
	else
		*convertedTimeString = std::to_string(hours - 12) + getMinutes(timeString) + " p.m.";
}