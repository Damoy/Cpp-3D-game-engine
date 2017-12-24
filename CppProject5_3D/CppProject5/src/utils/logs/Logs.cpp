#include <iostream>
#include "Logs.h"

unsigned long Logs::logsCount = 0L;
const char* Logs::HEADER = "[Logs:";
const char* Logs::EOF_HEADER = "]";

void Logs::print(const char* str, bool sflush, bool eflush) {
	if(sflush) incLogsCount();

	if(sflush)
		printHeader();

	std::cout << str;

	if (eflush)
		flush();
}

void Logs::print(const char* str, bool eflush){
	print(str, true, eflush);
}

void Logs::print(const char* str) {
	print(str, true, true);
}

void Logs::aprint(const char* str) {
	print(str, false, false);
}

void Logs::println(const char* str, bool sflush, bool eflush) {
	print(str, sflush, eflush);
	ln();
}

void Logs::println(const char* str, bool eflush){
	println(str, true, eflush);
}

void Logs::println(const char* str) {
	println(str, true, true);
}

void Logs::println(bool sflush, bool eflush) {
	incLogsCount();

	if (sflush)
		printHeader();

	if (eflush)
		flush();

	ln();
}

void Logs::println(bool eflush){
	println(false, eflush);
}

void Logs::println() {
	println(false, false);
}

void Logs::flush() {
	eoflush();
}

void Logs::eoflush() {
	printEOFHeader();
}

void Logs::ln() {
	std::cout << std::endl;
}

void Logs::printHeader() {
	// tool class
	std::string* time = CurrentTime::get();
	std::cout << HEADER << logsCount << " | " << *time << " | ";
	delete time;
}

void Logs::printEOFHeader() {
	std::cout << EOF_HEADER;
}

void Logs::incLogsCount() {
	if (logsCount + 1 >= LONG_MAX) {
		logsCount = 0;
	}
	logsCount++;
}