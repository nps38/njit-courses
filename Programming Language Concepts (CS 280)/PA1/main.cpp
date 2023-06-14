#include <iostream>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>
#include "lex.h"

using namespace std;

int main(int argc, char *argv[]) {
	int lnnum;
	int tokenCount = 0;
	LexItem item;
	
    if(argc == 1){
        cout << "NO SPECIFIED INPUT FILE NAME." << endl;
        exit(1);
    }
    
    bool vflag = false;
	bool iconstflag = false;
	bool rconstflag = false;
	bool sconstflag = false;
	bool identflag = false;
    
	for(int i=1; i<argc; i++) {
		string flag(argv[i]);
		if( flag == "-v" )
			vflag = true;
		else if( flag == "-iconst" )
			iconstflag = true;
		else if( flag == "-rconst" )
			rconstflag = true;
		else if( flag == "-sconst" )
			sconstflag = true;
		else if( flag == "-ident" )
			identflag = true;
		else if( flag[0] == '-' ) {
			cerr << "UNRECOGNIZED FLAG " << flag << endl;
			exit(1);
		}
        else if (i == 2 && flag[0] != '-'){
            cout << "ONLY ONE FILE NAME ALLOWED." << endl; 
            exit(1);
        }
	}
    
    string file(argv[1]);
    ifstream infile(file);
    
    if(!infile.is_open()){
        cout << "CANNOT OPEN the File " << file << endl;
        exit(1);
    }
    
    vector<LexItem> alltokens;
	vector<string> idents;
	vector<int> iconsts;
	vector<double> rconsts;
	vector<string> sconsts;
	
	while(true) {
        item = getNextToken(infile, lnnum);
        
        if (item.GetToken() == ERR){
            cout << "Error in line: " << lnnum << "(" << item.GetLexeme() << ")" << endl;
            exit(1);
        }
        if (item.GetToken() == DONE){
            break;
        }
        if (item.GetToken() == IDENT){
            item = id_or_kw(item.GetLexeme(), item.GetLinenum());
        }
        
        if (vflag) {
            alltokens.push_back(item);
            cout << item << endl;
        }
        
        if (item.GetToken() == IDENT){
            idents.push_back(item.GetLexeme());
        }
        
        if (item.GetToken() == ICONST){
            iconsts.push_back(stoi(item.GetLexeme()));
        }
        
        if (item.GetToken() == RCONST){
            rconsts.push_back(std::stod(item.GetLexeme()));
        }
        
        if (item.GetToken() == SCONST){
            sconsts.push_back(item.GetLexeme());
        }
        
        ++tokenCount;
	}

    if (lnnum == 0){
        cout <<"Lines: 0" << endl;
        exit(1);
    }
    cout << "Lines: " << lnnum << endl;
    cout << "Tokens: " << tokenCount << endl;
    
    if (iconstflag){
        cout << "INTEGERS:" << endl;
        sort(iconsts.begin(), iconsts.end());
        for (int i = 0; i < iconsts.size(); i++){
            cout << iconsts[i] << endl;
        }
    }
    
    if (identflag){
        cout << "IDENTIFIERS:" << endl;
        sort(idents.begin(), idents.end());
        for (int i = 0; i < idents.size(); i++){
            if ( i == 0 ) { cout << idents[i]; }
            cout << ", " << idents[i];
        }
        cout << endl;
    }
    
    if (rconstflag){
        cout << "REALS:" << endl;
        int i;
        sort(rconsts.begin(), rconsts.end());
        cout << rconsts[0] << endl;
        for (i = 1; i < rconsts.size(); i++){
            if (i != 0 && rconsts[i] != rconsts[i-1])
                cout << rconsts[i] << endl;
        }
    }
    
    if (sconstflag){
        cout << "STRINGS:" << endl;
        sort(sconsts.begin(), sconsts.end());
        for (int i = 0; i < sconsts.size(); i++){
            if ( i == 0 ) { 
                cout << sconsts[i]; 
            }
            if (i != sconsts.size()-1 && sconsts[i] != sconsts[i+1])
                cout << ", " << sconsts[i];
        }
        cout << endl;
    }
    
    
}

ostream& operator<<(ostream& out, const LexItem& tok){
    string tokenStrings[34] = {"PROGRAM", "WRITELN", "INTEGER", "BEGIN", "END", "IF", "REAL", "STRING", "VAR", "ELSE",
                        "FOR", "THEN", "DO", "TO", "DOWNTO", "IDENT", "ICONST", "RCONST", "SCONST", "PLUS", "MINUS",
                        "MULT", "DIV", "ASSOP", "LPAREN", "RPAREN", "COMMA", "EQUAL", "GTHAN", "LTHAN", "SEMICOL",
                        "COLON", "ERR", "DONE"};
    if (tokenStrings[tok.GetToken()] == "IDENT" || tokenStrings[tok.GetToken()] == "ICONST" || tokenStrings[tok.GetToken()] == "RCONST" || tokenStrings[tok.GetToken()] == "SCONST"){
    	cout << tokenStrings[tok.GetToken()] << " (" << tok.GetLexeme() << ")";
    	return out;
	}
	else {
		cout << tokenStrings[tok.GetToken()];
		return out;
	}
}
