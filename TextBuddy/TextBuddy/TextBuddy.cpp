#include "TextBuddy.h"
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

static const string EMPTY_MESSAGE = "%s is empty";
static const string CLEAR_MESSAGE = "all content deleted from %s";
static const string WELCOME_MESSAGE = "Welcome to TextBuddy. %s is ready for use";
static const string INVALID_FORMAT_MESSAGE = "invalid command format";
static const string NOT_FOUND_MESSAGE = "word not found in %s";
static const string ADDED_MESSAGE = "added to %s: \"%s\"";
static const string DELETED_MESSAGE = "deleted from %s: \"%s\"";
static const string SORTED_MESSAGE = "all content in %s are sorted alphabetically";
static const string WRONG_IMPLEMENTATION_MESSAGE = "ERROR: Please input textbuddy.exe <filename>.txt";
char buffer[200];
vector<string> vectorFile;
vector<string> matchedLines;

int main(int argc, char* argv[]){
	string fileName;

	if (argc != 2) { 
		cout<<WRONG_IMPLEMENTATION_MESSAGE<<endl; 
		exit(0); 
	} 

	fileName = argv[1]; 
	sprintf_s(buffer, WELCOME_MESSAGE.c_str(), fileName.c_str()); 
	cout<< buffer<<endl;  

	while (true) {
		string userCommand; 
		cout << "command:"; 
		getline(cin, userCommand); 
		cout<< TextBuddy::executeUserCommand(fileName, userCommand)<<endl; 
	}

	return 0;
}

//Takes into command and passes it to the appropriate operation.
string TextBuddy::executeUserCommand(string fileName, string userCommand) {
	CommandType commandType;
	string content;

	int endPosition;
	endPosition = userCommand.find_first_of(" ");
	commandType = determineCommandType( userCommand.substr(0, endPosition));

	int startPosition;
	startPosition = userCommand.find_first_of(" ")+1;
	content= userCommand.substr(startPosition);
	
	switch (commandType)
	{
		case ADD_LINE:
			return addLine(fileName, content);
		case CLEAR_ALL:
			return clear(fileName);
		case SORT:
			return sortAlphabetically(fileName);
		case DISPLAY_ALL:
			return display(fileName);
		case DELETE_LINE:
			return deleteLine(fileName, content);
		case SEARCH:
			return searchWord(fileName, content);
		case EXIT:
			exit(0);
		case INVALID:
			sprintf_s(buffer, INVALID_FORMAT_MESSAGE.c_str());
		    return buffer;
		default:
			break;
	}
}

TextBuddy::CommandType TextBuddy::determineCommandType(string command) {
	if (command == "add"){
		return ADD_LINE;
	}
	else if (command == "delete") {
		return DELETE_LINE;
	}
	else if (command == "display") {
		return DISPLAY_ALL;
	}
	else if (command == "clear") {
		return CLEAR_ALL;
	}
	else if (command == "sort"){
		return SORT;
	}
	else if (command == "search"){
		return SEARCH;
	}
	else if (command == "exit") {
		return EXIT;
	}
	return INVALID;
}

//Display all the lines in the file.
string TextBuddy::display(string fileName){
	ifstream f;
	f.open(fileName);
	string line;
	int numberOfLines = 0;

	while(getline(f, line)){
		numberOfLines++;
		cout << numberOfLines << ". " << line << endl;
		
	}

	if(numberOfLines == 0){
		sprintf_s(buffer, EMPTY_MESSAGE.c_str(), fileName.c_str());
		return buffer;
	}

	f.close();
	return"";
}

//Clear all the lines in the file.
string TextBuddy::clear(string fileName){
	ifstream f;
	f.open("temp.txt");
	f.close();
	remove(fileName.c_str());
	rename("temp.txt", fileName.c_str());
	sprintf_s(buffer, CLEAR_MESSAGE.c_str(), fileName.c_str());
    return buffer;
}

//Add new lines to the file
string TextBuddy::addLine(string fileName, string content){
	ofstream f;
	f.open(fileName, ios::app);
	f << content <<endl;
	f.close();    
	sprintf_s(buffer, ADDED_MESSAGE.c_str(), fileName.c_str(), content.c_str());
	return buffer;
}

//Delete assigned line from the file.
string TextBuddy::deleteLine(string fileName, string content){
	int lineNumber = stoi(content);
	
	ifstream originalFile;
	originalFile.open(fileName);
	ofstream editedFile;
	editedFile.open("temp.txt");
	
	string line;
	string deletedLine;
	int TCount = 1;
	
	while(getline(originalFile, line)){
		if (TCount == lineNumber){
			deletedLine = line;
		}
		else{
			editedFile << line << endl;
		}
		TCount++;
	}
	
	originalFile.close();
	editedFile.close();
	
	remove(fileName.c_str());
	rename("temp.txt", fileName.c_str());
	
	sprintf_s(buffer, DELETED_MESSAGE.c_str(), fileName.c_str(), deletedLine.c_str());
    return buffer;
}

//Search for the given word in all the lines and print out the lines that contain the word.
string TextBuddy::searchWord(string fileName, string target){
	TextBuddy::fileToVector(fileName);
	bool isMatched = false;
	for (int index = 0; index < vectorFile.size(); index++ ) {
		if( vectorFile[index].find(target) != string::npos) {
			isMatched = true;
			cout << "Word found in: " << vectorFile[index] << endl;
			matchedLines.push_back(vectorFile[index]);
			}
		}

	if(!isMatched){
		return NOT_FOUND_MESSAGE;
	}
	else{
	    return "";
	}
}
/*Store the lines of file into a vector, sort the vector alphabetically 
and then rewrite the sorted vector into the file.*/
string TextBuddy::sortAlphabetically(string fileName){
	TextBuddy::fileToVector(fileName);
	sort(vectorFile.begin(), vectorFile.end());
	TextBuddy::vectorToFile(fileName);
	sprintf_s(buffer, SORTED_MESSAGE.c_str(), fileName.c_str());
	return buffer;
}

void TextBuddy::fileToVector(string fileName){
	ifstream f;
	string content;
	f.open(fileName);
	while (getline(f, content)) {
		vectorFile.push_back(content);
	}

	f.close();
	return;
}

void TextBuddy::vectorToFile(string filename) {
	ofstream f;
	f.open(filename);
	f.close();
	
	for (vector<string>::iterator iter = vectorFile.begin();
		iter != vectorFile.end(); iter++) {
		f.open(filename, ios::app);
		f << *iter << endl;
		f.close();
	}

	return;
}
