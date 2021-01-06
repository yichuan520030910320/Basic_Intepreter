/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}
 void parser_the_token(){

}

Statement *parsestatement(bool ifhaslinenum,string index){
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();//enter the pattern of being able to read num
    //cout<<scanner.scanNumbersFlag<<endl;
    scanner.setInput(index);
    string token;
    if (ifhaslinenum) {
         token = scanner.nextToken();
    }
    token = scanner.nextToken();
    //cout<<token<<"****"<<endl;
    if (token=="INPUT"){
        Expression *temp= nullptr;
        temp=parseExp(scanner);
        if (temp->getType()!=IDENTIFIER) {error("SYNTAX ERROR");}
        return new INPUT(temp);
//       if (!scanner.hasMoreTokens()){error("SYNTAX ERROR");}
//        token = scanner.nextToken();
//       if (scanner.getTokenType(token)!=WORD) {error("SYNTAX ERROR");}
//    if (scanner.hasMoreTokens()) {error("SYNTAX ERROR");}
//        return new INPUT(token);
    } else if (token=="PRINT"){ Expression *exp = parseExp(scanner);
        return new PRINT(exp);
        }
    else if (token=="LET"){
       // cout<<"fuuuuuuuuck"<<endl;
        Expression *exp = parseExp(scanner);
        return new LET(exp);
    }
    else if (token=="END"){
        return new END();}
    else if (token=="IF"){

//Expression*tmp=readE(scanner);
//cout<<tmp->toString()<<"&&&7"<<endl;

        if(index.find('=') == string::npos){
            Expression*temp1=readE(scanner);
            string cmp=scanner.nextToken();
     if (cmp!="="&&cmp!="<"&&cmp!=">") {error("SYNTAX ERROR");}
        Expression* temp2=readE(scanner);
            Expression* temp3=readT(scanner);

      if (temp3->toString()!="THEN") {error("SYNTAX ERROR");}

    Expression* temp4=parseExp(scanner);


      return new IF(temp1,temp2,temp3,temp4,cmp);

        }
        else{
            string temp;
            while (scanner.hasMoreTokens()){
                string temp1=scanner.nextToken();
                if (temp1=="=") break;
                temp+=(temp1+" ");
            }
            Expression* temp2=readE(scanner);
            Expression* temp3=readT(scanner);

            if (temp3->toString()!="THEN") {error("SYNTAX ERROR");}

            Expression* temp4=parseExp(scanner);
            scanner.setInput(temp);
            Expression*temp1=readE(scanner);

            return new IF(temp1,temp2,temp3,temp4,"=");

        }



























//        Expression*temp1=readT(scanner);
//
//        if (temp1->getType()!=IDENTIFIER) {error("SYNTAX ERROR");}
//
//        string cmp=scanner.nextToken();
//        if (cmp!="="&&cmp!="<"&&cmp!=">") {error("SYNTAX ERROR");}
//        Expression* temp2=readT(scanner);
//
//
//        Expression* temp3=readT(scanner);
//
//        if (temp3->toString()!="THEN") {error("SYNTAX ERROR");}
//
//        Expression* temp4=parseExp(scanner);
//
//
//        return new IF(temp1,temp2,temp3,temp4,cmp);
    }
    else if (token=="GOTO"){
        Expression *exp = parseExp(scanner);
        return new GOTO(exp);
    }
    else if (token=="REM"){//do nothing
        Expression *exp = parseExp(scanner);
        return new REM(exp);
       }
    else {error("SYNTAX ERROR");}
}
INPUT::INPUT(Expression *temp) {  ptr=temp;}
INPUT::~INPUT() noexcept {};
void INPUT:: execute(EvalState & state) {
    int value;

    while (1){
        try {string temp;
            //char *temp= nullptr;
            cout<<" ? ";
            //cout<<"((((("<<endl;
            TokenScanner scanner;
            TokenScanner scanner1;
            getline(cin,temp);
            //cout<<temp<<"(((((((("<<endl;
            scanner.ignoreWhitespace();
            scanner.scanNumbers();
            scanner.setInput(temp);
            scanner1.ignoreWhitespace();
            scanner1.scanNumbers();
            scanner1.setInput(temp);
          string token = scanner.nextToken();
          if (token=="-") {
              value=-stringToInteger( scanner.nextToken());
          } else{  Expression *exp =parseExp(scanner1);
              //cout<<exp->toString()<<"((("<<endl;

              if (exp->getType()!=CONSTANT) throw 1;

              value=stringToInteger(temp);}







        } catch (...) {
            cout<<"INVALID NUMBER"<<endl;
            continue;
        }
        break;
    }
    state.setValue(((IdentifierExp *) ptr)->getName(),value);
}

