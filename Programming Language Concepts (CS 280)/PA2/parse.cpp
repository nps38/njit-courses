/* Definitions and some functions implementations
 * parse.cpp to be completed
 * Programming Assignment 2
 * Spring 2022
*/

#include "parse.h"


map<string, bool> defVar;
map<string, Token> SymTable;

namespace Parser {
	bool pushed_back = false;
	LexItem	pushed_token;

	static LexItem GetNextToken(istream& in, int& line) {
		if( pushed_back ) {
			pushed_back = false;
			return pushed_token;
		}
		return getNextToken(in, line);
	}

	static void PushBackToken(LexItem & t) {
		if( pushed_back ) {
			abort();
		}
		pushed_back = true;
		pushed_token = t;	
	}

}

static int error_count = 0;

int ErrCount()
{
    return error_count;
}

void ParseError(int line, string msg)
{
	++error_count;
	cout << line << ": " << msg << endl;
}

bool Prog(istream& in, int& line){
    //bool status;
    LexItem t = Parser::GetNextToken(in, line);
    if (t != PROGRAM){
		ParseError(line, "Missing PROGRAM.");
		return false;
	}
    
    t = Parser::GetNextToken(in,line);
    if (t != IDENT){
        ParseError(line, "Missing Program Name.");
        return false;
    }
    
    t = Parser::GetNextToken(in,line);
    if (t != SEMICOL){
        ParseError(line,"Missing SemiColon");
        return false;
        //Parser::PushBackToken(t);
    }
    
    bool db = DeclBlock(in, line);
    if (!db){
        ParseError(line, "Incorrect Declaration Section.");
        return false;
    }

    bool pb = ProgBody(in, line);
    if (!pb){
        ParseError(line, "Incorrect Program Body.");
        return false;
    }
    return true;   
}

bool DeclBlock(istream& in, int& line){
    LexItem t = Parser::GetNextToken(in,line);
    if (t!=VAR){
        ParseError(line, "Missing Variable");
        return false;
    }
    
    while (true){
        
        if (t == SEMICOL){
            t = Parser::GetNextToken(in,line);
            if (t == BEGIN){
                Parser::PushBackToken(t);
                break;
            }
            else{
                Parser::PushBackToken(t);
            }
        }
        
        bool ds = DeclStmt(in,line);
        if (!ds){
            ParseError(line, "Syntactic error in Declaration Block.");
            //Parser::PushBackToken(t);
            return false;
        }
        t = Parser::GetNextToken(in, line);
        if(t != SEMICOL) {
            ParseError(line, "Missing semicolon");
            return false;
        }
    }/*
        bool ds = DeclStmt(in,line);
        if (!ds){
            ParseError(line, "Syntactic error in Declaration Block.");
                //Parser::PushBackToken(t);
            return false;
        }
        t = Parser::GetNextToken(in, line);
        if(t != SEMICOL) {
            ParseError(line, "Missing semicolon");
            return false;
        }*/
    
    return true;
        
    /*
    bool dl = DeclStmt(in,line);
    if (dl){
        while(dl){
            t = Parser::GetNextToken(in,line);
            if (t !=SEMICOL){
                ParseError(line, "Missing SemiColon");
                return false;
            }
            else{
                Parser::GetNextToken(in,line);
            }
        }
        Parser::PushBackToken(t);
        return true;
    }
    else if(t.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << t.GetLexeme() << ")" << endl;
		return false;
	}
	else{
		Parser::PushBackToken(t);
		return true;
	}*/

}

