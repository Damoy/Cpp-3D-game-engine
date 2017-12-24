#pragma once

#include <iostream>
#include "utils\time\CurrentTime.h"

/*
	A sample Logs engine.
	Allows pretty timed prints and classic prints.
*/
class Logs{
public:
	// Prints
	// sflush for Logs header, eflush for Log entry end print
	static void print(const char* str, bool sflush, bool eflush);
	static void print(const char* str, bool flush);
	static void print(const char* str);

	// a Logs-independent print
	static void aprint(const char* str);

	static void println(const char* str, bool sflush, bool eflush);
	static void println(const char* str, bool flush);
	static void println(const char* str);

	static void println(bool slush, bool eflush);
	static void println(bool flush);
	static void println();

	static void eoflush();

	// More classics prints
	template<typename T>
	static void printG(T e) {
		std::cout << e;
	}

	template<typename T>
	static void printlnG(T e) {
		printG<T>(e);
		std::cout << std::endl;
	}

private:
	static unsigned long logsCount;
	const static char* HEADER;
	const static char* EOF_HEADER;

	Logs();
	// newline
	static void ln();
	// flushes to console
	static void flush();
	// logs count
	static void incLogsCount();
	// print the logs header
	static void printHeader();
	// prints the end of log
	static void printEOFHeader();
};

