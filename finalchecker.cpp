#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <sstream>

/*
*@Authors: Illan Gibson, Nicole Train, Robert Beer, Sky Gurnett
*@Version: 1.3
*@date: March 11, 2024
*@note: This program was built in part,specifically with the function titled correctIndentation
*		with the assistance of generative AI, specifically Copilot by Microsoft; https://copilot.microsoft.com
*		accessed on March 11, 2024. This was due to technical difficulties with the orignal implementation
*		that had a great deal of difficulty with integration.
*/

/*
*Functions
*/



/*@function; checkIfThere
* @param; std::string str
* @param; std::string token
* @returns; bool
* @description; A function that checks for the sub string token in str. returns true
*				if the sub string is found, false otherwise.
*/

bool checkIfThere(std::string &(str), std::string token){
	size_t found = str.find(token);
	if(found != std::string::npos){
		return true;
	}
	return false;
}

/*@function; getArguments
* @param; std::string str
* @param; size_t pos1
* @param; size_t pos2
* @returns; std::string args
* @description; A function that takes as arguments a string str, a size_t position1 (pos1)
*				and a size_t position2 (pos2). The function copies the string held between
*				the two positions, stores the string in std::string args and returns args.
*/
std::string getArguments(std::string str, size_t pos1, size_t pos2){
	std::string args = "";
	for(int i = pos1 + 1; i < pos2; i++){
		args = args + str[i];
	}
	return args;
}

/*@function; checkArguments
* @param; std::string args
* @return; std::string newArgs
* @description; A function that takes in a string args and checks
*				if there is anywhitespace without a preceeding ','
*				if so the append a ',' to newArgs, otherwise append
*				args[i] to newArgs and return newArgs.
*/
std::string checkArguments(std::string args){
	std::string newArgs = "";
	for(int i = 0; i < args.length(); i++){
		if(args[i] == ' ' && args[i - 1] != ','){
			newArgs = newArgs + ",";
		}
		newArgs = newArgs + args[i];
	}
	return newArgs;
}

/*@function; headerChecker
* @param; std::string str
* @returns; std::string newString
* @description; a function that takes in a string str, and iterates through
*				each word to see if the passed in string is a valid function
*				header in python. if the keyword "def" does not appear, then
*				then we return the original string with no modifications.
*				If we do find "def" we then search for all relevant tokens
*				"(", ")", and ":". If one does not exist we correct the issue
*				and return the modified string as newString. If all are present
*				we check if there are arguments to pass in and if they have the proper
*				indentation. If no arguments have been passed in we return the original
*				string as there are no corrections to be made, otherwise we correct
*				the arguments and return the newString with the corrections.
*/
std::string headerChecker(std::string &(str)){
	std::string newString = "";//the corrected string
	std::string arguments = "";//a substring holding any arguments in function header
	std::string correctedArgs = "";
	//bools for if we have found what is needed for a function header
	bool def = false;
	bool colon = false;
	bool openP = false;
	bool closedP = false;
	
	//check if "def" exists
	def = checkIfThere(str, std::string("def"));
	if(!def){
		return str;
	}
	//check if "(" exists
	openP = checkIfThere(str, std::string("("));
	if(!openP){
		for(int i = 0; i < str.length(); i++){
			if(str[i] == ')'){
				newString = newString + "(";
			}
			newString = newString + str[i];
		}
		return newString;
	}
	//check if ")" exists
	closedP = checkIfThere(str, std::string(")"));
	if(!closedP){
		for(int i = 0; i < str.length(); i++){
			if(str[i] == ':'){
				newString = newString + ")";
			}
			newString = newString + str[i];
		}
		return newString;
	}
	//check if ":" exists
	colon = checkIfThere(str, std::string(":"));
	if(!colon){
		for(int i = 0; i < str.length(); i++){
			newString = newString + str[i];
		}
		return newString + ":";
	}
	
	//if we make it to this point check if arguments is valid and correct if not
	arguments = getArguments(str, str.find("("), str.find(")"));
	if(arguments == ""){
		return str;
	}else{
		correctedArgs = checkArguments(arguments);
		for(int i = 0; i < str.length(); i ++){
			if(str[i] == '('){
				newString = newString + str[i] + correctedArgs + "):";
				break;
			}
			newString = newString + str[i];
		}
	}
	
	return newString;
}


/*@function; correctIndentation
* @param; const std::string& line
* @param; int indentSpaces
* @returns; std::string correctedLine
* @description; A function that takes a const std::string& line, and int indentSpaces
*				as input and returns a std::string correctedLine. The returned string
*				is built character by character by iterating through line and adjusting
*				the leading spaces to the desired length based on indentSpaces.
* @specialNote; This function was built in large part with the help of the 
*				Copilot AI by microsoft studios at https://copilot.microsoft.com/
*				this was due to difficulties with the original code written that 
*				could not be overcome. Copilot was accessed and consulted on March 11, 2024.
*/