bool DeclStmt(istream& in, int& line){
    LexItem t = Parser::GetNextToken(in,line);
    if (t!=IDENT){
        //"Missing identifier"
        //t.GetLexeme()
        ParseError(line, "b");
        return false;
    }
    if ((defVar.find(t.GetLexeme())) != defVar.end()){
        ParseError(line, "Variable Redefinition");
        return false;
    }
    else{
        defVar.insert({t.GetLexeme(), true});
    }
    t = Parser::GetNextToken(in,line);
    if (t == COMMA){
        while (t == COMMA) {
            t = Parser::GetNextToken(in,line);
            if (t != IDENT){
                ParseError(line,"Missing Identifier");
                return false;
            }
            if (t.GetToken() == ERR){
                ParseError(line, "Unrecognized Input Pattern");
                cout << "(" << t.GetLexeme() << ")" << endl;
                return false;
            }
            if ((defVar.find(t.GetLexeme())) != defVar.end()){
                ParseError(line, "Variable Redefinition");
                return false;
            }
            else{
                defVar.insert({t.GetLexeme(), true});
            }
            t = Parser::GetNextToken(in,line);
        }
        if (t == IDENT){
            ParseError(line, "Unrecognized Input Pattern");
		    cout << "(" << t.GetLexeme() << ")" << endl;
		    return false;
        }
	}
    else{
        
        Parser::PushBackToken(t);
    }/*
	else if(t.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << t.GetLexeme() << ")" << endl;
		return false;
	}
	else{
		Parser::PushBackToken(t);
		return true;
	}*/
    
    //t = Parser::GetNextToken(in,line);
    if (t != COLON){
        ParseError(line, "Missing Colon");
        return false;
    }
    /*
    t = Parser::GetNextToken(in,line);
    if( t != LPAREN ) {
		ParseError(line, "Missing Left Parenthesis");
		return false;
	}*/
    
    t = Parser::GetNextToken(in, line);
	if (t != INTEGER && t!= REAL && t!= STRING ) {
		ParseError(line,"Incorrect Declaration Type.");
        return false;
	}
    /*
    t = Parser::GetNextToken(in, line);
	if(t != RPAREN ) {
		ParseError(line, "Missing Right Parenthesis");
		return false;
	}*/
	return true;

}

bool ProgBody(istream& in, int& line){
    LexItem t = Parser::GetNextToken(in,line);
    
    if (t!=BEGIN){
        //"Missing Begin"
        ParseError(line, t.GetLexeme());
        return false;
    }
    //bool st = Stmt(in,line);
    /*
    if (Stmt(in,line)){
        t = Parser::GetNextToken(in,line);
        if (t != SEMICOL){
            ParseError(line,"Missing SemiColon after Statement");
            return false;
        }
        else{
            return true;
        }
    }
    else{
        t = Parser::GetNextToken(in,line);
        if (t!=END){
            ParseError(line,"Missing End");
            return false;
        }
        return true;
    }*/
    //t = Parser::GetNextToken(in,line);
    while (true){
        if (t == SEMICOL){
            t = Parser::GetNextToken(in,line);
            if (t == END){
                Parser::PushBackToken(t);
                break;
            }
            else{
                Parser::PushBackToken(t);
            }
        }
        
        bool st = Stmt(in,line);
        if (!st){
            //cout<<t.GetLexeme()<<endl;
            ParseError(line,"Syntactic error in Program Body.");
            return false;
        }
        t = Parser::GetNextToken(in,line);
        if (t!=SEMICOL){
            line -=1;
            ParseError(line,"Missing SemiColon in Statement");
            return false;
        }
    }
    t = Parser::GetNextToken(in,line);
    if (t!=END){
        ParseError(line,"Missing End");
        return false;
    }
    return true;
}

bool Stmt(istream& in, int& line) {
	bool status;
	//cout << "in ContrlStmt" << endl;
	LexItem t = Parser::GetNextToken(in, line);
	
	switch( t.GetToken() ) {

	case WRITELN:
		status = WriteLnStmt(in, line);
		//cout << "After WriteStmet status: " << (status? true:false) <<endl;
		break;

	case IF:
		status = IfStmt(in, line);
		break;

	case IDENT:
		Parser::PushBackToken(t);
        status = AssignStmt(in, line);
		
		break;
		
	case FOR:
		status = ForStmt(in, line);
		
		break;
		
		
	default:
		Parser::PushBackToken(t);
		return false;
	}

	return status;
}

bool WriteLnStmt(istream& in, int& line) {
	LexItem t;
	//cout << "in WriteStmt" << endl;
	
	t = Parser::GetNextToken(in, line);
	if( t != LPAREN ) {
		
		ParseError(line, "Missing Left Parethesis");
		return false;
	}
	
	bool ex = ExprList(in, line);
	
	if( !ex ) {
		ParseError(line, "Missing expression after WriteLn");
		return false;
	}
	
	t = Parser::GetNextToken(in, line);
	if(t != RPAREN ) {
		
		ParseError(line, "Missing Right Parenthesis");
		return false;
	}
	//Evaluate: print out the list of expressions values

	return ex;
}

