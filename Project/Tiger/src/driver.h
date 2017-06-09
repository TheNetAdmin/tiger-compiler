#ifndef __DRIVER_H__
#define __DRIVER_H__

#include <string>
#include "parser.h"
#include "location.hh"
#include "position.hh"
#include "absyntree.h"

#define YY_DECL \
    Tiger::Parser::symbol_type yylex(Tiger::Driver &driver)
YY_DECL;

namespace Tiger
{
class Driver
{
  public:
    bool syntaxError;
    bool trace_parsing;
    bool trace_scanning;
    std::string filename;
    shared_ptr<AST::Exp> result;
    Driver();
    virtual ~Driver();
    void scan_begin();
    void scan_end();
    int parse(const std::string &filename);
    void error(const Tiger::location &l, const std::string &m)
    {
        std::cerr << l << ": " << m << std::endl;
    }
};
}

#endif // ! __DRIVER_H__