#pragma once
#include"lexical.h"
#include<iostream>

typedef vector<string> Relation; //To save the arguements that have the same predicate.
struct Fact  //To save a fact and all the relation have to do with this fact.
{
	string name;
	vector<Relation> allTheRelation;
};

/*typedef vector<string, vector<string>> subRule;  
/*The predicates that constitude a rule.
The first element is the name of the predicate,the second element is the arguements related.*/

struct Rule
{
	string name;  //The name of a rule.
	vector<string> arguements;  //The arguements of a rule.
	vector<Fact> def;  //The define of the rule.
};

class Grammar
{
public:
	vector<Fact> allFacts;  //To save all the facts.
	vector<Rule> allRules;  //To save all the rules.

	vector<ErrorAndLine> allErrors;  //To save all the error existed.
	vector<string> ans; //To save the answer when consult the fact according the rule.

	void handle();  //To analysis the facts.
	void checkError();  //To check if some lexical errors exist and put the errors into "allErrors".
	void consultFact();  //To find the answer of a fact.
	void run();  //To carry out functions.
};