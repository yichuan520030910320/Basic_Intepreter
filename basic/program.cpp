/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */
//#include "evalstate.h"
#include <string>
#include "program.h"
#include <map>
#include "statement.h"
using namespace std;

Program::Program() {
   // Replace this stub with your own code
}

Program::~Program() {

   // Replace this stub with your own code
}

void Program::clear() {
    if (!Lineset.empty()){
        map<int,Line>::iterator iter;
        iter = Lineset.begin();
        while(iter != Lineset.end()){
            delete iter->second.linemeanig;
            iter++;
        }
    }
    Lineset.clear();


   // Replace this stub with your own code
}

void Program::addSourceLine(int lineNumber, string line) {
    //cout<<lineNumber<<"********"<<endl;
    if (Lineset.count(lineNumber)==1){
    Lineset[lineNumber].lineptr=line;
    Lineset[lineNumber].linemeanig=parsestatement(1,line);
    }
    else{
        //cout<<lineNumber<<"^^^^^"<<endl;
        Line temp;
        temp.lineptr=line;

        temp.linemeanig=parsestatement(1,line);

        //cout<<lineNumber<<"&&&&&&"<<endl;
        Lineset.insert(make_pair(lineNumber, temp));
        //cout<<Lineset.count(lineNumber)<<" "<<lineNumber<<"**"<<endl;
    }

//    map<int,Line>::iterator iter;
//    iter = Lineset.begin();
//    while(iter != Lineset.end()){
//        cout <<  iter->second.lineptr << endl;
//        iter++;
//    }






























//
//    auto iter=Lineset.find(lineNumber);
//    if(iter == Lineset.end()) { Line temp;
//    temp.lineptr=line;
//    //cout<<line<<"*********"<<endl;
//    temp.linemeanig=parsestatement(1,line);
//        Lineset.insert(make_pair(lineNumber, temp));
//        auto iter1=Lineset.find(lineNumber);
//      //  cout<<iter1->first<<"))))))"<<endl;
//        //cout<<iter1->second.lineptr<<"))))))"<<endl;
//        //cout<<temp.lineptr<<"******8"<<endl;
//
//    }
//    else {
//        removeSourceLine(lineNumber);
//        addSourceLine(lineNumber,line);
//
//    }
   // Replace this stub with your own code
}

void Program::removeSourceLine(int lineNumber) {//check if the line exsist
    //cout<<lineNumber<<"&&&&"<<endl;
    auto iter=Lineset.find(lineNumber);
    if(iter == Lineset.end()) return;
    else { delete iter->second.linemeanig, Lineset.erase(iter); }
   // Replace this stub with your own code
}

string Program::getSourceLine(int lineNumber) {
    auto iter=Lineset.find(lineNumber);
    if(iter == Lineset.end()) return " ";
    else return iter->second.lineptr;// Replace this stub with your own code
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    Lineset[lineNumber].linemeanig=stmt;
   // Replace this stub with your own code
}

Statement *Program::getParsedStatement(int lineNumber) {
    auto iter=Lineset.find(lineNumber);
    if(iter == Lineset.end()) return NULL;
    else return iter->second.linemeanig;  // Replace this stub with your own code
}

int Program::getFirstLineNumber() {
    if (!Lineset.empty()) { return Lineset.begin()->first; }
    else return 0;
       // Replace this stub with your own code
}

int Program::getNextLineNumber(int lineNumber) {
    auto iter=Lineset.find(lineNumber);
    if(iter == Lineset.end()) return 0;
  iter++;
    return iter->first;// Replace this stub with your own code
}
void Program::PRINT(){
    if (!Lineset.empty()){

        map<int,Line>::iterator iter;
        iter = Lineset.begin();
        while(iter != Lineset.end()){
            cout <<  iter->second.lineptr << endl;
            iter++;
        }
       //cout<<iSize<<"(((((("<<endl;

    }
}
void Program::RUN(EvalState & state){
//    map<int,Line>::iterator iter;
//    iter = Lineset.begin();
//    while(iter != Lineset.end()){
//        cout <<  iter->second.lineptr << endl;
//        iter++;
//    }
    if (!Lineset.empty()){

        map<int,Line>::iterator iter;
        iter = Lineset.begin();
        while(iter != Lineset.end()){
            //cout<<iter->first<<endl;
            Statement *temp;
            temp=parsestatement(1,iter->second.lineptr);

            try {
              // cout<<iter->first<<endl;
                temp->execute(state);
             //cout<<iter->first<<99999999<<endl;
            } catch (skipline temp) {
                //cout<<temp.action<<"******"<<endl;
                if (temp.action==0) {break;}
                if (temp.action==1){
                    //cout<<"****"<<endl;
                    map<int,Line>::iterator tmpiter;
                    //cout<<temp.linenum<<"*****"<<endl;
                    //cout<<111111111111111<<endl;
                    tmpiter=Lineset.find(temp.linenum);
                   // cout<<Lineset.count(50)<<"@@@@@@@@@@@"<<endl;
                    //cout<<temp.linenum<<"&&&&&"<<endl;
//cout<<tmpiter->first<<"******"<<endl;
                   // cout<<temp.linenum<<"((("<<endl;
                    if(tmpiter == Lineset.end()) { cout << "LINE NUMBER ERROR" << endl; }
                    else {
                        iter = tmpiter;
                        continue;
                    }
                }
            }//cout<<iter->first<<"^^^"<<endl;

            iter++;

        }
    }
}