//
// Created by PrinceXuan on 2017/5/25.
//

#ifndef TIGER_ERROR_H
#define TIGER_ERROR_H

#include <initializer_list>
#include <string>
#include "location.hh"

void error(std::initializer_list<std::string> err_msg_list);
void error(const location_type & loc, const std::string & msg);

class Error{
public:
    Error();
    virtual ~Error();

    virtual void print(std::initializer_list<std::string> err_msg_list);
};

class ParserError : public Error{
private:
    int tokenPos;
    int linePos;
    int inLinePos;
public:
    ParserError();
    void adjustTokenPos(int offset);
    void newLine();

    void print(std::initializer_list<std::string> err_msg_list) override;
};

#endif //TIGER_ERROR_H
