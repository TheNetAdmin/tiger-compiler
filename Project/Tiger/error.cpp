//
// Created by PrinceXuan on 2017/5/25.
//

#include "error.h"
#include <iostream>
using namespace std;

void error(initializer_list<string> err_msg_list) {
    for (const auto &entry : err_msg_list){
        cerr << entry << " ";
    }
    cerr << endl;
}

Error::Error() {}

Error::~Error() {

}

void Error::print(std::initializer_list<std::string> err_msg_list) {
    for (const auto &entry : err_msg_list){
        cerr << entry << " ";
    }
    cerr << endl;
}

ParserError::ParserError() :
        tokenPos(1), linePos(1), inLinePos(1) {}

void ParserError::adjustTokenPos(int offset) {
    this->tokenPos += offset;
    this->inLinePos += offset;
    // throw out of range if less than zero
}

void ParserError::newLine() {
    this->linePos++;
    this->inLinePos = 1;
}

void ParserError::print(std::initializer_list<std::string> err_msg_list) {
    cerr << "Parser error at [" << linePos << ":" << inLinePos << "] :" << endl;
    cerr << "\t";
    Error::print(err_msg_list);
}
