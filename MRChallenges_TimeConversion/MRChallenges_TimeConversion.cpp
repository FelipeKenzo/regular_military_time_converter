#include "pch.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <regex>
#include <algorithm>

std::string regexSearch(std::string str, std::regex reg);
bool isDumbTime(std::string input);
std::string preProcessInputString(std::string input);
int getHours(std::string str);
int getMinutes(std::string str);
std::string getMinutesString(std::string str);
bool isInputValid(std::string input);
void convertToNormal(std::string input, std::string timeString, std::string* convertedTimeString);
void convertToDumb(std::string timeString, std::string* convertedTimeString);

int main()
{
	std::cout << "===Time converter!===\n";
	while (1) {
		std::cout << "Input: ";

		std::string input;
		std::getline(std::cin, input);

		std::string timeString = preProcessInputString(input);
		std::string convertedTimeString = "";
		
		if (isInputValid(input)) {
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

std::string preProcessInputString(std::string input)
{
	std::regex time("(\\d?\\s*\\d\\s*:\\s*\\d\\s*\\d)");
	std::string preProcessedString = regexSearch(input, time);

	preProcessedString.erase(std::remove(preProcessedString.begin(), preProcessedString.end(), ' '),
		preProcessedString.end());

	return preProcessedString;
}

int getHours(std::string str)
{
	return stoi(str.substr(0, str.find(":")));
}

int getMinutes(std::string str)
{
	return stoi(str.substr(str.find(":") + 1, str.length()));
}

std::string getMinutesString(std::string str)
{
	return str.substr(str.find(":"), str.length());
}

bool isInputValid(std::string input)
{
	std::string preProcessedString = preProcessInputString(input);

	if (preProcessedString == "")
		return false;

	int minutes = getMinutes(preProcessedString);
	if (minutes > 59)
		return false;

	int hours = getHours(preProcessedString);

	if (isDumbTime(input)) {
		if (hours > 12)
			return false;
	}
	else {
		if (hours > 24)
			return false;
	}

	return true;
}

void convertToNormal(std::string input, std::string timeString, std::string* convertedTimeString) {
	int hours = getHours(timeString);
	std::string minutes = getMinutesString(timeString);


	if (hours > 12 || hours < 1) {
		std::cout << "Please, enter a valid input.\n";
		return;
	}

	std::regex am("[Aa]");
	if (regexSearch(input, am) != "") {
		if (hours == 12)
			*convertedTimeString = "00" + minutes;
		else if (hours < 10)
			*convertedTimeString = "0" + std::to_string(hours) + minutes;
		else
			*convertedTimeString = std::to_string(hours) + minutes;
	}
	else
		if (hours == 12)
			*convertedTimeString = "12" + minutes;
		else
			*convertedTimeString = std::to_string(hours + 12) + minutes;
}

void convertToDumb(std::string timeString, std::string* convertedTimeString) {
	int hours = getHours(timeString);
	std::string minutes = getMinutesString(timeString);

	if (hours > 24) {
		std::cout << "please, enter a valid input.\n";
		return;
	}
	else if (hours == 0 || hours == 24)
		*convertedTimeString = "12" + minutes + " a.m.";
	else if (hours < 12)
		*convertedTimeString = std::to_string(hours) + minutes + " a.m.";
	else if (hours == 12)
		*convertedTimeString = "12" + minutes + " p.m.";
	else
		*convertedTimeString = std::to_string(hours - 12) + minutes + " p.m.";
}