bool IfStmt(istream& in, int& line){
    bool status;
    LexItem t = Parser::GetNextToken(in,line);
    
    if(t != LPAREN){
		
		ParseError(line, "Missing Left Parethesis");
		return false;
	}
	
	bool logexp = LogicExpr(in, line);
	
	if(!logexp){
		ParseError(line, "Missing expression after If");
		return false;
	}
	
	t = Parser::GetNextToken(in, line);
    //cout<<t.GetLexeme()<<endl;
	if(t != RPAREN){
		ParseError(line, "Missing Right Parenthesis");
		return false;
    }
    t = Parser::GetNextToken(in,line);
    if (t != THEN){
        ParseError(line, "Missing Then");
		return false;
    }
    
    bool st = Stmt(in,line);
    if(!st){
        ParseError(line,"Missing Statement");
        return false;
    }
    LexItem tok = Parser::GetNextToken(in, line);
	
	if (tok == ELSE) {
		//cout << "before calling ExprList" << endl;
		status = Stmt(in, line);
		//cout << "after calling ExprList" << endl;
	}
	else if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	else{
		Parser::PushBackToken(tok);
		return true;
	}
	return status;
}

bool ForStmt(istream& in, int& line){
    //LexItem t = Parser::GetNextToken(in,line);
    //Parser::PushBackToken(t);
    //cout<<t.GetLexeme()<<endl;
    bool vr = Var(in,line);
    if (!vr){
        ParseError(line,"Missing Variable.");
        return false;
    }
    LexItem t = Parser::GetNextToken(in,line);
    if (t!=ASSOP){
        ParseError(line,"Missing Assop.");
        return false;
    }
    t = Parser::GetNextToken(in,line);
    if (t!=ICONST){
        ParseError(line,"Missing Integer.");
        return false;
    }
    t = Parser::GetNextToken(in,line);
    if (t!=TO && t!=DOWNTO){
        ParseError(line,"Missing TO or DOWNTO.");
        return false;
    }
    t = Parser::GetNextToken(in,line);
    if (t!=ICONST){
        ParseError(line,"Missing ICONST.");
        return false;
    }
    t = Parser::GetNextToken(in,line);
    if (t!=DO){
        ParseError(line,"Missing DO");
        return false;
    }
    bool st1 = Stmt(in,line);
    return st1;
}
    /*
    if (t==FOR){
        bool vr = Var(in,line);
        if (!vr){
            //cout<<t.GetLexeme()<<endl;
            ParseError(line,"Missing Variable");
            return false;
        }
        else{
            return true;
        }
    }
    else if(t==ICONST){
        t = Parser::GetNextToken(in,line);
        if(t != LPAREN){
            ParseError(line, "Missing Left Parenthesis");
            return false;
        }
        t = Parser::GetNextToken(in,line);
        if(t != TO){
            ParseError(line, "Missing To");
            return false;
        }
        if (t != DOWNTO){
            ParseError(line, "Missing DownTo");
            return false;
        }
        t = Parser::GetNextToken(in, line);
        if(t != RPAREN){
            ParseError(line, "Missing Right Parenthesis");
            return false;
        }
        t = Parser::GetNextToken(in, line);
        if (t!=ICONST){
            ParseError(line,"Missing Integer");
            return false;
        }
        t = Parser::GetNextToken(in, line);
        if (t!=DO){
            ParseError(line,"Missing Do");
            return false;
        }
        bool st = Stmt(in,line);
        return st;
        
    }
    else{
        return false;
    }*/

/*
bool AssignStmt(istream& in, int& line){
    bool vr = Var(in,line);
    bool xp = Expr(in,line);
    if (vr || xp){
        return true;
    }
    else{
        ParseError(line, "Missing a variable or expression");
        return false;
    }
}*/
bool AssignStmt(istream& in, int& line){
    LexItem t = Parser::GetNextToken(in,line);
    Parser::PushBackToken(t);
    bool vr = Var(in,line);
    if (!vr){
        //cout<<t.GetLexeme()<<endl;
        ParseError(line,"Missing Variable");
        return false;
    }
    
    t = Parser::GetNextToken(in,line);
    if (t!=ASSOP){
        ParseError(line, "Missing Assignment Operator.");
        return false;
    }
    t = Parser::GetNextToken(in,line);
    if (t!=PLUS && t!=MINUS){
        Parser::PushBackToken(t);
    }
    bool xp = Expr(in,line);
    if (!xp){
        ParseError(line,"Missing Expression");
        return false;
    }

    return true;
}

//ExprList:= Expr {,Expr}
bool ExprList(istream& in, int& line) {
	bool status = false;
	//cout << "in ExprList and before calling Expr" << endl;
	status = Expr(in, line);
	if(!status){
		ParseError(line, "Missing Expression");
		return false;
	}
	
	LexItem tok = Parser::GetNextToken(in, line);
	
	if (tok == COMMA) {
		//cout << "before calling ExprList" << endl;
		status = ExprList(in, line);
		//cout << "after calling ExprList" << endl;
	}
	else if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	else{
		Parser::PushBackToken(tok);
		return true;
	}
	return status;
}

