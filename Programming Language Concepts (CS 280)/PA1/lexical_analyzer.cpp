#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include "lex.h"
#include <cctype>
#include <map>
using std::map;
using namespace std;

map<string,Token> lexToToken() {
	map<string,Token> tokens;

	tokens.insert(pair<string, Token>("PROGRAM", PROGRAM));
	tokens.insert(pair<string, Token>("WRITELN", WRITELN));
	tokens.insert(pair<string, Token>("INTEGER", INTEGER));
	tokens.insert(pair<string, Token>("BEGIN", BEGIN));
	tokens.insert(pair<string, Token>("END", END));
	tokens.insert(pair<string, Token>("IF", IF));
	tokens.insert(pair<string, Token>("REAL", REAL));
	tokens.insert(pair<string, Token>("STRING", STRING));
	tokens.insert(pair<string, Token>("VAR", VAR));
	tokens.insert(pair<string, Token>("ELSE", ELSE));
	tokens.insert(pair<string, Token>("FOR", FOR));
	tokens.insert(pair<string, Token>("THEN", THEN));
	tokens.insert(pair<string, Token>("DO", DO));
	tokens.insert(pair<string, Token>("TO", TO));
	tokens.insert(pair<string, Token>("DOWNTO", DOWNTO));
	tokens.insert(pair<string, Token>("IDENT", IDENT));
	tokens.insert(pair<string, Token>("ICONST", ICONST));
	tokens.insert(pair<string, Token>("RCONST", RCONST));
	tokens.insert(pair<string, Token>("SCONST", SCONST));
	tokens.insert(pair<string, Token>("PLUS", PLUS));
	tokens.insert(pair<string, Token>("MINUS", MINUS));
	tokens.insert(pair<string, Token>("MULT", MULT));
	tokens.insert(pair<string, Token>("DIV", DIV));
	tokens.insert(pair<string, Token>("ASSOP", ASSOP));
	tokens.insert(pair<string, Token>("LPAREN", LPAREN));
	tokens.insert(pair<string, Token>("RPAREN", RPAREN));
	tokens.insert(pair<string, Token>("COMMA", COMMA));
	tokens.insert(pair<string, Token>("EQUAL", EQUAL));
	tokens.insert(pair<string, Token>("GTHAN", GTHAN));
	tokens.insert(pair<string, Token>("LTHAN", LTHAN));
	tokens.insert(pair<string, Token>("SEMICOL", SEMICOL));
	tokens.insert(pair<string, Token>("COLON", COLON));
	tokens.insert(pair<string, Token>("ERR", ERR));
	tokens.insert(pair<string, Token>("DONE", DONE));
	return tokens;
}


extern LexItem id_or_kw(const string& lexeme, int linenum){
    //string lextemp = toUpper(lexeme);
    //transform(lextemp.begin(), lextemp.end(), lextemp().begin(), ::toupper);
	map<string, Token> tokens = lexToToken();
    if (tokens.find(lexeme) != tokens.end())
    	return LexItem(tokens[lexeme], lexeme, linenum);
    return LexItem(IDENT, lexeme, linenum);
}

extern LexItem getNextToken(istream& in, int& linenum){
	enum TokState {START, INID, INSTRING, ININT, INREAL, INCOMMENT}
	lexstate = START;
	string lexeme = "";
	map<string, Token> tokens = lexToToken();
	char ch;
	while(in.get(ch)) {
		switch(lexstate) {
		case START:
			if(ch == '\n'){
				linenum++;
				break;
			}
			if(isspace(ch)){
				continue;
			}
			lexeme = "";
			lexeme += ch;
			if(isalpha(ch) || ch == '_') {
				lexstate = INID;
				continue;
			}
			else if (isdigit(ch)){
				//change later
				lexstate = ININT;
				continue;
			}
			else if (ch == '.'){
				lexstate = INREAL;
				continue;
			}
			else if (ch == '\''){
				lexstate = INSTRING;
				continue;
			}
			else if (ch == '(' && char(in.peek()) == '*'){
				lexstate = INCOMMENT;
				continue;
			}
			else if (ch == '+') {
				return LexItem (PLUS, "PLUS", linenum);
			}
			else if (ch == '-') {
				return LexItem (MINUS, "MINUS", linenum);
			}
			else if (ch == '*') {
				return LexItem (MULT, "MULT", linenum);
			}
			else if (ch == '/') {
				return LexItem (DIV, "DIV", linenum);
			}
			else if (ch == '(') {
				return LexItem (LPAREN, "LPAREN", linenum);
			}
			else if (ch == ')') {
				return LexItem (RPAREN, "RPAREN", linenum);
			}
			else if (ch == '=') {
				return LexItem (EQUAL, "EQUAL", linenum);
			}
			else if (ch == '>') {
				return LexItem (GTHAN, "GTHAN", linenum);
			}
			else if (ch == '<') {
				return LexItem (LTHAN, "LTHAN", linenum);
			}
			else if (ch == ';') {
				return LexItem (SEMICOL, "SEMICOL", linenum);
			}
			else if (ch == ',') {
				return LexItem (COMMA, "COMMA", linenum);
			}
			else if (ch == ':' && char(in.peek()) != '=' ) {
				return LexItem (LTHAN, "LTHAN", linenum);
			}
			else if (ch == ':' && char(in.peek() == '=')){
				in.get(ch);
				return LexItem(ASSOP, "ASSOP", linenum);
			}
			break;
		case INID:
		    if (!isalnum(ch) && ch != '_'){
				in.putback(ch);
				lexstate = START;
				return LexItem(IDENT, lexeme, linenum);
			}
			else {
				lexeme += ch;
				break;
			}
		case INSTRING:
			if (in.peek() == -1){
				return LexItem(ERR, lexeme, linenum);
			}
			else if (ch == '\'' && lexeme.size() != 1){
				lexstate = START;
				return LexItem(SCONST, lexeme, linenum);
			}
			lexeme += ch;
			break;
		case ININT:
			if (!isdigit(ch)){
				if (ch == '.'){
					lexeme += ch;
					lexstate = INREAL;
					continue;
				}	
				else{
					lexstate = START;
					return LexItem(ICONST, lexeme, linenum);
				}
			}
			else {
				lexeme += ch;
				break;
			}
			
		case INREAL:
			if (!isdigit(ch)){
				if (ch == '.' && lexeme.find('.') != std::string::npos)
					return LexItem(ERR, lexeme, linenum);
			    return LexItem(RCONST, lexeme, linenum);
			}
			lexeme += ch;
			break;
		case INCOMMENT:
			if (ch == '\n'){
				linenum++;
				break;
			}
			if (ch == ')' && lexeme.back() == '*'){
				lexeme = "";
				lexstate = START;
				break;
			}
		}
	}
	
	return LexItem(DONE, "", linenum);
}
