#pragma once
#include <ctime>
#include <iostream>
#include <string>

/*
	Class to get the current time.
*/
class CurrentTime {
private:
	CurrentTime();

public:
	// Get the current date
	static std::string* getDate(){
		time_t t = time(0);
		struct tm* now = localtime(&t);

		std::string* strTime = new std::string();

		std::string tmp = std::to_string(now->tm_year + 1900) + "y ";
		std::string tmp2 = std::to_string(now->tm_mon + 1) + "m ";
		std::string tmp3 = std::to_string(now->tm_mday) + "d";

		strTime->append(tmp);
		strTime->append(tmp2);
		strTime->append(tmp3);

		return strTime;
	}

	// Get the current time
	static std::string* get() {
		time_t t = time(0);
		struct tm* now = localtime(&t);

		std::string* strTime = new std::string();

		std::string tmp = std::to_string(now->tm_hour) + "h ";
		std::string tmp2 = std::to_string(now->tm_min) + "m ";
		std::string tmp3 = std::to_string(now->tm_sec) + "s ";

		strTime->append(tmp);
		strTime->append(tmp2);
		strTime->append(tmp3);

		return strTime;
	}
};