std::string correctIndentation(const std::string& line, int indentSpaces) {
	
    std::string correctedLine;
    int currentIndent = 0;

    for (char c : line) {
        if (c == ' ' || c == '\t') {
            correctedLine += c;
            currentIndent++;
            if (currentIndent > indentSpaces) {
                // Remove excess spaces or tabs
                correctedLine.pop_back();
                currentIndent--;
            }
        } else {
            correctedLine += c;
            currentIndent = 0;
        }
    }

    return correctedLine;
}

int main(){
	int currIndents = 0;
	std::string token;
	std::vector<std::string> tokens;
	std::cout << "Name of file?" << std::endl;
	std::string fileName;
	std::cin >> fileName;
	std::ifstream file(fileName);
	std::vector<std::string> lines;
	std::string currentLine = "";
	std::ofstream outputFile("final_output.txt", std::ofstream::trunc);
	
	
	
	
	if(!file){
		std::cerr << "File not Found" << std::endl;
	}
	
	while(std::getline(file, currentLine)){
		if(currentLine == ""){
			continue;
		}
		lines.push_back(currentLine);
		std::cout << currentLine << std::endl;
	}
	file.close();
	
	outputFile << "Original file:" << std::endl << std::endl;
	
	for(int i = 0; i < lines.size(); i++){
		outputFile << lines[i] << std::endl;
		//lines[i] = headerChecker(lines[i]);
		//outputFile << lines[i] << std::endl;
	}
	
	
	bool firstLine = false;//flag for first line after colon
	int spaces = 0;//number of leading spaces
	for(int i = 0; i < lines.size(); i++){
		//if def is found, set currIndents to 4 and ensure function
		//header has zero leading indents.
		if(lines[i].find("def") != std::string::npos){
			lines[i] = headerChecker(lines[i]);
			lines[i] = correctIndentation(lines[i], currIndents);
			currIndents += 4;
			firstLine = true;
			continue;
		}else if(lines[i].find(":") != std::string::npos){//if def not found check if ":" exists in the line
			lines[i] = correctIndentation(lines[i], currIndents);//correct any indentation mistakes
			currIndents += 4;//update the current number of indents needed
			firstLine = true;//set flag to ensure first line after a ":" is properly indented
			continue;
		}
		//check if flag is set and correct any indent mistakes in the block
		if(firstLine){
			lines[i] = correctIndentation(lines[i], currIndents);
			firstLine = false;//set flag to false to ensure we can reduce the number of indents needed
		}
		else{
			std::string temp = lines[i];//temporary storage for the current line
			for(int i = 0; temp[i] == ' '; i++){
				spaces++;//check how many leading spaces exist
			}
			if(spaces > currIndents){
				lines[i] = correctIndentation(lines[i], currIndents);
			}
			//if no leading spaces set needed indents to 0
			//if(spaces == 0){
				//currIndents = 0;
			//}
			else{
				currIndents = spaces;//else reduce the number of needed indents by number of leading spaces
			}
		}
		
	}
	
	
	
	outputFile << std::endl << "corrected file:" << std::endl << std::endl;

	for(int i = 0; i < lines.size(); i++){
		outputFile << lines[i] << std::endl;
	}

	for(auto line : lines){
		std::cout << line << std::endl;
	}
	
	//outputFile.close();
	
	file.open(fileName);
	// Number of Python print() function calls in the provided Python file
    int printCount = 0;
    // Indicates whether currently processing tokens that are within a Python string, including multiline strings
    bool inPythonString = false;

    while (std::getline(file, token)) {
        // Remove (ignore) comments
        std::stringstream ss(token.substr(0, token.find('#')));

        // Tokenize the string using space and parentheses '(' as delimiters
        // Note: carriage return, \n, is already delimited by getline()
        while (std::getline(ss, token, ' ')) {
            std::stringstream ss1(token);

            while (std::getline(ss1, token, '(')) {
                tokens.push_back(token);
            }
        }
    }

    // Count the number of Python print() function calls
    for (std::string t : tokens) {
        // Ignore any print keywords in Python strings; includes multiline strings
        if (t.find("\"") != std::string::npos)
            inPythonString = !inPythonString;

        if (inPythonString)
            continue;

        if (t == "print")
            printCount++;
    }

    // Print the tokens
    for (const auto& t : tokens) {
        std::cout << t << std::endl;
    }
	//print the number of times print() was used
	std::cout << "# of times print() was used: " + printCount << std::endl;
	outputFile << "Number of times print() was used: " << printCount << std::endl;
	//close output file stream.
	outputFile.close();
	
	return 0;
}
