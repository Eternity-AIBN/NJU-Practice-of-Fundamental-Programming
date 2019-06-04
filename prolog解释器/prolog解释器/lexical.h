#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<cctype>
using namespace std;

typedef pair<string, string> Token;  //The first element is morpheme,the second is type.
typedef pair<vector<Token>, bool> tokenLine;  //To save a line of token,the second is to judge if the line is a rule

typedef pair<int, vector<string>> ErrorAndLine; 
//To point out that a error(the seond element) exist in which line(the first element).

class Lexical
{
public:
	vector<tokenLine> tokenTable;  //To save all the tokens and their types.
	vector<ErrorAndLine> allErrors;  //To save all the error existed.

	bool readInfo(string fname);  //To read all the token from the .pl file to initialize the tokenTable(the first element).
	void handle();  //To remove the blank space and analysis the tokens and find their type.
	void checkError();  //To check if some lexical error exists and put the error into "allErrors" and show them.
	bool run(string fname);  //To carry out functions.
};