bool Expr(istream& in, int& line) {
    bool t1 = Term(in, line);
    LexItem tok;
    if( !t1 ) {
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    
    if(tok == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        return false;
    }
    /*
    if (tok != PLUS && tok != MINUS && tok != MULT && tok != DIV && tok != SEMICOL){
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }*/
    while ( tok == PLUS || tok == MINUS ) {
        t1 = Term(in, line);
        if( !t1 ) {
            ParseError(line, "Missing operand after operator");
            return false;
        }
        tok = Parser::GetNextToken(in, line);
        if(tok.GetToken() == ERR){
            ParseError(line, "Unrecognized Input Pattern");
            cout << "(" << tok.GetLexeme() << ")" << endl;
            return false;
        }
    }
    
    Parser::PushBackToken(tok); 
    return true;
}

bool Term(istream& in, int& line){
    bool t1 = SFactor(in, line);
    LexItem tok;
    if( !t1 ) {
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    
    if(tok.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        return false;
    }
    while ( tok == MULT|| tok == DIV ) {
        tok = Parser::GetNextToken(in,line);
        if (tok != PLUS && tok!= MINUS){
            Parser::PushBackToken(tok);
        }
        t1 = SFactor(in, line);
        if( !t1 ) {
            ParseError(line, "Missing operand");
            return false;
        }
        tok = Parser::GetNextToken(in, line);
        if(tok.GetToken() == ERR){
            ParseError(line, "Unrecognized Input Pattern");
            cout << "(" << tok.GetLexeme() << ")" << endl;
            return false;
        }
    }
    Parser::PushBackToken(tok); 
    return true;
}

bool SFactor(istream& in, int& line){
    LexItem t = Parser::GetNextToken(in,line);
    //cout<<t.GetLexeme()<<endl;
    bool status;
    if (t!=PLUS || t!=MINUS){
        
        string s =  t.GetLexeme();
        Parser::PushBackToken(t);
        status = Factor(in,line,1);
        
        
    }
    //stoi(t.GetLexeme())
    else{
        //string num = t.GetLexeme();
        t = Parser::GetNextToken(in,line);
        //num += t.GetLexeme();
        //cout<<num<<endl;
        status = Factor(in,line, 1);
    }
    if(!status){
		ParseError(line, "Missing Factor");
		return false;
	}
    return status;
}

bool LogicExpr(istream& in, int& line){
    bool xp = Expr(in,line);
    if (!xp){
        ParseError(line,"Missing Expression");
        return false;
    }
    
	LexItem t = Parser::GetNextToken(in,line);
    if (t != EQUAL && t!=LTHAN && t!=GTHAN){
        ParseError(line,"Missing EQUAL,LTHAN, or GTHAN");
        return false;
    }
	bool xp1 = Expr(in,line);
    if (!xp1){
        ParseError(line,"Missing Expression");
        return false;
    }
    return true;
    
}

bool Var(istream& in, int& line){
    LexItem t = Parser::GetNextToken(in,line);
    if ((defVar.find(t.GetLexeme())) == defVar.end()){
        //cout<<t.GetLexeme()<<endl;
        ParseError(line, "Unefined Variable");
        return false;
    }
    /*
    if (t != IDENT){
        ParseError(line,"Missing Identifier");
        return false;
    }*/
    else{
        //Parser::PushBackToken(t);
        return true;
    }
}

bool Factor(istream& in, int& line, int sign){
    LexItem t = Parser::GetNextToken(in,line);
    //Parser::PushBackToken(t);
    if (t == IDENT){
        if ((defVar.find(t.GetLexeme())) == defVar.end()){
            //cout<<t.GetLexeme()<<endl;
            ParseError(line, "Unefined Variable");
            return false;
        }
        return true;
    }
    else if (t == ICONST){
        return true;
    }
    else if (t == RCONST){
        return true;
    }
    else if (t == SCONST){
        return true;
    }
    
    else if (t == LPAREN){
        bool xp = Expr(in,line);
        if (!xp){
            ParseError(line,"Missing Expression");
            return false;
        }
        t = Parser::GetNextToken(in,line);
        if (t!=RPAREN){
            ParseError(line,"Missing Right Parenthesis");
            return false;
        }
        return true;
    }
    else{
        ParseError(line,"Missing IDENT, ICONST, RCONST, SCONST, or Parenthesis");
        //cout << t.GetLexeme()<<endl;
        return false;
    }
}
