#pragma once
#include"lexical.h"
#include<iostream>

extern Lexical lex;

typedef pair<string, string> partOfAns; //The first is variable,the second is answer
typedef vector<partOfAns> oneAns;  //One of the answers

struct Fact  //To save a fact and all the relation have to do with this fact.
{
	string name;
	vector<string> relation;
};

struct Rule
{
	string name;  //The name of a rule.
	int numOfVariable;  //The number of variables.
	vector<string> arguements;  //The arguements of a rule.
	vector<Fact> def;  //The define of the rule.
};

class Grammar
{
public:
	vector<Fact> allFacts;  //To save all the facts.
	vector<Rule> allRules;  //To save all the rules.

	vector<ErrorAndLine> allErrors;  //To save all the error existed.
	vector<oneAns> allAns; //To save the answer when consult the fact according the rule.

	void handleFact();  //To analysis the facts.
	void handleRule();  //To analysis the rules.
	void checkError();  //To check if some lexical errors exist and put the errors into "allErrors".
	bool judgeFact(Fact tmpFact);  //To judge a fact is true or not.
	void consultFact(string cmd);  //To find the answer of a fact.
	void consultRule(string cmd);  //To consult a rule.
	bool conRule0(Rule tmprule, Fact tmpfact);  //To consult a rule without variable.
	bool conRule1(Rule tmprule, Fact tmpfact);  //To consult a rule with one variable.
	bool conRule2(Rule tmprule, Fact tmpfact);  //To consult a rule with two variable.
	vector<string> findTheAns(Fact tmpFact, string anotherVariable);
	bool run();  //To carry out functions.
};