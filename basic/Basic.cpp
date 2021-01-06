/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */
#include <stdlib.h>
#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "statement.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include <sstream>
#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;
bool isNum(string str)//a function to check is num
{
    stringstream sin(str);
    double d;
    char c;
    if(!(sin >> d))
    {
        return false;
    }
    if (sin >> c)
    {
        return false;
    }
    return true;
}
/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

/* Main program */

int main() {
   EvalState state;
   Program program;
   //cout << "Stub implementation of BASIC" << endl;
   while (true) {
      try {
         processLine(getLine(), program, state);
      } catch (ErrorException & ex) {
         cout << ex.getMessage() << endl;
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program & program, EvalState & state) {
   // cout<<program.getFirstLineNumber()<<"(((((("<<endl;
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();//enter the pattern of being able to read num
   //cout<<scanner.scanNumbersFlag<<endl;
   scanner.setInput(line);

   if (line=="QUIT") exit(0);
   if (scanner.hasMoreTokens()){
       string token = scanner.nextToken();
       //cout<<token<<endl;
       //string token1 = scanner.nextToken();
       //cout<<token1<<endl;
      // cout<<scanner.nextToken()<<endl;
       if (isNum(token)){//with num
if (scanner.hasMoreTokens()) {//maybe need to transfer
//cout<<line<<"&&&&&"<<endl;
    const char *token_ = token.c_str();
    program.addSourceLine(atoi(token_), line);

} else{ const char *token_ = token.c_str();
    program.removeSourceLine(atoi(token_));
}
       } else if (scanner.hasMoreTokens()){//let print...
           //cout<<scanner.getStringValue()<<endl;

           if (token!="PRINT"&&token!="LET"&&token!="INPUT") error("SYNTAX ERROR");
           else{
               if (token=="PRINT"){
                   //
                   //cout<<scanner.nextToken()<<endl;
                   Expression *exp = parseExp(scanner);//cout<<"****"<<endl;
                   int value = exp->eval(state);
                   cout << value<< endl;
                   delete exp;
               }
               if (token=="LET"){

                 string temp1=scanner.nextToken();

              if (temp1=="LET"||temp1=="PRINT"||temp1=="INPUT") error("SYNTAX ERROR");
                   Statement *temp= nullptr;
                   temp=parsestatement(0,line);
//cout<<"******"<<endl;
                   temp->execute(state);
                   delete temp;





//                   string temp1=scanner.nextToken();
//
//                   if (temp1=="LET"||temp1=="PRINT"||temp1=="INPUT") error("SYNTAX ERROR");
//                   if (!scanner.hasMoreTokens()) error("SYNTAX ERROR");
//                   string sign=scanner.nextToken();
//
//                   if (!scanner.hasMoreTokens()) error("SYNTAX ERROR");
//                   string temp2=scanner.nextToken();
//                   if (sign!="="||!isNum(temp2)) error("SYNTAX ERROR");
//                   const char *num_ = temp2.c_str();
//                    state.setValue(temp1,atoi(num_));

               }
               if (token=="INPUT"){//the next lines may be cut
//                   string temp1=scanner.nextToken();
//                   cout<<endl;
//                   cout<<'?';
//                   string temp2=scanner.nextToken();
Statement *temp= nullptr;
temp=parsestatement(0,line);
//cout<<"******"<<endl;
//cout<<"*****"<<endl;
temp->execute(state);
                   delete temp;
               }
           }
       } else{//list quit...
if (token=="LIST") {
program.PRINT();
} else if (token=="HELP"){
//do nothing
cout<<"babalala"<<endl;
} else if (token=="CLEAR"){
    program.clear();
    state.clear();
} else if (token=="RUN"){
   // cout<<"888"<<endl;
    program.RUN( state);
} else{
    error("SYNTAX ERROR");
}
       }
   } else return;
}


