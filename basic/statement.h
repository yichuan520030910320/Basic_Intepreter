/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include "evalstate.h"
#include "exp.h"
#include "parser.h"

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */
class skipline{
public:
    int action;
    int linenum;
    //0 END,1 CHANGE ,3
    skipline(int a,int b ) {
        action=a,linenum=b;
    }
};

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

   Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

   virtual void execute(EvalState & state) = 0;

};

/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */
Statement *parsestatement(bool ifhaslinenum,string index);
class LET: public Statement{
private:Expression *exp;
public:LET(Expression* temp) {
exp=temp;
if (exp->getType()!=COMPOUND) {error("SYNTAX ERROR");}
if (((CompoundExp*)exp)->getOp()!="=")  {error("SYNTAX ERROR");}
}

    virtual ~LET(){
        delete exp;};
   void execute(EvalState & state) {
       exp->eval(state);}
};
class INPUT: public Statement{
private:
public:INPUT(Expression* temp) ;
//
    virtual ~INPUT();
    void execute(EvalState & state) ;
    Expression *ptr;
};

class IF: public Statement{
private:Expression *ptr1;
    Expression *ptr2;
    Expression *ptr3;
    Expression *ptr4;
    Expression *ptr5;
    string cmp__;
public:
    IF(Expression* temp_1,Expression* temp_2,Expression* temp_3,Expression* temp_4,string cmp_) {
        ptr1 =temp_1,ptr2=temp_2,ptr3=temp_3,ptr4=temp_4,cmp__=cmp_;
       //cout<<ptr1->toString()<<" "<<ptr2->toString()<<" "<<ptr3->toString()<<" "<<ptr4->toString()<<" "<<cmp__<<endl;
}
    virtual ~IF() {
        delete ptr5;delete ptr4;delete ptr3;delete ptr2;delete ptr1;
    }

    void execute(EvalState & state) {
//cout<<"(((((("<<endl;
if (cmp__=="="){
    //cout<<"(((((("<<endl;
    if (ptr1->eval(state)==ptr2->eval(state)) throw skipline(1,stringToInteger(ptr4->toString()));
} else if (cmp__=="<"){
    //cout<<"NNNNNNN"<<endl;
    if (ptr1->eval(state)<ptr2->eval(state)) throw skipline(1,stringToInteger(ptr4->toString()));
} else if (cmp__==">"){
    if (ptr1->eval(state)>ptr2->eval(state)) throw skipline(1,stringToInteger(ptr4->toString()));
}
    }
};
class GOTO: public Statement{
private: int linenum;Expression *Exp;
public:
    GOTO(Expression* temp) {
        Exp=temp;
        try {
            linenum=stringToInteger(Exp->toString());
        } catch (...) {
            error("SYNTAX ERROR");
        }
    }

    virtual ~GOTO() {
        delete Exp;
    }

    void execute(EvalState & state) {
        throw skipline(1,linenum);
    }
};
class END: public Statement{
private:
public:
    END() {}

    virtual ~END() {

    }

    void execute(EvalState & state) {
        throw skipline(0,0);
    }
};
class REM: public Statement{//finished
private:
public:
    REM(Expression* temp){} ;
    virtual ~REM(){};
    void execute(EvalState & state){

    };
};
class PRINT: public Statement{
private:Expression *content;
public:
    PRINT(Expression *x){
        content=x
;    }

    ~PRINT() {
        delete content;
    }
    void execute(EvalState & state) {
    cout<<content->eval(state)<<endl;
    }

};

#endif
