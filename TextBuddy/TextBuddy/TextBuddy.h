//TextBuddy.h
#ifndef TEXTBUDDY_H
#define TEXTBUDDY_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TextBuddy{
private:
	enum CommandType { ADD_LINE, DISPLAY_ALL, DELETE_LINE, CLEAR_ALL, SORT, EXIT, SEARCH, INVALID};

public:

	static CommandType determineCommandType(string command);
	static string display(string fileName);
	static string deleteLine(string fileName, string content);
	static string clear(string fileName);
	static string executeUserCommand(string fileName, string userCommand);
	static string addLine(string fileName, string content);
	static void fileToVector(string fileName);
	static void vectorToFile(string fileName);
	static string sortAlphabetically(string fileName);
	static string searchWord(string fileName, string word);
};

#endif


